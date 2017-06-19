#include <TH1D.h>
#include <TH2D.h>
#include <TH3F.h>
#include <stdio.h>
#include <TFile.h>
#include "TMath.h"

void Hist(){
	
	TFile *g = new TFile("/home/lhusova/diplomovka/data/AnalysisResults.root");
	TList *list = g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
	
	/*TH1D *hlh;
	hlh = (TH1D*)list->FindObject("fHistLambdaHadron");
	TH1D *hkh;
	hkh = (TH1D*)list->FindObject("fHistK0Hadron");
	TH1D *halh;
	halh = (TH1D*)list->FindObject("fHistAntiLambdaHadron");
	TH1D *hnl;
	hnl = (TH1D*)list->FindObject("fHistPocetLambda");
	TH1D *hnk;
	hnk = (TH1D*)list->FindObject("fHistPocetK0");
	TH1D *hnal;
	hnal = (TH1D*)list->FindObject("fHistPocetAntiLambda");
	
	hlh->Sumw2();
	hkh->Sumw2();
	hnl->Sumw2();
	hnk->Sumw2();
	hnal->Sumw2();
	halh->Sumw2();
	
	hlh->Scale(1./hnl->GetBinContent(1)); // normovanie na pocet trigger castic
	hkh->Scale(1./hnk->GetBinContent(1));
	halh->Scale(1./hnal->GetBinContent(1));
	
	hlh->SetXTitle("#Delta#phi");
	hkh->SetXTitle("#Delta#phi");
	hlh->SetYTitle("# parov / # trigger castic");
	hkh->SetYTitle("# parov / # trigger castic");
	halh->SetXTitle("#Delta#phi");
	halh->SetYTitle("# parov / # trigger castic");
	halh->SetTitle("Uhlove korelacie #bar{#Lambda}-hadron");

	TCanvas *c = new TCanvas;
	c->Divide(1,3);
	c->cd(1);
	hlh->DrawCopy("E");
	c->cd(2);
	hkh->DrawCopy("E");
	c->cd(3);
	halh->DrawCopy("E");*/
	
	TH3F *fHistK0MassPtCut = (TH3F*)list->FindObject("fHistK0MassPtCut");
	TH3F *fHistLambdaMassPtCut = (TH3F*)list->FindObject("fHistLambdaMassPtCut");
	TH3F *fHistAntiLambdaMassPtCut = (TH3F*)list->FindObject("fHistAntiLambdaMassPtCut");
	
	Int_t lPocetCutov = 6;
	Int_t lPocetPtBinov = 4;

	//=====inv. hmotnost K0 ==========
		
	TCanvas *a = new TCanvas;
	a->Divide(2,2);
	
	TCanvas *afin = new TCanvas;
	afin->Divide(2,2);
	TCanvas *canvas = new TCanvas;
	canvas->Divide(3,1);
	
	TLegend *lgK = new TLegend[lPocetPtBinov];
	
	char legendaK[50];
	char nazovK[50];
	char titleK[100];
	
	TH3F **hkmpc = new TH3F*[lPocetCutov];
	TH2D **hkmpc_2D = new TH2D*[lPocetCutov];
	for (Int_t i = 0; i<lPocetCutov; i++)
	{	
		hkmpc[i] = fHistK0MassPtCut->Clone();
		//~ hkmpc[i]->Sumw2();
		hkmpc[i]->GetZaxis()->SetRange(i+1,i+1);
		
		//projekcie podla jednotlivych cutov do xy roviny - mass-pt
		hkmpc_2D[i] = hkmpc[i]->Project3D("xy");
		
		//priprava na projekcie podla pt binov
		TH2D **hkmpc_2D_pt = new TH2D*[lPocetPtBinov];
		TH1D **hkmpc_pt_1D = new TH1D*[lPocetPtBinov];
		TH1D **tmp = new TH1D*[lPocetPtBinov];
		
		sprintf(legendaK,"invariantna hmotnost po aplikovani %d.cutu",i+1);

		if (i==lPocetCutov-1){
			canvas->cd(1);
			hkmpc_2D[i]->DrawCopy();
		}

		for (Int_t j = 0; j<lPocetPtBinov; j++)
		{
			hkmpc_2D_pt[j] = hkmpc_2D[i]->Clone();
			hkmpc_2D_pt[j] -> GetXaxis()->SetRange(j+1,j+1);
			hkmpc_pt_1D[j] = hkmpc_2D_pt[j]->ProjectionY();
			hkmpc_pt_1D[j] -> SetFillColor(i+1);
			hkmpc_pt_1D[j] -> SetLineColor(i+1);
			hkmpc_pt_1D[j] -> SetFillStyle(3001);
			
			tmp[j] = hkmpc_pt_1D[j]->Clone();
			lgK[j].AddEntry(tmp[j],legendaK,"f");	
			
			
			/*TPad *pad =*/ a->cd(j+1);
			
			//pad->SetLogy();
			
			if (i==0)
			{
				sprintf(nazovK,"Invaraintna hmotnost K^{0}_{S}, %d. p_{T} bin", j+1); 
				hkmpc_pt_1D[j]->SetTitle(nazovK);
				hkmpc_pt_1D[j]->SetYTitle("#");
				hkmpc_pt_1D[j]->SetXTitle("m");
				hkmpc_pt_1D[j]->DrawCopy();

				
				lgK[j].SetX1NDC(0.2); 
				lgK[j].SetX2NDC(0.9);
				lgK[j].SetY1NDC(0.75); 
				lgK[j].SetY2NDC(0.8); 
				
			}
			
			else
			{
				hkmpc_pt_1D[j]->DrawCopy("SAME");
			}
			
			if (i==lPocetCutov-1) {
				lgK[j].Draw();
				/*TPad *ppaf =*/ afin->cd(j+1);
				//ppaf->SetLogy();
				sprintf(titleK,"Invariantna hmotnost K^{0} po vsetkych cutoch, i=%d",i+1);
				hkmpc_pt_1D[j]->SetTitle(titleK);
				hkmpc_pt_1D[j]->DrawCopy();
			}
			
			
		}
		delete tmp;
		delete hkmpc_2D_pt;
		delete hkmpc_pt_1D;
		
	}
	


	//==== koniec K0 ===== 
	
	
	//=====inv. hmotnost Lambda ==========
	
	TCanvas *b = new TCanvas;
	b->Divide(2,2);
			
	TCanvas *bfin = new TCanvas;
	bfin->Divide(2,2);
	
	TLegend *lgL = new TLegend[lPocetPtBinov];
	
	char legendaL[50];
	char nazovL[50];
	char titleL[100];
	
	TH3F **hlmpc = new TH3F*[lPocetCutov];
	TH2D **hlmpc_2D = new TH2D*[lPocetCutov];
	for (Int_t i = 0; i<lPocetCutov; i++)
	{	
		hlmpc[i] = fHistLambdaMassPtCut->Clone();
		//~ hlmpc[i]->Sumw2();
		hlmpc[i]->GetZaxis()->SetRange(i+1,i+1);
		
		//projekcie podla jednotlivych cutov do xy roviny - mass-pt
		hlmpc_2D[i] = hlmpc[i]->Project3D("xy");
		
		//priprava na projekcie podla pt binov
		TH2D **hlmpc_2D_pt = new TH2D*[lPocetPtBinov];
		TH1D **hlmpc_pt_1D = new TH1D*[lPocetPtBinov];
		TH1D **tmp = new TH1D*[lPocetPtBinov];
		
		sprintf(legendaL,"invariantna hmotnost po aplikovani %d.cutu",i+1);

		if (i==lPocetCutov-1){
			canvas->cd(2);
			hlmpc_2D[i]->DrawCopy();
		}
		
		for (Int_t j = 0; j<lPocetPtBinov; j++)
		{
			
			hlmpc_2D_pt[j] = hlmpc_2D[i]->Clone();
			hlmpc_2D_pt[j] -> GetXaxis()->SetRange(j+1,j+1);
			hlmpc_pt_1D[j] = hlmpc_2D_pt[j]->ProjectionY();
			hlmpc_pt_1D[j] -> SetFillColor(i+1);
			hlmpc_pt_1D[j] -> SetLineColor(i+1);
			hlmpc_pt_1D[j] -> SetFillStyle(3001);
			
			tmp[j] = hlmpc_pt_1D[j]->Clone();
			lgL[j].AddEntry(tmp[j],legendaL,"f");
			
			
			
			/*TPad *ppb =*/ b->cd(j+1);
			//ppb->SetLogy();
			if (i==0)
			{
				sprintf(nazovL,"Invaraintna hmotnost #Lambda, %d. p_{T} bin", j+1); 
				hlmpc_pt_1D[j]->SetTitle(nazovL);
				hlmpc_pt_1D[j]->SetYTitle("#");
				hlmpc_pt_1D[j]->SetXTitle("m");
				hlmpc_pt_1D[j]->DrawCopy();

				lgL[j].SetX1NDC(0.2); 
				lgL[j].SetX2NDC(0.9);
				lgL[j].SetY1NDC(0.75); 
				lgL[j].SetY2NDC(0.8); 
				
			}
			else
			{
				hlmpc_pt_1D[j]->DrawCopy("SAME");								
			}
			
			if(i==lPocetCutov-1) {
				//printf("pocet cutov =%d, j=%d\n", lPocetCutov,j);
				lgL[j].Draw();
				/*TPad *pp =*/ bfin->cd(j+1);
				//pp->SetLogy();
				sprintf(titleL,"Invariantna hmotnost #Lambda po aplikovani vsetkych cutov, i=%d", i+1);
				hlmpc_pt_1D[j]->SetTitle(titleL);
				hlmpc_pt_1D[j]->DrawCopy();

			}
			
		}
		delete hlmpc_2D_pt;
		delete hlmpc_pt_1D;
		delete tmp;
		
	}
	//=====inv. hmotnost AntiLambda ==========
	
	TCanvas *d = new TCanvas;
	d->Divide(2,2);
			
	TCanvas *dfin = new TCanvas;
	dfin->Divide(2,2);
	
	TLegend *lgAl = new TLegend[lPocetPtBinov];
	
	char legendaAl[50];
	char nazovAl[50];
	char titleAl[100];
	
	TH3F **halmpc = new TH3F*[lPocetCutov];
	TH2D **halmpc_2D = new TH2D*[lPocetCutov];
	for (Int_t i = 0; i<lPocetCutov; i++)
	{	
		halmpc[i] = fHistAntiLambdaMassPtCut->Clone();
		//~ hlmpc[i]->Sumw2();
		halmpc[i]->GetZaxis()->SetRange(i+1,i+1);
		
		//projekcie podla jednotlivych cutov do xy roviny - mass-pt
		halmpc_2D[i] = halmpc[i]->Project3D("xy");
		
		//priprava na projekcie podla pt binov
		TH2D **halmpc_2D_pt = new TH2D*[lPocetPtBinov];
		TH1D **halmpc_pt_1D = new TH1D*[lPocetPtBinov];
		TH1D **tmp = new TH1D*[lPocetPtBinov];
		
		sprintf(legendaAl,"invariantna hmotnost po aplikovani %d.cutu",i+1);
		
		if (i==lPocetCutov-1){
			canvas->cd(3);
			halmpc_2D[i]->DrawCopy();
		}
		
		for (Int_t j = 0; j<lPocetPtBinov; j++)
		{
			
			halmpc_2D_pt[j] = halmpc_2D[i]->Clone();
			halmpc_2D_pt[j] -> GetXaxis()->SetRange(j+1,j+1);
			halmpc_pt_1D[j] = halmpc_2D_pt[j]->ProjectionY();
			halmpc_pt_1D[j] -> SetFillColor(i+1);
			halmpc_pt_1D[j] -> SetLineColor(i+1);
			halmpc_pt_1D[j] -> SetFillStyle(3001);
			
			tmp[j] = halmpc_pt_1D[j]->Clone();
			lgAl[j].AddEntry(tmp[j],legendaAl,"f");
			
			
			
			/*TPad *ppd =*/ d->cd(j+1);
			//ppb->SetLogy();
			if (i==0)
			{
				sprintf(nazovAl,"Invaraintna hmotnost #bar{#Lambda}, %d. p_{T} bin", j+1); 
				halmpc_pt_1D[j]->SetTitle(nazovAl);
				halmpc_pt_1D[j]->SetYTitle("#");
				halmpc_pt_1D[j]->SetXTitle("m");
				halmpc_pt_1D[j]->DrawCopy();

				lgAl[j].SetX1NDC(0.2); 
				lgAl[j].SetX2NDC(0.9);
				lgAl[j].SetY1NDC(0.75); 
				lgAl[j].SetY2NDC(0.8); 
				
			}
			else
			{
				halmpc_pt_1D[j]->DrawCopy("SAME");								
			}
			
			if(i==lPocetCutov-1) {
				//printf("pocet cutov =%d, j=%d\n", lPocetCutov,j);
				lgAl[j].Draw();
				/*TPad *ppdd =*/ dfin->cd(j+1);
				//pp->SetLogy();
				sprintf(titleAl,"Invariantna hmotnost #bar{#Lambda} po aplikovani vsetkych cutov, i=%d", i+1);
				halmpc_pt_1D[j]->SetTitle(titleAl);
				halmpc_pt_1D[j]->DrawCopy();
			}
			
		}
		delete halmpc_2D_pt;
		delete halmpc_pt_1D;
		delete tmp;
		
	}
	
	
}

