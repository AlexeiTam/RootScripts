#include <iostream>
#include <ostream>
#include <memory>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom.h"
#include "TH1.h"
#include "TStyle.h"
#include "TCanvas.h"

//void create() {

void AutoFlushTest(Long64_t NewAutoF = -30000000) {
	//GOAL: create one normal tree, and one with a given AutoFlush setting, then compare TTree::Print() of both

	//create file and tree
	
std::cout << "writing file and tree..." << std::endl;
	
	std::unique_ptr<TFile> myFile = std::make_unique<TFile>("AutoFlushTestingFile.root", "RECREATE");
	TTree* tree1 = new TTree("NormalTree","NormalTree");
	TTree* tree2 = new TTree("AutoFlushedTree","AutoFlushed Tree");
	
	//normal: Long64_t autof = -30000000
	tree2->SetAutoFlush(NewAutoF);
	
	//initializing tree branches, and float arrays to hold leaves
	
std::cout << "initializing vectors..." << std::endl;
	
	const Int_t N = 1500000;	//number of events: 1,500,000
	const Int_t NEntries = 20;
	
	std::vector<float> v0;
	std::vector<float> v1;
	std::vector<float> v2;
	std::vector<float> v3;
	std::vector<float> v4;
	
	float f0;
	float f1;
	float f2;
	float f3;
	float f4;
	
std::cout << "initializing branches..." << std::endl;
	
	tree1->Branch("branch0", &v0);
	tree1->Branch("branch1", &v1);
	tree1->Branch("branch2", &v2);
	tree1->Branch("branch3", &v3);
	tree1->Branch("branch4", &v3);
	
	tree2->Branch("branch0", &v0);
	tree2->Branch("branch1", &v1);
	tree2->Branch("branch2", &v2);
	tree2->Branch("branch3", &v3);
	tree2->Branch("branch4", &v4);

	//generating random numbers and filling trees
	for(int i = 0; i < N ; i++) {
		
if(i == 0) {
std::cout << "Generating Events 0 to 300,000..." << std::endl;
}
if(i == 300001) {
std::cout << "Generating Events 300,000 to 600,000..." << std::endl;
}
if(i == 600001) {
std::cout << "Generating Events 600,000 to 900,000..." << std::endl;
}
if(i == 900001) {
std::cout << "Generating Events 900,000 to 1,200,000..." << std::endl;
}
if(i == 120001) {
std::cout << "Generating Events 1,200,000 to 1,500,000..." << std::endl;
}
		
		v0.clear();
		v1.clear();
		v2.clear();
		v3.clear();
		v4.clear();

	
		for(int j = 0; j < NEntries; j++) {
			
		f0 = gRandom->Rndm();
		f1 = gRandom->Rndm();
		f2 = gRandom->Rndm();
		f3 = gRandom->Rndm();
		f4 = gRandom->Rndm();
			
		v0.emplace_back(f0);
		v1.emplace_back(f1);
		v2.emplace_back(f2);
		v3.emplace_back(f3);
		v4.emplace_back(f4);
			
		}
		
		tree1->Fill();
		tree2->Fill();
	}

	//writing tree header and saving file
	tree1->Write();
	tree2->Write();
	
	tree1->Print();
	tree2->Print();
	
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


	myFile->Save();
	myFile->Close();

	cnvs->Update();
	cnvs->SaveAs("FirstTreeCanvas.pdf");

}

//void AutoFlushTest() {
	//creates two trees with five branches, fills each with 1000 random numbers of different distributions
	//create();
	//read();
//}


int main() {
  AutoFlushTest();
  return 0; 
}

