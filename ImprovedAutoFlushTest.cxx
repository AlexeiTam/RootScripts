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

void ImprovedAutoFlushTest(Long64_t NewAutoF = -30000000) {
	//GOAL: create one normal tree, and one with a given AutoFlush setting, then compare TTree::Print() of both
	//GOAL2: scale down events, more dramatically change NewAutoF
	//create file and tree
	
	//creating canvas
std::cout << "creating canvases and histograms..." << std::endl;
	
	TCanvas *cnvs = new TCanvas("cnvs","Tree Scan", 10, 10, 1200, 800);
	cnvs->Divide(5,2);
	gStyle->SetOptStat(0);
	
	TCanvas *cnvs2 = new TCanvas("cnvs2","Tree Print", 10, 10, 1200, 800);
	gStyle->SetOptStat(0);
	
	//creating histograms
	
	const Int_t NBins = 2000;
	
	TH1D *h0 = new TH1D("h0","Branch0 Entries",NBins,-0.1,10.1);
	TH1D *h1 = new TH1D("h1","Branch1 Entries",NBins,-0.1,10.1);
	TH1D *h2 = new TH1D("h2","Branch2 Entries",NBins,-0.1,10.1);
	TH1D *h3 = new TH1D("h3","Branch3 Entries",NBins,-0.1,10.1);
	TH1D *h4 = new TH1D("h4","Branch4 Entries",NBins,-0.1,10.1);
	TH1D *h5 = new TH1D("h5","Branch5 Entries",NBins,-0.1,10.1);
	TH1D *h6 = new TH1D("h6","Branch6 Entries",NBins,-0.1,10.1);
	TH1D *h7 = new TH1D("h7","Branch7 Entries",NBins,-0.1,10.1);
	TH1D *h8 = new TH1D("h8","Branch8 Entries",NBins,-0.1,10.1);
	TH1D *h9 = new TH1D("h9","Branch9 Entries",NBins,-0.1,10.1);
	
	
std::cout << "writing file and tree..." << std::endl;
	
	std::unique_ptr<TFile> myFile = std::make_unique<TFile>("AutoFlushTestingFile.root", "RECREATE");
	TTree* tree1 = new TTree("NormalTree","NormalTree");
	TTree* tree2 = new TTree("AutoFlushedTree","AutoFlushed Tree");
	
	//normal: Long64_t autof = -30000000
	tree2->SetAutoFlush(NewAutoF);
	
	//initializing parameters, vectors, float variables
	
std::cout << "initializing vectors..." << std::endl;
	
	const Int_t NEvents = 10000;	//number of events: 10,000
	const Int_t N0 = 1;
	const Int_t N1 = 10;
	const Int_t N2 = 25;
	const Int_t N3 = 50;
	const Int_t N4 = 100;
	const Int_t N5 = 200;
	const Int_t N6 = 500;
	const Int_t N7 = 750;
	const Int_t N8 = 1000;
	const Int_t N9 = 2000;
	
	std::vector<float> v0, v1, v2, v3, v4, v5, v6, v7, v8, v9;
	
	float f0, f1, f2, f3, f4, f5, f6, f7, f8, f9;
	
	//initializing branches
	
std::cout << "initializing branches..." << std::endl;
	
	tree1->Branch("N5", &v0);
	tree1->Branch("N10", &v1);
	tree1->Branch("N20", &v2);
	tree1->Branch("N50", &v3);
	tree1->Branch("N100", &v4);
	tree1->Branch("N200", &v5);
	tree1->Branch("N500", &v6);
	tree1->Branch("N1000", &v7);
	tree1->Branch("N2000", &v8);
	tree1->Branch("N5000", &v9);
	
	
	tree2->Branch("A5", &v0);
	tree2->Branch("A10", &v1);
	tree2->Branch("A20", &v2);
	tree2->Branch("A50", &v3);
	tree2->Branch("A100", &v4);
	tree2->Branch("A200", &v5);
	tree2->Branch("A500", &v6);
	tree2->Branch("A1000", &v7);
	tree2->Branch("A2000", &v8);
	tree2->Branch("A5000", &v9);
	

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
		for(int j = 0; j < N0; j++) {
			
		f0 = (gRandom->Rndm())*10;
			
			h0->Fill(f0);
		
		v0.emplace_back(f0);
		}
		
		//branch1
		for(int j = 0; j < N1; j++) {
		
		f1 = gRandom->Poisson(1.1);
			if(f1 > 5) {
			f1 = 0;
			}
			if(f1 < -5) {
			f1 = 0;
			}
		h1->Fill(f1);
		v1.emplace_back(f1);
		}
		
		//branch2
		for(int j = 0; j < N2; j++) {
		
		f2 = gRandom->Rndm();
			if(f2 < 0) continue;
			if(f2 > 0) {
			f2 = 4;
			}
		h2->Fill(f2);
		v2.emplace_back(f2);
		}
		
		//branch3
		for(int j = 0; j < N3; j++) {
			
		f3 = gRandom->Rndm();
			if(f3 > 0.8) {
			f3 = 6;
			}
			if(f3 <= 0.8) {
			f3 = 2;
			}
		h3->Fill(f3);
		v3.emplace_back(f3);
		}
		
		//branch4
		for(int j = 0; j < N4; j++) {
		f4 = gRandom->Poisson(2.5);
			if(f4 > 10) {
			f4 = 0;
			}
		h4->Fill(f4);
		v4.emplace_back(f4);
		}
		
		//branch5
		for(int j = 0; j < N5; j++) {
		f5 = 10*(gRandom->Rndm());
		h5->Fill(f5);
		v5.emplace_back(f5);
		}
		
		//branch6
		for(int j = 0; j < N6; j++) {
		f6 = gRandom->Poisson(4.4);
			if(f6 > 10) {
			f6 = 0;
			}
		h6->Fill(f6);
		v6.emplace_back(f6);
		}
		
		//branch7
		for(int j = 0; j < N7; j++) { 
		f7 = gRandom->Rndm();
			if(f7 < 0.4) {
			f7 = 0;
			}
			if(f7 > 0.4 && f7 <= 0.7) {
			f7 = 5.5;
			}
			if(f7 > 0.7) {
			f7 = 7.5;
			}
		h7->Fill(f7);
		v7.emplace_back(f7);
		}
		
		//branch8
		for(int j = 0; j < N8; j++) {
			
		f8 = gRandom->Rndm();
			if(f8 <= 0.5) {
			f8 = 0;
			}
			else continue;
		h8->Fill(f8);
		v8.emplace_back(f8);
		}
		
		//branch9
		for(int j = 0; j < N9; j++) {
		
		f9 = gRandom->Poisson(7.7);
			if(f9 > 10) {
			f9 = 10;
			}
		h9->Fill(f9);
		v9.emplace_back(f9);
		}
		
		tree1->Fill();
		tree2->Fill();
		
	}

	//writing tree header and saving file
	tree1->Write();
	tree2->Write();
	
	std::cout <<"autof = " << NewAutoF << std::endl;
	std::cout <<"reminder: create histograms to show entries in each branch"<< std::endl;
	//std::cout << "Normal Tree Scan:" << std::endl;
	//tree1->Scan();
	//std::cout << "AutoFlushed Tree Scan:" << std::endl;
	//tree2->Scan();
	
	std::cout << "Print logs:" << std::endl;
	tree1->Print();
	tree2->Print();
	
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
	
	cnvs->cd(6);
	h5->Draw();
	
	cnvs->cd(7);
	h6->Draw();
	
	cnvs->cd(8);
	h7->Draw();
	
	cnvs->cd(9);
	h8->Draw();
	
	cnvs->cd(10);
	h9->Draw();


	myFile->Save();
	myFile->Close();
	
	cnvs->Update();
	cnvs->Draw();
	
	cnvs->Update();
	//? Is there a way to initialize this?
	//cnvs->SaveAs("FirstTreeCanvas.pdf");
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
  ImprovedAutoFlushTest();
  return 0; 
}

