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

void ImprovedAutoFlushTest(Long64_t NewAutoF = -30000000){
	//create file and tree
	
				//ISSUES
				//!!BASKET COUNTER NOT WORKING, TAKEN OUT FOR NOW
	
	//creating canvas
std::cout << "creating canvases and histograms..." << std::endl;
	
	TCanvas *cnvs = new TCanvas("cnvs","Tree Scan", 10, 10, 1200, 800);
	cnvs->Divide(5,2);
	gStyle->SetOptStat(0);
	
	TCanvas *cnvs2 = new TCanvas("cnvs2","Tree Print", 10, 10, 1200, 800);
	cnvs2->Divide(2,1)
	gStyle->SetOptStat(0);
	
	//creating histograms
	
	const Int_t NBins = 1000;
	
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
	
const Int_t NLabels = 20; //NLabels = # of NT Branches + # of AT Branches
const char *Labels[NLabels] = {"N1","A1","N10","A10","N25","A25","N50","A50","N100","A100","N200","A200","N500","A500","N750","A750","N1000","A1000","N2000","A2000"};
	
	TH1D *histSize = new TH1D("histSize","Branch Sizes",20,0,2001); //"NBins = 2*Num. of Branches, xmin = Vector length of smallest branch, xmax = sim. to xmin
	TH1D *histComp = new TH1D("histComp","Branch Compression",20,0,2001); //same as above

	histSize->SetFillColor(38);
	histComp->SetFillColor(48);
	
	for(i = 1; i <= NLabels; i++) {
		histSize->GetXaxis()->SetBinLabel(i,Labels[i-1]);
		histComp->GetXaxis()->SetBinLabel(i,Labels[i-1]);
	}
	
std::cout << "writing file and tree..." << std::endl;
	
	std::unique_ptr<TFile> myFile = std::make_unique<TFile>("AutoFlushTestingFile.root", "RECREATE");
	TTree* tree1 = new TTree("NormalTree","NormalTree");
	TTree* tree2 = new TTree("AutoFlushedTree","AutoFlushed Tree");
	
	//normal: Long64_t autof = -30000000
	tree2->SetAutoFlush(NewAutoF);
	
	//initializing parameters, vectors, float variables
	
std::cout << "initializing vectors..." << std::endl;
	
	const Int_t NEvents = 1000;	//number of events: 1,000
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
	
	TBranch *n1 = tree1->Branch("N1", &v0);
	TBranch *n10 = tree1->Branch("N10", &v1);
	TBranch *n25 = tree1->Branch("N25", &v2);
	TBranch *n50 = tree1->Branch("N50", &v3);
	TBranch *n100 = tree1->Branch("N100", &v4);
	TBranch *n200 = tree1->Branch("N200", &v5);
	TBranch *n500 = tree1->Branch("N500", &v6);
	TBranch *n750 = tree1->Branch("N750", &v7);
	TBranch *n1000 = tree1->Branch("N1000", &v8);
	TBranch *n2000 = tree1->Branch("N2000", &v9);
	
	
	TBranch *a1 = tree2->Branch("A1", &v0);
	TBranch *a10 = tree2->Branch("A10", &v1);
	TBranch *a25 = tree2->Branch("A25", &v2);
	TBranch *a50 = tree2->Branch("A50", &v3);
	TBranch *a100 = tree2->Branch("A100", &v4);
	TBranch *a200 = tree2->Branch("A200", &v5);
	TBranch *a500 = tree2->Branch("A500", &v6);
	TBranch *a750 = tree2->Branch("A750", &v7);
	TBranch *a1000 = tree2->Branch("A1000", &v8);
	TBranch *a2000 = tree2->Branch("A2000", &v9);
	
	

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
	
	//TEST: variables
	Int_t N1Size, A1Size;
	//Double_t N5Count, A5Count;
	Double_t N1TotBytes, A1TotBytes;
	Double_t N1TotZipBytes, A1TotZipBytes;
	Double_t N1Comp, A1Comp;
	
	//TEST: calculations
		//Basket Sizes
		N1Size = n1->GetBasketSize();
		A1Size = a1->GetBasketSize();
	
		//Basket Counts
		N1TotBytes = n1->GetTotBytes();
		A1TotBytes = a1->GetTotBytes();
	
		N1TotZipBytes = n1->GetZipBytes();
		A1TotZipBytes = a1->GetZipBytes();
	
		//??Why are basket counts not working??
	
		//N5Count = 1 + (N5TotBytes/N5Size);
		//A5Count = 1 + (A5TotBytes/A5Size);
	
		//Compression
		N1Comp = (N1TotBytes)/(N1TotZipBytes);
		A1Comp = (A1TotBytes)/(A1TotZipBytes);
	
	
	//std::cout << "Normal Tree Scan:" << std::endl;
	//tree1->Scan();
	//std::cout << "AutoFlushed Tree Scan:" << std::endl;
	//tree2->Scan();
	
	std::cout << "Print logs:" << std::endl;
	tree1->Print();
	tree2->Print();
	
	//filling size and comp. arrays
	
	Int_t Size[NLabels]; 
	Float_t Comp[NLabels];
	
	Size[0] = N1Size; Size[1] = A1Size; Size[2] = N10Size; Size[3] = A10Size; Size[4] = N25Size; Size[5] = A25Size;
	Size[6] = N50Size; Size[7] = A50Size;Size[8] = N100Size; Size[9] = A100Size;Size[10] = N200Size; Size[11] = A200Size;Size[12] = N500Size; Size[13] = A500Size; 
	Size[14] = N750Size;Size[15] = A750Size;Size[16] = N1000Size; Size[17] = A1000Size; Size[18] = N2000Size; Size[19] = A2000Size;
	
	Comp[0] = N1Comp; Comp[1] = A1Comp; Comp[2] = N10Comp; Comp[3] = A10Comp; Comp[4] = N25Comp; Comp[5] = A25Comp;
	Comp[6] = N50Comp; Comp[7] = A50Comp;Comp[8] = N100Comp; Comp[9] = A100Comp;Comp[10] = N200Comp; Comp[11] = A200Comp;Comp[12] = N500Comp; Comp[13] = A500Comp; 
	Comp[14] = N750Comp;Comp[15] = A750Comp;Comp[16] = N1000Comp; Comp[17] = A1000Comp; Comp[18] = N2000Comp; Comp[19] = A2000Comp;
	 
	//drawing histograms
	cnvs2->cd(1);
	histSize->Draw();
	TGraph *grSize = new TGraph(NLabels);
	for(int i = 0; i < NLabels; i++) {
		grSize->SetPoint(i+1,	
	}
	
	
	
	cnvs2->cd(2):
	histComp->Draw();
	
	
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
	
	//cnvs->Update();
	//? Is there a way to initialize this?
	//cnvs->SaveAs("FirstTreeCanvas.pdf");
}



//void write() {
	//creates two trees with five branches, fills each with 1000 random numbers of different distributions
	//write();
	//read();
//}


int main() {
  ImprovedAutoFlushTest();
  return 0; 
}

