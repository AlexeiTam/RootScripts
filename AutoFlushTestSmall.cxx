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
	
	const Int_t N = 1000;	//number of events: 1,500,000-->1000
	const Int_t NS = 5;
	const Int_t NB = 20;
	
	std::vector<float> vs0;
	std::vector<float> vs1;
	std::vector<float> vs2;
	std::vector<float> vs3;
	std::vector<float> vs4;
	std::vector<float> vs5;
	std::vector<float> vs6;
	std::vector<float> vs7;
	
	std::vector<float> vb0;
	std::vector<float> vb1;
	
	float fs0;
	float fs1;
	float fs2;
	float fs3;
	float fs4;
	float fs5;
	float fs6;
	float fs7;
	float fb0;
	float fb1;
	
	//initializing branches
	
std::cout << "initializing branches..." << std::endl;
	
	tree1->Branch("NS0", &vs0);
	tree1->Branch("NS1", &vs1);
	tree1->Branch("NS2", &vs2);
	tree1->Branch("NS3", &vs3);
	tree1->Branch("NS4", &vs4);
	tree1->Branch("NS5", &vs5);
	tree1->Branch("NS6", &vs6);
	tree1->Branch("NS7", &vs7);
	
	tree1->Branch("NB0", &vb0);
	tree1->Branch("NB1", &vb1);
	
	tree2->Branch("AS0", &vs0);
	tree2->Branch("AS1", &vs1);
	tree2->Branch("AS2", &vs2);
	tree2->Branch("AS3", &vs3);
	tree2->Branch("AS4", &vs4);
	tree2->Branch("AS5", &vs5);
	tree2->Branch("AS6", &vs6);
	tree2->Branch("AS7", &vs7);
	
	tree2->Branch("AB0", &vb0);
	tree2->Branch("AB1", &vb1);

	//generating random numbers and filling trees
	for(int i = 0; i < N ; i++) {
		
		vs0.clear();
		vs1.clear();
		vs2.clear();
		vs3.clear();
		vs4.clear();
		vs5.clear();
		vs6.clear();
		vs7.clear();
		
		vs0.clear();
		vb1.clear();

	
		for(int j = 0; j < NS; j++) {
			
		fs0 = gRandom->Rndm();
		fs1 = gRandom->Rndm();
		fs2 = gRandom->Rndm();
		fs3 = gRandom->Rndm();
		fs4 = gRandom->Rndm();
		fs5 = gRandom->Rndm();
		fs6 = gRandom->Rndm();
		fs7 = gRandom->Rndm();
			
		vs0.emplace_back(fs0);
		vs1.emplace_back(fs1);
		vs2.emplace_back(fs2);
		vs3.emplace_back(fs3);
		vs4.emplace_back(fs4);
		vs5.emplace_back(fs5);
		vs6.emplace_back(fs6);
		vs7.emplace_back(fs7);
			
		}
		
		for(int m = 0; m < NB; m++) {
		
		fb0 = gRandom->Rndm();
		fb1 = gRandom->Rndm();
			
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

