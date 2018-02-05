#include <TH1D.h>
#include <TH2D.h>
#include <THnSparse.h>
#include <stdio.h>
#include <TFile.h>
#include "TMath.h"

void MCclosurePomery(){
	//gStyle->SetOptStat(0000000000);

    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMC15+16.root");
    //TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/AnalysisResults.root");
    TList *list = (TList*)g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
    
    TFile *gg = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/EfiiciencyMC15+16.root");
    
    THnSparse *fHistKorelacieRec = (THnSparse*)list->FindObject("fHistKorelacieMCrec");
    THnSparse *fHistMCKorelacie = (THnSparse*)list->FindObject("fHistMCKorelacie");
    THnSparse *fHistNumberOfTriggersGen = (THnSparse*)list->FindObject("fHistNumberOfTriggersGen");
    THnSparse *fHistNumberOfTriggersRec = (THnSparse*)list->FindObject("fHistNumberOfTriggersRec");
    //THnSparse *fHistMCMixingRec = (THnSparse*)list->FindObject("fHistMCMixingRec");
    
    TH3D *fHistRCPtAs = (TH3D*) gg->Get("fHistRCPtAs");
    TH3D *fHistRCPtTrigg = (TH3D*) gg->Get("fHistRCPtTrigg");
    
    TH3D *fHistEff3DK0 = (TH3D*) gg->Get("fHistRecV03DK0");
    TH3D *fHistEff3DLam = (TH3D*) gg->Get("fHistRecV03DLam");
    TH3D *fHistEff3DALam = (TH3D*) gg->Get("fHistRecV03DAntiLam");

    const Double_t kPi = TMath::Pi();
    const Int_t nPtBins = 6;
    const Int_t nTig =3;

   // Printf ("x %d y %d z %d\n",fHistRCPtAs->GetXaxis()->GetNbins(),fHistRCPtAs->GetYaxis()->GetNbins(),fHistRCPtAs->GetZaxis()->GetNbins());
   
    const Int_t nEtaBins = fHistKorelacieRec->GetAxis(7)->GetNbins();
   // Printf("nEtaBins %d\n",nEtaBins);
    const Int_t nVzBins = fHistKorelacieRec->GetAxis(4)->GetNbins();
    const Int_t nPtAssocBins = fHistKorelacieRec->GetAxis(1)->GetNbins();
    const Int_t nPtTrigBins = fHistKorelacieRec->GetAxis(0)->GetNbins();

    THnSparse **fHistCorTypeMC=new THnSparse*[nTig];
    THnSparse **fHistRangePtMC=new THnSparse*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtaMC = new TH2D*[nTig*nPtBins];
    char htitle[50];
    char hname[50];
    char hnameMix[50];
    char hnamerec[50];
    TCanvas *cMC = new TCanvas;
    cMC->Divide(nPtBins,nTig);

    THnSparse **fHistCorTyperec=new THnSparse*[nTig];
    THnSparse **fHistMixTyperec=new THnSparse*[nTig];
    THnSparse **fHistRangePtrec=new THnSparse*[nTig*nPtBins];
    //THnSparse **fHistRangePtMixrec=new THnSparse*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtarec = new TH2D*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtaMixrec = new TH2D*[nTig*nPtBins];
    TH1D **fHistNumberOfTrigg = new TH1D*[nTig*nPtBins];

    TCanvas *cMCrec = new TCanvas;
    cMCrec->Divide(nPtBins,nTig);

    TH1D **fHistProjPhi=new TH1D*[nTig*nPtBins];
    char hnamePom[50]; 
    TH1D **fHistProjEta=new TH1D*[nTig*nPtBins];
    char hnameEta[50]; 


    TCanvas *cpomery = new TCanvas;
    cpomery->Divide(nPtBins,nTig);

    TCanvas *phiMC = new TCanvas;
    phiMC->Divide(nPtBins,nTig);
    TCanvas *etaMC = new TCanvas;
    etaMC->Divide(nPtBins,nTig);

    TCanvas *phiRec = new TCanvas;
    phiRec->Divide(nPtBins,nTig);
    TCanvas *etaRec = new TCanvas;
    etaRec->Divide(nPtBins,nTig);

    TCanvas *cpomeryPhi = new TCanvas;
    cpomeryPhi->Divide(nPtBins,nTig);
    TCanvas *cpomeryEta = new TCanvas;
    cpomeryEta->Divide(nPtBins,nTig);


    TH1D **fHistPartGen = new TH1D*[nPtBins];
    THnSparse **fHistPartCloneGen = new THnSparse*[nPtBins];
    char hnameentgen[50];
    char hname2dvela[50];
    char hname1dvela[50];

    TH1D **fHistPartRec = new TH1D*[nPtBins];
    TH1D **fHistPartRecStare = new TH1D*[nPtBins];
    THnSparse **fHistPartCloneRec = new THnSparse*[nPtBins];
    char hnameentrec[50];
    TCanvas *gen=new TCanvas();
    gen->Divide(1,nPtBins);

    TCanvas *rec=new TCanvas();
    rec->Divide(1,nPtBins);
    
    TCanvas *recNove=new TCanvas();
    recNove->Divide(1,nPtBins);
    
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
                // Printf("%g %d %d %d \n",fHistRCPtAs->GetBinContent(m+1,l3D+1,k3D+1),k,l,m);
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
    
    Double_t fitPhiHodnoty[nTig][nPtBins];
    Double_t fitPhiChyby[nTig][nPtBins];
    Double_t fitEtaHodnoty[nTig][nPtBins];
    Double_t fitEtaChyby[nTig][nPtBins];
    Double_t ptBins[nPtBins]={4.5,5.5,6.5,8,10,13.5};
    Double_t ptBinsChyby[nPtBins]={0.5,0.5,0.5,1,1,2.5};

    for(Int_t i=0;i<nPtBins;i++){
        fHistPartCloneGen[i]=(THnSparse *)fHistNumberOfTriggersGen->Clone();
        if (i==0) fHistPartCloneGen[i]->GetAxis(0)->SetRange(1,1);
        if (i==1) fHistPartCloneGen[i]->GetAxis(0)->SetRange(2,2);
        if (i==2) fHistPartCloneGen[i]->GetAxis(0)->SetRange(3,3);
        if (i==3) fHistPartCloneGen[i]->GetAxis(0)->SetRange(4,5);
        if (i==4) fHistPartCloneGen[i]->GetAxis(0)->SetRange(6,7);
        if (i==5) fHistPartCloneGen[i]->GetAxis(0)->SetRange(8,11);
        fHistPartGen[i] = fHistPartCloneGen[i]->Projection(3);
        sprintf(hnameentgen,"proj_%dgen",i);
        fHistPartGen[i]->SetName(hnameentgen);

        fHistPartCloneRec[i]=(THnSparse *)fHistNumberOfTriggersRec->Clone();
        if (i==0) fHistPartCloneRec[i]->GetAxis(0)->SetRange(1,1);
        if (i==1) fHistPartCloneRec[i]->GetAxis(0)->SetRange(2,2);
        if (i==2) fHistPartCloneRec[i]->GetAxis(0)->SetRange(3,3);
        if (i==3) fHistPartCloneRec[i]->GetAxis(0)->SetRange(4,5);
        if (i==4) fHistPartCloneRec[i]->GetAxis(0)->SetRange(6,7);
        if (i==5) fHistPartCloneRec[i]->GetAxis(0)->SetRange(8,11);
        fHistPartRec[i] = fHistPartCloneRec[i]->Projection(3);
        sprintf(hnameentrec,"proj_%drec",i);
        fHistPartRec[i]->SetName(hnameentrec);

        gen->cd(i+1);
        fHistPartGen[i]->DrawCopy();
        rec->cd(i+1);
        fHistPartRec[i]->DrawCopy();

    }

    
    TFile *fNewFile = TFile::Open("McClosure15+16_K0_bezTrigCorr.root","RECREATE");
    for(Int_t i=0;i<1;i++){   // looop cez druhy triggra
        fHistCorTypeMC[i]=(THnSparse *)fHistMCKorelacie->Clone();
        if(i==0) fHistCorTypeMC[i]->GetAxis(5)->SetRange(i+1,i+1);
        if(i==1) fHistCorTypeMC[i]->GetAxis(5)->SetRange(i+1,i+2);
        if(i==2) fHistCorTypeMC[i]->GetAxis(5)->SetRange(i+2,i+2);

        fHistCorTyperec[i]=(THnSparse *)fHistKorelacieRec->Clone();
        if(i==0) fHistCorTyperec[i]->GetAxis(5)->SetRange(i+1,i+1);
        if(i==1) fHistCorTyperec[i]->GetAxis(5)->SetRange(i+1,i+2);
        if(i==2) fHistCorTyperec[i]->GetAxis(5)->SetRange(i+2,i+2);
        
        /*fHistMixTyperec[i]= (THnSparse *)fHistMCMixingRec->Clone();
        if(i==0) fHistMixTyperec[i]->GetAxis(5)->SetRange(i+1,i+1);
        if(i==1) fHistMixTyperec[i]->GetAxis(5)->SetRange(i+1,i+2);
        if(i==2) fHistMixTyperec[i]->GetAxis(5)->SetRange(i+2,i+2);*/
        
        for(Int_t j=0;j<nPtBins;j++){ // loop cez pt triggra
            fHistRangePtMC[i*nPtBins+j]=(THnSparse *)fHistCorTypeMC[i]->Clone();

            if (j==0) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(1,1);
            if (j==1) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(2,2);
            if (j==2) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(3,3);
            if (j==3) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(4,5);
            if (j==4) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(6,7);
            if (j==5) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(8,11);
            
            fHistRangePtProjPhiEtaMC[i*nPtBins+j] = (TH2D *)fHistRangePtMC[i*nPtBins+j]->Projection(2,3);
            sprintf(hname,"2dproj_%d_pt_%d",i,j);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->SetName(hname);
            sprintf(htitle,"Gen #Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,j);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->SetTitle(htitle);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->RebinX(4);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->RebinY(4);

            fHistRangePtrec[i*nPtBins+j]=(THnSparse *)fHistCorTyperec[i]->Clone();

            if (j==0) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(1,1);
            if (j==1) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(2,2);
            if (j==2) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(3,3);
            if (j==3) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(4,5);
            if (j==4) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(6,7);
            if (j==5) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(8,11);
            
            /*fHistRangePtMixrec[i*nPtBins+j]=(THnSparse *)fHistMixTyperec[i]->Clone();
            
            if (j==0) fHistRangePtMixrec[i*nPtBins+j]->GetAxis(0)->SetRange(1,1);
            if (j==1) fHistRangePtMixrec[i*nPtBins+j]->GetAxis(0)->SetRange(2,2);
            if (j==2) fHistRangePtMixrec[i*nPtBins+j]->GetAxis(0)->SetRange(3,3);
            if (j==3) fHistRangePtMixrec[i*nPtBins+j]->GetAxis(0)->SetRange(4,5);
            if (j==4) fHistRangePtMixrec[i*nPtBins+j]->GetAxis(0)->SetRange(6,7);
            if (j==5) fHistRangePtMixrec[i*nPtBins+j]->GetAxis(0)->SetRange(8,11);*/

            Int_t l3D =0;
            Int_t nHist =0;
            Int_t nHistTrig =0;

            for(Int_t l=0;l<nVzBins ; l++){ //loop cez vertex biny
                Printf(" ----------- l %d --------------------- \n",l);
                THnSparse * tmpHist1 = (THnSparse*)fHistRangePtrec[i*nPtBins+j]->Clone();
                tmpHist1->GetAxis(4)->SetRange(l+1,l+2);
                
                THnSparse * tmpHistTrigg1 = (THnSparse*)fHistPartCloneRec[j]->Clone();
                tmpHistTrigg1->GetAxis(1)->SetRange(l+1,l+2);
                Int_t k3D =0;
                
                
              /*  for (Int_t k=0; k<nEtaBins; k++) {//loop cez eta trigg
                    //Printf("l3D %d\n",l3D);
                    THnSparse *tmpHist2 = (THnSparse*)tmpHist1->Clone();
                    tmpHist2->GetAxis(6)->SetRange(k+1,k+4);
                    
                    THnSparse *tmpHist2Trigg = (THnSparse*)tmpHistTrigg1->Clone();
                    tmpHist2Trigg->GetAxis(2)->SetRange(k+1,k+4);
                    TH1D * proj1DTrigg = (TH1D *)tmpHist2Trigg->Projection(3);
                    sprintf(hname1dvela,"%d_%d_%d",j,k3D,l3D);
                    proj1DTrigg->SetName(hname1dvela);
                    
                    //Printf("scale h %g\n", sclaleAssoc[k3D][l3D][j]);
                    Printf("+++++ k ++++++ \n" );
                    if(i==0){
                       // Printf("pred %g \n ", proj1DTrigg->GetBinContent(1));
                        if(sclaleK0[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(1,proj1DTrigg->GetBinContent(1)/sclaleK0[k3D][l3D][j]);
                       // Printf("po %g \n ",proj1DTrigg->GetBinContent(1));
                    }
                    
                    if(i==1){
                        if(sclaleLam[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(2,proj1DTrigg->GetBinContent(2)/sclaleLam[k3D][l3D][j]);
                    
                        if(sclaleAntiL[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(3,proj1DTrigg->GetBinContent(3)/sclaleAntiL[k3D][l3D][j]);
                    }
                    
                    if(i==2){
                        if(sclaleTrigg[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(4,proj1DTrigg->GetBinContent(4)/sclaleTrigg[k3D][l3D][j]);
                    }
                    if (nHistTrig==0) fHistNumberOfTrigg[i*nPtBins+j] =(TH1D *)proj1DTrigg->Clone();
                    else fHistNumberOfTrigg[i*nPtBins+j]->Add(proj1DTrigg);
                    nHistTrig+=1;
                    
                        */
                    Int_t n3D =0;
                    for (Int_t n=0; n<nEtaBins; n++) { // loop cez eta assoc
                        
                        THnSparse *tmpHist3 = (THnSparse*)tmpHist1->Clone();
                        tmpHist3->GetAxis(7)->SetRange(n+1,n+4);
                        
                        //Printf ("n %d eta assoc \n", n);
                        
                        for (Int_t m=0; m<nPtAssocBins; m++){ // loop cez pt assoc
                            
                            THnSparse *tmpHist4 = (THnSparse*)tmpHist3->Clone();
                            tmpHist4->GetAxis(1)->SetRange(m+1,m+1);
                            
                            TH2D * proj2DRac = (TH2D *)tmpHist4->Projection(2,3);
                            sprintf(hname2dvela,"%d_%d_%d",m,n3D,l3D);
                            proj2DRac->SetName(hname2dvela);
                            
                            //if(sclaleAssoc[n3D][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[n3D][l3D][m]);
                            
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
                            
                            //Printf("scale assoc %g\n",sclaleAssoc[n3D][l3D][m] );
                            
                        /*    if(i==0&&sclaleK0[k3D][l3D][j]!=0){
                                if(sclaleK0[k3D][l3D][j]!=0) proj2DRac->Scale(1./sclaleK0[k3D][l3D][j]);
                                //Printf("eff k0 %g\n", sclaleK0[k3D][l3D][j] );
                            }
                            if(i==1&&sclaleLam[k3D][l3D][j]!=0&&sclaleAntiL[k3D][l3D][j]!=0){
                                Double_t scalelamAntilam = (sclaleLam[k3D][l3D][j]+sclaleAntiL[k3D][l3D][j])/2;
                                if(sclaleLam[k3D][l3D][j]!=0) proj2DRac->Scale(1./scalelamAntilam);
                                //Printf("eff Lam %g\n", scalelamAntilam );
                            }

                            if(i==2&&sclaleTrigg[k3D][l3D][j]!=0){
                                if(sclaleTrigg[k3D][l3D][j]!=0) proj2DRac->Scale(1./sclaleTrigg[k3D][l3D][j]);
                                //Printf("eff h %g\n", sclaleTrigg[k3D][l3D][j] );
                            }
                            */
                          /*  if(i==0&&(proj1DTrigg->GetBinContent(1)!=0)) {
                                Printf("max pred %g \n", proj2DRac->GetMaximum());
                                proj2DRac->Scale(1./(proj1DTrigg->GetBinContent(1)));
                                Printf("max po %g \n", proj2DRac->GetMaximum());
                             //   Printf("num of triggers K0  %g \n",proj1DTrigg->GetBinContent(1));
                            }
                            if(i==1&&(proj1DTrigg->GetBinContent(2)+proj1DTrigg->GetBinContent(3))!=0) {
                                proj2DRac->Scale(1./(proj1DTrigg->GetBinContent(2)+proj1DTrigg->GetBinContent(3)));
                                //Printf("num of triggers Lam %g \n",proj1DTrigg->GetBinContent(2)+proj1DTrigg->GetBinContent(3));
                            }
                            if(i==2&&proj1DTrigg->GetBinContent(4)!=0){
                                proj2DRac->Scale(1./(proj1DTrigg->GetBinContent(4)));
                                //Printf("num of triggers h %g \n",proj1DTrigg->GetBinContent(4));
                            }*/
                            //Printf("maxim co sa spocitava %g \n",proj2DRac->GetMaximum());
                            if (nHist==0) fHistRangePtProjPhiEtarec[i*nPtBins+j] =(TH2D *)proj2DRac->Clone();
                            else fHistRangePtProjPhiEtarec[i*nPtBins+j]->Add(proj2DRac);
                            nHist+=1;
                            
                            delete proj2DRac;
                            delete tmpHist4;
                        }
                        
                        delete tmpHist3;
                        
                        n+=3;
                        n3D+=1;
                        
                    //}
                    
                    
                    
                   // delete proj1DTrigg;
                    //delete tmpHist2Trigg;
                    //delete tmpHist2;
                    
                    
                  //  k+=3;
                  //  k3D+=1;
                    
                }
                
                
                delete tmpHist1;
                delete tmpHistTrigg1;

                l3D+=1;
                l+=1;
            }
            
            Printf("nHist %d\n",nHist);
            
            //fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(./1nHist); // je to zle lebo spocitavam histogrami, ktore sa nijak neprekryvaju
           /* sprintf(hnameentrec,"proj_%drec",j);
            fHistPartRec[j]->SetName(hnameentrec);
            recNove->cd(j+1);
            fHistPartRec[j]->DrawCopy();*/
            
            
            
            /*fHistRangePtProjPhiEtaMixrec[i*nPtBins+j] = (TH2D *) fHistRangePtMixrec[i*nPtBins+j]->Projection(2,3);
            sprintf(hnameMix,"2dproj_%d_pt_%d_Mix",i,j);
            fHistRangePtProjPhiEtaMixrec[i*nPtBins+j]->SetName(hnameMix);
            fHistRangePtProjPhiEtaMixrec[i*nPtBins+j]->RebinX(4);
            fHistRangePtProjPhiEtaMixrec[i*nPtBins+j]->RebinY(4);
            Double_t maximum = fHistRangePtProjPhiEtaMixrec[i*nPtBins+j]->GetMaximum();
            fHistRangePtProjPhiEtaMixrec[i*nPtBins+j]->Scale(1./maximum);
            
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Divide(fHistRangePtProjPhiEtaMixrec[i*nPtBins+j]);*/
            if(i==0) fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Scale(1./(fHistPartGen[j]->GetBinContent(1)));
            if(i==1) fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Scale(1./(fHistPartGen[j]->GetBinContent(2)+fHistPartGen[j]->GetBinContent(3)));
            if(i==2) fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Scale(1./(fHistPartGen[j]->GetBinContent(4)));
            cMC->cd(i*nPtBins+j+1);
            //Printf("Entries MC %d \n", fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetEntries());
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->DrawCopy("lego2z");
            
            sprintf(hnamerec,"2dproj_%d_pt_%d",i,j);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->SetName(hnamerec);
            sprintf(htitle,"Rec #Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,j);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->SetTitle(htitle);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->RebinX(4);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->RebinY(4);
            
            //fHistRangePtProjPhiEtarec[i*nPtBins+j]->Divide(fHistRangePtProjPhiEtaMixrec[i*nPtBins+j]);
            
            if(i==0) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistPartRec[i]->GetBinContent(1)));   //(fHistNumberOfTrigg[i*nPtBins+j]->GetBinContent(1)));
            if(i==1) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistPartRec[i]->GetBinContent(2)+fHistPartRec[i]->GetBinContent(3)));   //(fHistNumberOfTrigg[i*nPtBins+j]->GetBinContent(2)+fHistNumberOfTrigg[i*nPtBins+j]->GetBinContent(3)));
            if(i==2) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistPartRec[i]->GetBinContent(4)));   //(fHistNumberOfTrigg[i*nPtBins+j]->GetBinContent(4)));


            cMCrec->cd(i*nPtBins+j+1);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->DrawCopy("lego2z");

            Printf("maimum gen %g, max rec %g\n",fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetMaximum(),fHistRangePtProjPhiEtarec[i*nPtBins+j]->GetMaximum());
            //fHistPomery[i*nPtBins+j]=
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Divide(fHistRangePtProjPhiEtarec[i*nPtBins+j]);
            
           
            fHistProjPhi[i*nPtBins+j]=fHistRangePtProjPhiEtaMC[i*nPtBins+j]->ProjectionY();
            sprintf(hnamePom,"hnamePom%d%d",i,j);
            fHistProjPhi[i*nPtBins+j]->SetName(hnamePom);
            phiMC->cd(i*nPtBins+j+1);

            fHistProjEta[i*nPtBins+j] =fHistRangePtProjPhiEtaMC[i*nPtBins+j]->ProjectionX();
            etaMC->cd(i*nPtBins+j+1);

            sprintf(hnameEta,"hnameEta%d%d",i,j);
            fHistProjEta[i*nPtBins+j]->SetName(hnameEta);

            Int_t nBinsEta = fHistProjEta[i*nPtBins+j]->GetNbinsX();
            Int_t nBinsPhi = fHistProjPhi[i*nPtBins+j]->GetNbinsX();
            Printf("bins eta %d \n",nBinsEta);
           

            for (Int_t k=4; k<(nBinsEta-4); k++){

                Double_t scaleEta=0;
                Double_t chybaEta=0;
                for(Int_t l=0; l<(nBinsPhi); l++){
                    if(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(k+1,l+1)>0) {
                        scaleEta++;
                        chybaEta+=TMath::Power(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinError(k+1,l+1),2);
                    }

                }
                //Printf("scaleEta %g , bincont %g \n", scaleEta,fHistProjEta[i*nPtBins+j]->GetBinContent(k+1));
                if(scaleEta>0) fHistProjEta[i*nPtBins+j]->SetBinContent(k+1,(fHistProjEta[i*nPtBins+j]->GetBinContent(k+1))/scaleEta);
                chybaEta=TMath::Sqrt(chybaEta);
                chybaEta=chybaEta/scaleEta;
                fHistProjEta[i*nPtBins+j]->SetBinError(k+1,chybaEta);
            }

            for (Int_t k=0; k<(nBinsPhi); k++){
                Double_t scalePhi=0;
                Double_t chybaPhi=0;
                Double_t hodnotaPhi = 0;
                for(Int_t l=4; l<(nBinsEta-4); l++){
                    if(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(l+1,k+1)>0) {
                        scalePhi++;
                        hodnotaPhi+=fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(l+1,k+1);
                        chybaPhi+=TMath::Power(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinError(l+1,k+1),2);
                    }
                }
                if (i==1&&j==5) Printf("scalePhi %g \n", scalePhi);
                if(scalePhi>0) fHistProjPhi[i*nPtBins+j]->SetBinContent(k+1,hodnotaPhi/scalePhi);
                else fHistProjPhi[i*nPtBins+j]->SetBinContent(k+1,0);
                chybaPhi=TMath::Sqrt(chybaPhi);
                if(scalePhi>0) chybaPhi=chybaPhi/scalePhi;
                else chybaPhi=0;
                fHistProjPhi[i*nPtBins+j]->SetBinError(k+1,chybaPhi);
            }

           // fHistProjPhi[i*nPtBins+j]->Scale(1./scalePhi);
            //fHistProjEta[i*nPtBins+j]->Scale(1./scaleEta);

            TF1 *fitPhi = new TF1("fitphi"," [0]",-kPi/2, -kPi/2+2*kPi);
            fitPhi->SetParameter(0,1);
            cpomeryPhi->cd(i*nPtBins+j+1);
            fHistProjPhi[i*nPtBins+j]->SetAxisRange(0,2,"y");
            fHistProjPhi[i*nPtBins+j]->DrawCopy();
            fHistProjPhi[i*nPtBins+j]->Fit(fitPhi);
            fitPhiHodnoty[i][j]=fitPhi->GetParameter(0);
            fitPhiChyby[i][j]=fitPhi->GetParError(0);
            Printf("phi param %g \n", fitPhi->GetParameter(0));
            fHistProjPhi[i*nPtBins+j]->Write();

            TF1 *fitEta = new TF1("fitEta"," [0]",-1.5, 1.5);
            fitEta->SetParameter(0,1);
            cpomeryEta->cd(i*nPtBins+j+1);
            fHistProjEta[i*nPtBins+j]->SetAxisRange(-1.5,1.5,"x");
            fHistProjEta[i*nPtBins+j]->SetAxisRange(0,2,"y");
            fHistProjEta[i*nPtBins+j]->DrawCopy();
            fHistProjEta[i*nPtBins+j]->Fit(fitEta);
            fitEtaHodnoty[i][j]=fitEta->GetParameter(0);
            fitEtaChyby[i][j]=fitEta->GetParError(0);
            Printf("eta param %g \n", fitEta->GetParameter(0));
            fHistProjEta[i*nPtBins+j]->Write();
            
            delete fitPhi;
            delete fitEta;
            
            cpomery->cd(i*nPtBins+j+1);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetXaxis()->SetRangeUser(-1.5,1.5);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->DrawCopy("colz");
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Write();
        }
        
    }
    
    TGraphErrors * k0Phi = new TGraphErrors(nPtBins,ptBins,fitPhiHodnoty[0],ptBinsChyby,fitPhiChyby[0]);
    TGraphErrors * k0Eta = new TGraphErrors(nPtBins,ptBins,fitEtaHodnoty[0],ptBinsChyby,fitEtaChyby[0]);
    
    TGraphErrors * LamPhi = new TGraphErrors(nPtBins,ptBins,fitPhiHodnoty[1],ptBinsChyby,fitPhiChyby[1]);
    TGraphErrors * LamEta = new TGraphErrors(nPtBins,ptBins,fitEtaHodnoty[1],ptBinsChyby,fitEtaChyby[1]);
    
    TGraphErrors * hPhi = new TGraphErrors(nPtBins,ptBins,fitPhiHodnoty[2],ptBinsChyby,fitPhiChyby[2]);
    TGraphErrors * hEta = new TGraphErrors(nPtBins,ptBins,fitEtaHodnoty[2],ptBinsChyby,fitEtaChyby[2]);
    
    TCanvas *graphK0Phi = new TCanvas;
    k0Phi->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger K_{0}_{S}, phi projekcia");
    k0Phi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    k0Phi->GetYaxis()->SetTitle("hodnota fitu");
    k0Phi->SetMarkerStyle(23);
    k0Phi->SetMarkerColor(kBlue);
    k0Phi->SetLineColor(kBlue);
    k0Phi->SetMarkerSize(1.8);
    k0Phi->Draw("ap");
    TCanvas *graphK0Eta = new TCanvas;
    k0Eta->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger K_{0}_{S}, eta projekcia");
    k0Eta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    k0Eta->GetYaxis()->SetTitle("hodnota fitu");
    k0Eta->SetMarkerStyle(23);
    k0Eta->SetMarkerColor(kBlue);
    k0Eta->SetLineColor(kBlue);
    k0Eta->SetMarkerSize(1.8);
    k0Eta->Draw("ap");
    
    TCanvas *graphLamPhi = new TCanvas;
    LamPhi->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger  #{Lambda}+#bar{#Lambda}, phi projekcia");
    LamPhi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    LamPhi->GetYaxis()->SetTitle("hodnota fitu");
    LamPhi->SetMarkerStyle(23);
    LamPhi->SetMarkerColor(kBlue);
    LamPhi->SetLineColor(kBlue);
    LamPhi->SetMarkerSize(1.8);
    LamPhi->Draw("ap");
    TCanvas *graphLamEta = new TCanvas;
    LamEta->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger #Lambda+#bar{#Lambda}, eta projekcia");
    LamEta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    LamEta->GetYaxis()->SetTitle("hodnota fitu");
    LamEta->SetMarkerStyle(23);
    LamEta->SetMarkerColor(kBlue);
    LamEta->SetLineColor(kBlue);
    LamEta->SetMarkerSize(1.8);
    LamEta->Draw("ap");
    
    TCanvas *graphhhPhi = new TCanvas;
    hPhi->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger h, phi projekcia");
    hPhi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    hPhi->GetYaxis()->SetTitle("hodnota fitu");
    hPhi->GetYaxis()->SetRangeUser(0.9,1.1);
    hPhi->SetMarkerStyle(23);
    hPhi->SetMarkerColor(kBlue);
    hPhi->SetLineColor(kBlue);
    hPhi->SetMarkerSize(1.8);
    hPhi->Draw("ap");
    TCanvas *graphhEta = new TCanvas;
    hEta->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger h, eta projekcia");
    hEta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    hEta->GetYaxis()->SetTitle("hodnota fitu");
    hEta->GetYaxis()->SetRangeUser(0.9,1.1);
    hEta->SetMarkerStyle(23);
    hEta->SetMarkerColor(kBlue);
    hEta->SetLineColor(kBlue);
    hEta->SetMarkerSize(1.8);
    hEta->Draw("ap");
    
    k0Phi->Write();
    k0Eta->Write();
    LamPhi->Write();
    LamEta->Write();
    hPhi->Write();
    hEta->Write();
    fNewFile->Close();

}

