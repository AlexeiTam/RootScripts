#include <iostream>
#include <ostream>
#include <memory>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom.h"

void create() {

	//create file and tree
	
	std::unique_ptr<TFile> myFile = std::make_unique<TFile>("BigTreeFile.root", "RECREATE");
	TTree* tree = new TTree("myTree","myTree");
	
	//initializing tree branches, and float arrays to hold leaves
	const Int_t N = 1000;
	float var[5];
	tree->Branch("branch0", &var[0]);
	tree->Branch("branch1", &var[1]);
	tree->Branch("branch2", &var[2]);
	tree->Branch("branch3", &var[3]);
	tree->Branch("branch4", &var[4]);

	//generating random numbers and filling trees
	for(int i = 0; i < N ; i++) {
	
		var[0] = i;
		var[1] = gRandom->Rndm();
		var[2] = gRandom->Gaus(0,1);
		var[3] = gRandom->Exp(-0.6);
		var[4] = gRandom->Landau(0.25,1.1);
		
		tree->Fill();
	}

	//writing tree header and saving file
	tree->Write();
	myFile->Save();
	myFile->Close();
	
	
	
}

void read() {
	
	//Create canvas, histograms to visualize results later
	TCanvas *cnvs = new TCanvas("cnvs","Tree Display", 10, 10, 800, 500);
	cnvs->Divide(3,2);
	gStyle->SetOptStat(0);
	
	TH1F *h0 = new TH1F("h0","Branch 0 Distributions",100,-1.1,1.1);
	TH1F *h1 = new TH1F("h1","Branch 1 Distributions",100,-1.1,1.1);
	TH1F *h2 = new TH1F("h2","Branch 2 Distributions",100,-1.1,1.1);
	TH1F *h3 = new TH1F("h3","Branch 3 Distributions",100,-1.1,1.1);
	TH1F *h4 = new TH1F("h4","Branch 4 Distributions",100,-1.1,1.1);
	
	
	//opening file and giving it pointer "myFile"
	
	std::unique_ptr<TFile> myFile = std::make_unique<TFile>("BigTreeFile.root", "READ");
			if(!myFile) { 
			std::cout << "File Open Failed!" << std::endl;
			return;
			}
	
	//giving variables, branches a ptr
	float var[5];
	
	TBranch *b0 = 0;
	TBranch *b1 = 0;
	TBranch *b2 = 0;
	TBranch *b3 = 0;
	TBranch *b4 = 0;
	
	//getting tree from file, giving it a ptr
	
	TTree *tree = (TTree*) myFile->Get("myTree");
				if(!myFile) {
				std::cout << "Can't open file to get tree!" << std::endl;
				return;
				}
	
	//Assigning branches
	
	tree->SetBranchAddress("branch0", &var[0], &b0);
	tree->SetBranchAddress("branch1", &var[1], &b1);
	tree->SetBranchAddress("branch2", &var[2], &b2);
	tree->SetBranchAddress("branch3", &var[3], &b3);
	tree->SetBranchAddress("branch4", &var[4], &b4);
	
	//getting tree entries, filling histograms
	for(int i=0;i<tree->GetEntries();i++) {
	tree->LoadTree(i);
			
			b0->GetEntry(i);
			b1->GetEntry(i);
			b2->GetEntry(i);
			b3->GetEntry(i);
			b4->GetEntry(i);
		
			h0->Fill(var[0]);
			h1->Fill(var[1]);
			h2->Fill(var[2]);
			h3->Fill(var[3]);
			h4->Fill(var[4]);
	}
	
	//draw histograms
	cnvs->Update();
	
	cnvs->cd(1);
	h0->Draw();
	
	cnvs->cd(2);
	h1->Draw();
	
	cnvs->cd(3);
	h2->Draw();
	
	cnvs->cd(4);
	h3->Draw();
	
	cnvs->cd(5);
	h4->Draw();
}

void CreateTree() {
	//creates a tree with five branches, fills each with 1000 random numbers of different distributions
	create();
	read();
}
