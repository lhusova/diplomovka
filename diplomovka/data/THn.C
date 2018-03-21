#include <TH1D.h>
#include <TH2D.h>
#include <THnSparse.h>
#include <stdio.h>
#include <TFile.h>
#include "TMath.h"

void THn(){
	gStyle->SetOptStat(0000000000);

    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsDataNajnovsie03.root");
	TList *list = (TList*) g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
    
    TFile *gg = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/EfiiciencyMC15c_07.root");
	
    THnSparse *fHistKorelacie = (THnSparse*)list->FindObject("fHistKorelacie");
	THnSparse *fHistdPhidEtaMix = (THnSparse*)list->FindObject("fHistdPhidEtaMix");
    THnSparse *fHistNumberOfTriggers = (THnSparse*)list->FindObject("fHistNumberOfTriggers");
    
   // THnSparse *fHistKorelacie = (THnSparse*)list->FindObject("fHistKorelacieMCrec");
   // THnSparse *fHistNumberOfTriggers = (THnSparse*)list->FindObject("fHistNumberOfTriggersRec");
   // THnSparse *fHistdPhidEtaMix = (THnSparse*)list->FindObject("fHistMCMixingRec");
    
    TH3D *fHistRCPtAs = (TH3D*) gg->Get("fHistRCPtAs");
    TH3D *fHistRCPtTrigg = (TH3D*) gg->Get("fHistRCPtTrigg");
    TH3D *fHistEff3DK0 = (TH3D*) gg->Get("fHistRecV03DK0");
    TH3D *fHistEff3DLam = (TH3D*) gg->Get("fHistRecV03DLam");
    TH3D *fHistEff3DALam = (TH3D*) gg->Get("fHistRecV03DAntiLam");

	const Double_t kPi = TMath::Pi();

	//fHistNumberOfTriggers->Sumw2();

	const Int_t nPtBins = 6;
	const Int_t nTig =3;
    
    const Int_t nMuliplBins = fHistKorelacie->GetAxis(10)->GetNbins();

    const Int_t nEtaBins = fHistKorelacie->GetAxis(7)->GetNbins();
    const Int_t nVzBins = fHistKorelacie->GetAxis(4)->GetNbins();
    const Int_t nPtAssocBins = fHistKorelacie->GetAxis(1)->GetNbins();

	TH1D **fHistPart = new TH1D*[nPtBins*nMuliplBins];
	THnSparse **fHistPartClone = new THnSparse*[nPtBins*nMuliplBins];
	char hnameent[50];
	TCanvas *a = new TCanvas;
	a->Divide(nMuliplBins,nPtBins);
    
    TH1D **fHistNumberOfTrigg = new TH1D*[nTig*nPtBins*nMuliplBins];
    
    Double_t sclaleAssoc[10][10][13];
    Double_t sclaleTrigg[10][10][11];
    Double_t sclaleK0[10][10][11];
    Double_t sclaleLam[10][10][11];
    Double_t sclaleAntiL[10][10][11];

    Int_t k3D =0;
     for(Int_t k=0;k<nEtaBins; k++){
         Int_t l3D =0;
         for (Int_t l=0; l<nVzBins; l++) {
             for (Int_t m=0; m<nPtAssocBins; m++){
                 sclaleAssoc[k3D][l3D][m]=fHistRCPtAs->GetBinContent(m+1,l3D+1,k3D+1);
             }
             for (Int_t m=0; m<nPtBins; m++){
                 sclaleTrigg[k3D][l3D][m]=fHistRCPtTrigg->GetBinContent(m+1,l3D+1,k3D+1);
                 sclaleK0[k3D][l3D][m]=fHistEff3DK0->GetBinContent(m+1,l3D+1,k3D+1);
                 sclaleLam[k3D][l3D][m]=fHistEff3DLam->GetBinContent(m+1,l3D+1,k3D+1);
                 sclaleAntiL[k3D][l3D][m]=fHistEff3DALam->GetBinContent(m+1,l3D+1,k3D+1);
                 
                 if (m==0||m==1||m==2) {
                     sclaleTrigg[k3D][l3D][m]=fHistRCPtTrigg->GetBinContent(m+1,l3D+1,k3D+1);
                     sclaleK0[k3D][l3D][m]=fHistEff3DK0->GetBinContent(m+1,l3D+1,k3D+1);
                     sclaleLam[k3D][l3D][m]=fHistEff3DLam->GetBinContent(m+1,l3D+1,k3D+1);
                     sclaleAntiL[k3D][l3D][m]=fHistEff3DALam->GetBinContent(m+1,l3D+1,k3D+1);
                     
                 }
                 if (m==3){
                     sclaleTrigg[k3D][l3D][m] = (fHistRCPtTrigg->GetBinContent(4,l3D+1,k3D+1)+fHistRCPtTrigg->GetBinContent(5,l3D+1,k3D+1))/2;
                     sclaleK0[k3D][l3D][m]=(fHistEff3DK0->GetBinContent(4,l3D+1,k3D+1)+fHistEff3DK0->GetBinContent(5,l3D+1,k3D+1))/2;
                     sclaleLam[k3D][l3D][m]=(fHistEff3DLam->GetBinContent(4,l3D+1,k3D+1)+fHistEff3DLam->GetBinContent(5,l3D+1,k3D+1))/2;
                     sclaleAntiL[k3D][l3D][m]=(fHistEff3DALam->GetBinContent(4,l3D+1,k3D+1)+fHistEff3DALam->GetBinContent(5,l3D+1,k3D+1))/2;
                     
                 }
                 if (m==4) {
                     sclaleTrigg[k3D][l3D][m] = (fHistRCPtTrigg->GetBinContent(6,l3D+1,k3D+1)+fHistRCPtTrigg->GetBinContent(7,l3D+1,k3D+1))/2;
                     sclaleK0[k3D][l3D][m]=(fHistEff3DK0->GetBinContent(6,l3D+1,k3D+1)+fHistEff3DK0->GetBinContent(7,l3D+1,k3D+1))/2;
                     sclaleLam[k3D][l3D][m]=(fHistEff3DLam->GetBinContent(6,l3D+1,k3D+1)+fHistEff3DLam->GetBinContent(7,l3D+1,k3D+1))/2;
                     sclaleAntiL[k3D][l3D][m]=(fHistEff3DALam->GetBinContent(6,l3D+1,k3D+1)+fHistEff3DALam->GetBinContent(7,l3D+1,k3D+1))/2;
                     
                 }
                 if (m==5) {
                     sclaleTrigg[k3D][l3D][m] = (fHistRCPtTrigg->GetBinContent(8,l3D+1,k3D+1)+fHistRCPtTrigg->GetBinContent(9,l3D+1,k3D+1)+fHistRCPtTrigg->GetBinContent(10,l3D+1,k3D+1)+fHistRCPtTrigg->GetBinContent(11,l3D+1,k3D+1))/4;
                     sclaleK0[k3D][l3D][m]=(fHistEff3DK0->GetBinContent(8,l3D+1,k3D+1)+fHistEff3DK0->GetBinContent(9,l3D+1,k3D+1)+fHistEff3DK0->GetBinContent(11,l3D+1,k3D+1)+fHistEff3DK0->GetBinContent(9,l3D+1,k3D+1))/4;
                     sclaleLam[k3D][l3D][m]=(fHistEff3DLam->GetBinContent(8,l3D+1,k3D+1)+fHistEff3DLam->GetBinContent(9,l3D+1,k3D+1)+fHistEff3DLam->GetBinContent(10,l3D+1,k3D+1)+fHistEff3DLam->GetBinContent(11,l3D+1,k3D+1))/4;
                     sclaleAntiL[k3D][l3D][m]=(fHistEff3DALam->GetBinContent(8,l3D+1,k3D+1)+fHistEff3DALam->GetBinContent(9,l3D+1,k3D+1)+fHistEff3DALam->GetBinContent(10,l3D+1,k3D+1)+fHistEff3DALam->GetBinContent(11,l3D+1,k3D+1))/4;
                     
                 }
             }
             
             l3D+=1;
             l+=1;
         }
         
         
         k+=3;
         k3D+=1;
     }

	TCanvas *TrigMulti = new TCanvas;
	TrigMulti->Divide(1,3);
	TH1D **fHistMulti = new TH1D*[nTig];
	THnSparse **fHistMultiClone = new THnSparse*[nTig];
	char hnamemulti[100];

	for (Int_t i=0; i<nTig; i++){
		fHistMultiClone[i]=(THnSparse * )fHistNumberOfTriggers->Clone();
		if(i==0) fHistMultiClone[i]->GetAxis(1)->SetRange(1,1);
		if(i==1) fHistMultiClone[i]->GetAxis(1)->SetRange(2,3);
		if(i==2) fHistMultiClone[i]->GetAxis(1)->SetRange(4,4);
		fHistMulti[i] = fHistMultiClone[i]->Projection(0);
		if(i==0) sprintf(hnamemulti, "Zavislost poctu K^{0}_{S} nekorigovane od p_{T}");
		if(i==1) sprintf(hnamemulti, "Zavislost poctu #Lambda a #bar{#Lambda} nekorigovane od p_{T}");
		if(i==2) sprintf(hnamemulti, "Zavislost poctu nabitych trackov nekorigovane od p_{T}");
		sprintf(hnameent,"proj_%d",i);
		fHistMulti[i] -> SetName(hnameent);
		fHistMulti[i] ->SetTitle(hnamemulti);
		fHistMulti[i] ->SetXTitle("p_{T} (GeV)");
		fHistMulti[i] ->SetYTitle("#");
		TrigMulti->cd(i+1);
		fHistMulti[i] ->DrawCopy();
	}
	delete[] fHistMultiClone;

	THnSparse **fHistCorType=new THnSparse*[nTig*nMuliplBins];
	THnSparse **fHistRangePt=new THnSparse*[nTig*nPtBins*nMuliplBins];
	TH2D **fHistRangePtProjPhiEta = new TH2D*[nTig*nPtBins*nMuliplBins];
	char htitle[50];
	char hname[50];
    char hname2dvela[50];
	TCanvas *c = new TCanvas;
	c->Divide(nMuliplBins*nPtBins,nTig);
	
    char hname1dvela[50];
    char nameeff[20];
    
    for(Int_t iMultBin = 0; iMultBin<1;iMultBin++ ){ // loop cez multiplicitne biny
       // fHistKorelacie->GetAxis(10)->SetRange(iMultBin+1,iMultBin+1);
       // fHistNumberOfTriggers->GetAxis(6)->SetRange(iMultBin+1,iMultBin+1);
        
        for(Int_t i=1;i<2;i++){ // loop cez druh triggra

            if(i==0) fHistKorelacie->GetAxis(5)->SetRange(i+1,i+1);
            if(i==1) fHistKorelacie->GetAxis(5)->SetRange(i+1,i+2);
            if(i==2) fHistKorelacie->GetAxis(5)->SetRange(i+2,i+2);
            for(Int_t j=0;j<nPtBins;j++){ // loop cez pt trigger
                
                if (j==0) {
                    fHistKorelacie->GetAxis(0)->SetRange(1,1);
                    fHistNumberOfTriggers->GetAxis(0)->SetRange(1,1);
                }
                if (j==1) {
                    fHistKorelacie->GetAxis(0)->SetRange(2,2);
                    fHistNumberOfTriggers->GetAxis(0)->SetRange(2,2);
                }
                if (j==2){
                    fHistKorelacie->GetAxis(0)->SetRange(3,3);
                    fHistNumberOfTriggers->GetAxis(0)->SetRange(3,3);
                }
                if (j==3) {
                    fHistKorelacie->GetAxis(0)->SetRange(4,5);
                    fHistNumberOfTriggers->GetAxis(0)->SetRange(4,5);
                }
                if (j==4) {
                    fHistKorelacie->GetAxis(0)->SetRange(6,7);
                    fHistNumberOfTriggers->GetAxis(0)->SetRange(6,7);
                }
                if (j==5) {
                    fHistKorelacie->GetAxis(0)->SetRange(8,11);
                    fHistNumberOfTriggers->GetAxis(0)->SetRange(8,11);
                }
                
                sprintf(nameeff,"eff_%d_%d",i,j);
                TH3D *fHistEff = (TH3D*)gg->Get(nameeff);
                
               Int_t l3D =0;
                Int_t nHist =0;
                Int_t nHistTrig =0;
                
                for(Int_t l=0;l<nVzBins ; l++){ //loop cez vertex biny
                    Printf(" ----------- l %d --------------------- \n",l);
                    fHistKorelacie->GetAxis(4)->SetRange(l+1,l+2);
                    
                    fHistNumberOfTriggers->GetAxis(1)->SetRange(l+1,l+2);

                    Int_t k3D =0;
                    
                    for (Int_t k=0; k<nEtaBins; k++) {//loop cez eta trigg
                        fHistKorelacie->GetAxis(6)->SetRange(k+1,k+4);
                        
                        fHistNumberOfTriggers->GetAxis(2)->SetRange(k+1,k+4);
                        TH1D * proj1DTrigg = (TH1D *)fHistNumberOfTriggers->Projection(3);
                        sprintf(hname1dvela,"%d_%d_%d",j,k3D,l3D);
                        proj1DTrigg->SetName(hname1dvela);
                        
                        Printf("+++++ k ++++++ \n" );
                       if(i==0){
                            if(sclaleK0[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(1,proj1DTrigg->GetBinContent(1)/sclaleK0[k3D][l3D][j]);
                        }
                        
                        if(i==1){
                            if(sclaleLam[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(2,proj1DTrigg->GetBinContent(2)/sclaleLam[k3D][l3D][j]);
                            
                            if(sclaleAntiL[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(3,proj1DTrigg->GetBinContent(3)/sclaleAntiL[k3D][l3D][j]);
                        }
                        
                        if(i==2){
                            if(sclaleTrigg[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(4,proj1DTrigg->GetBinContent(4)/sclaleTrigg[k3D][l3D][j]);
                        }
                        if (nHistTrig==0) fHistNumberOfTrigg[iMultBin*nTig+i*nPtBins+j] =(TH1D *)proj1DTrigg->Clone();
                        else fHistNumberOfTrigg[iMultBin*nTig+i*nPtBins+j]->Add(proj1DTrigg);
                        nHistTrig+=1;
                        
                        Int_t n3D =0;
                        for (Int_t n=0; n<nEtaBins; n++) { // loop cez eta assoc
                            
                            fHistKorelacie->GetAxis(7)->SetRange(n+1,n+4);
                            
                            for (Int_t m=0; m<nPtAssocBins; m++){ // loop cez pt assoc
                                
                                fHistKorelacie->GetAxis(1)->SetRange(m+1,m+1);
                            
                                TH2D * proj2DRac = (TH2D *)fHistKorelacie->Projection(2,3);
                                sprintf(hname2dvela,"%d_%d_%d",m,n3D,l3D);
                                proj2DRac->SetName(hname2dvela);
           
                                if (n3D==0&&sclaleAssoc[0][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[0][l3D][m]);
                                if (n3D==1&&sclaleAssoc[1][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[1][l3D][m]);
                                if (n3D==2&&sclaleAssoc[2][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[2][l3D][m]);
                                if (n3D==3&&sclaleAssoc[3][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[3][l3D][m]);
                                if (n3D==4&&sclaleAssoc[4][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[4][l3D][m]);
                                if (n3D==5&&sclaleAssoc[5][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[5][l3D][m]);
                                if (n3D==6&&sclaleAssoc[6][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[6][l3D][m]);
                                if (n3D==7&&sclaleAssoc[7][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[7][l3D][m]);
                                if (n3D==8&&sclaleAssoc[8][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[8][l3D][m]);
                                if (n3D==9&&sclaleAssoc[9][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[9][l3D][m]);
                                
                                if(i==0&&sclaleK0[k3D][l3D][j]!=0){
                                    proj2DRac->Scale(1./sclaleK0[k3D][l3D][j]);
                                }
                                if(i==1&&sclaleLam[k3D][l3D][j]!=0&&sclaleAntiL[k3D][l3D][j]!=0){
                                    Double_t scalelamAntilam = (sclaleLam[k3D][l3D][j]+sclaleAntiL[k3D][l3D][j])/2;
                                    proj2DRac->Scale(1./scalelamAntilam);
                                    
                                }
                                
                                if(i==2&&sclaleTrigg[k3D][l3D][j]!=0){
                                    proj2DRac->Scale(1./sclaleTrigg[k3D][l3D][j]);
                                    
                                }
           
                                if (nHist==0) fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j] =(TH2D *)proj2DRac->Clone();
                                else fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->Add(proj2DRac);
                                nHist+=1;
                                
                                delete proj2DRac;
                                fHistKorelacie->GetAxis(1)->SetRange(0,-1);
                            }
                            
                            fHistKorelacie->GetAxis(7)->SetRange(0,-1);
                            n+=3;
                            n3D+=1;
                            
                        }
                        
                        delete proj1DTrigg;
                        fHistNumberOfTriggers->GetAxis(2)->SetRange(0,-1);
                        fHistKorelacie->GetAxis(6)->SetRange(0,-1);
                        
                        k+=3;
                        k3D+=1;
                        
                    }
                    
                    fHistKorelacie->GetAxis(4)->SetRange(0,-1);
                    fHistNumberOfTriggers->GetAxis(1)->SetRange(0,-1);
                    
                    l3D+=1;
                    l+=1;
                }
           
              //  fHistNumberOfTrigg[iMultBin*nTig+i*nPtBins+j] = (TH1D *)fHistNumberOfTriggers->Projection(3);
              //  fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]=fHistKorelacie->Projection(2,3);
                sprintf(hname,"2dproj_%d_pt_%d_mult_%d",i,j,iMultBin);
                fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->SetName(hname);
                sprintf(htitle,"#Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d, mult. bin %d", i,j, iMultBin);
                fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->SetTitle(htitle);
                fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->RebinX(4);
                fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->RebinY(4);
                c->cd(iMultBin*nTig+i*nPtBins+j+1);
                fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->DrawCopy("lego2z");
                
                fHistKorelacie->GetAxis(0)->SetRange(0,-1);
                fHistNumberOfTriggers->GetAxis(0)->SetRange(0,-1);
                
            }
            fHistKorelacie->GetAxis(5)->SetRange(0,-1);
        }
        
      //  fHistKorelacie->GetAxis(10)->SetRange(0,-1);
      //  fHistNumberOfTriggers->GetAxis(6)->SetRange(0,-1);
    }
	

	//THnSparse **fHistMixType= new THnSparse*[nTig];
	TH2D **fHistRangePtProjPhiEtaMix = new TH2D*[nMuliplBins*nTig*nPtBins];
	char hnamemix[50];
	char htitlemix[100];
	TCanvas *d = new TCanvas;
	d->Divide(nTig,nPtBins);

    for(Int_t iMultBin = 0; iMultBin<1/*nMuliplBins*/;iMultBin++ ){ // loop cez multiplicitne biny
        //fHistdPhidEtaMix->GetAxis(7)->SetRange(iMultBin+1,iMultBin+1);
        
        for(Int_t i=1;i<2;i++){
            //HistMixType[i]=(THnSparse*)fHistdPhidEtaMix->Clone();
            if(i==0) fHistdPhidEtaMix->GetAxis(5)->SetRange(1,1);
            if(i==1) fHistdPhidEtaMix->GetAxis(5)->SetRange(2,3);
            if(i==2) fHistdPhidEtaMix->GetAxis(5)->SetRange(4,4);
            
            for(Int_t j=0;j<nPtBins;j++){
                
                if (j==0) fHistdPhidEtaMix->GetAxis(0)->SetRange(1,1);
                if (j==1) fHistdPhidEtaMix->GetAxis(0)->SetRange(2,2);
                if (j==2) fHistdPhidEtaMix->GetAxis(0)->SetRange(3,3);
                if (j==3) fHistdPhidEtaMix->GetAxis(0)->SetRange(4,5);
                if (j==4) fHistdPhidEtaMix->GetAxis(0)->SetRange(6,7);
                if (j==5) fHistdPhidEtaMix->GetAxis(0)->SetRange(8,11);
                
                fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j] = fHistdPhidEtaMix->Projection(2,3);
                
                sprintf(hnamemix,"2dproj_mix_%d_pt_%d_mult_%d",i,j,iMultBin);
                fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->SetName(hnamemix);
                sprintf(htitlemix,"#Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d, mult bin %d, mixed", i,j,iMultBin);
                fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->SetTitle(htitlemix);
                fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->RebinX(4);
                fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->RebinY(4);
                Double_t maximum = fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->GetMaximum();
                
                Int_t nPhiBins = fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->GetYaxis()->GetNbins();
                Int_t bin0 =fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->GetXaxis()->FindBin(0.);
                Double_t scale=0.;
                for(Int_t iBinPhi=0; iBinPhi<nPhiBins; iBinPhi++){
                    scale+=fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->GetBinContent(bin0,iBinPhi+1);
                }
                scale=scale/nPhiBins;
                
                Printf("maximum %g, priemer %g \n", maximum,scale);
                fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->Scale(1./scale);
                d->cd(i*nPtBins+j+1);
                fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]->DrawCopy("lego2z");
                
                fHistdPhidEtaMix->GetAxis(0)->SetRange(0,-1);
            }
             fHistdPhidEtaMix->GetAxis(5)->SetRange(0,-1);
        }
        
      //  fHistdPhidEtaMix->GetAxis(7)->SetRange(0,-1);
    }
	//delete fHistMixType;

	TH1D **fHistProjPhi = new TH1D*[nMuliplBins*nPtBins*nTig];
	TH1D **fHistProjEta = new TH1D*[nMuliplBins*nPtBins*nTig];
	TCanvas *e = new TCanvas;
	e->Divide(nMuliplBins*nPtBins,nTig);
	TCanvas *f = new TCanvas;
	f->Divide(nMuliplBins*nPtBins,nTig);
	TCanvas *canK = new TCanvas;
	canK->Divide(nMuliplBins,nPtBins);
	TCanvas *canLam = new TCanvas;
	canLam->Divide(nMuliplBins,nPtBins);
	TCanvas *canAntiLam = new TCanvas;
	canAntiLam->Divide(nMuliplBins,nPtBins);
	TCanvas *canH = new TCanvas;
	canH->Divide(nMuliplBins,nPtBins);

	char hnamephi[50];
	Double_t yieldnear[nMuliplBins][nTig][nPtBins];
	Double_t yieldaway[nMuliplBins][nTig][nPtBins];
	Double_t yieldnearerror[nMuliplBins][nTig][nPtBins];
	Double_t yieldawayerror[nMuliplBins][nTig][nPtBins];
	char nameprojphi[20];
    char nameprojeta[20];
    char titleprojphi[100];
	char titleprojeta[100];
	char bezpoz[150];
	Double_t poz=0;
    char nameproj2D[20];
    char triggname[20];

	TH1D **fHistBack = new TH1D*[nTig];
	TFile *fFile = TFile::Open("GraphMC_2015c_07_averageMixingLam.root","RECREATE");
	
    for(Int_t iMultBin = 0; iMultBin<1;iMultBin++ ){ // loop cez multiplicitne biny
        for(Int_t i=1; i<2;i++){ //i - type of Trigger particle
            for(Int_t j=0;j<nPtBins;j++){ //j - pt bin
                fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->Divide(fHistRangePtProjPhiEtaMix[iMultBin*nTig+i*nPtBins+j]);
                
                sprintf(nameproj2D, "2dproj_%d_%d_%d",iMultBin,i,j);
                fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->SetName(nameproj2D);
                fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->Write();
                
                sprintf(triggname, "1dtrigg_%d_%d_%d",iMultBin,i,j);
                fHistNumberOfTrigg[iMultBin*nTig+i*nPtBins+j]->SetName(triggname);
                fHistNumberOfTrigg[iMultBin*nTig+i*nPtBins+j]->Write();
                
                if (i==0) fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->Scale(1./fHistNumberOfTrigg[iMultBin*nTig+i*nPtBins+j]->GetBinContent(1));
                if (i==1) fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->Scale(1./(fHistNumberOfTrigg[iMultBin*nTig+i*nPtBins+j]->GetBinContent(2)+fHistNumberOfTrigg[iMultBin*nTig+i*nPtBins+j]->GetBinContent(3)));
                if (i==2) fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->Scale(1./fHistNumberOfTrigg[iMultBin*nTig+i*nPtBins+j]->GetBinContent(4));
                
              //
                //Printf("dd\n");
                //d->cd(i*nPtBins+j+1);
                //fHistRangePtProjPhiEta[i*nPtBins+j]->DrawCopy("lego2z");
                
                //Printf("ee\n");
                
                 fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->SetAxisRange(-1,1,"x");
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]=(TH1D *)fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->ProjectionY();
                
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetXTitle("#Delta #Phi");
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetYTitle("# parov / # trigger castic");
                sprintf(titleprojphi,"Rozdelenie #Delta #Phi pre trigger %d pre pt bin %d, mult bin %d", i+1,j+1,iMultBin+1);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetTitle(titleprojphi);
                sprintf(nameprojphi,"projPhi_%d_%d_%d",i+1,j+1,iMultBin+1);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetName(nameprojphi);
                e->cd(iMultBin*nTig+i*nPtBins+j+1);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->DrawCopy();
                
                fHistProjEta[iMultBin*nTig+i*nPtBins+j]=fHistRangePtProjPhiEta[iMultBin*nTig+i*nPtBins+j]->ProjectionX();
                
                fHistProjEta[iMultBin*nTig+i*nPtBins+j]->SetXTitle("#Delta #eta");
                fHistProjEta[iMultBin*nTig+i*nPtBins+j]->SetYTitle("# parov / # trigger castic");
                sprintf(titleprojeta,"Rozdelenie #Delta #eta pre trigger %d pre pt bin %d, mult bin %d", i+1, j+1,iMultBin+1);
                fHistProjEta[iMultBin*nTig+i*nPtBins+j]->SetTitle(titleprojeta);
                sprintf(nameprojeta,"projPhi_%d_%d_%d",i+1,j+1,iMultBin+1);
                fHistProjEta[iMultBin*nTig+i*nPtBins+j]->SetName(nameprojeta);
                f->cd(iMultBin*nTig+i*nPtBins+j+1);
                fHistProjEta[iMultBin*nTig+i*nPtBins+j]->DrawCopy();
                
                Double_t val1 = fHistProjPhi[iMultBin*nTig+i*nPtBins+j] -> GetBinContent((fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(1) );
                Double_t val2 = fHistProjPhi[iMultBin*nTig+i*nPtBins+j] -> GetBinContent((fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(1) +1);
                Double_t val3 = fHistProjPhi[iMultBin*nTig+i*nPtBins+j] -> GetBinContent((fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(1) -1);
                Double_t val4 = fHistProjPhi[iMultBin*nTig+i*nPtBins+j] -> GetBinContent((fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(-1));
                Double_t val5 = fHistProjPhi[iMultBin*nTig+i*nPtBins+j] -> GetBinContent((fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(-1)+1);
                Double_t val6 = fHistProjPhi[iMultBin*nTig+i*nPtBins+j] -> GetBinContent((fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(-1)-1);
                
                
                poz = (val1+val2+val3+val4+val5+val6)/6;
                cout << poz<< endl;
                
                TF1 *fFuncBack = new TF1("fFuncBack"," [0]",-kPi/2, -kPi/2+2*kPi);
                fFuncBack->SetParameter(0,poz);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->Add(fFuncBack,-1);
                
                Double_t max = fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetMaximum();
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetAxisRange(0.,max*1.1,"y");
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetXTitle("#Delta #phi");
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetYTitle("pocet parov / pocet trigrovacich castic");
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis()->SetTitleOffset(0.4);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis()->SetTitleSize(0.08);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis()->SetLabelSize(0.055);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetYaxis()->SetTitleOffset(0.7);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetYaxis()->SetTitleSize(0.055);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetYaxis()->SetLabelSize(0.055);
                fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetYaxis()->SetLabelOffset(0.004);
                
                if (i==0){
                    if(j==0) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 4 GeV/c<p_{T}^{trig}<5 GeV/c, mult bin %d",iMultBin);
                    if(j==1) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 5 GeV/c<p_{T}^{trig}<6 GeV/c, mult bin %d",iMultBin);
                    if(j==2) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 6 GeV/c<p_{T}^{trig}<7 GeV/c, mult bin %d",iMultBin);
                    if(j==3) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 7 GeV/c<p_{T}^{trig}<9 GeV/c, mult bin %d",iMultBin);
                    if(j==4) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 9 GeV/c<p_{T}^{trig}<11 GeV/c, mult bin %d",iMultBin);
                    if(j==5) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 11 GeV/c<p_{T}^{trig}<15 GeV/c, mult bin %d",iMultBin);
                    fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetTitle(bezpoz);
                    canK->cd(iMultBin*nPtBins+j+1);
                    fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->DrawCopy();
                    fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->Write();
                }
                
                if (i==1) {
                    if(j==0) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 4 GeV/c<p_{T}^{trig}<5 GeV/c, mult bin %d",iMultBin);
                    if(j==1) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 5 GeV/c<p_{T}^{trig}<6 GeV/c, mult bin %d",iMultBin);
                    if(j==2) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 6 GeV/c<p_{T}^{trig}<7 GeV/c, mult bin %d",iMultBin);
                    if(j==3) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 7 GeV/c<p_{T}^{trig}<9 GeV/c, mult bin %d",iMultBin);
                    if(j==4) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 9 GeV/c<p_{T}^{trig}<11 GeV/c, mult bin %d",iMultBin);
                    if(j==5) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 11 GeV/c<p_{T}^{trig}<15 GeV/c, mult bin %d",iMultBin);
                    fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetTitle(bezpoz);
                    canLam->cd(iMultBin*nPtBins+j+1);
                    fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->DrawCopy();
                    fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->Write();
                }
                
                
                if (i==2){
                    if(j==0) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 4 GeV/c<p_{T}^{trig}<5 GeV/C, mult bin %d",iMultBin);
                    if(j==1) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 5 GeV/c<p_{T}^{trig}<6 GeV/C, mult bin %d",iMultBin);
                    if(j==2) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 6 GeV/c<p_{T}^{trig}<7 GeV/C, mult bin %d",iMultBin);
                    if(j==3) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 7 GeV/c<p_{T}^{trig}<9 GeV/C, mult bin %d",iMultBin);
                    if(j==4) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 9 GeV/c<p_{T}^{trig}<11 GeV/C, mult bin %d",iMultBin);
                    if(j==5) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 11 GeV/c<p_{T}^{trig}<15 GeV/C, mult bin %d",iMultBin);
                    fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->SetTitle(bezpoz);
                    canH->cd(iMultBin*nPtBins+j+1);
                    fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->DrawCopy();
                    fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->Write();
                    
                }
                
                Int_t minnear = (fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(-0.9);
                Int_t maxnear = (fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(0.9);
                Double_t widthnear = fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetBinWidth(maxnear);
                Double_t integralnear =0.;
                Double_t errornear =0.;
                
                for(Int_t k=minnear; k<maxnear; k++){
                    integralnear+= fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetBinContent(k);
                    errornear+= TMath::Power(fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetBinError(k),2);
                }
                
                yieldnearerror[iMultBin][i][j] = TMath::Sqrt(errornear);
                yieldnearerror[iMultBin][i][j] = yieldnearerror[iMultBin][i][j] *widthnear;
                integralnear=integralnear*widthnear;
                yieldnear[iMultBin][i][j] = integralnear;
                
                Int_t minaway = (fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(kPi-1.5);
                Int_t maxaway = (fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetXaxis())->FindBin(kPi+1.5);
                Double_t widthaway = fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetBinWidth(maxaway);
                Double_t integralaway =0.;
                Double_t erroralaway =0.;
                
                for(Int_t k=minaway; k<maxaway; k++){
                    integralaway+= fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetBinContent(k);
                    erroralaway+= TMath::Power(fHistProjPhi[iMultBin*nTig+i*nPtBins+j]->GetBinError(k),2);
                }
                
                yieldawayerror[iMultBin][i][j] = TMath::Sqrt(erroralaway);
                yieldawayerror[iMultBin][i][j] = yieldawayerror[iMultBin][i][j] *widthaway;
                integralaway=integralaway*widthaway;
                yieldaway[iMultBin][i][j] = integralaway;
                
                
                cout << "yield near side  = "<< yieldnear[iMultBin][i][j] << "  yield away side = " << yieldaway[iMultBin][i][j] << endl;
                delete fFuncBack;
                
            }
            
        }
        
    }

	Double_t PtGraph[nPtBins] = {4.5, 5.5, 6.5, 8, 10, 13};
	Double_t PtHist[nPtBins+1] = {4, 5, 6, 7, 9, 11, 15};
	Double_t PtError[nPtBins] = {0.5, 0.5, 0.5, 1, 1, 2};

	TH1D *fHistK0Near1 = new TH1D("fHistK0Near1","fHistK0Near1",nPtBins,PtHist);
	TH1D *fHistLambdaNear1 = new TH1D("fHistLambdaNear1","fHistLambdaNear1",nPtBins,PtHist);
	TH1D *fHistHadronNear1 = new TH1D("fHistHadronNear1","fHistHadronNear1",nPtBins,PtHist);
    
    TH1D *fHistK0Near2 = new TH1D("fHistK0Near2","fHistK0Near2",nPtBins,PtHist);
    TH1D *fHistLambdaNear2 = new TH1D("fHistLambdaNear2","fHistLambdaNear2",nPtBins,PtHist);
    TH1D *fHistHadronNear2 = new TH1D("fHistHadronNear2","fHistHadronNear2",nPtBins,PtHist);
    
    TH1D *fHistK0Near3 = new TH1D("fHistK0Nea3r","fHistK0Near3",nPtBins,PtHist);
    TH1D *fHistLambdaNear3 = new TH1D("fHistLambdaNear3","fHistLambdaNear3",nPtBins,PtHist);
    TH1D *fHistHadronNear3 = new TH1D("fHistHadronNear3","fHistHadronNear3",nPtBins,PtHist);
    
    TH1D *fHistK0Away1 = new TH1D("fHistK0Away1","fHistK0Away1",nPtBins,PtHist);
    TH1D *fHistLambdaAway1 = new TH1D("fHistLambdaAway1","fHistLambdaAway1",nPtBins,PtHist);
    TH1D *fHistHadronAway1 = new TH1D("fHistHadronAway1","fHistHadronAway1",nPtBins,PtHist);
    
    TH1D *fHistK0Away2 = new TH1D("fHistK0Away2","fHistK0Away2",nPtBins,PtHist);
    TH1D *fHistLambdaAway2 = new TH1D("fHistLambdaAway2","fHistLambdaAway2",nPtBins,PtHist);
    TH1D *fHistHadronAway2 = new TH1D("fHistHadronAway2","fHistHadronAway2",nPtBins,PtHist);
    
    TH1D *fHistK0Away3 = new TH1D("fHistK0Away3","fHistK0Away3",nPtBins,PtHist);
    TH1D *fHistLambdaAway3 = new TH1D("fHistLambdaAway3","fHistLambdaAway3",nPtBins,PtHist);
    TH1D *fHistHadronAway3 = new TH1D("fHistHadronAway3","fHistHadronAway3",nPtBins,PtHist);


	for(Int_t i=0; i<nPtBins; i++ ){

		fHistK0Near1->Fill(PtGraph[i], yieldnear[0][0][i]);
		fHistK0Near1->SetBinError(i+1,yieldnearerror[0][0][i]);
        fHistK0Near2->Fill(PtGraph[i], yieldnear[1][0][i]);
        fHistK0Near2->SetBinError(i+1,yieldnearerror[1][0][i]);
        fHistK0Near3->Fill(PtGraph[i], yieldnear[2][0][i]);
        fHistK0Near3->SetBinError(i+1,yieldnearerror[2][0][i]);

		fHistLambdaNear1->Fill(PtGraph[i], yieldnear[0][1][i]);
		fHistLambdaNear1->SetBinError(i+1,yieldnearerror[0][1][i]);
        fHistLambdaNear2->Fill(PtGraph[i], yieldnear[1][1][i]);
        fHistLambdaNear2->SetBinError(i+1,yieldnearerror[1][1][i]);
        fHistLambdaNear3->Fill(PtGraph[i], yieldnear[2][1][i]);
        fHistLambdaNear3->SetBinError(i+1,yieldnearerror[2][1][i]);

		fHistHadronNear1->Fill(PtGraph[i], yieldnear[0][2][i]);
		fHistHadronNear1->SetBinError(i+1,yieldnearerror[0][2][i]);
        fHistHadronNear2->Fill(PtGraph[i], yieldnear[1][2][i]);
        fHistHadronNear2->SetBinError(i+1,yieldnearerror[1][2][i]);
        fHistHadronNear3->Fill(PtGraph[i], yieldnear[2][2][i]);
        fHistHadronNear3->SetBinError(i+1,yieldnearerror[2][2][i]);
        
        fHistK0Away1->Fill(PtGraph[i], yieldaway[0][0][i]);
        fHistK0Away1->SetBinError(i+1,yieldawayerror[0][0][i]);
        fHistK0Away2->Fill(PtGraph[i], yieldaway[1][0][i]);
        fHistK0Away2->SetBinError(i+1,yieldawayerror[1][0][i]);
        fHistK0Away3->Fill(PtGraph[i], yieldaway[2][0][i]);
        fHistK0Away3->SetBinError(i+1,yieldawayerror[2][0][i]);
        
        fHistLambdaAway1->Fill(PtGraph[i], yieldaway[0][1][i]);
        fHistLambdaAway1->SetBinError(i+1,yieldawayerror[0][1][i]);
        fHistLambdaAway2->Fill(PtGraph[i], yieldaway[1][1][i]);
        fHistLambdaAway2->SetBinError(i+1,yieldawayerror[1][1][i]);
        fHistLambdaAway3->Fill(PtGraph[i], yieldaway[2][1][i]);
        fHistLambdaAway3->SetBinError(i+1,yieldawayerror[2][1][i]);
        
        fHistHadronAway1->Fill(PtGraph[i], yieldaway[0][2][i]);
        fHistHadronAway1->SetBinError(i+1,yieldawayerror[0][2][i]);
        fHistHadronAway2->Fill(PtGraph[i], yieldaway[1][2][i]);
        fHistHadronAway2->SetBinError(i+1,yieldawayerror[1][2][i]);
        fHistHadronAway3->Fill(PtGraph[i], yieldaway[2][2][i]);
        fHistHadronAway3->SetBinError(i+1,yieldawayerror[2][2][i]);

	}

	fHistK0Near1->Write();
    fHistK0Near2->Write();
    fHistK0Near3->Write();
	fHistLambdaNear1->Write();
    fHistLambdaNear2->Write();
    fHistLambdaNear3->Write();
	fHistHadronNear1->Write();
    fHistHadronNear2->Write();
    fHistHadronNear3->Write();
    
    fHistK0Away1->Write();
    fHistK0Away2->Write();
    fHistK0Away3->Write();
    fHistLambdaAway1->Write();
    fHistLambdaAway2->Write();
    fHistLambdaAway3->Write();
    fHistHadronAway1->Write();
    fHistHadronAway2->Write();
    fHistHadronAway3->Write();
	
	TGraphErrors *fGraphK0Near1 = new TGraphErrors(nPtBins,PtGraph,yieldnear[0][0],PtError,yieldnearerror[0][0]);
    TGraphErrors *fGraphK0Near2 = new TGraphErrors(nPtBins,PtGraph,yieldnear[1][0],PtError,yieldnearerror[1][0]);
    TGraphErrors *fGraphK0Near3 = new TGraphErrors(nPtBins,PtGraph,yieldnear[2][0],PtError,yieldnearerror[2][0]);
	TGraphErrors *fGraphLambdaNear1 = new TGraphErrors(nPtBins,PtGraph,yieldnear[0][1],PtError,yieldnearerror[0][1]);
    TGraphErrors *fGraphLambdaNear2 = new TGraphErrors(nPtBins,PtGraph,yieldnear[1][1],PtError,yieldnearerror[1][1]);
    TGraphErrors *fGraphLambdaNear3 = new TGraphErrors(nPtBins,PtGraph,yieldnear[2][1],PtError,yieldnearerror[2][1]);
	TGraphErrors *fGraphTrackNear1 = new TGraphErrors(nPtBins,PtGraph,yieldnear[0][2],PtError,yieldnearerror[0][2]);
    TGraphErrors *fGraphTrackNear2 = new TGraphErrors(nPtBins,PtGraph,yieldnear[1][2],PtError,yieldnearerror[1][2]);
    TGraphErrors *fGraphTrackNear3 = new TGraphErrors(nPtBins,PtGraph,yieldnear[2][2],PtError,yieldnearerror[2][2]);

	fGraphK0Near1->SetName("fGraphK0Near1");
    fGraphK0Near2->SetName("fGraphK0Near2");
    fGraphK0Near3->SetName("fGraphK0Near3");
    fGraphLambdaNear1->SetName("fGraphLambdaNear1");
	fGraphLambdaNear2->SetName("fGraphLambdaNear2");
    fGraphLambdaNear3->SetName("fGraphLambdaNear3");
	fGraphTrackNear1->SetName("fGraphTrackNear1");
    fGraphTrackNear2->SetName("fGraphTrackNear2");
    fGraphTrackNear3->SetName("fGraphTrackNear3");
	
	fGraphK0Near1->SetMarkerStyle(23);
	fGraphK0Near1->SetMarkerColor(kBlue);
	fGraphK0Near1->SetMarkerSize(1.8);
	fGraphK0Near1->SetLineColor(kBlue);
	fGraphK0Near1->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik MC 2015c");
	fGraphK0Near1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	fGraphK0Near1->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
	fGraphK0Near1->GetYaxis()->SetRangeUser(-0.1,1);

	fGraphLambdaNear1->SetMarkerStyle(21);
	fGraphLambdaNear1->SetMarkerColor(kGreen);
	fGraphLambdaNear1->SetMarkerSize(1.8);
	fGraphLambdaNear1->SetLineColor(kGreen);

	fGraphTrackNear1->SetMarkerStyle(29);
	fGraphTrackNear1->SetMarkerColor(kRed);
	fGraphTrackNear1->SetMarkerSize(1.8);
	fGraphTrackNear1->SetLineColor(kRed);

	TLegend *fLegendNear = new TLegend(0.2,0.9,0.75,0.8);
	fLegendNear->AddEntry(fGraphK0Near1,"Triger K^{0}_{S}","pl");
	fLegendNear->AddEntry(fGraphLambdaNear1,"Triger #Lambda a #bar{#Lambda}","pl");
	fLegendNear->AddEntry(fGraphTrackNear1,"Triger nabity hadron","pl");

	fGraphK0Near1->Write();
    fGraphK0Near2->Write();
    fGraphK0Near3->Write();
	fGraphTrackNear1->Write();
    fGraphTrackNear2->Write();
    fGraphTrackNear3->Write();
	fGraphLambdaNear1->Write();
    fGraphLambdaNear2->Write();
    fGraphLambdaNear3->Write();

	TCanvas *canNear = new TCanvas;
	fGraphK0Near1->Draw("ap");
	fGraphLambdaNear1->Draw("pSAME");
	fGraphTrackNear1->Draw("pSAME");
	fLegendNear->Draw();

	TGraphErrors *fGraphK0Away1 = new TGraphErrors(nPtBins,PtGraph,yieldaway[0][0],PtError,yieldawayerror[0][0]);
    TGraphErrors *fGraphK0Away2 = new TGraphErrors(nPtBins,PtGraph,yieldaway[1][0],PtError,yieldawayerror[1][0]);
    TGraphErrors *fGraphK0Away3 = new TGraphErrors(nPtBins,PtGraph,yieldaway[2][0],PtError,yieldawayerror[2][0]);
	TGraphErrors *fGraphLambdaAway1 = new TGraphErrors(nPtBins,PtGraph,yieldaway[0][1],PtError,yieldawayerror[0][1]);
    TGraphErrors *fGraphLambdaAway2 = new TGraphErrors(nPtBins,PtGraph,yieldaway[1][1],PtError,yieldawayerror[1][1]);
    TGraphErrors *fGraphLambdaAway3 = new TGraphErrors(nPtBins,PtGraph,yieldaway[2][1],PtError,yieldawayerror[2][1]);
	TGraphErrors *fGraphTrackAway1 = new TGraphErrors(nPtBins,PtGraph,yieldaway[0][2],PtError,yieldawayerror[0][2]);
    TGraphErrors *fGraphTrackAway2 = new TGraphErrors(nPtBins,PtGraph,yieldaway[1][2],PtError,yieldawayerror[1][2]);
    TGraphErrors *fGraphTrackAway3 = new TGraphErrors(nPtBins,PtGraph,yieldaway[2][2],PtError,yieldawayerror[2][2]);
	
	fGraphK0Away1->SetMarkerStyle(23);
	fGraphK0Away1->SetMarkerColor(kBlue);
	fGraphK0Away1->SetMarkerSize(1.8);
	fGraphK0Away1->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik MC2015a");
	fGraphK0Away1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	fGraphK0Away1->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
	fGraphK0Away1->SetLineColor(kBlue);
	fGraphK0Away1->GetYaxis()->SetRangeUser(-0.1,1);

	fGraphLambdaAway1->SetMarkerStyle(21);
	fGraphLambdaAway1->SetMarkerColor(kGreen);
	fGraphLambdaAway1->SetMarkerSize(1.8);
	fGraphLambdaAway1->SetLineColor(kGreen);

	fGraphTrackAway1->SetMarkerStyle(29);
	fGraphTrackAway1->SetMarkerColor(kRed);
	fGraphTrackAway1->SetMarkerSize(1.8);
	fGraphTrackAway1->SetLineColor(kRed);

	TLegend *fLegendAway = new TLegend(0.2,0.9,0.75,0.8);
	fLegendAway->AddEntry(fGraphK0Away1,"Triger K^{0}_{S}","pl");
	fLegendAway->AddEntry(fGraphLambdaAway1,"Triger #Lambda a #bar{#Lambda}","pl");
	fLegendAway->AddEntry(fGraphTrackAway1,"Triger nabity hadron","pl");

	TCanvas *canAway = new TCanvas;
	fGraphK0Away1->Draw("ap");
	fGraphLambdaAway1->Draw("pSAME");
	fGraphTrackAway1->Draw("pSAME");
	fLegendAway->Draw();
    
    fGraphTrackAway1->SetName("fGraphTrackAway1");
    fGraphTrackAway2->SetName("fGraphTrackAway2");
    fGraphTrackAway3->SetName("fGraphTrackAway3");
    fGraphLambdaAway1->SetName("fGraphLambdaAway1");
    fGraphLambdaAway2->SetName("fGraphLambdaAway2");
    fGraphLambdaAway3->SetName("fGraphLambdaAway3");
    fGraphK0Away1->SetName("fGraphK0Away1");
    fGraphK0Away2->SetName("fGraphK0Away2");
    fGraphK0Away3->SetName("fGraphK0Away3");
    fGraphTrackAway1->Write();
    fGraphTrackAway2->Write();
    fGraphTrackAway3->Write();
    fGraphLambdaAway1->Write();
    fGraphLambdaAway2->Write();
    fGraphLambdaAway3->Write();
    fGraphK0Away1->Write();
    fGraphK0Away2->Write();
    fGraphK0Away3->Write();

	 fFile->Close();
	
}

