

void Graph(){

    gStyle->SetOptStat(0000000000);
    TFile *g =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphMCDataLikeNove.root");
    TFile *f =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphDataNove.root");
                            //DataNove.root");

    TGraphErrors *fGraphMCK0 = (TGraphErrors*) g->Get("fGraphK0Near");
    TGraphErrors *fGraphDataK0 = (TGraphErrors*) f->Get("fGraphK0Near");

    TH1D * fHistK0NearMC = (TH1D*) g->Get("fHistK0Near");
    TH1D * fHistK0NearData = (TH1D*) f->Get("fHistK0Near");

    TGraphErrors *fGraphMCLambda = (TGraphErrors*) g->Get("fGraphLambdaNear");
    TGraphErrors *fGraphDataLambda = (TGraphErrors*) f->Get("fGraphLambdaNear");

    TH1D * fHistLambdaNearMC = (TH1D*) g->Get("fHistLambdaNear");
    TH1D * fHistLambdaNearData = (TH1D*) f->Get("fHistLambdaNear");

    TGraphErrors *fGraphMCAntiL = (TGraphErrors*) g->Get("fGraphAntilambdaNear");
    TGraphErrors *fGraphDataAntiL = (TGraphErrors*) f->Get("fGraphAntilambdaNear");

    TH1D * fHistAntiLNearMC = (TH1D*) g->Get("fHistAntiLambdaNear");
    TH1D * fHistAntiLNearData = (TH1D*) f->Get("fHistAntiLambdaNear");

    TGraphErrors *fGraphMCH = (TGraphErrors*) g->Get("fGraphTrackNear");
    TGraphErrors *fGraphDataH = (TGraphErrors*) f->Get("fGraphTrackNear");

    TH1D * fHistHNearMC = (TH1D*) g->Get("fHistHadronNear");
    TH1D * fHistHNearData = (TH1D*) f->Get("fHistHadronNear");

    fGraphMCK0->SetMarkerColor(kMagenta);
    fGraphMCK0->SetLineColor(kMagenta);

    TLegend *lg = new TLegend(0.2,0.9,0.75,0.8);
    lg->AddEntry(fGraphDataK0,"realne data","pl");
	lg->AddEntry(fGraphMCK0,"MC(Data Like) rekonstruovane data","pl");

     TCanvas *c1 = new TCanvas("c1","",600,800);
	TPad * pad1 = new TPad("pad1","This is pad1",0.001,0.3,0.999,0.999);
	TPad * pad2 = new TPad("pad2","This is pad2",0.001,0.001,0.999,0.3);
	
	pad1->SetMargin(0.1,0.1,0,0.1);  
	pad2->SetMargin(0.1,0.1,0.2,0);
	
	pad1->Draw();
    pad2->Draw();
    pad1->cd();
     
    fGraphMCK0->GetXaxis()->SetRangeUser(4,15);
    fGraphMCK0->SetTitle("Porovnanie zavislosti vytazkov od p_{T}^{trig} pre K^{0}_{S}");
    fGraphMCK0->GetYaxis()->SetTitleSize(0.04);
    fGraphMCK0->GetYaxis()->SetRangeUser(0,1);

    fGraphMCK0->Draw("ap");
    fGraphDataK0->Draw("pSAME");
    lg->Draw();

    Int_t bins = fHistK0NearMC->GetNbinsX();
    Double_t binconMC =0.;
    Double_t binconData =0.;
    Double_t errorMC=0.;
    Double_t errorData=0.;
    Double_t podiel = 0.;
    Double_t chyba = 0.;
    Double_t PtHist[7] = {4, 5, 6, 7, 9, 11, 15};
    TH1D * fHistPodiel = new TH1D ("fHistPodiel","fHistPodiel",bins,PtHist);

    for (Int_t i=1; i<= bins; i++){
        binconMC=fHistK0NearMC->GetBinContent(i);
        binconData=fHistK0NearData->GetBinContent(i);
        errorMC=fHistK0NearMC->GetBinError(i);
        errorData=fHistK0NearData->GetBinError(i);
        podiel=binconMC/binconData;
        fHistPodiel->SetBinContent(i,podiel);

        chyba = TMath::Power(errorMC/binconMC ,2) + TMath::Power(errorData/binconData ,2);
    
        chyba = TMath::Sqrt(chyba);
        cout << chyba << endl; 


        fHistPodiel->SetBinError(i,chyba);        

    }

    pad2->cd();
    fHistPodiel->SetTitle("");
    fHistPodiel->SetYTitle("");
    fHistPodiel->SetXTitle("p_{T} (GeV/c)");
    fHistPodiel->GetXaxis()->SetTitleSize(0.085);
    fHistPodiel->GetXaxis()->SetLabelSize(0.075);
    fHistPodiel->GetYaxis()->SetLabelSize(0.055);
    fHistPodiel->DrawCopy();

    //===================================

   fGraphMCLambda->SetMarkerColor(kMagenta);
    fGraphMCLambda->SetLineColor(kMagenta);

    fGraphDataLambda->SetMarkerColor(kBlue);
    fGraphDataLambda->SetLineColor(kBlue);

    TLegend *lg1 = new TLegend(0.2,0.9,0.75,0.8);
    lg1->AddEntry(fGraphDataLambda,"realne data","pl");
	lg1->AddEntry(fGraphMCLambda,"MC(DataLike) rekonstruovane data","pl");

    TCanvas *c2 = new TCanvas("c2","",600,800);
	TPad * pad21 = new TPad("pad21","This is pad21",0.001,0.3,0.999,0.999);
	TPad * pad22 = new TPad("pad22","This is pad22",0.001,0.001,0.999,0.3);
	
	pad21->SetMargin(0.1,0.1,0,0.1);  
	pad22->SetMargin(0.1,0.1,0.2,0);
	
	pad21->Draw();
    pad22->Draw();
    pad21->cd();
     
    fGraphDataLambda->GetXaxis()->SetRangeUser(4,15);
    fGraphDataLambda->SetTitle("Porovnanie zavislosti vytazkov od p_{T}^{trig} pre #Lambda a #bar{#Lambda}");
    fGraphDataLambda->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphDataLambda->GetYaxis()->SetTitleSize(0.04);
    fGraphDataLambda->GetYaxis()->SetRangeUser(0,1);

    fGraphDataLambda->Draw("ap");
    fGraphMCLambda->Draw("pSAME");
    lg1->Draw();

    Double_t binconMCl =0.;
    Double_t binconDatal =0.;
    Double_t errorMCl=0.;
    Double_t errorDatal=0.;
    Double_t podiell = 0.;
    Double_t chybal = 0.;

    TH1D * fHistPodiell = new TH1D ("fHistPodiell","fHistPodiell",bins,PtHist);

    for (Int_t i=1; i<= bins; i++){
        binconMCl=fHistLambdaNearMC->GetBinContent(i);
        binconDatal=fHistLambdaNearData->GetBinContent(i);
        errorMCl=fHistLambdaNearMC->GetBinError(i);
        errorDatal=fHistLambdaNearData->GetBinError(i);
        podiell=binconMCl/binconDatal;
        fHistPodiell->SetBinContent(i,podiell);

        chybal = TMath::Power(errorMCl/binconMCl ,2) + TMath::Power(errorDatal/binconDatal ,2);
     
        chybal = TMath::Sqrt(chybal);

        fHistPodiell->SetBinError(i,chybal);        

    }

    pad22->cd();
    fHistPodiell->SetTitle("");
    fHistPodiell->SetYTitle("");
    fHistPodiell->SetXTitle("p_{T} (GeV/c)");
    fHistPodiell->GetXaxis()->SetTitleSize(0.085);
    fHistPodiell->GetXaxis()->SetLabelSize(0.075);
    fHistPodiell->GetYaxis()->SetLabelSize(0.055);
    fHistPodiell->DrawCopy();

    //======================================


/*    

    fGraphMCAntiL->SetMarkerColor(kMagenta);
    fGraphMCAntiL->SetLineColor(kMagenta);

    fGraphDataAntiL->SetMarkerColor(kBlue);
    fGraphDataAntiL->SetLineColor(kBlue);

    TLegend *lg3 = new TLegend(0.2,0.9,0.75,0.8);
	lg3->AddEntry(fGraphDataAntiL,"rekonstruovane data","pl");	
	lg3->AddEntry(fGraphMCAntiL,"Monte Carlo","pl");	

    TCanvas *c3 = new TCanvas("c3","",600,800);
	pad31 = new TPad("pad31","This is pad31",0.001,0.3,0.999,0.999);
	pad32 = new TPad("pad32","This is pad32",0.001,0.001,0.999,0.3);
	
	pad31->SetMargin(0.1,0.1,0,0.1);  
	pad32->SetMargin(0.1,0.1,0.2,0);
	
	pad31->Draw();
    pad32->Draw();
    pad31->cd();
     
    fGraphMCAntiL->GetXaxis()->SetRangeUser(4,15);
    fGraphMCAntiL->SetTitle("Porovnanie zavislosti vytazkov pre #bar{#Lambda} ");
    fGraphMCAntiL->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");

    fGraphMCAntiL->Draw("ap");
    fGraphDataAntiL->Draw("pSAME");
    lg3->Draw();

    Double_t binconMCal =0.;
    Double_t binconDataal =0.;
    Double_t errorMCal=0.;
    Double_t errorDataal=0.;
    Double_t podielal = 0.;
    Double_t chybaal = 0.;

    TH1D * fHistPodielal = new TH1D ("fHistPodielal","fHistPodielal",bins,PtHist);

    for (Int_t i=1; i<= bins; i++){
        binconMCal=fHistAntiLNearMC->GetBinContent(i);
        binconDataal=fHistAntiLNearData->GetBinContent(i);
        errorMCal=fHistAntiLNearMC->GetBinError(i);
        errorDataal=fHistAntiLNearData->GetBinError(i);
        podielal=binconMCal/binconDataal;
        fHistPodielal->SetBinContent(i,podielal);

        chybaal = TMath::Power(errorMCal/binconMCal ,2) + TMath::Power(errorDataal/binconDataal ,2);
     
        chybaal = TMath::Sqrt(chybaal);

        fHistPodielal->SetBinError(i,chybaal);        

    }

    pad32->cd();
    fHistPodielal->SetTitle("");
    fHistPodielal->SetYTitle("");
    fHistPodielal->SetXTitle("p_{T} (GeV/c)");
    fHistPodielal->DrawCopy();
*/
    //===============================================
    

    fGraphMCH->SetMarkerColor(kMagenta);
    fGraphMCH->SetLineColor(kMagenta);

    fGraphDataH->SetMarkerColor(kBlue);
    fGraphDataH->SetLineColor(kBlue);

    TLegend *lg3 = new TLegend(0.2,0.9,0.75,0.8);
    lg3->AddEntry(fGraphDataH,"realne data","pl");
	lg3->AddEntry(fGraphMCH,"MC(DataLike) rekonstruovane data","pl");

    TCanvas *c4 = new TCanvas("c4","",600,800);
	TPad * pad31 = new TPad("pad31","This is pad31",0.001,0.3,0.999,0.999);
	TPad * pad32 = new TPad("pad32","This is pad32",0.001,0.001,0.999,0.3);
	
	pad31->SetMargin(0.1,0.1,0,0.1);  
	pad32->SetMargin(0.1,0.1,0.2,0);
	
	pad31->Draw();
    pad32->Draw();
    pad31->cd();
     
    fGraphMCH->GetXaxis()->SetRangeUser(4,15);
    fGraphMCH->SetTitle("Porovnanie zavislosti vytazkov od p_{T}^{trig} pre nabity hadron ");
    fGraphMCH->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphMCH->GetYaxis()->SetTitleSize(0.04);
    fGraphMCH->GetYaxis()->SetRangeUser(0,1);

    fGraphMCH->Draw("ap");
    fGraphDataH->Draw("pSAME");
    lg3->Draw();

    Double_t binconMCh =0.;
    Double_t binconDatah =0.;
    Double_t errorMCh=0.;
    Double_t errorDatah=0.;
    Double_t podielh = 0.;
    Double_t chybah = 0.;

    TH1D * fHistPodielh = new TH1D ("fHistPodielh","fHistPodielh",bins,PtHist);

    for (Int_t i=1; i<= bins; i++){
        binconMCh=fHistHNearMC->GetBinContent(i);
        binconDatah=fHistHNearData->GetBinContent(i);
        errorMCh=fHistHNearMC->GetBinError(i);
        errorDatah=fHistHNearData->GetBinError(i);
        podielh=binconMCh/binconDatah;
        fHistPodielh->SetBinContent(i,podielh);

        chybah = TMath::Power(errorMCh/binconMCh ,2) + TMath::Power(errorDatah/binconDatah ,2);
     
        chybah = TMath::Sqrt(chybah);

        fHistPodielh->SetBinError(i,chybah);        

    }

    pad32->cd();
    fHistPodielh->SetTitle("");
    fHistPodielh->SetYTitle("");
    fHistPodielh->SetXTitle("p_{T} (GeV/c)");
    fHistPodielh->GetXaxis()->SetTitleSize(0.085);
    fHistPodielh->GetXaxis()->SetLabelSize(0.075);
    fHistPodielh->GetYaxis()->SetLabelSize(0.055);
    fHistPodielh->DrawCopy();
    
   /* TCanvas *ccc = new TCanvas;
    fGraphDataLambda->SetTitle("Vytazky pre prilahly pik");
    fGraphDataLambda->GetXaxis()->SetTitle("p_{T} trigg");
    fGraphDataLambda->SetMarkerColor(kGreen);
    fGraphDataLambda->SetLineColor(kGreen);
    fGraphDataLambda->Draw("ap");
    fGraphDataH->SetMarkerColor(kRed);
    fGraphDataH->SetLineColor(kRed);
    fGraphDataH->Draw("psame");
    fGraphDataK0->Draw("psame");
    TLegend *lg4 = new TLegend(0.2,0.9,0.75,0.8);
    lg4->AddEntry(fGraphDataLambda,"trigger - #Lambda + #bar{#Lambda}","pl");
    lg4->AddEntry(fGraphDataH,"trigger - nabity hadron","pl");
    lg4->AddEntry(fGraphDataK0,"trigger - K_{0}^{S}","pl");
    lg4->Draw();*/
    
}
