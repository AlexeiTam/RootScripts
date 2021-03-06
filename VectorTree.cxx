#include <iostream>
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
  Int_t NEntriesF;
  Int_t NEntriesI;
  Int_t NEntriesD;
  Int_t NEntriesS;
  
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
  std::cout << "generating events..." << std::endl;
  
  for (int j = 0; j < NEvents; j++) {
    
    //randomizing number of entries
    int NEntriesF = (gRandom->Rndm())*15;
    int NEntriesI = (gRandom->Rndm())*15;
    int NEntriesD = (gRandom->Rndm())*15;
    int NEntriesS = (gRandom->Rndm())*15;
   
    //clearing events
    vf.clear();
    vi.clear();
    vd.clear();
    vs.clear();
          
        //generating vector elements, filling vectors
        
        //generating vf
        for(int m = 0; m < NEntriesF; m++) {
          f = gRandom->Rndm();
          vf.emplace_back(f);
        }
    
        //generating vi
        for(int n = 0; n < NEntriesI; n++) {
          i = 3*n + 4;
          vi.emplace_back(i);
        }
    
        //generating vd
        for(int b = 0; b < NEntriesD; b++) {
          d = b*b + 1;
          vd.emplace_back(d);
        }
    
        //generating vs
        for(int a = 0; a < NEntriesS; a++) {
          s = a;
          vs.emplace_back(s);
        }
    
        
    tree->Fill();
    
  }
  
  //saving tree and file
  tree->Write();
  
    //let's look in the tree:
    tree->Scan();
    tree->Print();
  
  myFile->Save();
  myFile->Close();
  
  


}
