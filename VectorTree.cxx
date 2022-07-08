#include <iostrem>
#include <ostream>
#include <memory>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"

void VectorTree() {
  
  std::cout << "Initializing..." << std::endl;
  
  //CREATING FILE AND TREE
  std::cout << "creating file and tree..." << std::endl;
  
  std::unique_ptr<TFile> myFile = std::make_unique<TFile>("VectorTreeFile.root", "RECREATE");
  TTree *tree = new TTree("myTree","myTree");
  
  if(!myFile) {
    std::cout << "Error: file creation failed" << std::endl;
  }
  
  //INITIALIZING VARIABLES
  std::cout << "initializing variables and vector" << std::endl;
  
  const Int_t NEvents = 1000000; // N = 1,000,000
  const Int_t NEntries = 15;
  
      //vectors
      std::vector<float> vf;
      std::vector<int> vi;
      std::vector<double> vd;
      std::vector<short> vs;
  
      //variables
      float f;
      int i;
      double d;
      short s;
  
  
  //INITIALIZING BRANCHES
  std::cout << "creating branches" << std::endl;
  
  tree->Branch("FloatBranch", &vf);
  tree->Branch("IntBranch", &vi);
  tree->Branch("DoubleBranch", &vd);
  tree->Branch("ShortBranch", &vs);
  
  //EVENTS LOOP
  
  for (int j = 0; j < NEvents; j++) {
   
    //clearing events
    vf.clear();
    vi.clear();
    vd.clear();
    vs.clear();
          
        //generating vector elements, filling vectors
        for(int m = 0; m < NEntries; m++) {
        
          f = gRandom->Rndm();
          i = 3*m + 4;
          d = m*m + 1;
          s = m;
          
          vf.emplace_back(f);
          vi.emplace_back(i);
          vd.emplace_back(d);
          vs.emplace_back(s);
          
        }
        
    tree->Fill();
    
  }
  
  //saving tree and file
  tree->Write();
  myFile->Save();
  myFile->Close();
  
  


}
