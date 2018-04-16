void SetHist(TH1D *hist, Int_t mstyle, Color_t mcolor, Color_t lcolor, Float_t msize){
    
    hist->SetMarkerColor(mcolor);
    hist->SetLineColor(lcolor);
    hist->SetMarkerStyle(mstyle);
    hist->SetMarkerSize(msize);
    
};

void MC(){

    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMC15c_10Grid.root ");  //MC2015c_Grid02.root");
    //TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/AnalysisResults.root");
	TList *list = (TList*)g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
    
    TFile *gg = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResults2015a_Grid04.root");
    TList *listg = (TList*)g->Get("MyTask/MyOutputContainer");

    TH3D *fHistMCPtAs = (TH3D*)list->FindObject("fHistMCPtAs");
    TH3D *fHistRCPtAs = (TH3D*)list->FindObject("fHistRCPtAs");
    
    TH3D *fHistMCPtTrigg = (TH3D*)list->FindObject("fHistMCPtTrigg");
    TH3D *fHistRCPtTrigg = (TH3D*)list->FindObject("fHistRCPtTrigg");
    
    THnSparseF *fHistGenV0 = (THnSparseF*)list->FindObject("fHistGenV0");
    THnSparseF *fHistRecV0 = (THnSparseF*)list->FindObject("fHistRecV0");
    
    TH3D *fHistMCPtAs15a = (TH3D*)listg->FindObject("fHistMCPtAs");
    TH3D *fHistRCPtAs15a = (TH3D*)listg->FindObject("fHistRCPtAs");
    
    TH3D *fHistMCPtTrigg15a = (TH3D*)listg->FindObject("fHistMCPtTrigg");
    TH3D *fHistRCPtTrigg15a = (TH3D*)listg->FindObject("fHistRCPtTrigg");
    
    THnSparseF *fHistGenV015a = (THnSparseF*)listg->FindObject("fHistGenV0");
    THnSparseF *fHistRecV015a = (THnSparseF*)listg->FindObject("fHistRecV0");
    
    fHistMCPtAs->Add(fHistMCPtAs15a);
    fHistRCPtAs->Add(fHistRCPtAs15a);
    fHistMCPtTrigg->Add(fHistMCPtTrigg15a);
    fHistRCPtTrigg->Add(fHistRCPtTrigg15a);
    fHistGenV0->Add(fHistGenV015a);
    fHistRecV0->Add(fHistRecV015a);
    
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
    SetHist(fHistMCPtAsPojX,23,kMagenta,kMagenta,1.5);
    
    fHistMCPtAsPojX->SetYTitle("#");
    fHistMCPtAsPojX->SetTitle("Rozdelenie p_{T} pre MC a rekostruovane MC drahy");

    //fHistRCPtAs->Sumw2();
    TH1D* fHistRCPtAsProjX = fHistRCPtAs->ProjectionX();
    fHistRCPtAsProjX->SetName("fHistRCPtAsProjX");
    SetHist(fHistRCPtAsProjX,23,kBlue,kBlue,1.5);

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
    SetHist(histV0GenK0,23,kMagenta,kMagenta,1.5);

    //histV0GenK0->SetAxisRange(0,6000,"y");
    histV0GenK0->SetTitle("ucinnost rekonstrukcie K^0_{S}");
    histV0GenK0->DrawCopy();
    
    
    fHistRecV0->GetAxis(2)->SetRange(1,1);
    TH1D *histV0RecK0 = fHistRecV0->Projection(0);
    histV0RecK0->SetName("histV0RecK0");
    SetHist(histV0RecK0,23,kBlue,kBlue,1.5);
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
    SetHist(histV0GenLam,23,kMagenta,kMagenta,1.5);
    //histV0GenLam->SetAxisRange(0,4000,"y");
    histV0GenLam->SetTitle("ucinnost rekonstrukcie  #Lambda");
    histV0GenLam->DrawCopy();
    
    
    fHistRecV0->GetAxis(2)->SetRange(2,2);
    TH1D *histV0RecLam = fHistRecV0->Projection(0);
    histV0RecLam->SetName("histV0RecLam");
    SetHist(histV0RecLam,23,kBlue,kBlue,1.5);
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
    SetHist(histV0GenALam,23,kMagenta,kMagenta,1.5);
    //histV0GenLam->SetAxisRange(0,4000,"y");
    histV0GenALam->SetTitle("ucinnost rekonstrukcie #bar{#Lambda}");
    histV0GenALam->DrawCopy();
    
    
    fHistRecV0->GetAxis(2)->SetRange(3,3);
    TH1D *histV0RecALam = fHistRecV0->Projection(0);
    histV0RecALam->SetName("histV0RecALam");
    SetHist(histV0RecALam,23,kBlue,kBlue,1.5);
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
    
    SetHist(histV0RecK0,23,kBlue-3,kBlue-3,1.5);
    SetHist(histV0RecLam,21,kGreen-3,kGreen-3,1.5);
    SetHist(histV0RecALam,22,kOrange-3,kOrange-3,1.5);
    SetHist(fHistRCPtAsProjX,29,kRed-3,kRed-3,1.5);
    
    fHistRCPtAsProjX->GetYaxis()->SetRangeUser(0.,0.9);
    fHistRCPtAsProjX->SetXTitle("p_{T}^{trig} (GeV/c)");
    fHistRCPtAsProjX->SetTitle("Ucinnost rekonstrukcie v zavislosti od p_{T}^{trig}");
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
    
    TCanvas *canvasY = new TCanvas;
    TH1D* fHistRCPtAsProjY = fHistRCPtAs->ProjectionY();
    fHistRCPtAsProjY->SetName("fHistRCPtAsProjY");
    fHistGenV0->GetAxis(2)->SetRange(1,1);
    TH1D *histV0GenK0Vz = fHistGenV0->Projection(1);
    histV0GenK0Vz->SetName("histV0GenK0Vz");
    histV0GenK0Vz->RebinX(rebinY);
    fHistGenV0->GetAxis(2)->SetRange(2,2);
    TH1D *histV0GenLamVz = fHistGenV0->Projection(1);
    histV0GenLamVz->SetName("histV0GenLamVz");
    histV0GenLamVz->RebinX(rebinY);
    fHistGenV0->GetAxis(2)->SetRange(3,3);
    TH1D *histV0GenALamVz = fHistGenV0->Projection(1);
    histV0GenALamVz->SetName("histV0GenALamVz");
    histV0GenALamVz->RebinX(rebinY);
    
    TH1D *fHistMCPtAsPojY = fHistMCPtAs->ProjectionY();
    fHistMCPtAsPojY->SetName("fHistMCPtAsPojY");
    fHistRecV0->GetAxis(2)->SetRange(1,1);
    TH1D *histV0RecK0Vz = fHistRecV0->Projection(1);
    histV0RecK0Vz->SetName("histV0RecK0Vz");
    histV0RecK0Vz->RebinX(rebinY);
    fHistRecV0->GetAxis(2)->SetRange(2,2);
    TH1D *histV0RecLamVz = fHistRecV0->Projection(1);
    histV0RecLamVz->SetName("histV0RecLamVz");
    histV0RecLamVz->RebinX(rebinY);
    fHistRecV0->GetAxis(2)->SetRange(3,3);
    TH1D *histV0RecALamVz = fHistRecV0->Projection(1);
    histV0RecALamVz->SetName("histV0RecALamVz");
    histV0RecALamVz->RebinX(rebinY);
    
    fHistRCPtAsProjY->Divide(fHistMCPtAsPojY);
    histV0RecK0Vz->Divide(histV0GenK0Vz);
    histV0RecLamVz->Divide(histV0GenLamVz);
    histV0RecALamVz->Divide(histV0GenALamVz);
    
    fHistRCPtAsProjY->SetXTitle("p_{vz} (cm)");
    fHistRCPtAsProjY->SetTitle("Ucinnost rekonstrukcie v zavislosti od p_{vz}");
    fHistRCPtAsProjY->GetYaxis()->SetRangeUser(0.,0.9);
    
    SetHist(fHistRCPtAsProjY,29,kRed-3,kRed-3,1.5);
    SetHist(histV0RecK0Vz,23,kBlue-3,kBlue-3,1.5);
    SetHist(histV0RecLamVz,21,kGreen-3,kGreen-3,1.5);
    SetHist(histV0RecALamVz,22,kOrange-3,kOrange-3,1.5);
    
    TLegend *lgPvz = new TLegend;
    lgPvz->AddEntry(histV0RecK0Vz,"K^{0}_{S}","pl");
    lgPvz->AddEntry(histV0RecALamVz," #bar{#Lambda}","pl");
    lgPvz->AddEntry(histV0RecLamVz,"#Lambda","pl");
    lgPvz->AddEntry(fHistRCPtAsProjY,"nabity hadron","pl");
    
    fHistRCPtAsProjY->SetStats(kFALSE);
    fHistRCPtAsProjY->DrawCopy();
    histV0RecK0Vz->DrawCopy("same");
    histV0RecALamVz->DrawCopy("same");
    histV0RecLamVz->DrawCopy("same");
    lgPvz->Draw();
    
    TCanvas *canvasZ = new TCanvas;
    
    TH1D* fHistRCPtAsProjZ = fHistRCPtAs->ProjectionZ();
    fHistRCPtAsProjZ->SetName("fHistRCPtAsProjZ");
    fHistGenV0->GetAxis(2)->SetRange(1,1);
    TH1D *histV0GenK0Eta = fHistGenV0->Projection(3);
    histV0GenK0Eta->SetName("histV0GenK0Eta");
    histV0GenK0Eta->RebinX(rebinZ);
    fHistGenV0->GetAxis(2)->SetRange(2,2);
    TH1D *histV0GenLamEta = fHistGenV0->Projection(3);
    histV0GenLamEta->SetName("histV0GenLamEta");
    histV0GenLamEta->RebinX(rebinZ);
    fHistGenV0->GetAxis(2)->SetRange(3,3);
    TH1D *histV0GenALamEta = fHistGenV0->Projection(3);
    histV0GenALamEta->SetName("histV0GenALamEta");
    histV0GenALamEta->RebinX(rebinZ);
    
    TH1D *fHistMCPtAsPojZ = fHistMCPtAs->ProjectionZ();
    fHistMCPtAsPojZ->SetName("fHistMCPtAsPojZ");
    fHistRecV0->GetAxis(2)->SetRange(1,1);
    TH1D *histV0RecK0Eta = fHistRecV0->Projection(3);
    histV0RecK0Eta->SetName("histV0RecK0Eta");
    histV0RecK0Eta->RebinX(rebinZ);
    fHistRecV0->GetAxis(2)->SetRange(2,2);
    TH1D *histV0RecLamEta = fHistRecV0->Projection(3);
    histV0RecLamEta->SetName("histV0RecLamEta");
    histV0RecLamEta->RebinX(rebinZ);
    fHistRecV0->GetAxis(2)->SetRange(3,3);
    TH1D *histV0RecALamEta = fHistRecV0->Projection(3);
    histV0RecALamEta->SetName("histV0RecALamEta");
    histV0RecALamEta->RebinX(rebinZ);
    
    fHistRCPtAsProjZ->Divide(fHistMCPtAsPojZ);
    histV0RecK0Eta->Divide(histV0GenK0Eta);
    histV0RecLamEta->Divide(histV0GenLamEta);
    histV0RecALamEta->Divide(histV0GenALamEta);
    
    fHistRCPtAsProjZ->SetXTitle("#eta");
    fHistRCPtAsProjZ->SetTitle("Ucinnost rekonstrukcie v zavislosti od #eta");
    fHistRCPtAsProjZ->GetYaxis()->SetRangeUser(0.,0.9);
    
    SetHist(fHistRCPtAsProjZ,29,kRed-3,kRed-3,1.5);
    SetHist(histV0RecK0Eta,23,kBlue-3,kBlue-3,1.5);
    SetHist(histV0RecLamEta,21,kGreen-3,kGreen-3,1.5);
    SetHist(histV0RecALamEta,22,kOrange-3,kOrange-3,1.5);
    
    TLegend *lgEta = new TLegend;
    lgEta->AddEntry(histV0RecK0Eta,"K^{0}_{S}","pl");
    lgEta->AddEntry(histV0RecALamEta," #bar{#Lambda}","pl");
    lgEta->AddEntry(histV0RecLamEta,"#Lambda","pl");
    lgEta->AddEntry(fHistRCPtAsProjZ,"nabity hadron","pl");
    
    fHistRCPtAsProjZ->SetStats(kFALSE);
    fHistRCPtAsProjZ->DrawCopy();
    histV0RecK0Eta->DrawCopy("same");
    histV0RecLamEta->DrawCopy("same");
    histV0RecALamEta->DrawCopy("same");
    lgEta->Draw();
    
    TFile *fNewFile = TFile::Open("EfiiciencyMC15c+a_04.root","RECREATE");
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
    /*
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
           /* sprintf(nameEff,"eff_%d_%d",i,j);
            
            TH1D * fHistPtPvzEtaGen = fHistMCKorelGen->Projection(1);
            TH1D * fHistPtPvzEtaRec = fHistMCKorelRec->Projection(1);
            
          /*  fHistPtPvzEtaGen->RebinZ(rebinZ);
            fHistPtPvzEtaGen->RebinY(rebinY);
            fHistPtPvzEtaRec->RebinZ(rebinZ);
            fHistPtPvzEtaRec->RebinY(rebinY);
            */
         /*   fHistPtPvzEtaRec->Divide(fHistPtPvzEtaGen);
            fHistPtPvzEtaRec->SetName(nameEff);
            fHistPtPvzEtaRec->Write();
            
            delete fHistPtPvzEtaGen;
            delete fHistPtPvzEtaRec;
            
            fHistMCKorelGen->GetAxis(0)->SetRange(0,-1);
            fHistMCKorelRec->GetAxis(0)->SetRange(0,-1);
        }
        
        
        fHistMCKorelGen->GetAxis(5)->SetRange(0,-1);
        fHistMCKorelRec->GetAxis(5)->SetRange(0,-1);
        
    }*/
    
    fNewFile->Close();
}
