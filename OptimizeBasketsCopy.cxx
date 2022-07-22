void TTree::OptimizeBaskets(ULong64_t maxMemory, Float_t minComp, Option_t *option)
{
   //Flush existing baskets if the file is writable
   if (this->GetDirectory()->IsWritable()) this->FlushBasketsImpl();
 
   TString opt( option );
   opt.ToLower();
   Bool_t pDebug = opt.Contains("d"); //?? What's "d"?
   TObjArray *leaves = this->GetListOfLeaves();
   Int_t nleaves = leaves->GetEntries();
   Double_t treeSize = (Double_t)this->GetTotBytes();
 
   if (nleaves == 0 || treeSize == 0) {
      // We're being called too early, we really have nothing to do ...
      return;
   }
   Double_t aveSize = treeSize/nleaves;
   UInt_t bmin = 512;
   UInt_t bmax = 256000;
   Double_t memFactor = 1;
   Int_t i, oldMemsize,newMemsize,oldBaskets,newBaskets;
   i = oldMemsize = newMemsize = oldBaskets = newBaskets = 0;
 
   //we make two passes
   //one pass to compute the relative branch buffer sizes
   //a second pass to compute the absolute values
   for (Int_t pass =0;pass<2;pass++) {
      oldMemsize = 0;  //to count size of baskets in memory with old buffer size
      newMemsize = 0;  //to count size of baskets in memory with new buffer size
      oldBaskets = 0;  //to count number of baskets with old buffer size
      newBaskets = 0;  //to count number of baskets with new buffer size
      for (i=0;i<nleaves;i++) {	//!! Comments on this loop?
         TLeaf *leaf = (TLeaf*)leaves->At(i);
         TBranch *branch = leaf->GetBranch();
         Double_t totBytes = (Double_t)branch->GetTotBytes();
         Double_t idealFactor = totBytes/aveSize;
         UInt_t sizeOfOneEntry;
         if (branch->GetEntries() == 0) {
            // There is no data, so let's make a guess ...
            sizeOfOneEntry = aveSize;
         } else {
            sizeOfOneEntry = 1+(UInt_t)(totBytes / (Double_t)branch->GetEntries());	
         }
         Int_t oldBsize = branch->GetBasketSize();
         oldMemsize += oldBsize;
         oldBaskets += 1+Int_t(totBytes/oldBsize);	//!! NTS: oldBaskets = # of Baskets, totBytes = branch->GetTotBytes(), oldBsize = branch->GetBasketSize(),
         Int_t nb = branch->GetListOfBranches()->GetEntries();
         if (nb > 0) {
            newBaskets += 1+Int_t(totBytes/oldBsize);
            continue;
         }
	//!! Buffer size rescaling comments?
         Double_t bsize = oldBsize*idealFactor*memFactor; //bsize can be very large !	//?? HOW LARGE??
         if (bsize < 0) bsize = bmax;
         if (bsize > bmax) bsize = bmax;	//NTS: STRANGE TO CALCULATE bsize WITH ALL THESE FACTORS, ONLY TO DEFINE IT ARBITRARILY...
         UInt_t newBsize = UInt_t(bsize);
         if (pass) { // only on the second pass so that it doesn't interfere with scaling
            // If there is an entry offset, it will be stored in the same buffer as the object data; hence,
            // we must bump up the size of the branch to account for this extra footprint.
            // If fAutoFlush is not set yet, let's assume that it is 'in the process of being set' to
            // the value of GetEntries().
            Long64_t clusterSize = (fAutoFlush > 0) ? fAutoFlush : branch->GetEntries();
            if (branch->GetEntryOffsetLen()) {
               newBsize = newBsize + (clusterSize * sizeof(Int_t) * 2);
            }
            // We used ATLAS fully-split xAOD for testing, which is a rather unbalanced TTree, 10K branches,
            // with 8K having baskets smaller than 512 bytes. To achieve good I/O performance ATLAS uses auto-flush 100,
            // resulting in the smallest baskets being ~300-400 bytes, so this change increases their memory by about 8k*150B =~ 1MB,
            // at the same time it significantly reduces the number of total baskets because it ensures that all 100 entries can be
            // stored in a single basket (the old optimization tended to make baskets too small). In a toy example with fixed sized
            // structures we found a factor of 2 fewer baskets needed in the new scheme.
            // rounds up, increases basket size to ensure all entries fit into single basket as intended
            newBsize = newBsize - newBsize%512 + 512;
         }
         if (newBsize < sizeOfOneEntry) newBsize = sizeOfOneEntry;
         if (newBsize < bmin) newBsize = bmin;
         if (newBsize > 10000000) newBsize = bmax;
         if (pass) {
            if (pDebug) Info("OptimizeBaskets", "Changing buffer size from %6d to %6d bytes for %s\n",oldBsize,newBsize,branch->GetName());
            branch->SetBasketSize(newBsize);
         }
         newMemsize += newBsize;
         // For this number to be somewhat accurate when newBsize is 'low'
         // we do not include any space for meta data in the requested size (newBsize) even-though SetBasketSize will
         // not let it be lower than 100+TBranch::fEntryOffsetLen.
         newBaskets += 1+Int_t(totBytes/newBsize);
         if (pass == 0) continue;
         //Reset the compression level in case the compression factor is small
         Double_t comp = 1;
         if (branch->GetZipBytes() > 0) comp = totBytes/Double_t(branch->GetZipBytes());	//?? IS THIS HOW CX IS CALCULATED? 
         if (comp > 1 && comp < minComp) {
            if (pDebug) Info("OptimizeBaskets", "Disabling compression for branch : %s\n",branch->GetName());
            branch->SetCompressionSettings(ROOT::RCompressionSetting::EAlgorithm::kUseGlobal);
         }
      }
      // coverity[divide_by_zero] newMemsize can not be zero as there is at least one leaf
      memFactor = Double_t(maxMemory)/Double_t(newMemsize);
      if (memFactor > 100) memFactor = 100;
      Double_t bmin_new = bmin*memFactor;
      Double_t bmax_new = bmax*memFactor;
      static const UInt_t hardmax = 1*1024*1024*1024; // Really, really never give more than 1Gb to a single buffer.
 
      // Really, really never go lower than 8 bytes (we use this number
      // so that the calculation of the number of basket is consistent
      // but in fact SetBasketSize will not let the size go below
      // TBranch::fEntryOffsetLen + (100 + strlen(branch->GetName())
      // (The 2nd part being a slight over estimate of the key length.
      static const UInt_t hardmin = 8;
      bmin = (bmin_new > hardmax) ? hardmax : ( bmin_new < hardmin ? hardmin : (UInt_t)bmin_new );
      bmax = (bmax_new > hardmax) ? bmin : (UInt_t)bmax_new;
   }
   if (pDebug) {
      Info("OptimizeBaskets", "oldMemsize = %d,  newMemsize = %d\n",oldMemsize, newMemsize);
      Info("OptimizeBaskets", "oldBaskets = %d,  newBaskets = %d\n",oldBaskets, newBaskets);
   }
}
 
