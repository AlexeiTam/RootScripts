#include <iostream>
#include <memory>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom.h"

void create()
{
//Create file and tree    
  std::unique_ptr<TFile> myFile=std::make_unique<TFile>("MyTreeFile.root", "RECREATE"); 
  //auto tree=std::make_unique<TTree>("tree","MyTree");  
  TTree *tree = new TTree("MyTree","MyTree");
  
//declare float, TBranch  
  float var;
  tree->Branch("BranchZero", &var);
  
//filling tree with random numbers  
  for(int i=0;i<100;i++) {
    var = gRandom->Rndm();
    tree->Fill();
  }

//giving tree a header, saving and closing file  
  tree->Write();
  
  myFile->Save();
  myFile->Close();
  
  cout<<"create() is clear"<<endl;
}

void read() 
{
//Create canvas, histogram to visualize results later
TCanvas *cnvs = new TCanvas("cnvs","Tree Display",10,10,800,500);
  
TH1F *h1 = new TH1F("h1","Tree Entries",100,-2,2);  
  
//opening file  
  std::unique_ptr<TFile> myFile=std::make_unique<TFile>("MyTreeFile.root", "READ");
  if(!myFile) {
    std::cout << "Cannot open the file!" << std::endl;
    return;
  }
  
  std::cout<<"File Opening is good"<<std::endl;

//giving pointers to float entries, TBranch in TTree  
  float var;
  TBranch *bvar=0;
  //std::unique_ptr<TTree> tree(myFile->Get<TTree>("MyTree"));
  //above version of below line is fine
  TTree* tree = (TTree*) myFile->Get("MyTree");
  if(!myFile) {
    std::cout << "Cannot open get the tree!" << std::endl;
    return;
  }
  
  std::cout<<"Pointer creation is good"<<std::endl;
  
  tree->SetBranchAddress("BranchZero",&var,&bvar);
  
  std::cout<<"Before for-loop is good"<<std::endl;
  std::cout<<"Total number of entries in the tree "<<tree->GetEntries()<<std::endl;

//telling tree to get entries from memories, 
//then fill histogram and print  
  for(int i=0;i<tree->GetEntries();i++) {
    tree->LoadTree(i);
    bvar->GetEntry(i);
    h1->Fill(var);
    std::cout<<var<<std::endl;
  }
  
  std::cout<<"read() is good"<<std::endl;

  //draw histogram
  cnvs->Update();
  h1->Draw();
 
}

void MakeTree()
{
  std::cout << "Starting..." << std::endl;
  create();
  read();
}
