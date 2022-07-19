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

void AutoFlushTestSmall(Long64_t NewAutoF = -30000000) {
	//GOAL: create one normal tree, and one with a given AutoFlush setting, then compare TTree::Print() of both
	//GOAL2: scale down events, more dramatically change NewAutoF
	//create file and tree
	
std::cout << "writing file and tree..." << std::endl;
	
	std::unique_ptr<TFile> myFile = std::make_unique<TFile>("AutoFlushTestingFile.root", "RECREATE");
	TTree* tree1 = new TTree("NormalTree","NormalTree");
	TTree* tree2 = new TTree("AutoFlushedTree","AutoFlushed Tree");
	
	//normal: Long64_t autof = -30000000
	tree2->SetAutoFlush(NewAutoF);
	
	//initializing parameters, vectors, float variables
	
std::cout << "initializing vectors..." << std::endl;
	
	const Int_t NEvents = 10000;	//number of events: 10,000
	const Int_t N0 = 5;
	const Int_t N1 = 10;
	const Int_t N2 = 20;
	const Int_t N3 = 50;
	const Int_t N4 = 100;
	const Int_t N5 = 200;
	const Int_t N6 = 500;
	const Int_t N7 = 1000;
	const Int_t N8 = 2000;
	const Int_t N9 = 5000;
	
	std::vector<float> v0;
	std::vector<float> v1;
	std::vector<float> v2;
	std::vector<float> v3;
	std::vector<float> v4;
	std::vector<float> v5;
	std::vector<float> v6;
	std::vector<float> v7;
	std::vector<float> v8;
	std::vector<float> v9;
	
	float f0;
	float f1;
	float f2;
	float f3;
	float f4;
	float f5;
	float f6;
	float f7;
	float f8;
	float f9;
	
	//initializing branches
	
std::cout << "initializing branches..." << std::endl;
	
	tree1->Branch("N0", &v0);
	tree1->Branch("N1", &v1);
	tree1->Branch("N2", &v2);
	tree1->Branch("N3", &v3);
	tree1->Branch("N4", &v4);
	tree1->Branch("N5", &v5);
	tree1->Branch("N6", &v6);
	tree1->Branch("N7", &v7);
	tree1->Branch("N8", &v8);
	tree1->Branch("N9", &v9);
	
	
	tree2->Branch("A0", &v0);
	tree2->Branch("A1", &v1);
	tree2->Branch("A2", &v2);
	tree2->Branch("A3", &v3);
	tree2->Branch("A4", &v4);
	tree2->Branch("A5", &v5);
	tree2->Branch("A6", &v6);
	tree2->Branch("A7", &v7);
	tree2->Branch("A8", &v8);
	tree2->Branch("A9", &v9);
	

	//generating random numbers and filling trees
	for(int i = 0; i < NEvents ; i++) {
		
		//clearing vectors for new event
		v0.clear();
		v1.clear();
		v2.clear();
		v3.clear();
		v4.clear();
		v5.clear();
		v6.clear();
		v7.clear();
		v8.clear();
		v9.clear();

	
		//branch0
		//BOOKMARK!!!
		for(int j = 0; j < NS; j++) {
			
		fs0 = gRandom->Rndm();
		fs1 = gRandom->Gaus(2,1);
		fs2 = gRandom->Gaus(2,3);
		fs3 = gRandom->Landau(0,1);
		fs4 = gRandom->Landau(0,3);
		fs5 = gRandom->Poisson(23.12);
		
		vs0.emplace_back(fs0);
		vs1.emplace_back(fs1);
		vs2.emplace_back(fs2);
		vs3.emplace_back(fs3);
		vs4.emplace_back(fs4);
		vs5.emplace_back(fs5);
			
		}
		
		for(int m = 0; m < NB; m++) {
		
		fb0 = gRandom->Rndm();
		fb1 = gRandom->Poisson(23.12);
			
		vb0.emplace_back(fb0);
		vb1.emplace_back(fb1);
		
		}
		
		tree1->Fill();
		tree2->Fill();
	}

	//writing tree header and saving file
	tree1->Write();
	tree2->Write();
	
	std::cout <<"autof = " << NewAutoF << std::endl;
	std::cout << "Normal Tree Scan:" << std::endl;
	tree1->Scan();
	std::cout << "AutoFlushed Tree Scan:" << std::endl;
	tree2->Scan();
	
	std::cout << "Print logs:" << std::endl;
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
  AutoFlushTestSmall();
  return 0; 
}

