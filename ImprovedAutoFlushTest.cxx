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
	
	TCanvas *cnvs2 = new TCanvas("cnvs2","Tree Print", 10, 10, 2400, 2000);
	cnvs2->Divide(2,1);
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
	
	TH2D *histSize = new TH2D("histSize","Branch Sizes",20,0,2001,20,0,2560); 
	//"NBins = 2*Num. of Branches, xmin = Vector length of smallest branch, xmax = sim. to xmin, ymin = 0; ymax = largest possible basket size
	TH2D *histComp = new TH2D("histComp","Branch Compression",20,0,2001,20,0,100); //same as above

	//histSize->SetFillColor(38);
	//histComp->SetFillColor(48);
	
	histSize->GetXaxis()->SetTitle("Entries per Row");
	histComp->GetXaxis()->SetTitle("Entries per Row");
	
	histSize->GetYaxis()->SetTitle("Basket Size[kB]");
	histComp->GetYaxis()->SetTitle("CX");
	
	
	
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
	Int_t N1Size, A1Size, N10Size, A10Size, N25Size, A25Size, N50Size, A50Size, N100Size, A100Size; 
	Int_t N200Size, A200Size, N500Size, A500Size, N750Size, A750Size, N1000Size, A1000Size, N2000Size, A2000Size;
	//Double_t N5Count, A5Count;
	Double_t N1TotBytes, A1TotBytes, N10TotBytes, A10TotBytes, N25TotBytes, A25TotBytes, N50TotBytes, A50TotBytes, N100TotBytes, A100TotBytes; 
	Double_t N200TotBytes, A200TotBytes, N500TotBytes, A500TotBytes, N750TotBytes, A750TotBytes, N1000TotBytes, A1000TotBytes, N2000TotBytes, A2000TotBytes;
	
	Double_t N1TotZipBytes, A1TotZipBytes, N10TotZipBytes, A10TotZipBytes, N25TotZipBytes, A25TotZipBytes, N50TotZipBytes, A50TotZipBytes;
	Double_t N100TotZipBytes, A100TotZipBytes, N200TotZipBytes, A200TotZipBytes, N500TotZipBytes, A500TotZipBytes, N750TotZipBytes, A750TotZipBytes;
	Double_t N1000TotZipBytes, A1000TotZipBytes, N2000TotZipBytes, A2000TotZipBytes;
	
	Double_t N1Comp, A1Comp, N10Comp, A10Comp, N25Comp, A25Comp, N50Comp, A50Comp, N100Comp, A100Comp, N200Comp, A200Comp;
	Double_t N500Comp, A500Comp, N750Comp, A750Comp, N1000Comp, A1000Comp, N2000Comp, A2000Comp;
	
	//TEST: calculations
		//Basket Sizes
		N1Size = n1->GetBasketSize();
		A1Size = a1->GetBasketSize();
		
		N10Size = n10->GetBasketSize();
		A10Size = a10->GetBasketSize();
	
		N25Size = n25->GetBasketSize();
		A25Size = a25->GetBasketSize();
	
		N50Size = n50->GetBasketSize();
		A50Size = a50->GetBasketSize();
	
		N100Size = n100->GetBasketSize();
		A100Size = a100->GetBasketSize();
	
		N200Size = n200->GetBasketSize();
		A200Size = a200->GetBasketSize();
	
		N500Size = n500->GetBasketSize();
		A500Size = a500->GetBasketSize();
	
		N750Size = n750->GetBasketSize();
		A750Size = a750->GetBasketSize();
	
		N1000Size = n1000->GetBasketSize();
		A1000Size = a1000->GetBasketSize();
	
		N2000Size = n2000->GetBasketSize();
		A2000Size = a2000->GetBasketSize();
	
		//Basket Counts
		N1TotBytes = n1->GetTotBytes();
		A1TotBytes = a1->GetTotBytes();
	
		N10TotBytes = n10->GetTotBytes();
		A10TotBytes = a10->GetTotBytes();
	
		N25TotBytes = n25->GetTotBytes();
		A25TotBytes = a25->GetTotBytes();
	
		N50TotBytes = n50->GetTotBytes();
		A50TotBytes = a50->GetTotBytes();
	
		N100TotBytes = n100->GetTotBytes();
		A100TotBytes = a100->GetTotBytes();
	
		N200TotBytes = n200->GetTotBytes();
		A200TotBytes = a200->GetTotBytes();
	
		N500TotBytes = n500->GetTotBytes();
		A500TotBytes = a500->GetTotBytes();
	
		N750TotBytes = n750->GetTotBytes();
		A750TotBytes = a750->GetTotBytes();
	
		N1000TotBytes = n1000->GetTotBytes();
		A1000TotBytes = a1000->GetTotBytes();
	
		N2000TotBytes = n2000->GetTotBytes();
		A2000TotBytes = a2000->GetTotBytes();
	
	
		N1TotZipBytes = n1->GetZipBytes();
		A1TotZipBytes = a1->GetZipBytes();
	
		N10TotBytes = n10->GetZipBytes();
		A10TotBytes = a10->GetZipBytes();
	
		N25TotBytes = n25->GetZipBytes();
		A25TotBytes = a25->GetZipBytes();
	
		N50TotBytes = n50->GetZipBytes();
		A50TotBytes = a50->GetZipBytes();
	
		N100TotBytes = n100->GetZipBytes();
		A100TotBytes = a100->GetZipBytes();
	
		N200TotBytes = n200->GetZipBytes();
		A200TotBytes = a200->GetZipBytes();
	
		N500TotBytes = n500->GetZipBytes();
		A500TotBytes = a500->GetZipBytes();
	
		N750TotBytes = n750->GetZipBytes();
		A750TotBytes = a750->GetZipBytes();
	
		N1000TotBytes = n1000->GetZipBytes();
		A1000TotBytes = a1000->GetZipBytes();
	
		N2000TotBytes = n2000->GetZipBytes();
		A2000TotBytes = a2000->GetZipBytes();
	
		//basket count: fix later
	
		//N5Count = 1 + (N5TotBytes/N5Size);
		//A5Count = 1 + (A5TotBytes/A5Size);
	
		//Compression
		N1Comp = (N1TotBytes)/(N1TotZipBytes);
		A1Comp = (A1TotBytes)/(A1TotZipBytes);
	
		N10Comp = (N10TotBytes)/(N10TotZipBytes);
		A10Comp = (A10TotBytes)/(A10TotZipBytes);
	
		N25Comp = (N25TotBytes)/(N25TotZipBytes);
		A25Comp = (A25TotBytes)/(A25TotZipBytes);
	
		N50Comp = (N50TotBytes)/(N50TotZipBytes);
		A50Comp = (A50TotBytes)/(A50TotZipBytes);
	
		N100Comp = (N100TotBytes)/(N100TotZipBytes);
		A100Comp = (A100TotBytes)/(A100TotZipBytes);
	
		N200Comp = (N200TotBytes)/(N200TotZipBytes);
		A200Comp = (A200TotBytes)/(A200TotZipBytes);
	
		N500Comp = (N500TotBytes)/(N500TotZipBytes);
		A500Comp = (A500TotBytes)/(A500TotZipBytes);
	
		N750Comp = (N750TotBytes)/(N750TotZipBytes);
		A750Comp = (A750TotBytes)/(A750TotZipBytes);
	
		N1000Comp = (N1000TotBytes)/(N1000TotZipBytes);
		A1000Comp = (A1000TotBytes)/(A1000TotZipBytes);
	
		N2000Comp = (N2000TotBytes)/(N2000TotZipBytes);
		A2000Comp = (A2000TotBytes)/(A2000TotZipBytes);
	
	
	//std::cout << "Normal Tree Scan:" << std::endl;
	//tree1->Scan();
	//std::cout << "AutoFlushed Tree Scan:" << std::endl;
	//tree2->Scan();
	
	std::cout << "Print logs:" << std::endl;
	tree1->Print();
	tree2->Print();
	
	//filling arrays to store Basket Size and Compression
	Int_t nlabels = NLabels/2;
	Int_t NSize[nlabels], ASize[nlabels], VecSize[nlabels]; 
	Float_t NComp[nlabels], AComp[nlabels];
	
	VecSize[0] = 1; VecSize[1] = 10; VecSize[2] = 25; VecSize[3] = 50; VecSize[4] = 100;
	VecSize[5] = 200; VecSize[6] = 500; VecSize[7] = 750; VecSize[8] = 1000; VecSize[9] = 2000;
	
	NSize[0] = N1Size; NSize[1] = N10Size; NSize[2] = N25Size; NSize[3] = N50Size; NSize[4] = N100Size; NSize[5] = N200Size; NSize[6] = N500Size;  
	NSize[7] = N750Size; NSize[8] = N1000Size; NSize[9] = N2000Size;
	
	ASize[0] = A1Size; ASize[1] = A10Size; ASize[2] = A25Size; ASize[3] = A50Size; ASize[4] = A100Size; ASize[5] = A200Size; ASize[6] = A500Size;  
	ASize[7] = A750Size; ASize[8] = A1000Size; ASize[9] = A2000Size;
	
	NComp[0] = N1Comp; NComp[1] = N10Comp; NComp[2] = N25Comp; NComp[3] = N50Comp; NComp[4] = N100Comp; NComp[5] = N200Comp; NComp[6] = N500Comp;  
	NComp[7] = N750Comp; NComp[8] = N1000Comp; NComp[9] = N2000Comp;
	
	AComp[0] = A1Comp; AComp[1] = A10Comp; AComp[2] = A25Comp; AComp[3] = A50Comp; AComp[4] = A100Comp; AComp[5] = A200Comp; AComp[6] = A500Comp;  
	AComp[7] = A750Comp; AComp[8] = A1000Comp; AComp[9] = A2000Comp;
	
	//convert size to kB:
	for(int i = 0; i < nlabels; i++) {
		NSize[i] = NSize[i]/1000;
		ASize[i] = ASize[i]/1000;
	}
	
	 
	//Basket Size and Compression graphs
	cnvs2->cd(1);
	histSize->Draw();
	
	TGraph *grSize = new TGraph(NLabels);
	
		for(int i = 0; i < nlabels ; i++) {
			grSize->AddPoint(i+1,VecSize[i]-0.5,NSize[i]);
			grSize->AddPoint(i+1,VecSize[i]+0.5,ASize[i]);
		}
		
		grSize->Draw("sameB");
	
			 
	
	
	
	cnvs2->cd(2);
	histComp->Draw();
	
	TGraph *grComp = new TGraph(NLabels);
	
		for(int i = 0; i < nlabels ; i++) {
			grComp->AddPoint(i+1,VecSize[i]-0.5,NComp[i]);
			grComp->AddPoint(i+1,VecSize[i]+0.5,AComp[i]);
		}
	
	grComp->Draw("sameB");
	
	
	
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

