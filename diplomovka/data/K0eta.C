#include <TFile.h>

void K0eta(){
    
    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMC2015c_Grid07.root");
    TList *list = (TList*) g->Get("MyTask/MyOutputContainer");
    
    Bool_t trigg = kFALSE;
    
    char nameGen [20];
    char namerec [20];
    char nameeff [20];
    
    if(trigg){
        sprintf (nameGen,"fHistNumberOfTriggersGen" );
        sprintf (namerec,"fHistNumberOfTriggersRec" );
        sprintf (nameeff,"fHistRecV03DK0" );
    }else{
        sprintf (nameGen,"fHistMCKorelacie" );
        sprintf (namerec,"fHistKorelacieMCrec" );
        sprintf (nameeff,"fHistRCPtTrigg" );
        
    }
    
    THnSparse *fHistKorelacieRec = (THnSparse*)list->FindObject(namerec);
    THnSparse *fHistMCKorelacie = (THnSparse*)list->FindObject(nameGen);
    
    TFile *gg = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/EfiiciencyMC15c_07.root");
    TH3D *fHistEff3DK0 = (TH3D*) gg->Get(nameeff);
    
    fHistKorelacieRec->GetAxis(0)->SetRange(8,11);
    fHistMCKorelacie->GetAxis(0)->SetRange(8,11);
    
    TCanvas *eff = new TCanvas;
    fHistEff3DK0->GetXaxis()->SetRange(8,11);
    fHistEff3DK0->Project3DProfile("yz")->DrawCopy();
    fHistEff3DK0->GetXaxis()->SetRange(0,-1);
    
    if(trigg){
        fHistKorelacieRec->GetAxis(3)->SetRange(1,1);
        fHistMCKorelacie->GetAxis(3)->SetRange(1,1);
    }else{
        fHistKorelacieRec->GetAxis(5)->SetRange(1,1);
        fHistMCKorelacie->GetAxis(5)->SetRange(1,1);
    }
    
    TH1D * etaK0gen = (TH1D*) fHistMCKorelacie ->Projection(4);
    TH1D * etaK0rec = (TH1D*) fHistKorelacieRec ->Projection(4);
    
   // TH1D * etaassocgen = (TH1D*) fHistMCKorelacie ->Projection(7);
    //TH1D * etaassocrec = (TH1D*) fHistKorelacieRec ->Projection(7);
    
    etaK0gen->SetLineColor(kBlack);
    etaK0rec->SetLineColor(kRed);
    
   // etaassocgen->SetLineColor(kBlack);
    //etaassocrec->SetLineColor(kRed);
    
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
    etaK0rec->Divide(etaK0gen);
    etaK0rec->DrawCopy();
    
   /* TCanvas *canAssoc = new TCanvas;
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
    etaassocgen->DrawCopy();*/
    Int_t nEtaBins = 0;
    Int_t nVzBins = 0;
    TH2D * fHistTrigGen2D = 0x0;
    
    if(trigg){
        fHistTrigGen2D = (TH2D * ) fHistMCKorelacie->Projection(2,4);
        nVzBins = fHistKorelacieRec->GetAxis(1)->GetNbins();
        nEtaBins = fHistKorelacieRec->GetAxis(2)->GetNbins();
    }else{
        fHistTrigGen2D = (TH2D * ) fHistMCKorelacie->Projection(7,8);
        nVzBins = fHistKorelacieRec->GetAxis(4)->GetNbins();
        nEtaBins = fHistKorelacieRec->GetAxis(7)->GetNbins();
    }

    Double_t scale =0;
    Int_t nHist =0;
    TH2D *fHistTrig2D = 0x0;
    char hname2dvela[10];
    TCanvas *recraw = new TCanvas;
    fHistKorelacieRec->Projection(7,8)->DrawCopy("lego2z");
    TCanvas *gen = new TCanvas;
    fHistTrigGen2D->DrawCopy("lego2z");
    
    for (Int_t l=0; l<nVzBins; l++) {
        if(trigg) fHistKorelacieRec->GetAxis(1)->SetRange(l+1,l+1);
        else fHistKorelacieRec->GetAxis(4)->SetRange(l+1,l+1);
        //Printf("-- k %d -- \n",k);
        
        for(Int_t i=8; i<12; i++){

            fHistKorelacieRec->GetAxis(0)->SetRange(i,i);
            TH2D * proj2D = 0x0;
            if (trigg) proj2D = (TH2D *)fHistKorelacieRec->Projection(2,4);
            else proj2D = (TH2D *)fHistKorelacieRec->Projection(7,8);
            sprintf(hname2dvela,"_%d",l);
            proj2D->SetName(hname2dvela);
          //  Printf("bin 6 %d\n", proj2D->GetXaxis()->GetNbins());

           for(Int_t k=0;k<nEtaBins; k++){
            //
                //tmpHist2->GetAxis(6)->SetRange(k+1,k+3);
                //Printf("+++ k %d +++ \n",k);
                scale = fHistEff3DK0->GetBinContent(i,l+1,k+1);
                for(Int_t j=0; j<72;j++){
                    //Printf("scale %g for eta bin %d for phi value %s\n",scale,k,proj2D->GetYaxis()->GetBinLabel(j));
                    if(scale!=0){
                        //Printf("scale %g eta %d phi %d \n",scale,k,j);
                        proj2D->SetBinContent(j+1,k+1, (proj2D->GetBinContent(j+1,k+1)/scale));

                    }/*else if (trigg){
                        proj2D->SetBinContent(j+1,k+1, (proj2D->GetBinContent(j+1,k+1)/0.3));

                    } else {
                        proj2D->SetBinContent(j+1,k+1, (proj2D->GetBinContent(j+1,k+1)/0.8));

                    }*/
             }
                //proj2D->GetYaxis()->SetRange(k+1,k+3);
            
                //if (scale !=0 ) proj2D->Scale(1./scale);
                //else if (trigg) proj2D->Scale(1./0.5);
                //else
               // proj2D->Scale(1./0.35);
            
                //proj2D->GetYaxis()->SetRange(0,-1);
            
                //Printf(" scale %g\n", scale);
            
                if(k+1==nEtaBins){
                    if (nHist==0) {
                        fHistTrig2D=(TH2D *)proj2D->Clone();
                        nHist+=1;
                    }
                    else {
                        fHistTrig2D->Add(proj2D);
                        nHist+=1;
                    }
                }

            }
            
            fHistKorelacieRec->GetAxis(0)->SetRange(0,-1);
            
            delete proj2D;
            
        }
        
        if(trigg) fHistKorelacieRec->GetAxis(1)->SetRange(0,-1);
        else fHistKorelacieRec->GetAxis(4)->SetRange(0,-1);


    }
    TCanvas *reckor = new TCanvas;
    fHistTrig2D->DrawCopy("lego2z");
   // Printf("max gen %g, max rec %g \n",fHistTrigGen2D->GetMaximum(),fHistTrig2D->GetMaximum() );
    fHistTrig2D->Divide(fHistTrigGen2D);
    TCanvas *aa = new TCanvas();
    fHistTrig2D->DrawCopy("lego2z");
    
    TH1D * fHistProjPhi= (TH1D*) fHistTrig2D->ProjectionX();
    fHistProjPhi->SetName("projPhi");
    fHistProjPhi->SetTitle("projPhi");
    
    TH1D * fHistProjEta = (TH1D*) fHistTrig2D->ProjectionY();
    fHistProjEta->SetName("projEta");
    fHistProjEta->SetTitle("projEta");
    
    Int_t nBinsEta = fHistProjEta->GetNbinsX();
    Int_t nBinsPhi = fHistProjPhi->GetNbinsX();
  //  Printf("bins eta %d bins phi %d\n",nBinsEta, nBinsPhi );
   // Printf("2D bins eta %d bins phi %d\n",fHistTrig2D->GetYaxis()->GetNbins(), fHistTrig2D->GetXaxis()->GetNbins());
    
    for (Int_t k=0; k<nBinsEta; k++){
        
        Double_t scaleEta=0;
        Double_t chybaEta=0;
        for(Int_t l=0; l<nBinsPhi; l++){
            if(fHistTrig2D->GetBinContent(l+1,k+1)>0) {
                scaleEta++;
                chybaEta+=TMath::Power(fHistTrig2D->GetBinError(l+1,k+1),2);
               // Printf ("scale %g, error %g\n",scaleEta,chybaEta);
            }
            
        }
        if(scaleEta>0) fHistProjEta->SetBinContent(k+1,(fHistProjEta->GetBinContent(k+1))/scaleEta);
        else fHistProjEta->SetBinContent(k+1,0);
        chybaEta=TMath::Sqrt(chybaEta);
        if(scaleEta>0) chybaEta=chybaEta/scaleEta;
        else chybaEta =0;
        fHistProjEta->SetBinError(k+1,chybaEta);
    }
    
    for (Int_t k=0; k<nBinsPhi; k++){
        Double_t scalePhi=0;
        Double_t chybaPhi=0;
        Double_t hodnotaPhi = 0;
        for(Int_t l=0; l<nBinsEta; l++){
            if(fHistTrigGen2D->GetBinContent(k+1,l+1)>0) {
                scalePhi++;
                hodnotaPhi+=fHistTrig2D->GetBinContent(k+1,l+1);
                chybaPhi+=TMath::Power(fHistTrig2D->GetBinError(k+1,l+1),2);
            }
        }

        if(scalePhi>0) fHistProjPhi->SetBinContent(k+1,hodnotaPhi/scalePhi);
        else fHistProjPhi->SetBinContent(k+1,0);
        chybaPhi=TMath::Sqrt(chybaPhi);
        if(scalePhi>0) chybaPhi=chybaPhi/scalePhi;
        else chybaPhi=0;
        fHistProjPhi->SetBinError(k+1,chybaPhi);
        
        
    }

    TCanvas *proj = new TCanvas;
    proj->Divide(1,2);
    proj->cd(1);
    fHistProjEta->DrawCopy();
    proj->cd(2);
    fHistProjPhi->DrawCopy();
    TFile *fNewFile = TFile::Open("K0etaAssoc.root","RECREATE");
    fHistTrig2D->Write();
    fHistProjEta->Write();
    fHistProjPhi->Write();
    fNewFile->Close();
}
