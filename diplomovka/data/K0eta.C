#include <TFile.h>

void K0eta(){
    
    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMC2015a+c_01.root");
    TList *list = (TList*) g->Get("MyTask/MyOutputContainer");
    
    THnSparse *fHistKorelacieRec = (THnSparse*)list->FindObject("fHistKorelacieMCrec");
    THnSparse *fHistMCKorelacie = (THnSparse*)list->FindObject("fHistMCKorelacie");
    
    TFile *gg = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/EfiiciencyMC15a+c_01.root");
    TH3D *fHistEff3DK0 = (TH3D*) gg->Get("fHistRecV03DK0");
    
    fHistKorelacieRec->GetAxis(0)->SetRange(8,11);
    fHistMCKorelacie->GetAxis(0)->SetRange(8,11);
    
    fHistKorelacieRec->GetAxis(5)->SetRange(1,1);
    fHistMCKorelacie->GetAxis(5)->SetRange(1,1);
    
    TH1D * etaK0gen = (TH1D*) fHistMCKorelacie ->Projection(6);
    TH1D * etaK0rec = (TH1D*) fHistKorelacieRec ->Projection(6);
    
    TH1D * etaassocgen = (TH1D*) fHistMCKorelacie ->Projection(7);
    TH1D * etaassocrec = (TH1D*) fHistKorelacieRec ->Projection(7);
    
    etaK0gen->SetLineColor(kBlack);
    etaK0rec->SetLineColor(kRed);
    
    etaassocgen->SetLineColor(kBlack);
    etaassocrec->SetLineColor(kRed);
    
    TCanvas *canK0 = new TCanvas;
    TPad* pad1 = new TPad("pad1","This is pad1",0.001,0.3,0.999,0.999);
    TPad* pad2 = new TPad("pad2","This is pad2",0.001,0.001,0.999,0.3);

    pad1->SetMargin(0.1,0.1,0,0.1);
    pad2->SetMargin(0.1,0.1,0.2,0);
    
    pad1->Draw();
    pad2->Draw();
    pad1->cd();
    etaK0gen->DrawCopy();
    etaK0rec->DrawCopy("same");
    pad2->cd();
    etaK0gen->Divide(etaK0rec);
    etaK0gen->DrawCopy();
    
    TCanvas *canAssoc = new TCanvas;
    TPad* pad3 = new TPad("pad3","This is pad3",0.001,0.3,0.999,0.999);
    TPad* pad4 = new TPad("pad4","This is pad4",0.001,0.001,0.999,0.3);

    pad3->SetMargin(0.1,0.1,0,0.1);
    pad4->SetMargin(0.1,0.1,0.2,0);
    
    pad3->Draw();
    pad4->Draw();
    pad3->cd();
    etaassocgen->DrawCopy();
    etaassocrec->DrawCopy("same");
    pad4->cd();
    etaassocgen->Divide(etaassocrec);
    etaassocgen->DrawCopy();
    
    TH2D * fHistTrigGen2D = (TH2D * ) fHistMCKorelacie->Projection(6,8);
    
    const Int_t nVzBins = fHistKorelacieRec->GetAxis(4)->GetNbins();
    const Int_t nEtaBins = fHistKorelacieRec->GetAxis(6)->GetNbins();
    Double_t scale =0;
    Int_t l3D =0;
    Int_t nHist =0;
    TH2D *fHistTrig2D = 0x0;
    char hname2dvela[10];
    for (Int_t l=0; l<nVzBins; l++) {
         THnSparse * tmpHist1 = (THnSparse*)fHistKorelacieRec->Clone();
        tmpHist1->GetAxis(4)->SetRange(l+1,l+1);
        //Printf("-- k %d -- \n",k);
        
        Int_t k3D =0;
        
        for(Int_t k=0;k<nEtaBins; k++){
            //THnSparse * tmpHist2 = (THnSparse*)tmpHist1->Clone();
            //tmpHist2->GetAxis(6)->SetRange(k+1,k+3);
            Printf("+++ k %d +++ \n",k);
            scale = (fHistEff3DK0->GetBinContent(8,l3D+1,k3D+1)+fHistEff3DK0->GetBinContent(9,l3D+1,k3D+1)+fHistEff3DK0->GetBinContent(11,l3D+1,k3D+1)+fHistEff3DK0->GetBinContent(9,l3D+1,k3D+1))/4;
            TH2D * proj2D = (TH2D *)tmpHist1->Projection(6,8);
            
            sprintf(hname2dvela,"%d_%d",k3D,l3D);
            proj2D->SetName(hname2dvela);
            
            proj2D->GetYaxis()->SetRange(k+1,k+3);
            
            if (scale !=0 ) proj2D->Scale(1./scale);
            else proj2D->Scale(1./0.35);
            
            proj2D->GetYaxis()->SetRange(0,-1);
            
            Printf(" scale %g\n", scale);
            if(k==36){
                if (nHist==0) fHistTrig2D=(TH2D *)proj2D->Clone();
                else {
                    fHistTrig2D->Add(proj2D);
                }
                nHist+=1;
            }
            
            //delete tmpHist2;
            delete proj2D;
            
            k3D+=1;
            k+=3;
        }
        delete tmpHist1;
        l+=1;
        l3D+=1;
    }

fHistTrigGen2D->Divide(fHistTrig2D);
    
    TCanvas *aa = new TCanvas();
    fHistTrigGen2D->DrawCopy("colz");
    
    TH1D * fHistProjPhi= (TH1D*) fHistTrigGen2D->ProjectionY();
    fHistProjPhi->SetName("projPhi");
    
    TH1D * fHistProjEta = (TH1D*) fHistTrigGen2D->ProjectionX();
    fHistProjEta->SetName("projEta");
    
    Int_t nBinsEta = fHistProjEta->GetNbinsX();
    Int_t nBinsPhi = fHistProjPhi->GetNbinsX();
    
    for (Int_t k=0; k<nBinsEta; k++){
        
        Double_t scaleEta=0;
        Double_t chybaEta=0;
        for(Int_t l=0; l<(nBinsPhi); l++){
            if(fHistTrigGen2D->GetBinContent(k+1,l+1)>0) {
                scaleEta++;
                chybaEta+=TMath::Power(fHistTrigGen2D->GetBinError(k+1,l+1),2);
            }
            
        }
        if(scaleEta>0) fHistProjEta->SetBinContent(k+1,(fHistProjEta->GetBinContent(k+1))/scaleEta);
        chybaEta=TMath::Sqrt(chybaEta);
        chybaEta=chybaEta/scaleEta;
        fHistProjEta->SetBinError(k+1,chybaEta);
    }
    
    for (Int_t k=0; k<nBinsPhi; k++){
        Double_t scalePhi=0;
        Double_t chybaPhi=0;
        Double_t hodnotaPhi = 0;
        for(Int_t l=0; l<nBinsEta; l++){
            if(fHistTrigGen2D->GetBinContent(l+1,k+1)>0) {
                scalePhi++;
                hodnotaPhi+=fHistTrigGen2D->GetBinContent(l+1,k+1);
                chybaPhi+=TMath::Power(fHistTrigGen2D->GetBinError(l+1,k+1),2);
            }
        }

        if(scalePhi>0) fHistProjPhi->SetBinContent(k+1,hodnotaPhi/scalePhi);
        else fHistProjPhi->SetBinContent(k+1,0);
        chybaPhi=TMath::Sqrt(chybaPhi);
        if(scalePhi>0) chybaPhi=chybaPhi/scalePhi;
        else chybaPhi=0;
        fHistProjPhi->SetBinError(k+1,chybaPhi);
        
        
    }

    TFile *fNewFile = TFile::Open("K0eta.root","RECREATE");
    fHistTrigGen2D->Write();
    fHistProjEta->Write();
    fHistProjPhi->Write();
    fNewFile->Close();
}
