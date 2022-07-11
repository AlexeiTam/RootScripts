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

void ExpandTree() {

  //Goal: create vectors of diff. variables, then fill Branches with them
  //Goal 2: create even more branches, rename (FloatBranch1->F1)

  std::cout << "Initializing..." << std::endl;
  
  //CREATING FILE AND TREE
  std::cout << "creating file and tree..." << std::endl;
  
  std::unique_ptr<TFile> myFile = std::make_unique<TFile>("ExpandTreeFile.root", "RECREATE");
  TTree *tree = new TTree("myTree","myTree");
  
  if(!myFile) {
    std::cout << "Error: file creation failed" << std::endl;
  }
  
  //INITIALIZING VARIABLES
  std::cout << "initializing variables and vectors..." << std::endl;
  
  const Int_t NEvents = 1000000; // N = 1,000,000
  Int_t NEntriesF;
  Int_t NEntriesI;
  Int_t NEntriesD;
  Int_t NEntriesS;
  
      //vectors
  //floats
      std::vector<float> vf0;
      std::vector<float> vf1;
      std::vector<float> vf2;
      std::vector<float> vf3;
  
  //ints
      std::vector<int> vi0;
      std::vector<int> vi1;
      std::vector<int> vi2;
      std::vector<int> vi3;
  
  //doubles
      std::vector<double> vd0;
      std::vector<double> vd1;
      std::vector<double> vd2;
      std::vector<double> vd3;
  
  //shorts
      std::vector<short> vs0;
      std::vector<short> vs1;
      std::vector<short> vs2;
      std::vector<short> vs3;
  
      //variables
      float f0,f1,f2,f3;
      int i0,i1,i2,i3;
      double d0,d1,d2,d3;
      short s0,s1,s2,s3;
  
  
  //INITIALIZING BRANCHES
  std::cout << "creating branches..." << std::endl;
  
    //floats
    tree->Branch("F0", &vf0);
    tree->Branch("F1", &vf1);
    tree->Branch("F2", &vf2);
    tree->Branch("F3", &vf3);
    
  
    //ints
    tree->Branch("I0", &vi0);
    tree->Branch("I1", &vi1);
    tree->Branch("I2", &vi2);
    tree->Branch("I3", &vi3);
    
    //doubles
    tree->Branch("D0", &vd0);
    tree->Branch("D1", &vd1);
    tree->Branch("D2", &vd2);
    tree->Branch("D3", &vd3);
    
    //shorts
    tree->Branch("S0", &vs0);
    tree->Branch("S1", &vs1);
    tree->Branch("S2", &vs2);
    tree->Branch("S3", &vs3);
  
  //EVENTS LOOP
  std::cout << "generating events..." << std::endl;
  
  for (int j = 0; j < NEvents; j++) {
    
    //randomizing number of entries
    int NEntriesF = (gRandom->Rndm())*15;
    int NEntriesI = (gRandom->Rndm())*15;
    int NEntriesD = (gRandom->Rndm())*15;
    int NEntriesS = (gRandom->Rndm())*15;
   
    //clearing events
    vf0.clear();
    vf1.clear();
    vf2.clear();
    vf3.clear();
    
    vi0.clear();
    vi1.clear();
    vi2.clear();
    vi3.clear();
    
    vd0.clear();
    vd1.clear();
    vd2.clear();
    vd3.clear();
    
    vs0.clear();
    vs1.clear();
    vs2.clear();
    vs3.clear();
          
        //generating vector elements, filling vectors
        
        //generating vf's
        for(int m = 0; m < NEntriesF; m++) {
          f0 = gRandom->Rndm();
          f1 = 100*(gRandom->Rndm());
          f2 = 1500*(gRandom->Rndm());
          f3 = (gRandom->Rndm())*(gRandom->Rndm());
          
          vf0.emplace_back(f0);
          vf1.emplace_back(f1);
          vf2.emplace_back(f2);
          vf3.emplace_back(f3);
        }
    
        //generating vi's
        for(int n = 0; n < NEntriesI; n++) {
          i0 = n*n*j*j + j*(gRandom->Rndm());
          i1 = (j + n)*(j - n) + j*j*j*(gRandom->Gaus(n,j));
          i2 = (j - n*(gRandom->Exp(-0.6)))*(j*(gRandom->Landau(0.25,1.1)) + n);
          i3 = (n + i2)*(sqrt((j*j*j)));
          
          vi0.emplace_back(i0);
          vi1.emplace_back(i1);
          vi2.emplace_back(i2);
          vi3.emplace_back(i3);
        }
    
        //generating vd's
        for(int b = 0; b < NEntriesD; b++) {
          d0 = j*j + b*(gRandom->Rndm()) + 5*b*j;
          d1 = (gRandom->Rndm())*(gRandom->Landau(2.22,5.9));
          d2 = b*b*(gRandom->Landau((j*j*b*0.0000001),5.5)) + (sqrt(15*(gRandom->Gaus(j,33))));
          d3 = 17000*(gRandom->Rndm());
          
          vd0.emplace_back(d0);
          vd1.emplace_back(d1);
          vd2.emplace_back(d2);
          vd3.emplace_back(d3);
        }
    
        //generating vs's
        for(int a = 0; a < NEntriesS; a++) {
          s0 = a*j + 1500*(gRandom->Rndm());
          s1 = j*j*(gRandom->Gaus(23,j));
          s2 = j*(gRandom->Landau(0.1111,7.7));
          s3 = 145000*(gRandom->Landau(s0,s1));
          
          vs0.emplace_back(s0);
          vs1.emplace_back(s1);
          vs2.emplace_back(s2);
          vs3.emplace_back(s3);
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
