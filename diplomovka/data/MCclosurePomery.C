#include <TH1D.h>
#include <TH2D.h>
#include <THnSparse.h>
#include <stdio.h>
#include <TFile.h>
#include "TMath.h"

void MCclosurePomery(){
	//gStyle->SetOptStat(0000000000);

    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMC2016_01.root");
   //TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/AnalysisResults.root");
    TList *list = g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
    
    TFile *gg = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/Efiiciency1.root");
    
    THnSparse *fHistKorelacieRec = (THnSparse*)list->FindObject("fHistKorelacieMCrec");
    THnSparse *fHistMCKorelacie = (THnSparse*)list->FindObject("fHistMCKorelacie");
    THnSparse *fHistNumberOfTriggersGen = (THnSparse*)list->FindObject("fHistNumberOfTriggersGen");
    THnSparse *fHistNumberOfTriggersRec = (THnSparse*)list->FindObject("fHistNumberOfTriggersRec");
    
    TH3D *fHistRCPtAs = (TH3D*) gg->Get("fHistRCPtAs");

    const Double_t kPi = TMath::Pi();
    const Int_t nPtBins = 6;
    const Int_t nTig =3;

   // Printf ("x %d y %d z %d\n",fHistRCPtAs->GetXaxis()->GetNbins(),fHistRCPtAs->GetYaxis()->GetNbins(),fHistRCPtAs->GetZaxis()->GetNbins());
   
    const Int_t nEtaBins = fHistKorelacieRec->GetAxis(7)->GetNbins();
   // Printf("nEtaBins %d\n",nEtaBins);
    const Int_t nVzBins = fHistKorelacieRec->GetAxis(4)->GetNbins();
    const Int_t nPtAssocBins = fHistKorelacieRec->GetAxis(1)->GetNbins();

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
    char hname2dvela[50];

    TH1D **fHistPartRec = new TH1D*[nPtBins];
    THnSparse **fHistPartCloneRec = new THnSparse*[nPtBins];
    char hnameentrec[50];
    TCanvas *gen=new TCanvas();
    gen->Divide(1,nPtBins);

    TCanvas *rec=new TCanvas();
    rec->Divide(1,nPtBins);
    
    Double_t sclale[10][10][13];
    Int_t k3D =0;
    for(Int_t k=0;k<nEtaBins; k++){
        Int_t l3D =0;
        for (Int_t l=0; l<nVzBins; l++) {
            for (Int_t m=0; m<nPtAssocBins; m++){
                // Printf("%g %d %d %d \n",fHistRCPtAs->GetBinContent(m+1,l3D+1,k3D+1),k,l,m);
                sclale[k3D][l3D][m]=fHistRCPtAs->GetBinContent(m+1,l3D+1,k3D+1);
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
    TFile *fNewFile = TFile::Open("McClosureLocal12.root","RECREATE");
    for(Int_t i=0;i<nTig;i++){   // looop cez druhy triggra
        fHistCorTypeMC[i]=fHistMCKorelacie->Clone();
        if(i==0) fHistCorTypeMC[i]->GetAxis(5)->SetRange(i+1,i+1);
        if(i==1) fHistCorTypeMC[i]->GetAxis(5)->SetRange(i+1,i+2);
        if(i==2) fHistCorTypeMC[i]->GetAxis(5)->SetRange(i+2,i+2);

        fHistCorTyperec[i]=fHistKorelacieRec->Clone();
        if(i==0) fHistCorTyperec[i]->GetAxis(5)->SetRange(i+1,i+1);
        if(i==1) fHistCorTyperec[i]->GetAxis(5)->SetRange(i+1,i+2);
        if(i==2) fHistCorTyperec[i]->GetAxis(5)->SetRange(i+2,i+2);
        
        for(Int_t j=0;j<nPtBins-4;j++){ // loop cez pt triggra
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
        
            Int_t k3D =0;
            
            Int_t nHist =0;
            
            for(Int_t k=0;k<nEtaBins; k++){ //loop cez eta assoc
                Printf("     k %d\n",k);
                THnSparse * tmpHist1 = (THnSparse*)fHistRangePtrec[i*nPtBins+j]->Clone();
                tmpHist1->GetAxis(7)->SetRange(k+1,k+4);
                
                Int_t l3D =0;
                //.Printf("l3D %d\n",l3D);
                for (Int_t l=0; l<nVzBins; l++) {// loop cez vertex biny
                    //Printf("l3D %d\n",l3D);
                    THnSparse *tmpHist2 = (THnSparse*)tmpHist1->Clone();
                    tmpHist2->GetAxis(4)->SetRange(l+1,l+2);
                    
                  /*  if(tmpHist2->Projection(2,3)->GetEntries()<1) {
                        l3D+=1;
                        l+=1;
                        continue;
                    }*/

                    for (Int_t m=0; m<nPtAssocBins; m++){ // loop cez pt assoc

                        THnSparse *tmpHist3 = (THnSparse*)tmpHist2->Clone();
                        tmpHist3->GetAxis(1)->SetRange(m+1,m+1);
                        TH2D * proj2DRac = tmpHist3->Projection(2,3);
                        sprintf(hname2dvela,"%d_%d_%d",m,k3D,l3D);
                        proj2DRac->SetName(hname2dvela);
                        
                        if(proj2DRac->GetEntries()<1) {
                            delete proj2DRac;
                            continue;
                        }
                        //Printf("korr %g\n ",fHistRCPtAs->GetBinContent(m+1,l3D+1,k3D+1));
                        if (k3D==0&&sclale[0][l3D][m]!=0) proj2DRac->Scale(1./sclale[0][l3D][m]);
                        if (k3D==1&&sclale[1][l3D][m]!=0) proj2DRac->Scale(1./sclale[1][l3D][m]);
                        if (k3D==2&&sclale[2][l3D][m]!=0) proj2DRac->Scale(1./sclale[2][l3D][m]);
                        if (k3D==3&&sclale[3][l3D][m]!=0) proj2DRac->Scale(1./sclale[3][l3D][m]);
                        if (k3D==4&&sclale[4][l3D][m]!=0) proj2DRac->Scale(1./sclale[4][l3D][m]);
                        if (k3D==5&&sclale[5][l3D][m]!=0) proj2DRac->Scale(1./sclale[5][l3D][m]);
                        if (k3D==6&&sclale[6][l3D][m]!=0) proj2DRac->Scale(1./sclale[6][l3D][m]);
                        if (k3D==7&&sclale[7][l3D][m]!=0) proj2DRac->Scale(1./sclale[7][l3D][m]);
                        if (k3D==8&&sclale[8][l3D][m]!=0) proj2DRac->Scale(1./sclale[8][l3D][m]);
                        if (k3D==9&&sclale[9][l3D][m]!=0) proj2DRac->Scale(1./sclale[9][l3D][m]);
                        //if(fHistRCPtAs->GetBinContent(m+1,l3D+1,k3D+1)<=0) continue;
                        
                        //proj2DRac->Scale(1./fHistRCPtAs->GetBinContent(m+1,l3D+1,k3D+1));
                       
                        if (nHist==0) fHistRangePtProjPhiEtarec[i*nPtBins+j] =proj2DRac->Clone();
                        else fHistRangePtProjPhiEtarec[i*nPtBins+j]->Add(proj2DRac);
                        nHist+=1;

                        delete proj2DRac;
                        delete tmpHist3;
                    }

                    delete tmpHist2;
                    
                    l3D+=1;
                    l+=1;
                }
                delete tmpHist1;

                k+=3;
                k3D+=1;
            }
            
            Printf("nHist %d\n",nHist);
            
            //fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(./1nHist); // je to zle lebo spocitavam histogrami, ktore sa nijak neprekryvaju
          
            sprintf(hname,"2dproj_%d_pt_%d",i,j);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->SetName(hname);
            sprintf(htitle,"Rec #Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,j);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->SetTitle(htitle);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->RebinX(4);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->RebinY(4);
            if(i==0) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistPartRec[j]->GetBinContent(1)));
            if(i==1) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistPartRec[j]->GetBinContent(2)+fHistPartRec[j]->GetBinContent(3)));
            if(i==2) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistPartRec[j]->GetBinContent(4)));

            cMCrec->cd(i*nPtBins+j+1);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->DrawCopy("lego2z");

            
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

