#include <TH1D.h>
#include <TH2D.h>
#include <THnSparse.h>
#include <stdio.h>
#include <TFile.h>
#include "TMath.h"

void THn(){
	gStyle->SetOptStat(0000000000);

	TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMC_05.root");
	TList *list = g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
	
	THnSparse *fHistKorelacie = (THnSparse*)list->FindObject("fHistKorelacie");
	THnSparse *fHistdPhidEtaMix = (THnSparse*)list->FindObject("fHistdPhidEtaMix");
	THnSparse *fHistNumberOfTriggers = (THnSparse*)list->FindObject("fHistNumberOfTriggers");

	const Double_t kPi = TMath::Pi();

	fHistNumberOfTriggers->Sumw2();

	const Int_t nPtBins = 6;
	const Int_t nTig =3;


	TH1D **fHistPart = new TH1D*[nPtBins];
	THnSparse **fHistPartClone = new THnSparse*[nPtBins];
	char hnameent[50];
	TCanvas *a = new TCanvas;
	a->Divide(1,nPtBins);

	for(Int_t i=0;i<nPtBins;i++){
		fHistPartClone[i]=fHistNumberOfTriggers->Clone();
		if (i==0) fHistPartClone[i]->GetAxis(0)->SetRange(1,1);
		if (i==1) fHistPartClone[i]->GetAxis(0)->SetRange(2,2);
		if (i==2) fHistPartClone[i]->GetAxis(0)->SetRange(3,3);
		if (i==3) fHistPartClone[i]->GetAxis(0)->SetRange(4,5);
		if (i==4) fHistPartClone[i]->GetAxis(0)->SetRange(6,7);
		if (i==5) fHistPartClone[i]->GetAxis(0)->SetRange(8,11);
		fHistPart[i] = fHistPartClone[i]->Projection(1);
		sprintf(hnameent,"proj_%d",i);
		fHistPart[i]->SetName(hnameent);
		a->cd(i+1);
		fHistPart[i]->DrawCopy();
	}
	delete fHistPartClone;

	TCanvas *TrigMulti = new TCanvas;
	TrigMulti->Divide(1,3);
	TH1D **fHistMulti = new TH1D*[nTig];
	THnSparse **fHistMultiClone = new THnSparse*[nTig];
	char hnamemulti[100];

	for (Int_t i=0; i<nTig; i++){
		fHistMultiClone[i]=fHistNumberOfTriggers->Clone();
		if(i==0) fHistMultiClone[i]->GetAxis(1)->SetRange(1,1);
		if(i==1) fHistMultiClone[i]->GetAxis(1)->SetRange(2,3);
		if(i==2) fHistMultiClone[i]->GetAxis(1)->SetRange(4,4);
		fHistMulti[i] = fHistMultiClone[i]->Projection(0);
		if(i==0) sprintf(hnamemulti, "Zavislost poctu K^{0}_{S} od p_{T}");
		if(i==1) sprintf(hnamemulti, "Zavislost poctu #Lambda a #bar{#Lambda} od p_{T}");
		if(i==2) sprintf(hnamemulti, "Zavislost poctu nabitych trackov od p_{T}");
		sprintf(hnameent,"proj_%d",i);
		fHistMulti[i] -> SetName(hnameent);
		fHistMulti[i] ->SetTitle(hnamemulti);
		fHistMulti[i] ->SetXTitle("p_{T} (GeV)");
		fHistMulti[i] ->SetYTitle("#");
		TrigMulti->cd(i+1);
		fHistMulti[i] ->DrawCopy();
	}
	delete fHistMultiClone;

	THnSparse **fHistCorType=new THnSparse*[nTig];
	THnSparse **fHistRangePt=new THnSparse*[nTig*nPtBins];
	TH2D **fHistRangePtProjPhiEta = new TH2D*[nTig*nPtBins];
	char htitle[50];
	char hname[50]; 
	TCanvas *c = new TCanvas;
	c->Divide(nPtBins,nTig);
	

	for(Int_t i=0;i<nTig;i++){
		fHistCorType[i]=fHistKorelacie->Clone();
		if(i==0) fHistCorType[i]->GetAxis(5)->SetRange(i+1,i+1);
		if(i==1) fHistCorType[i]->GetAxis(5)->SetRange(i+1,i+2);
		if(i==2) fHistCorType[i]->GetAxis(5)->SetRange(i+2,i+2);
		for(Int_t j=0;j<nPtBins;j++){
			fHistRangePt[i*nPtBins+j]=fHistCorType[i]->Clone();

			if (j==0) fHistRangePt[i*nPtBins+j]->GetAxis(0)->SetRange(1,1);
			if (j==1) fHistRangePt[i*nPtBins+j]->GetAxis(0)->SetRange(2,2);
			if (j==2) fHistRangePt[i*nPtBins+j]->GetAxis(0)->SetRange(3,3);
			if (j==3) fHistRangePt[i*nPtBins+j]->GetAxis(0)->SetRange(4,5);
			if (j==4) fHistRangePt[i*nPtBins+j]->GetAxis(0)->SetRange(6,7);
			if (j==5) fHistRangePt[i*nPtBins+j]->GetAxis(0)->SetRange(8,11);
			
			fHistRangePtProjPhiEta[i*nPtBins+j] = fHistRangePt[i*nPtBins+j]->Projection(2,3);
			sprintf(hname,"2dproj_%d_pt_%d",i,j);
			fHistRangePtProjPhiEta[i*nPtBins+j]->SetName(hname);
			sprintf(htitle,"#Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,j);
			fHistRangePtProjPhiEta[i*nPtBins+j]->SetTitle(htitle);
			fHistRangePtProjPhiEta[i*nPtBins+j]->RebinX(4);
			fHistRangePtProjPhiEta[i*nPtBins+j]->RebinY(4);
			c->cd(i*nPtBins+j+1);
			fHistRangePtProjPhiEta[i*nPtBins+j]->DrawCopy("lego2z");

			
		}
		
	}

	THnSparse **fHistMixType= new THnSparse*[nTig];
	TH2D **fHistRangePtProjPhiEtaMix = new TH2D*[nTig*nPtBins];
	char hnamemix[50];
	char htitlemix[100];
	TCanvas *d = new TCanvas;
	d->Divide(nPtBins,nTig);

	for(Int_t i=0;i<nTig;i++){
		fHistMixType[i]=fHistdPhidEtaMix->Clone();
		if(i==0) fHistMixType[i]->GetAxis(5)->SetRange(1,1);
		if(i==1) fHistMixType[i]->GetAxis(5)->SetRange(2,3);
		if(i==2) fHistMixType[i]->GetAxis(5)->SetRange(4,4);
		for(Int_t j=0;j<nPtBins;j++){
			
			if (j==0) fHistMixType[i]->GetAxis(0)->SetRange(1,1);
			if (j==1)  fHistMixType[i]->GetAxis(0)->SetRange(2,2);
			if (j==2)  fHistMixType[i]->GetAxis(0)->SetRange(3,3);
			if (j==3)  fHistMixType[i]->GetAxis(0)->SetRange(4,5);
			if (j==4)  fHistMixType[i]->GetAxis(0)->SetRange(6,7);
			if (j==5)  fHistMixType[i]->GetAxis(0)->SetRange(8,11);
			
			
			fHistRangePtProjPhiEtaMix[i*nPtBins+j] = fHistMixType[i]->Projection(2,3);

			sprintf(hnamemix,"2dproj_mix_%d_pt_%d",i,j);
			fHistRangePtProjPhiEtaMix[i*nPtBins+j]->SetName(hnamemix);
			sprintf(htitlemix,"#Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d, mixed", i,j);
			fHistRangePtProjPhiEtaMix[i*nPtBins+j]->SetTitle(htitlemix);
			fHistRangePtProjPhiEtaMix[i*nPtBins+j]->RebinX(4);
			fHistRangePtProjPhiEtaMix[i*nPtBins+j]->RebinY(4);
			Double_t maximum = fHistRangePtProjPhiEtaMix[i*nPtBins+j]->GetMaximum();
			fHistRangePtProjPhiEtaMix[i*nPtBins+j]->Scale(1./maximum);
			d->cd(i*nPtBins+j+1);
			fHistRangePtProjPhiEtaMix[i*nPtBins+j]->DrawCopy("lego2z");
			fHistMixType[i]->GetAxis(0)->SetRange(-1,0);
		}
	}
	delete fHistMixType;

	TH1D **fHistProjPhi = new TH1D*[nPtBins*nTig];
	TH1D **fHistProjEta = new TH1D*[nPtBins*nTig];
	TCanvas *e = new TCanvas;
	e->Divide(nPtBins,nTig);
	TCanvas *f = new TCanvas;
	f->Divide(nPtBins,nTig);
	TCanvas *canK = new TCanvas;
	canK->Divide(2,3);
	TCanvas *canLam = new TCanvas;
	canLam->Divide(2,3);
	TCanvas *canAntiLam = new TCanvas;
	canAntiLam->Divide(2,3);
	TCanvas *canH = new TCanvas;
	canH->Divide(2,3);

	char hnamephi[50];
	Double_t yieldnear[nTig][nPtBins];
	Double_t yieldaway[nTig][nPtBins];
	Double_t yieldnearerror[nTig][nPtBins];
	Double_t yieldawayerror[nTig][nPtBins];
	char nameprojphi[100];
	char nameprojeta[100];
	char bezpoz[150];
	Double_t poz=0;

	TH1D **fHistBack = new TH1D*[nTig];
	
	

	for(Int_t i=0; i<nTig;i++){ //i - type of Trigger particle
		for(Int_t j=0;j<nPtBins;j++){ //j - pt bin
			fHistRangePtProjPhiEta[i*nPtBins+j]->Divide(fHistRangePtProjPhiEtaMix[i*nPtBins+j]);
			fHistRangePtProjPhiEta[i*nPtBins+j]->SetAxisRange(-1,1,"x"); 

			//d->cd(i*nPtBins+j+1);
			//fHistRangePtProjPhiEta[i*nPtBins+j]->DrawCopy("lego2z");

			fHistProjPhi[i*nPtBins+j]=(TH1D *)fHistRangePtProjPhiEta[i*nPtBins+j]->ProjectionY();

			if (i==0) fHistProjPhi[i*nPtBins+j]->Scale(1./fHistPart[j]->GetBinContent(1));
			if (i==1) fHistProjPhi[i*nPtBins+j]->Scale(1./(fHistPart[j]->GetBinContent(2)+fHistPart[j]->GetBinContent(3)));
			if (i==2) fHistProjPhi[i*nPtBins+j]->Scale(1./fHistPart[j]->GetBinContent(4));
            
			fHistProjPhi[i*nPtBins+j]->SetXTitle("#Delta #Phi");
			fHistProjPhi[i*nPtBins+j]->SetYTitle("# parov / # trigger castic");
			sprintf(nameprojphi,"Rozdelenie #Delta #Phi pre trigger %d pre pt bin %d", i+1,j+1);
			fHistProjPhi[i*nPtBins+j]->SetTitle(nameprojphi);
			e->cd(i*nPtBins+j+1);
			fHistProjPhi[i*nPtBins+j]->DrawCopy();

			fHistProjEta[i*nPtBins+j]=fHistRangePtProjPhiEta[i*nPtBins+j]->ProjectionX();

            if (i==0) fHistProjEta[i*nPtBins+j]->Scale(1./fHistPart[j]->GetBinContent(1));
            if (i==1) fHistProjEta[i*nPtBins+j]->Scale(1./(fHistPart[j]->GetBinContent(2)+fHistPart[j]->GetBinContent(3)));
            if (i==2) fHistProjEta[i*nPtBins+j]->Scale(1./fHistPart[j]->GetBinContent(4));
			fHistProjEta[i*nPtBins+j]->SetXTitle("#Delta #eta");
			fHistProjEta[i*nPtBins+j]->SetYTitle("# parov / # trigger castic");
			sprintf(nameprojeta,"Rozdelenie #Delta #eta pre trigger %d pre pt bin %d", i+1, j+1);
			fHistProjEta[i*nPtBins+j]->SetTitle(nameprojeta);
			f->cd(i*nPtBins+j+1);
			fHistProjEta[i*nPtBins+j]->DrawCopy();

			Double_t val1 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) );
			Double_t val2 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) +1);
			Double_t val3 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) -1);
			Double_t val4 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1));
			Double_t val5 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1)+1);
			Double_t val6 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1)-1);

		
			poz = (val1+val2+val3+val4+val5+val6)/6;
			cout << poz<< endl;

			TF1 *fFuncBack = new TF1("fFuncBack"," [0]",-kPi/2, -kPi/2+2*kPi);
			fFuncBack->SetParameter(0,poz);
			fHistProjPhi[i*nPtBins+j]->Add(fFuncBack,-1);

			Double_t max = fHistProjPhi[i*nPtBins+j]->GetMaximum();
			fHistProjPhi[i*nPtBins+j]->SetAxisRange(0.,max*1.1,"y");
			fHistProjPhi[i*nPtBins+j]->SetXTitle("#Delta #phi");
			fHistProjPhi[i*nPtBins+j]->SetYTitle("pocet parov / pocet trigrovacich castic");
			fHistProjPhi[i*nPtBins+j]->Scale(1/0.803);
			fHistProjPhi[i*nPtBins+j]->GetXaxis()->SetTitleOffset(0.4);
			fHistProjPhi[i*nPtBins+j]->GetXaxis()->SetTitleSize(0.08);
			fHistProjPhi[i*nPtBins+j]->GetXaxis()->SetLabelSize(0.055);
			fHistProjPhi[i*nPtBins+j]->GetYaxis()->SetTitleOffset(0.7);
			fHistProjPhi[i*nPtBins+j]->GetYaxis()->SetTitleSize(0.055);
			fHistProjPhi[i*nPtBins+j]->GetYaxis()->SetLabelSize(0.055);
			fHistProjPhi[i*nPtBins+j]->GetYaxis()->SetLabelOffset(0.004);

			if (i==0){
				if(j==0) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 4 GeV/c<p_{T}^{trig}<5 GeV/c");
				if(j==1) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 5 GeV/c<p_{T}^{trig}<6 GeV/c");
				if(j==2) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 6 GeV/c<p_{T}^{trig}<7 GeV/c");
				if(j==3) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 7 GeV/c<p_{T}^{trig}<9 GeV/c");
				if(j==4) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 9 GeV/c<p_{T}^{trig}<11 GeV/c");
				if(j==5) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 11 GeV/c<p_{T}^{trig}<15 GeV/c");
				fHistProjPhi[i*nPtBins+j]->SetTitle(bezpoz);
				canK->cd(j+1);
				fHistProjPhi[i*nPtBins+j]->DrawCopy();
			}

			if (i==1) {
				if(j==0) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 4 GeV/c<p_{T}^{trig}<5 GeV/c");
				if(j==1) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 5 GeV/c<p_{T}^{trig}<6 GeV/c");
				if(j==2) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 6 GeV/c<p_{T}^{trig}<7 GeV/c");
				if(j==3) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 7 GeV/c<p_{T}^{trig}<9 GeV/c");
				if(j==4) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 9 GeV/c<p_{T}^{trig}<11 GeV/c");
				if(j==5) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 11 GeV/c<p_{T}^{trig}<15 GeV/c");
				fHistProjPhi[i*nPtBins+j]->SetTitle(bezpoz);
				canLam->cd(j+1);
				fHistProjPhi[i*nPtBins+j]->DrawCopy();
			}


			if (i==2){
				if(j==0) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 4 GeV/c<p_{T}^{trig}<5 GeV/C");
				if(j==1) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 5 GeV/c<p_{T}^{trig}<6 GeV/C");
				if(j==2) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 6 GeV/c<p_{T}^{trig}<7 GeV/C");
				if(j==3) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 7 GeV/c<p_{T}^{trig}<9 GeV/C");
				if(j==4) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 9 GeV/c<p_{T}^{trig}<11 GeV/C");
				if(j==5) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 11 GeV/c<p_{T}^{trig}<15 GeV/C");
				fHistProjPhi[i*nPtBins+j]->SetTitle(bezpoz);
				canH->cd(j+1);
				fHistProjPhi[i*nPtBins+j]->DrawCopy();

			}

			Int_t minnear = (fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-0.9);
			Int_t maxnear = (fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(0.9);
			Double_t widthnear = fHistProjPhi[i*nPtBins+j]->GetBinWidth(maxnear);
			Double_t integralnear =0.;
			Double_t errornear =0.;

			for(Int_t k=minnear; k<maxnear; k++){
				integralnear+= fHistProjPhi[i*nPtBins+j]->GetBinContent(k);
				errornear+= fHistProjPhi[i*nPtBins+j]->GetBinError(k);
			} 
			
			yieldnearerror[i][j] = TMath::Sqrt(errornear);
			yieldnearerror[i][j] = yieldnearerror[i][j] *widthnear;
			integralnear=integralnear*widthnear;
			yieldnear[i][j] = integralnear;

			Int_t minaway = (fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(kPi-1.5);
			Int_t maxaway = (fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(kPi+1.5);
			Double_t widthaway = fHistProjPhi[i*nPtBins+j]->GetBinWidth(maxaway);
			Double_t integralaway =0.;
			Double_t erroralaway =0.;

			for(Int_t k=minaway; k<maxaway; k++){
				integralaway+= fHistProjPhi[i*nPtBins+j]->GetBinContent(k);
				erroralaway+= fHistProjPhi[i*nPtBins+j]->GetBinError(k);
			} 
			
			yieldawayerror[i][j] = TMath::Sqrt(erroralaway);
			yieldawayerror[i][j] = yieldawayerror[i][j] *widthaway;
			integralaway=integralaway*widthaway;
			yieldaway[i][j] = integralaway;
			

			cout << "yield near side  = "<< yieldnear[i][j] << "  yield away side = " << yieldaway[i][j] << endl;
			delete fFuncBack;

		}
		
	}

	Double_t PtGraph[nPtBins] = {4.5, 5.5, 6.5, 8, 10, 13};
	Double_t PtHist[nPtBins+1] = {4, 5, 6, 7, 9, 11, 15};
	Double_t PtError[nPtBins] = {0.5, 0.5, 0.5, 1, 1, 2};

	TFile *fFile = TFile::Open("GraphMC.root","RECREATE");

	TH1D *fHistK0Near = new TH1D("fHistK0Near","fHistK0Near",nPtBins,PtHist);
	TH1D *fHistLambdaNear = new TH1D("fHistLambdaNear","fHistLambdaNear",nPtBins,PtHist);
	TH1D *fHistHadronNear = new TH1D("fHistHadronNear","fHistHadronNear",nPtBins,PtHist);


	for(Int_t i=0; i<nPtBins; i++ ){

		fHistK0Near->Fill(PtGraph[i], yieldnear[0][i]); 
		fHistK0Near->SetBinError(i+1,yieldnearerror[0][i]);

		fHistLambdaNear->Fill(PtGraph[i], yieldnear[1][i]); 
		fHistLambdaNear->SetBinError(i+1,yieldnearerror[1][i]);

	//	fHistAntiLambdaNear->Fill(PtGraph[i], yieldnear[2][i]); 
	//	fHistAntiLambdaNear->SetBinError(i+1,yieldnearerror[2][i]);

		fHistHadronNear->Fill(PtGraph[i], yieldnear[2][i]); 
		fHistHadronNear->SetBinError(i+1,yieldnearerror[2][i]);

	}

	fHistK0Near->Write();
	fHistLambdaNear->Write();
	fHistHadronNear->Write();
	
	TGraphErrors *fGraphK0Near = new TGraphErrors(nPtBins,PtGraph,yieldnear[0],PtError,yieldnearerror[0]);
	TGraphErrors *fGraphLambdaNear = new TGraphErrors(nPtBins,PtGraph,yieldnear[1],PtError,yieldnearerror[1]);
	TGraphErrors *fGraphTrackNear = new TGraphErrors(nPtBins,PtGraph,yieldnear[2],PtError,yieldnearerror[2]);

	fGraphK0Near->SetName("fGraphK0Near");
	fGraphLambdaNear->SetName("fGraphLambdaNear");
	fGraphTrackNear->SetName("fGraphTrackNear");
	
	fGraphK0Near->SetMarkerStyle(23);
	fGraphK0Near->SetMarkerColor(kBlue);
	fGraphK0Near->SetMarkerSize(1.8);
	fGraphK0Near->SetLineColor(kBlue);
	fGraphK0Near->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik");
	fGraphK0Near->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	fGraphK0Near->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
	fGraphK0Near->GetYaxis()->SetRangeUser(-0.1,1);

	fGraphLambdaNear->SetMarkerStyle(21);
	fGraphLambdaNear->SetMarkerColor(kGreen);
	fGraphLambdaNear->SetMarkerSize(1.8);
	fGraphLambdaNear->SetLineColor(kGreen);

	fGraphTrackNear->SetMarkerStyle(29);
	fGraphTrackNear->SetMarkerColor(kRed);
	fGraphTrackNear->SetMarkerSize(1.8);
	fGraphTrackNear->SetLineColor(kRed);

	TLegend *fLegendNear = new TLegend(0.2,0.9,0.75,0.8);
	fLegendNear->AddEntry(fGraphK0Near,"Triger K^{0}_{S}","pl");	
	fLegendNear->AddEntry(fGraphLambdaNear,"Triger #Lambda a #bar{#Lambda}","pl");	
	fLegendNear->AddEntry(fGraphTrackNear,"Triger nabity hadron","pl");	

	fGraphK0Near->Write();
	fGraphTrackNear->Write();
	fGraphLambdaNear->Write();

	TCanvas *canNear = new TCanvas;
	fGraphK0Near->Draw("ap");
	fGraphLambdaNear->Draw("pSAME");
	fGraphTrackNear->Draw("pSAME");
	fLegendNear->Draw();

	TGraphErrors *fGraphK0Away = new TGraphErrors(nPtBins,PtGraph,yieldaway[0],PtError,yieldawayerror[0]);
	TGraphErrors *fGraphLambdaAway = new TGraphErrors(nPtBins,PtGraph,yieldaway[1],PtError,yieldawayerror[1]);
	TGraphErrors *fGraphTrackAway = new TGraphErrors(nPtBins,PtGraph,yieldaway[2],PtError,yieldawayerror[2]);
	
	fGraphK0Away->SetMarkerStyle(23);
	fGraphK0Away->SetMarkerColor(kBlue);
	fGraphK0Away->SetMarkerSize(1.8);
	fGraphK0Away->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik");
	fGraphK0Away->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	fGraphK0Away->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
	fGraphK0Away->SetLineColor(kBlue);
	fGraphK0Away->GetYaxis()->SetRangeUser(-0.1,1);

	fGraphLambdaAway->SetMarkerStyle(21);
	fGraphLambdaAway->SetMarkerColor(kGreen);
	fGraphLambdaAway->SetMarkerSize(1.8);
	fGraphLambdaAway->SetLineColor(kGreen);

	fGraphTrackAway->SetMarkerStyle(29);
	fGraphTrackAway->SetMarkerColor(kRed);
	fGraphTrackAway->SetMarkerSize(1.8);
	fGraphTrackAway->SetLineColor(kRed);

	TLegend *fLegendAway = new TLegend(0.2,0.9,0.75,0.8);
	fLegendAway->AddEntry(fGraphK0Away,"Triger K^{0}_{S}","pl");	
	fLegendAway->AddEntry(fGraphLambdaAway,"Triger #Lambda a #bar{#Lambda}","pl");		
	fLegendAway->AddEntry(fGraphTrackAway,"Triger nabity hadron","pl");	

	TCanvas *canAway = new TCanvas;
	fGraphK0Away->Draw("ap");
	fGraphLambdaAway->Draw("pSAME");
	fGraphTrackAway->Draw("pSAME");
	fLegendAway->Draw();

	 fFile->Close();
	
}

