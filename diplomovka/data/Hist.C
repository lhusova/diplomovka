#include <TH1D.h>
#include <TH2D.h>
#include <TH3F.h>
#include <stdio.h>
#include <TFile.h>
#include "TMath.h"

void Hist(){
	
	TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsDataNajnovsie03.root");
	TList *list = (TList*)g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
	
	TH3F *fHistK0MassPtCut = (TH3F*)list->FindObject("fHistK0MassPtCut");
	TH3F *fHistLambdaMassPtCut = (TH3F*)list->FindObject("fHistLambdaMassPtCut");
	TH3F *fHistAntiLambdaMassPtCut = (TH3F*)list->FindObject("fHistAntiLambdaMassPtCut");
	
    fHistK0MassPtCut->GetZaxis()->SetRange(6,6);
    TH1F * fHistInvMassK0 = (TH1F *)fHistK0MassPtCut->Project3D("x");
    fHistInvMassK0->GetXaxis()->SetRangeUser(0.46,0.54);
    TCanvas *cMassK0 = new TCanvas;
    fHistInvMassK0->SetTitle("Rozdelenie invariantnej hmotnosti kandidatov na K^{0}_{S}");
    fHistInvMassK0->SetXTitle("m_{#pi^{+} #pi^{-}}(GeV/c^{2})");
    fHistInvMassK0->SetYTitle("#");
    fHistInvMassK0->DrawCopy();
    
    Double_t integralCeleK0 =fHistInvMassK0->Integral("width");
    Double_t vyskapozadiaK0 = (fHistInvMassK0->GetBinContent(fHistInvMassK0->FindBin(0.485))+fHistInvMassK0->GetBinContent(fHistInvMassK0->FindBin(0.511)))/2;
    Double_t integralpozadieK0 = (0.52-0.48)*vyskapozadiaK0;
    Double_t podielPozadiaK0 = (integralpozadieK0/integralCeleK0)*100;
    Printf("cele %g pozadie %g, vyska pozadia %g K0\n",integralCeleK0,integralpozadieK0,vyskapozadiaK0);
    Printf("podiel pozadia pre K0 %g \n",podielPozadiaK0);
    
    fHistLambdaMassPtCut->GetZaxis()->SetRange(6,6);
    TH1F * fHistInvMassLam = (TH1F *)fHistLambdaMassPtCut->Project3D("x");
    fHistInvMassLam->GetXaxis()->SetRangeUser(1.08,1.15);
    TCanvas *cMassLam = new TCanvas;
    fHistInvMassLam->SetTitle("Rozdelenie invariantnej hmotnosti kandidatov na #Lambda");
    fHistInvMassLam->SetXTitle("m_{p#pi^{-}}(GeV/c^{2})");
    fHistInvMassLam->SetYTitle("#");
    fHistInvMassLam->DrawCopy();
    
    Double_t integralCeleLam =fHistInvMassLam->Integral("width");
    Double_t vyskapozadiaLam = (fHistInvMassLam->GetBinContent(fHistInvMassLam->FindBin(1.102))+fHistInvMassLam->GetBinContent(fHistInvMassLam->FindBin(1.127)))/2;
    Double_t integralpozadieLam = (1.2-1.05)*vyskapozadiaLam;
    Double_t podielPozadiaLam = (integralpozadieLam/integralCeleLam)*100;
    Printf("cele %g pozadie %g, vyska pozadia %g K0\n",integralCeleLam,integralpozadieLam,vyskapozadiaLam);
    Printf("podiel pozadia pre Lambda %g \n",podielPozadiaLam);
    
    fHistAntiLambdaMassPtCut->GetZaxis()->SetRange(6,6);
    TH1F * fHistInvMassALam = (TH1F *)fHistAntiLambdaMassPtCut->Project3D("x");
    fHistInvMassALam->GetXaxis()->SetRangeUser(1.08,1.15);
    TCanvas *cMassALam = new TCanvas;
    fHistInvMassALam->SetTitle("Rozdelenie invariantnej hmotnosti kandidatov na #bar{#Lambda}");
    fHistInvMassALam->SetXTitle("m_{#bar{p}#pi^{+}}(GeV/c^{2})");
    fHistInvMassALam->SetYTitle("#");
    fHistInvMassALam->DrawCopy();
    
    Double_t integralCeleALam =fHistInvMassALam->Integral("width");
    Double_t vyskapozadiaALam = (fHistInvMassALam->GetBinContent(fHistInvMassALam->FindBin(1.102))+fHistInvMassALam->GetBinContent(fHistInvMassALam->FindBin(1.127)))/2;
    Double_t integralpozadieALam = (1.2-1.05)*vyskapozadiaALam;
    Double_t podielPozadiaALam = (integralpozadieALam/integralCeleALam)*100;
    Printf("cele %g pozadie %g, vyska pozadia %g AntiLambda\n",integralCeleALam,integralpozadieALam,vyskapozadiaALam);
    Printf("podiel pozadia pre AntiLambda %g \n",podielPozadiaALam);
    
/*	Int_t lPocetCutov = 7;
	Int_t lPocetPtBinov = 10;

	//=====inv. hmotnost K0 ==========
		
	TCanvas *a = new TCanvas;
	a->Divide(2,3);
	
	TCanvas *afin = new TCanvas;
	afin->Divide(2,3);
	TCanvas *canvas = new TCanvas;
	canvas->Divide(3,1);
	
	TLegend *lgK = new TLegend[lPocetPtBinov];
	
	char legendaK[50];
	char nazovK[50];
	char titleK[100];
	
	TH3F **hkmpc = new TH3F*[lPocetCutov];
	TH2D **hkmpc_2D = new TH2D*[lPocetCutov];
	for (Int_t i = 6; i<lPocetCutov; i++)
	{	
		hkmpc[i] = (TH3F*)fHistK0MassPtCut->Clone();
		//~ hkmpc[i]->Sumw2();
		hkmpc[i]->GetZaxis()->SetRange(i+1,i+1);
		
		//projekcie podla jednotlivych cutov do xy roviny - mass-pt
		hkmpc_2D[i] = (TH2D*)hkmpc[i]->Project3D("xy");
		
		//priprava na projekcie podla pt binov
		TH2D **hkmpc_2D_pt = new TH2D*[lPocetPtBinov];
		TH1D **hkmpc_pt_1D = new TH1D*[lPocetPtBinov];
		TH1D **tmp = new TH1D*[lPocetPtBinov];
		
		sprintf(legendaK,"invariantna hmotnost K^{0}_{S} po aplikovani %d.cutu",i+1);

		if (i==lPocetCutov-1){
			canvas->cd(1);
			hkmpc_2D[i]->DrawCopy();
		}

		for (Int_t j = 4; j<lPocetPtBinov; j++)
		{
			hkmpc_2D_pt[j] = (TH2D*)hkmpc_2D[i]->Clone();
			hkmpc_2D_pt[j] -> GetXaxis()->SetRange(j+1,j+1);
			hkmpc_pt_1D[j] = (TH1D*) hkmpc_2D_pt[j]->ProjectionY();
			/*hkmpc_pt_1D[j] -> SetFillColor(i+1);
			hkmpc_pt_1D[j] -> SetLineColor(i+1);
			hkmpc_pt_1D[j] -> SetFillStyle(3001);*/
			
		/*	tmp[j] = (TH1D* )hkmpc_pt_1D[j]->Clone();
			lgK[j].AddEntry(tmp[j],legendaK,"f");	
			
			
			/*TPad *pad =*/ //a->cd(j+1);
			
			//pad->SetLogy();
			
			/*if (i==0)
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
			}*/
			
	/*		if (i==lPocetCutov-1) {
				lgK[j].Draw();
				/*TPad *ppaf =*/ //afin->cd(j-3);
				//ppaf->SetLogy();
	/*			sprintf(titleK,"Invariantna hmotnost K^{0} po vsetkych cutoch, i=%d, pt bin %d",i+1, j);
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
	b->Divide(2,3);
			
	TCanvas *bfin = new TCanvas;
	bfin->Divide(2,3);
	
	TLegend *lgL = new TLegend[lPocetPtBinov];
	
	char legendaL[50];
	char nazovL[50];
	char titleL[100];
	
	TH3F **hlmpc = new TH3F*[lPocetCutov];
	TH2D **hlmpc_2D = new TH2D*[lPocetCutov];
	for (Int_t i = 6; i<lPocetCutov; i++)
	{	
		hlmpc[i] = (TH3F*)fHistLambdaMassPtCut->Clone();
		//~ hlmpc[i]->Sumw2();
		hlmpc[i]->GetZaxis()->SetRange(i+1,i+1);
		
		//projekcie podla jednotlivych cutov do xy roviny - mass-pt
		hlmpc_2D[i] = (TH2D*)hlmpc[i]->Project3D("xy");
		
		//priprava na projekcie podla pt binov
		TH2D **hlmpc_2D_pt = new TH2D*[lPocetPtBinov];
		TH1D **hlmpc_pt_1D = new TH1D*[lPocetPtBinov];
		TH1D **tmp = new TH1D*[lPocetPtBinov];
		
		sprintf(legendaL,"invariantna hmotnost po aplikovani %d.cutu",i+1);

		if (i==lPocetCutov-1){
			canvas->cd(2);
			hlmpc_2D[i]->DrawCopy();
		}
		
		for (Int_t j = 4; j<lPocetPtBinov; j++)
		{
			
			hlmpc_2D_pt[j] = (TH2D*)hlmpc_2D[i]->Clone();
			hlmpc_2D_pt[j] -> GetXaxis()->SetRange(j+1,j+1);
			hlmpc_pt_1D[j] = (TH1D*) hlmpc_2D_pt[j]->ProjectionY();
			/*hlmpc_pt_1D[j] -> SetFillColor(i+1);
			hlmpc_pt_1D[j] -> SetLineColor(i+1);
			hlmpc_pt_1D[j] -> SetFillStyle(3001);*/
			
		/*	tmp[j] = (TH1D*) hlmpc_pt_1D[j]->Clone();
			lgL[j].AddEntry(tmp[j],legendaL,"f");
			
			
			
		//	//ppb->SetLogy();
			/*if (i==0)
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
			}*/
			
	/*		if(i==lPocetCutov-1) {
				//printf("pocet cutov =%d, j=%d\n", lPocetCutov,j);
				lgL[j].Draw();
				/*TPad *pp =*/ //bfin->cd(j-3);
				//pp->SetLogy();
	/*			sprintf(titleL,"Invariantna hmotnost #Lambda po aplikovani vsetkych cutov, i=%d", i+1);
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
	d->Divide(2,3);
			
	TCanvas *dfin = new TCanvas;
	dfin->Divide(2,3);
	
	TLegend *lgAl = new TLegend[lPocetPtBinov];
	
	char legendaAl[50];
	char nazovAl[50];
	char titleAl[100];
	
	TH3F **halmpc = new TH3F*[lPocetCutov];
	TH2D **halmpc_2D = new TH2D*[lPocetCutov];
	for (Int_t i = 6; i<lPocetCutov; i++)
	{	
		halmpc[i] = (TH3F*) fHistAntiLambdaMassPtCut->Clone();
		//~ hlmpc[i]->Sumw2();
		halmpc[i]->GetZaxis()->SetRange(i+1,i+1);
		
		//projekcie podla jednotlivych cutov do xy roviny - mass-pt
		halmpc_2D[i] = (TH2D*) halmpc[i]->Project3D("xy");
		
		//priprava na projekcie podla pt binov
		TH2D **halmpc_2D_pt = new TH2D*[lPocetPtBinov];
		TH1D **halmpc_pt_1D = new TH1D*[lPocetPtBinov];
		TH1D **tmp = new TH1D*[lPocetPtBinov];
		
		sprintf(legendaAl,"invariantna hmotnost po aplikovani %d.cutu",i+1);
		
		if (i==lPocetCutov-1){
			canvas->cd(3);
			halmpc_2D[i]->DrawCopy();
		}
		
		for (Int_t j = 4; j<lPocetPtBinov; j++)
		{
			
			halmpc_2D_pt[j] = (TH2D*) halmpc_2D[i]->Clone();
			halmpc_2D_pt[j] -> GetXaxis()->SetRange(j+1,j+1);
			halmpc_pt_1D[j] = (TH1D*) halmpc_2D_pt[j]->ProjectionY();
			/*halmpc_pt_1D[j] -> SetFillColor(i+1);
			halmpc_pt_1D[j] -> SetLineColor(i+1);
			halmpc_pt_1D[j] -> SetFillStyle(3001);*/
			
	/*		tmp[j] = (TH1D*) halmpc_pt_1D[j]->Clone();
			lgAl[j].AddEntry(tmp[j],legendaAl,"f");
			
			
			
			/*TPad *ppd =*/ //d->cd(j+1);
			//ppb->SetLogy();
			/*if (i==0)
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
			}*/
			
		/*	if(i==lPocetCutov-1) {
				//printf("pocet cutov =%d, j=%d\n", lPocetCutov,j);
				lgAl[j].Draw();
				/*TPad *ppdd =*/ //dfin->cd(j-3);
				//pp->SetLogy();
		/*		sprintf(titleAl,"Invariantna hmotnost #bar{#Lambda} po aplikovani vsetkych cutov, i=%d", i+1);
				halmpc_pt_1D[j]->SetTitle(titleAl);
				halmpc_pt_1D[j]->DrawCopy();
			}
			
		}
		delete halmpc_2D_pt;
		delete halmpc_pt_1D;
		delete tmp;
		
	}*/
	
	
}

