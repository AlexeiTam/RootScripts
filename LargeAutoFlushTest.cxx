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

void LargeAutoFlushTest(Long64_t NewAutoF = -30000000) {
	//GOAL: create one normal tree, and one with a given AutoFlush setting, then compare TTree::Print() of both
	//GOAL2: scale down events, more dramatically change NewAutoF
	
			//ISSUE1:  need TLegend to state X axis and Y axis
			//ISSUE2:  need to fix bin Edges and bin numbers, b/c fill color not very visible
	
	//create file and tree
	
	//creating canvas
	TCanvas *cnvs = new TCanvas("cnvs","Tree Display", 10, 10, 2400, 2000);
	cnvs->Divide(5,2);
	gStyle->SetOptStat(0);
	
	//creating histograms
	TH1D *h0 = new TH1D("h0","N1,A1 Entries",100,-0.1,10.1);	//all histograms originally had same binCount,binEdges as h0
	TH1D *h1 = new TH1D("h1","N10,A10 Entries",100,-0.1,5.1);
	TH1D *h2 = new TH1D("h2","N25,A25 Entries",50,0,2.1);
	TH1D *h3 = new TH1D("h3","N50,A50 Entries",50,1.9,3.1);
	TH1D *h4 = new TH1D("h4","N100,A100 Entries",50,-0.1,10.1);
	TH1D *h5 = new TH1D("h5","N200,A200 Entries",100,-0.1,10.1);
	TH1D *h6 = new TH1D("h6","N500,A500 Entries",50,-0.1,10.1);
	TH1D *h7 = new TH1D("h7","N750,A750 Entries",50,-0.1,3);
	TH1D *h8 = new TH1D("h8","N1000,A1000 Entries",50,-1.1,1.1);
	TH1D *h9 = new TH1D("h9","N2000,A2000 Entries",50,-0.1,10.1);
	
	//add TLegend later: X axis = Entry Value, Y axis = Events
	//add fill colors
	h0->GetXaxis()->SetTitle("Entry Value");
	h0->GetYaxis()->SetTitle("Number of Entries");
	
	h1->GetXaxis()->SetTitle("Entry Value");
	h1->GetYaxis()->SetTitle("Number of Entries");
	
	h2->GetXaxis()->SetTitle("Entry Value");
	h2->GetYaxis()->SetTitle("Number of Entries");
	
	h3->GetXaxis()->SetTitle("Entry Value");
	h3->GetYaxis()->SetTitle("Number of Entries");
	
	h4->GetXaxis()->SetTitle("Entry Value");
	h4->GetYaxis()->SetTitle("Number of Entries");
	
	h5->GetXaxis()->SetTitle("Entry Value");
	h5->GetYaxis()->SetTitle("Number of Entries");
	
	h6->GetXaxis()->SetTitle("Entry Value");
	h6->GetYaxis()->SetTitle("Number of Entries");
	
	h7->GetXaxis()->SetTitle("Entry Value");
	h7->GetYaxis()->SetTitle("Number of Entries");
	
	h8->GetXaxis()->SetTitle("Entry Value");
	h8->GetYaxis()->SetTitle("Number of Entries");
	
	h9->GetXaxis()->SetTitle("Entry Value");
	h9->GetYaxis()->SetTitle("Number of Entries");
	
	
	h0->SetFillColor(0);
	h1->SetFillColor(1);
	h2->SetFillColor(2);
	h3->SetFillColor(3);
	h4->SetFillColor(4);
	h5->SetFillColor(5);
	h6->SetFillColor(6);
	h7->SetFillColor(7);
	h8->SetFillColor(8);
	h9->SetFillColor(9);
	
	h1->SetLineColor(1);
	h2->SetLineColor(2);
	h3->SetLineColor(3);
	h4->SetLineColor(4);
	h5->SetLineColor(5);
	h6->SetLineColor(6);
	h7->SetLineColor(7);
	h8->SetLineColor(8);
	h9->SetLineColor(9);
	
std::cout << "writing file and tree..." << std::endl;
	
	std::unique_ptr<TFile> myFile = std::make_unique<TFile>("AutoFlushTestingFile.root", "RECREATE");
	TTree* tree1 = new TTree("NormalTree","NormalTree");
	TTree* tree2 = new TTree("AutoFlushedTree","AutoFlushed Tree");
	
	//normal: Long64_t autof = -30000000
	tree2->SetAutoFlush(NewAutoF);
	
	//initializing parameters, vectors, float variables
	
std::cout << "initializing vectors..." << std::endl;
	
	const Int_t NEvents = 10000;	//number of events: 10,000
	
	const Int_t NEntries[10] = {1,10,25,50,100,200,500,750,1000,2000};
	
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
	
	tree1->Branch("N1", &v0);
	tree1->Branch("N10", &v1);
	tree1->Branch("N25", &v2);
	tree1->Branch("N50", &v3);
	tree1->Branch("N100", &v4);
	tree1->Branch("N200", &v5);
	tree1->Branch("N500", &v6);
	tree1->Branch("N750", &v7);
	tree1->Branch("N1000", &v8);
	tree1->Branch("N2000", &v9);
	
	
	tree2->Branch("A1", &v0);
	tree2->Branch("A10", &v1);
	tree2->Branch("A25", &v2);
	tree2->Branch("A50", &v3);
	tree2->Branch("A100", &v4);
	tree2->Branch("A200", &v5);
	tree2->Branch("A500", &v6);
	tree2->Branch("A750", &v7);
	tree2->Branch("A1000", &v8);
	tree2->Branch("A2000", &v9);
	

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
			f2 = 1;
			}
		h2->Fill(f2);
		v2.emplace_back(f2);
		}
		
		//branch3
		for(int j = 0; j < N3; j++) {
			
		f3 = gRandom->Rndm();
			if(f3 > 0.8) {
			f3 = 3;
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
			f7 = 1.5;
			}
			if(f7 > 0.7) {
			f7 = 2.5;
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
}


//void AutoFlushTest() {
	//creates two trees with five branches, fills each with 1000 random numbers of different distributions
	//create();
	//read();
//}


int main() {
  LargeAutoFlushTest();
  return 0; 
}

