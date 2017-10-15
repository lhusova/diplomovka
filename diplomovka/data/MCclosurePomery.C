#include <TH1D.h>
#include <TH2D.h>
#include <THnSparse.h>
#include <stdio.h>
#include <TFile.h>
#include "TMath.h"

void MCclosurePomery(){
	//gStyle->SetOptStat(0000000000);

    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMCnew05.root");
   //TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/AnalysisResults.root");
    TList *list = g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
    
    THnSparse *fHistKorelacieRec = (THnSparse*)list->FindObject("fHistKorelacieMCrec");
    THnSparse *fHistMCKorelacie = (THnSparse*)list->FindObject("fHistMCKorelacie");
    THnSparse *fHistNumberOfTriggersGen = (THnSparse*)list->FindObject("fHistNumberOfTriggersGen");
    THnSparse *fHistNumberOfTriggersRec = (THnSparse*)list->FindObject("fHistNumberOfTriggersRec");

    const Double_t kPi = TMath::Pi();
    const Int_t nPtBins = 6;
    const Int_t nTig =3;


    THnSparse **fHistCorTypeMC=new THnSparse*[nTig];
    THnSparse **fHistRangePtMC=new THnSparse*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtaMC = new TH2D*[nTig*nPtBins];
    char htitle[50];
    char hname[50]; 
    TCanvas *cMC = new TCanvas;
    cMC->Divide(nPtBins,nTig);

    THnSparse **fHistCorTyperec=new THnSparse*[nTig];
    THnSparse **fHistRangePtrec=new THnSparse*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtarec = new TH2D*[nTig*nPtBins];
    char htitle[50];
    char hname[50]; 
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

    TH1D **fHistPartRec = new TH1D*[nPtBins];
    THnSparse **fHistPartCloneRec = new THnSparse*[nPtBins];
    char hnameentrec[50];
    TCanvas *gen=new TCanvas();
    gen->Divide(1,nPtBins);

    TCanvas *rec=new TCanvas();
    rec->Divide(1,nPtBins);

    for(Int_t i=0;i<nPtBins;i++){
        fHistPartCloneGen[i]=fHistNumberOfTriggersGen->Clone();
        if (i==0) fHistPartCloneGen[i]->GetAxis(0)->SetRange(1,1);
        if (i==1) fHistPartCloneGen[i]->GetAxis(0)->SetRange(2,2);
        if (i==2) fHistPartCloneGen[i]->GetAxis(0)->SetRange(3,3);
        if (i==3) fHistPartCloneGen[i]->GetAxis(0)->SetRange(4,5);
        if (i==4) fHistPartCloneGen[i]->GetAxis(0)->SetRange(6,7);
        if (i==5) fHistPartCloneGen[i]->GetAxis(0)->SetRange(8,11);
        fHistPartGen[i] = fHistPartCloneGen[i]->Projection(1);
        sprintf(hnameentgen,"proj_%dgen",i);
        fHistPartGen[i]->SetName(hnameentgen);

        fHistPartCloneRec[i]=fHistNumberOfTriggersRec->Clone();
        if (i==0) fHistPartCloneRec[i]->GetAxis(0)->SetRange(1,1);
        if (i==1) fHistPartCloneRec[i]->GetAxis(0)->SetRange(2,2);
        if (i==2) fHistPartCloneRec[i]->GetAxis(0)->SetRange(3,3);
        if (i==3) fHistPartCloneRec[i]->GetAxis(0)->SetRange(4,5);
        if (i==4) fHistPartCloneRec[i]->GetAxis(0)->SetRange(6,7);
        if (i==5) fHistPartCloneRec[i]->GetAxis(0)->SetRange(8,11);
        fHistPartRec[i] = fHistPartCloneRec[i]->Projection(1);
        sprintf(hnameentrec,"proj_%drec",i);
        fHistPartRec[i]->SetName(hnameentrec);

        gen->cd(i+1);
        fHistPartGen[i]->DrawCopy();
        rec->cd(i+1);
        fHistPartRec[i]->DrawCopy();

    }

    for(Int_t i=0;i<nTig;i++){
        fHistCorTypeMC[i]=fHistMCKorelacie->Clone();
        if(i==0) fHistCorTypeMC[i]->GetAxis(5)->SetRange(i+1,i+1);
        if(i==1) fHistCorTypeMC[i]->GetAxis(5)->SetRange(i+1,i+2);
        if(i==2) fHistCorTypeMC[i]->GetAxis(5)->SetRange(i+2,i+2);

        fHistCorTyperec[i]=fHistKorelacieRec->Clone();
        if(i==0) fHistCorTyperec[i]->GetAxis(5)->SetRange(i+1,i+1);
        if(i==1) fHistCorTyperec[i]->GetAxis(5)->SetRange(i+1,i+2);
        if(i==2) fHistCorTyperec[i]->GetAxis(5)->SetRange(i+2,i+2);
        for(Int_t j=0;j<nPtBins;j++){
            fHistRangePtMC[i*nPtBins+j]=fHistCorTypeMC[i]->Clone();

            if (j==0) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(1,1);
            if (j==1) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(2,2);
            if (j==2) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(3,3);
            if (j==3) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(4,5);
            if (j==4) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(6,7);
            if (j==5) fHistRangePtMC[i*nPtBins+j]->GetAxis(0)->SetRange(8,11);
            
            fHistRangePtProjPhiEtaMC[i*nPtBins+j] = fHistRangePtMC[i*nPtBins+j]->Projection(2,3);
            sprintf(hname,"2dproj_%d_pt_%d",i,j);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->SetName(hname);
            sprintf(htitle,"Gen #Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,j);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->SetTitle(htitle);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->RebinX(4);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->RebinY(4);
            if(i==0) fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Scale(1./(fHistPartGen[j]->GetBinContent(1)));
            if(i==1) fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Scale(1./(fHistPartGen[j]->GetBinContent(2)+fHistPartGen[j]->GetBinContent(3)));
            if(i==2) fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Scale(1./(fHistPartGen[j]->GetBinContent(4)));
            cMC->cd(i*nPtBins+j+1);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->DrawCopy("lego2z");

            fHistRangePtrec[i*nPtBins+j]=fHistCorTyperec[i]->Clone();

            if (j==0) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(1,1);
            if (j==1) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(2,2);
            if (j==2) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(3,3);
            if (j==3) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(4,5);
            if (j==4) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(6,7);
            if (j==5) fHistRangePtrec[i*nPtBins+j]->GetAxis(0)->SetRange(8,11);
            
            fHistRangePtProjPhiEtarec[i*nPtBins+j] = fHistRangePtrec[i*nPtBins+j]->Projection(2,3);
            sprintf(hname,"2dproj_%d_pt_%d",i,j);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->SetName(hname);
            sprintf(htitle,"Rec #Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,j);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->SetTitle(htitle);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->RebinX(4);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->RebinY(4);
            if(i==0) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistPartRec[j]->GetBinContent(1)));
            if(i==1) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistPartRec[j]->GetBinContent(2)+fHistPartRec[j]->GetBinContent(3)));
            if(i==2) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistPartRec[j]->GetBinContent(4)));
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./0.803);
            cMCrec->cd(i*nPtBins+j+1);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->DrawCopy("lego2z");

            cpomery->cd(i*nPtBins+j+1);
            //fHistPomery[i*nPtBins+j]=
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Divide(fHistRangePtProjPhiEtarec[i*nPtBins+j]);
           //fHistRangePtProjPhiEtarec[i*nPtBins+j]->Divide(fHistRangePtProjPhiEtaMC[i*nPtBins+j]);
            //sprintf(hnamePom, "pomGenRec_%d_%d",i,j);
            //fHistPomery[i*nPtBins+j]->SetName(hnamePom);
            //sprintf(htitlePom, "pom gen/rec  trig %d pt int %d"i,j);
            //fHistPomery[i*nPtBins+j]->SetTitle(htitlePom);
            //fHistRangePtProjPhiEtaMC[i*nPtBins+j]->DrawCopy("colz");
           fHistRangePtProjPhiEtaMC[i*nPtBins+j]->DrawCopy("colz");


       /*     fHistProjPhi[i*nPtBins+j]=fHistRangePtProjPhiEtaMC[i*nPtBins+j]->ProjectionY();
            sprintf(hnamePom,"hnamePom%d%d",i,j);
            fHistProjPhi[i*nPtBins+j]->SetName(hnamePom);
            phiMC->cd(i*nPtBins+j+1);
            //fHistProjPhi[i*nPtBins+j]->Sumw2();
           // fHistProjPhi[i*nPtBins+j]->SetLineColor(kRed);
            //fHistProjPhi[i*nPtBins+j]->SetMarkerSize(1.5); 
            //fHistProjPhi[i*nPtBins+j]->DrawCopy();
            //phiRec->cd(i*nPtBins+j+1);
            //(fHistRangePtProjPhiEtarec[i*nPtBins+j]->ProjectionY())->DrawCopy("same");
            //fHistProjPhi[i*nPtBins+j]->Divide(fHistRangePtProjPhiEtarec[i*nPtBins+j]->ProjectionY());


            fHistProjEta[i*nPtBins+j] =fHistRangePtProjPhiEtaMC[i*nPtBins+j]->ProjectionX();
            etaMC->cd(i*nPtBins+j+1);
            //fHistProjEta[i*nPtBins+j]->Sumw2();
            //fHistProjEta[i*nPtBins+j]->DrawCopy();
            //etaRec->cd(i*nPtBins+j+1);
            //(fHistRangePtProjPhiEtarec[i*nPtBins+j]->ProjectionX())->DrawCopy();
            //fHistProjEta[i*nPtBins+j]->Divide(fHistRangePtProjPhiEtarec[i*nPtBins+j]->ProjectionX());
            sprintf(hnameEta,"hnameEta%d%d",i,j);
            fHistProjEta[i*nPtBins+j]->SetName(hnameEta);

            Int_t nBinsEta = fHistProjEta[i*nPtBins+j]->GetSize();
            Int_t nBinsPhi = fHistProjPhi[i*nPtBins+j]->GetSize();

           

            for (Int_t k=0; k<(nBinsEta-2); k++){

            Double_t scaleEta=0;
                for(Int_t l=0; l<(nBinsPhi-2); l++){
                    if(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(l+1,k+1)>0) scaleEta++;

                }
                Printf("scaleEta %g \n", scaleEta);
               if(scaleEta>0) fHistProjEta[i*nPtBins+j]->SetBinContent(k+1,(fHistProjEta[i*nPtBins+j]->GetBinContent(k+1))/scaleEta);

            }

            for (Int_t k=0; k<(nBinsPhi-2); k++){
                Double_t scalePhi=0;
                for(Int_t l=0; l<(nBinsEta-2); l++){
                    if(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(l+1,k+1)>0) scalePhi++;
                }
                Printf("scalePhi %g \n", scalePhi);
                if(scalePhi>0) fHistProjPhi[i*nPtBins+j]->SetBinContent(k+1,fHistProjPhi[i*nPtBins+j]->GetBinContent(k+1)/scalePhi);

            }

           // fHistProjPhi[i*nPtBins+j]->Scale(1./scalePhi);
            //fHistProjEta[i*nPtBins+j]->Scale(1./scaleEta);

            cpomeryPhi->cd(i*nPtBins+j+1);
            fHistProjPhi[i*nPtBins+j]->DrawCopy();

            cpomeryEta->cd(i*nPtBins+j+1);
            fHistProjEta[i*nPtBins+j]->SetAxisRange(-1,1,"x");
           fHistProjEta[i*nPtBins+j]->DrawCopy();

            */
        }
        
    }

   /* TCanvas *jedenGen = new TCanvas();
    //fHistRangePtProjPhiEtaMC[20]->Rebin2D(2,2);
    fHistRangePtProjPhiEtaMC[20]->DrawCopy("lego2z");

    TCanvas *jedenRec = new TCanvas();
    fHistRangePtProjPhiEtarec[20]->Scale(1./0.803);
   // fHistRangePtProjPhiEtarec[20]->Rebin2D(2,2);
    fHistRangePtProjPhiEtarec[20]->DrawCopy("lego2z");

    TCanvas *jeden = new TCanvas();
    fHistRangePtProjPhiEtaMC[20]->Divide(fHistRangePtProjPhiEtarec[20]);
    fHistRangePtProjPhiEtaMC[20]->DrawCopy("lego2z");

    TCanvas *jedenprojy = new TCanvas();
    (fHistRangePtProjPhiEtaMC[20]->ProjectionY())->DrawCopy("");

    TCanvas *jedenprojx = new TCanvas();
    (fHistRangePtProjPhiEtaMC[20]->ProjectionX())->DrawCopy("");*/
}

