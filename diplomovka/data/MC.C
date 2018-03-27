#include <TH1D.h>

void MC(){

    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMC2015c_Grid07.root ");  //MC2015c_Grid02.root");
    //TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/AnalysisResults.root");
	TList *list = (TList*)g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy

    TH3D *fHistMCPtAs = (TH3D*)list->FindObject("fHistMCPtAs");
    TH3D *fHistRCPtAs = (TH3D*)list->FindObject("fHistRCPtAs");
    
    TH3D *fHistMCPtTrigg = (TH3D*)list->FindObject("fHistMCPtTrigg");
    TH3D *fHistRCPtTrigg = (TH3D*)list->FindObject("fHistRCPtTrigg");
    
    THnSparseF *fHistGenV0 = (THnSparseF*)list->FindObject("fHistGenV0");
    THnSparseF *fHistRecV0 = (THnSparseF*)list->FindObject("fHistRecV0");
    
    const Int_t rebinZ = 2;
    const Int_t rebinY = 2;

    TCanvas *c1 = new TCanvas("c1","",600,800);
	TPad* pad1 = new TPad("pad1","This is pad1",0.001,0.3,0.999,0.999);
	TPad* pad2 = new TPad("pad2","This is pad2",0.001,0.001,0.999,0.3);
	Printf ("x %d y %d z %d\n",fHistRCPtAs->GetXaxis()->GetNbins(),fHistRCPtAs->GetYaxis()->GetNbins(),fHistRCPtAs->GetZaxis()->GetNbins());
	pad1->SetMargin(0.1,0.1,0,0.1);  
	pad2->SetMargin(0.1,0.1,0.2,0);
	
	pad1->Draw();
    pad2->Draw();
   
    fHistMCPtAs->RebinZ(rebinZ);
    fHistMCPtAs->RebinY(rebinY);
    fHistRCPtAs->RebinZ(rebinZ);
    fHistRCPtAs->RebinY(rebinY);
    
    fHistMCPtTrigg->RebinZ(rebinZ);
    fHistMCPtTrigg->RebinY(rebinY);
    fHistRCPtTrigg->RebinZ(rebinZ);
    fHistRCPtTrigg->RebinY(rebinY);
    
    //fHistMCPtAs->Sumw2();
    TH1D *fHistMCPtAsPojX = fHistMCPtAs->ProjectionX();
    fHistMCPtAsPojX->SetName("fHistMCPtAsPojX");
    fHistMCPtAsPojX->SetMarkerStyle(23);
    fHistMCPtAsPojX->SetMarkerSize(1.5);
    fHistMCPtAsPojX->SetMarkerColor(kMagenta);
    
    fHistMCPtAsPojX->SetYTitle("#");
    fHistMCPtAsPojX->SetTitle("Rozdelenie p_{T} pre MC a rekostruovane MC drahy");

    //fHistRCPtAs->Sumw2();
    TH1D* fHistRCPtAsProjX = fHistRCPtAs->ProjectionX();
    fHistRCPtAsProjX->SetName("fHistRCPtAsProjX");
    fHistRCPtAsProjX->SetMarkerStyle(23);
    fHistRCPtAsProjX->SetMarkerSize(1.5);
    fHistRCPtAsProjX->SetMarkerColor(kBlue);

    TLegend *lg1 = new TLegend(0.2,0.9,0.75,0.8);
	lg1->AddEntry(fHistMCPtAsPojX,"MC generovane drahy","pl");
	lg1->AddEntry(fHistRCPtAsProjX,"rekonstruovane MC drahy","pl");

    pad1->cd();
    pad1->SetLogy();
    fHistMCPtAsPojX->SetStats(kFALSE);
    fHistMCPtAsPojX->DrawCopy();
    fHistRCPtAsProjX->DrawCopy("same");
    lg1->Draw();

    pad2->cd();
    fHistRCPtAsProjX->Divide(fHistMCPtAsPojX);
    fHistRCPtAsProjX->SetXTitle("p_{T} (GeV)");
    fHistRCPtAsProjX->SetTitle("");
    fHistRCPtAsProjX->SetYTitle("");
    fHistRCPtAsProjX->SetStats(kFALSE);
    fHistRCPtAsProjX->DrawCopy();

    TF1 *f1 = new TF1("fiting","[0]",0,15);
    f1->SetParameter(0,0.8);
    //f1->Draw();
    //fHistRCPtAsProjX->Fit("fiting");

    TCanvas *cK0 = new TCanvas("c2","",600,800);
    TPad* padK01 = new TPad("padK01","This is padK01",0.001,0.3,0.999,0.999);
    TPad* padK02 = new TPad("padK02","This is padK02",0.001,0.001,0.999,0.3);
    
    padK01->SetMargin(0.1,0.1,0,0.1);
    padK02->SetMargin(0.1,0.1,0.2,0);
    
    padK01->Draw();
    padK02->Draw();
    
    padK01->cd();
    
    fHistGenV0->GetAxis(2)->SetRange(1,1);
    TH1D *histV0GenK0 = fHistGenV0->Projection(0);
    histV0GenK0->SetName("histV0GenK0");
    histV0GenK0->SetMarkerStyle(23);
    histV0GenK0->SetMarkerSize(1.5);
    histV0GenK0->SetMarkerColor(kMagenta);
    histV0GenK0->SetLineColor(kMagenta);
    //histV0GenK0->SetAxisRange(0,6000,"y");
    histV0GenK0->SetTitle("ucinnost rekonstrukcie K^0_{S}");
    histV0GenK0->DrawCopy();
    
    
    fHistRecV0->GetAxis(2)->SetRange(1,1);
    TH1D *histV0RecK0 = fHistRecV0->Projection(0);
    histV0RecK0->SetName("histV0RecK0");
    histV0RecK0->SetMarkerStyle(23);
    histV0RecK0->SetMarkerSize(1.5);
    histV0RecK0->SetMarkerColor(kBlue);
    histV0RecK0->SetLineColor(kBlue);
    histV0RecK0->DrawCopy("same");
    
    TLegend *lg2 = new TLegend(0.2,0.9,0.75,0.8);
    lg2->AddEntry(histV0GenK0,"MC generovane K0","pl");
    lg2->AddEntry(histV0RecK0,"rekonstruovane MC K0","pl");
    lg2->Draw();
    
  
    padK02->cd();
    histV0RecK0->Divide(histV0GenK0);
    histV0RecK0->SetXTitle("p_{T} (GeV)");
    histV0RecK0->SetTitle("");
    histV0RecK0->SetYTitle("");
    histV0RecK0->SetStats(kFALSE);
    histV0RecK0->DrawCopy();
    
    fHistRecV0->GetAxis(2)->SetRange(-1,0);
    fHistGenV0->GetAxis(2)->SetRange(-1,0);
    
    TCanvas *cLam = new TCanvas("c3","",600,800);
    TPad* padLam1 = new TPad("padLam1","This is padLam1",0.001,0.3,0.999,0.999);
    TPad* padLam2 = new TPad("padLam2","This is padLam2",0.001,0.001,0.999,0.3);
    
    padLam1->SetMargin(0.1,0.1,0,0.1);
    padLam2->SetMargin(0.1,0.1,0.2,0);
    
    padLam1->Draw();
    padLam2->Draw();
    
    padLam1->cd();
    
    fHistGenV0->GetAxis(2)->SetRange(2,2);
    TH1D *histV0GenLam = fHistGenV0->Projection(0);
    histV0GenLam->SetName("histV0GenLam");
    histV0GenLam->SetMarkerStyle(23);
    histV0GenLam->SetMarkerSize(1.5);
    histV0GenLam->SetMarkerColor(kMagenta);
    histV0GenLam->SetLineColor(kMagenta);
    //histV0GenLam->SetAxisRange(0,4000,"y");
    histV0GenLam->SetTitle("ucinnost rekonstrukcie  #Lambda");
    histV0GenLam->DrawCopy();
    
    
    fHistRecV0->GetAxis(2)->SetRange(2,2);
    TH1D *histV0RecLam = fHistRecV0->Projection(0);
    histV0RecLam->SetName("histV0RecLam");
    histV0RecLam->SetMarkerStyle(23);
    histV0RecLam->SetMarkerSize(1.5);
    histV0RecLam->SetMarkerColor(kBlue);
    histV0RecLam->SetLineColor(kBlue);
    histV0RecLam->DrawCopy("same");
    
    TLegend *lg3 = new TLegend(0.2,0.9,0.75,0.8);
    lg3->AddEntry(histV0GenLam,"MC generovane #Lambda","pl");
    lg3->AddEntry(histV0RecLam,"rekonstruovane MC #Lambda ","pl");
    lg3->Draw();
    
    
    padLam2->cd();
    histV0RecLam->Divide(histV0GenLam);
    histV0RecLam->SetXTitle("p_{T} (GeV)");
    histV0RecLam->SetTitle("");
    histV0RecLam->SetYTitle("");
    histV0RecLam->SetStats(kFALSE);
    histV0RecLam->DrawCopy();
    
    fHistRecV0->GetAxis(2)->SetRange(-1,0);
    fHistGenV0->GetAxis(2)->SetRange(-1,0);
    
    TCanvas *cALam = new TCanvas("c5","",600,800);
    TPad* padALam1 = new TPad("padALam1","This is padALam1",0.001,0.3,0.999,0.999);
    TPad* padALam2 = new TPad("padALam2","This is padALam2",0.001,0.001,0.999,0.3);
    
    padALam1->SetMargin(0.1,0.1,0,0.1);
    padALam2->SetMargin(0.1,0.1,0.2,0);
    
    padALam1->Draw();
    padALam2->Draw();
    
    padALam1->cd();
    
    fHistGenV0->GetAxis(2)->SetRange(3,3);
    TH1D *histV0GenALam = fHistGenV0->Projection(0);
    histV0GenALam->SetName("histV0GenALam");
    histV0GenALam->SetMarkerStyle(23);
    histV0GenALam->SetMarkerSize(1.5);
    histV0GenALam->SetMarkerColor(kMagenta);
    histV0GenALam->SetLineColor(kMagenta);
    //histV0GenLam->SetAxisRange(0,4000,"y");
    histV0GenALam->SetTitle("ucinnost rekonstrukcie #bar{#Lambda}");
    histV0GenALam->DrawCopy();
    
    
    fHistRecV0->GetAxis(2)->SetRange(3,3);
    TH1D *histV0RecALam = fHistRecV0->Projection(0);
    histV0RecALam->SetName("histV0RecALam");
    histV0RecALam->SetMarkerStyle(23);
    histV0RecALam->SetMarkerSize(1.5);
    histV0RecALam->SetMarkerColor(kBlue);
    histV0RecALam->SetLineColor(kBlue);
    histV0RecALam->DrawCopy("same");
    
    TLegend *lg4 = new TLegend(0.2,0.9,0.75,0.8);
    lg4->AddEntry(histV0GenALam,"MC generovane #bar{#Lambda}","pl");
    lg4->AddEntry(histV0RecALam,"rekonstruovane #bar{#Lambda}","pl");
    lg4->Draw();
    
    
    padALam2->cd();
    histV0RecALam->Divide(histV0GenALam);
    histV0RecALam->SetXTitle("p_{T} (GeV)");
    histV0RecALam->SetTitle("");
    histV0RecALam->SetYTitle("");
    histV0RecALam->SetStats(kFALSE);
    histV0RecALam->DrawCopy();
    
    TCanvas *canvas = new TCanvas;
    
    histV0RecK0->SetMarkerColor(kGreen);
    fHistRCPtAsProjX->GetYaxis()->SetRangeUser(0.,0.9);
    histV0RecK0->SetMarkerStyle(20);
    histV0RecK0->SetLineColor(kGreen);
    histV0RecLam->SetMarkerColor(28);
    histV0RecLam->SetMarkerStyle(21);
    histV0RecLam->SetLineColor(28);
    histV0RecALam->SetMarkerStyle(22);
    fHistRCPtAsProjX->SetMarkerColor(kRed);
    fHistRCPtAsProjX->SetLineColor(kRed);
    
    fHistRCPtAsProjX->SetXTitle("p_T (GeV/c)");
    fHistRCPtAsProjX->SetTitle("Ucinnost rekonstrukcie");
    fHistRCPtAsProjX->DrawCopy();
    histV0RecK0->DrawCopy("same");
    histV0RecLam->DrawCopy("same");
    histV0RecALam->DrawCopy("same");
    
    TLegend *lg5 = new TLegend(0.2,0.9,0.75,0.8);
    lg5->AddEntry(histV0RecK0,"K^{0}_{S}","pl");
    lg5->AddEntry(histV0RecALam," #bar{#Lambda}","pl");
    lg5->AddEntry(histV0RecLam,"#Lambda","pl");
    lg5->AddEntry(fHistRCPtAsProjX,"nabity hadron","pl");
    lg5->Draw();
    
    
    TFile *fNewFile = TFile::Open("EfiiciencyMC15c_07.root","RECREATE");
    fHistRCPtAsProjX->Write();
    histV0RecK0->Write();
    histV0RecLam->Write();
    histV0RecALam->Write();
    fHistRCPtAs->Divide(fHistMCPtAs);
    TCanvas * cccc = new TCanvas;
    fHistRCPtAs->DrawCopy("colz");
    fHistRCPtAs->Write();
    
    fHistRCPtTrigg->Divide(fHistMCPtTrigg);
    TCanvas * ccccc = new TCanvas;
    fHistRCPtTrigg->DrawCopy("colz");
    fHistRCPtTrigg->Write();
    
    fHistGenV0->GetAxis(2)->SetRange(1,1);
    TH3D *fHistGenV03DK0 = fHistGenV0->Projection(0,1,3);
    fHistGenV03DK0->SetName("fHistGenV03DK0");
    fHistRecV0->GetAxis(2)->SetRange(1,1);
    TH3D *fHistRecV03DK0 = fHistRecV0->Projection(0,1,3);
    fHistRecV03DK0->SetName("fHistRecV03DK0");
    
    fHistGenV03DK0->RebinZ(rebinZ);
    fHistGenV03DK0->RebinY(rebinY);
    fHistRecV03DK0->RebinZ(rebinZ);
    fHistRecV03DK0->RebinY(rebinY);
    
    fHistRecV03DK0->Divide(fHistGenV03DK0);
    fHistRecV03DK0->Write();
    
    fHistGenV0->GetAxis(2)->SetRange(-1,0);
    fHistRecV0->GetAxis(2)->SetRange(-1,0);
    
    fHistGenV0->GetAxis(2)->SetRange(2,2);
    TH3D *fHistGenV03DLam = fHistGenV0->Projection(0,1,3);
    fHistGenV03DLam->SetName("fHistGenV03DLam");
    fHistRecV0->GetAxis(2)->SetRange(2,2);
    TH3D *fHistRecV03DLam = fHistRecV0->Projection(0,1,3);
    fHistRecV03DLam->SetName("fHistRecV03DLam");
    
    fHistGenV03DLam->RebinZ(rebinZ);
    fHistGenV03DLam->RebinY(rebinY);
    fHistRecV03DLam->RebinZ(rebinZ);
    fHistRecV03DLam->RebinY(rebinY);
    
    fHistRecV03DLam->Divide(fHistGenV03DLam);
    fHistRecV03DLam->Write();
    
    fHistGenV0->GetAxis(2)->SetRange(3,3);
    TH3D *fHistGenV03DALam = fHistGenV0->Projection(0,1,3);
    fHistGenV03DALam->SetName("fHistGenV03DAntiLam");
    fHistRecV0->GetAxis(2)->SetRange(3,3);
    TH3D *fHistRecV03DALam = fHistRecV0->Projection(0,1,3);
    fHistRecV03DALam->SetName("fHistRecV03DAntiLam");
    
    fHistGenV03DALam->RebinZ(rebinZ);
    fHistGenV03DALam->RebinY(rebinY);
    fHistRecV03DALam->RebinZ(rebinZ);
    fHistRecV03DALam->RebinY(rebinY);
    
    fHistRecV03DALam->Divide(fHistGenV03DALam);
    fHistRecV03DALam->Write();
    
    THnSparseF *fHistMCKorelGen = (THnSparseF*)list->FindObject("fHistMCKorelacie");
    THnSparseF *fHistMCKorelRec = (THnSparseF*)list->FindObject("fHistKorelacieMCrec");
    
    char nameEff[20];
    
    for(Int_t i=0;i<3; i++) { //loop cez druh trigg
        if(i==0){
            fHistMCKorelGen->GetAxis(5)->SetRange(1,1);
            fHistMCKorelRec->GetAxis(5)->SetRange(1,1);
        }
        if(i==1){
            fHistMCKorelGen->GetAxis(5)->SetRange(2,3);
            fHistMCKorelRec->GetAxis(5)->SetRange(2,3);
        }
        if(i==3) {
            fHistMCKorelGen->GetAxis(5)->SetRange(4,4);
            fHistMCKorelRec->GetAxis(5)->SetRange(4,4);
        }
        for(Int_t j=0; j<11; j++){ //loop cez pt trigg
           // if (j==0) {
                fHistMCKorelGen->GetAxis(0)->SetRange(j+1,j+1);
                fHistMCKorelRec->GetAxis(0)->SetRange(j+1,j+1);
          /*  }
            if (j==1) {
                fHistMCKorelGen->GetAxis(0)->SetRange(2,2);
                fHistMCKorelRec->GetAxis(0)->SetRange(2,2);
            }
            if (j==2){
                fHistMCKorelGen->GetAxis(0)->SetRange(3,3);
                fHistMCKorelRec->GetAxis(0)->SetRange(3,3);
            }
            if (j==3) {
                fHistMCKorelGen->GetAxis(0)->SetRange(4,5);
                fHistMCKorelRec->GetAxis(0)->SetRange(4,5);
            }
            if (j==4) {
                fHistMCKorelGen->GetAxis(0)->SetRange(6,7);
                fHistMCKorelRec->GetAxis(0)->SetRange(6,7);
            }
            if (j==5) {
                fHistMCKorelGen->GetAxis(0)->SetRange(8,11);
                fHistMCKorelRec->GetAxis(0)->SetRange(8,11);
            }
            */
            sprintf(nameEff,"eff_%d_%d",i,j);
            
            TH1D * fHistPtPvzEtaGen = fHistMCKorelGen->Projection(1);
            TH1D * fHistPtPvzEtaRec = fHistMCKorelRec->Projection(1);
            
          /*  fHistPtPvzEtaGen->RebinZ(rebinZ);
            fHistPtPvzEtaGen->RebinY(rebinY);
            fHistPtPvzEtaRec->RebinZ(rebinZ);
            fHistPtPvzEtaRec->RebinY(rebinY);
            */
            fHistPtPvzEtaRec->Divide(fHistPtPvzEtaGen);
            fHistPtPvzEtaRec->SetName(nameEff);
            fHistPtPvzEtaRec->Write();
            
            delete fHistPtPvzEtaGen;
            delete fHistPtPvzEtaRec;
            
            fHistMCKorelGen->GetAxis(0)->SetRange(0,-1);
            fHistMCKorelRec->GetAxis(0)->SetRange(0,-1);
        }
        
        
        fHistMCKorelGen->GetAxis(5)->SetRange(0,-1);
        fHistMCKorelRec->GetAxis(5)->SetRange(0,-1);
        
    }
    
    fNewFile->Close();
}
