TH1D* Podiel(TH1D* fHistData, TH1D* fHistMC, Int_t nbins, Double_t *bins,const char * hname, const char * htitle){
    
    TH1D * fHistPodiel = new TH1D(hname,htitle,nbins,bins);
    
    Double_t binconMC =0.;
    Double_t binconData =0.;
    Double_t errorMC=0.;
    Double_t errorData=0.;
    Double_t podiel = 0.;
    Double_t chyba = 0.;
    
    for (Int_t i=1; i<= nbins; i++){
        binconMC=fHistMC->GetBinContent(i);
        binconData=fHistData->GetBinContent(i);
        errorMC=fHistMC->GetBinError(i);
        errorData=fHistData->GetBinError(i);
        podiel=binconMC/binconData;
        fHistPodiel->SetBinContent(i,podiel);
        
        chyba = TMath::Power(errorMC/binconMC ,2) + TMath::Power(errorData/binconData ,2);
        
        chyba = TMath::Sqrt(chyba);
    //    cout << chyba << endl;
        
        
        fHistPodiel->SetBinError(i,chyba);
        
    }
    return fHistPodiel;
};

void Graph(){

    gStyle->SetOptStat(0000000000);
    TFile *g =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphMC_2015a_03.root");
    TFile *f =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphMC_2015c_Grid07.root");
    TFile *ff =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphMC_2016_05.root");
    TFile *fdata =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/Vytazky_minBias_data.root");
    
    Bool_t Near = kFALSE;
    
  //  if (Near){
 /*   TGraphErrors *fGraphMCK015a = (TGraphErrors*) g->Get("fGraphK0Near1");
    TGraphErrors *fGraphMCK015c = (TGraphErrors*) f->Get("fGraphK0Near1");
    TGraphErrors *fGraphMCK016 = (TGraphErrors*) ff->Get("fGraphK0Near1");
   // TGraphErrors *fGraphDataK0 = (TGraphErrors*) fdata->Get("fGraphK0Near");

    TH1D * fHistK0NearMC15a = (TH1D*) g->Get("fHistK0Near1");
    TH1D * fHistK0NearMC15c = (TH1D*) f->Get("fHistK0Near1");
    TH1D * fHistK0NearMC16 = (TH1D*) ff->Get("fHistK0Near1");
    TH1D * fHistK0NearData = (TH1D*) fdata->Get("fHistK0Near");

    TGraphErrors *fGraphMCLambda15a = (TGraphErrors*) g->Get("fGraphLambdaNear1");
    TGraphErrors *fGraphMCLambda15c = (TGraphErrors*) f->Get("fGraphLambdaNear1");
    TGraphErrors *fGraphMCLambda16 = (TGraphErrors*) ff->Get("fGraphLambdaNear1");
   // TGraphErrors *fGraphDataLambda = (TGraphErrors*) fdata->Get("fGraphLambdaNear");

    TH1D * fHistLambdaNearMC15a = (TH1D*) g->Get("fHistLambdaNear1");
    TH1D * fHistLambdaNearMC15c = (TH1D*) f->Get("fHistLambdaNear1");
    TH1D * fHistLambdaNearMC16 = (TH1D*) ff->Get("fHistLambdaNear1");
    TH1D * fHistLambdaNearData = (TH1D*) fdata->Get("fHistLambdaNear");

    TGraphErrors *fGraphMCH15a = (TGraphErrors*) g->Get("fGraphTrackNear1");
    TGraphErrors *fGraphMCH15c = (TGraphErrors*) f->Get("fGraphTrackNear1");
    TGraphErrors *fGraphMCH16 = (TGraphErrors*) ff->Get("fGraphTrackNear1");
   // TGraphErrors *fGraphDataH = (TGraphErrors*) fdata->Get("fGraphTrackNear");

        TH1D * fHistHNearMC15a = (TH1D*) g->Get("fHistHadronNear1");
        TH1D * fHistHNearMC15c = (TH1D*) f->Get("fHistHadronNear1");
        TH1D * fHistHNearMC16 = (TH1D*) ff->Get("fHistHadronNear1");
        TH1D * fHistHNearData = (TH1D*) fdata->Get("fHistHadronNear");
        
    }else{*/
    TGraphErrors *fGraphMCK015a = (TGraphErrors*) g->Get("fGraphK0Away1");
    TGraphErrors *fGraphMCK015c = (TGraphErrors*) f->Get("fGraphK0Away1");
    TGraphErrors *fGraphMCK016 = (TGraphErrors*) ff->Get("fGraphK0Away1");
    //TGraphErrors *fGraphDataK0 = (TGraphErrors*) fdata->Get("Graph;3");
        
        TH1D * fHistK0NearMC15a = (TH1D*) g->Get("fHistK0Away1");
        TH1D * fHistK0NearMC15c = (TH1D*) f->Get("fHistK0Away1");
        TH1D * fHistK0NearMC16 = (TH1D*) ff->Get("fHistK0Away1");
        TH1D * fHistK0NearData = (TH1D*) fdata->Get("fHistK0Away");
        
    TGraphErrors *fGraphMCLambda15a = (TGraphErrors*) g->Get("fGraphLambdaAway1");
    TGraphErrors *fGraphMCLambda15c = (TGraphErrors*) f->Get("fGraphLambdaAway1");
    TGraphErrors *fGraphMCLambda16 = (TGraphErrors*) ff->Get("fGraphLambdaAway1");
    //TGraphErrors *fGraphDataLambda = (TGraphErrors*) fdata->Get("Graph;2");
        
        TH1D * fHistLambdaNearMC15a = (TH1D*) g->Get("fHistLambdaAway1");
        TH1D * fHistLambdaNearMC15c = (TH1D*) f->Get("fHistLambdaAway1");
        TH1D * fHistLambdaNearMC16 = (TH1D*) ff->Get("fHistLambdaAway1");
        TH1D * fHistLambdaNearData = (TH1D*) fdata->Get("fHistLambdaAway");
        
    TGraphErrors *fGraphMCH15a = (TGraphErrors*) g->Get("fGraphTrackAway1");
    TGraphErrors *fGraphMCH15c = (TGraphErrors*) f->Get("fGraphTrackAway1");
    TGraphErrors *fGraphMCH16 = (TGraphErrors*) ff->Get("fGraphTrackAway1");
    //TGraphErrors *fGraphDataH = (TGraphErrors*) fdata->Get("Graph;1");
        
        TH1D * fHistHNearMC15a = (TH1D*) g->Get("fHistHadronAway1");
        TH1D * fHistHNearMC15c = (TH1D*) f->Get("fHistHadronAway1");
        TH1D * fHistHNearMC16 = (TH1D*) ff->Get("fHistHadronAway1");
        TH1D * fHistHNearData = (TH1D*) fdata->Get("fHistHadronAway");
        
//    }

    fGraphMCK015a->SetMarkerColor(kMagenta);
    fGraphMCK015a->SetLineColor(kMagenta);
    fGraphMCK015a->SetMarkerStyle(20);
    fGraphMCK015a->SetMarkerSize(1.2);
    
    fGraphMCK015c->SetMarkerColor(kGreen);
    fGraphMCK015c->SetLineColor(kGreen);
    fGraphMCK015c->SetMarkerStyle(22);
    fGraphMCK015c->SetMarkerSize(1.2);
    
    fGraphMCK016->SetMarkerColor(kBlue);
    fGraphMCK016->SetLineColor(kBlue);
    fGraphMCK016->SetMarkerStyle(21);
    fGraphMCK016->SetMarkerSize(1.2);
    
    fHistK0NearData->SetMarkerColor(kBlack);
    fHistK0NearData->SetLineColor(kBlack);
    fHistK0NearData->SetMarkerStyle(23);
    fHistK0NearData->SetMarkerSize(1.2);

    TLegend *lg = new TLegend(0.2,0.9,0.75,0.8);
    lg->AddEntry(fHistK0NearData,"realne data","pl");
	lg->AddEntry(fGraphMCK015a,"MC rekonstruovane data PYTHIA8 - Monash ","pl");
    lg->AddEntry(fGraphMCK015c,"MC rekonstruovane data PYTHIA6 - Perugia ","pl");
    lg->AddEntry(fGraphMCK016,"MC rekonstruovane data EPOS-LHC ","pl");

     TCanvas *c1 = new TCanvas("c1","",600,800);
	TPad * pad1 = new TPad("pad1","This is pad1",0.001,0.3,0.999,0.999);
	TPad * pad2 = new TPad("pad2","This is pad2",0.001,0.001,0.999,0.3);
	
	pad1->SetMargin(0.1,0.1,0,0.1);  
	pad2->SetMargin(0.1,0.1,0.2,0);
	
	pad1->Draw();
    pad2->Draw();
    pad1->cd();
     
    fGraphMCK015a->GetXaxis()->SetRangeUser(4,15);
    if(Near){
        fGraphMCK015a->SetTitle("Porovnanie zavislosti vytazkov od p_{T}^{trig} pre K^{0}_{S}, Prilahly pik");
    }else{
        fGraphMCK015a->SetTitle("Porovnanie zavislosti vytazkov od p_{T}^{trig} pre K^{0}_{S}, Protilahly pik");
    }
    fGraphMCK015a->GetYaxis()->SetTitleSize(0.04);
    Double_t MaxGrafK = TMath::Max(fHistK0NearMC15a->GetMaximum(),TMath::Max(fHistK0NearMC15c->GetMaximum(),TMath::Max(fHistK0NearData->GetMaximum(),fHistK0NearMC16->GetMaximum()) ));
    fGraphMCK015a->GetYaxis()->SetRangeUser(0,1.2*MaxGrafK);

    fGraphMCK015a->Draw("ap");
    fGraphMCK015c->Draw("pSAME");
    fHistK0NearData->Draw("SAME");
    fGraphMCK016->Draw("pSAME");
    
    lg->Draw();

    Int_t bins = fHistK0NearData->GetNbinsX();
    
    Double_t PtHist[7] = {4, 5, 6, 7, 9, 11, 15};

    TH1D * fHistPodiel15a = Podiel(fHistK0NearData,fHistK0NearMC15a,bins,PtHist,"fHistPodiel15a","fHistPodiel15a");
    TH1D * fHistPodiel15c = Podiel(fHistK0NearData,fHistK0NearMC15c,bins,PtHist,"fHistPodiel15c","fHistPodiel15c");
    TH1D * fHistPodiel16 = Podiel(fHistK0NearData,fHistK0NearMC16,bins,PtHist,"fHistPodiel16","fHistPodiel16");

    Double_t min = TMath::Min(fHistPodiel15a->GetMinimum(),TMath::Min(fHistPodiel15c->GetMinimum(),fHistPodiel16->GetMinimum()) );
    Double_t max = TMath::Max(fHistPodiel15a->GetMaximum(),TMath::Max(fHistPodiel15c->GetMaximum(),fHistPodiel16->GetMaximum() ));
    
    pad2->cd();
    fHistPodiel15a->SetTitle("");
    fHistPodiel15a->SetYTitle("");
    fHistPodiel15a->SetXTitle("p_{T} (GeV/c)");
    fHistPodiel15a->GetXaxis()->SetTitleSize(0.085);
    fHistPodiel15a->GetXaxis()->SetLabelSize(0.075);
    fHistPodiel15a->GetYaxis()->SetLabelSize(0.055);
    fHistPodiel15a->GetYaxis()->SetRangeUser(0.9*min,1.1*max);
    fHistPodiel15a->SetMarkerStyle(20);
    fHistPodiel15a->SetMarkerSize(1.2);
    fHistPodiel15a->SetMarkerColor(kMagenta);
    fHistPodiel15a->SetLineColor(kMagenta);
    fHistPodiel15a->DrawCopy();
    
    fHistPodiel16->SetMarkerSize(1.2);
    fHistPodiel16->SetMarkerStyle(21);
    fHistPodiel16->SetMarkerColor(kBlue);
    fHistPodiel16->SetLineColor(kBlue);
    fHistPodiel16->DrawCopy("same");
    
    fHistPodiel15c->SetMarkerSize(1.2);
    fHistPodiel15c->SetMarkerStyle(22);
    fHistPodiel15c->SetMarkerColor(kGreen);
    fHistPodiel15c->SetLineColor(kGreen);
    fHistPodiel15c->DrawCopy("same");

    TLine *line = new TLine(4,1,15,1);
    line->SetLineColor(kRed);
    line->Draw();
    //===================================

    fGraphMCLambda15a->SetMarkerColor(kMagenta);
    fGraphMCLambda15a->SetLineColor(kMagenta);
    fGraphMCLambda15a->SetMarkerStyle(20);
    fGraphMCLambda15a->SetMarkerSize(1.2);
    
    fGraphMCLambda15c->SetMarkerColor(kGreen);
    fGraphMCLambda15c->SetLineColor(kGreen);
    fGraphMCLambda15c->SetMarkerStyle(22);
    fGraphMCLambda15c->SetMarkerSize(1.2);
    
    fGraphMCLambda16->SetMarkerColor(kBlue);
    fGraphMCLambda16->SetLineColor(kBlue);
    fGraphMCLambda16->SetMarkerStyle(21);
    fGraphMCLambda16->SetMarkerSize(1.2);
    
    fHistLambdaNearData->SetMarkerColor(kBlack);
    fHistLambdaNearData->SetLineColor(kBlack);
    fHistLambdaNearData->SetMarkerStyle(23);
    fHistLambdaNearData->SetMarkerSize(1.2);

    TLegend *lg1 = new TLegend(0.2,0.9,0.75,0.8);
    lg1->AddEntry(fHistLambdaNearData,"realne data","pl");
	lg1->AddEntry(fGraphMCLambda15a,"MC rekonstruovane data PYTHIA8 - Monash","pl");
    lg1->AddEntry(fGraphMCLambda15c,"MC rekonstruovane data PYTHIA6 - Perugia","pl");
    lg1->AddEntry(fGraphMCLambda16,"MC rekonstruovane data EPOS - LHC","pl");

    TCanvas *c2 = new TCanvas("c2","",600,800);
	TPad * pad21 = new TPad("pad21","This is pad21",0.001,0.3,0.999,0.999);
	TPad * pad22 = new TPad("pad22","This is pad22",0.001,0.001,0.999,0.3);
	
	pad21->SetMargin(0.1,0.1,0,0.1);  
	pad22->SetMargin(0.1,0.1,0.2,0);
	
	pad21->Draw();
    pad22->Draw();
    pad21->cd();
     
    fGraphMCLambda15a->GetXaxis()->SetRangeUser(4,15);
    if(Near){
        fGraphMCLambda15a->SetTitle("Porovnanie zavislosti vytazkov od p_{T}^{trig} pre #Lambda a #bar{#Lambda}, Prilahly pik");
    }else{
        fGraphMCLambda15a->SetTitle("Porovnanie zavislosti vytazkov od p_{T}^{trig} pre #Lambda a #bar{#Lambda}, Protilahly pik");
    }
    fGraphMCLambda15a->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphMCLambda15a->GetYaxis()->SetTitleSize(0.04);
    Double_t MaxGrafL = TMath::Max(fHistLambdaNearMC15a->GetMaximum(),TMath::Max(fHistLambdaNearMC15c->GetMaximum(),TMath::Max(fHistLambdaNearData->GetMaximum(),fHistLambdaNearMC16->GetMaximum()) ));
    fGraphMCLambda15a->GetYaxis()->SetRangeUser(0,1.2*MaxGrafL);

    fGraphMCLambda15a->Draw("ap");
    fGraphMCLambda15c->Draw("pSAME");
    fHistLambdaNearData->Draw("SAME");
    fGraphMCLambda16->Draw("pSAME");
    lg1->Draw();

    TH1D * fHistPodielL15a = Podiel(fHistLambdaNearData,fHistLambdaNearMC15a,bins,PtHist,"fHistPodielL15a","fHistPodielL15a");
    TH1D * fHistPodielL15c = Podiel(fHistLambdaNearData,fHistLambdaNearMC15c,bins,PtHist,"fHistPodielL15c","fHistPodielL15c");
    TH1D * fHistPodieLl16 = Podiel(fHistLambdaNearData,fHistLambdaNearMC16,bins,PtHist,"fHistPodielL16","fHistPodielL16");
    
    Double_t minl = TMath::Min(fHistPodielL15a->GetMinimum(),TMath::Min(fHistPodielL15c->GetMinimum(), fHistPodieLl16->GetMinimum()) );
    Double_t maxl = TMath::Max(fHistPodielL15a->GetMaximum(),TMath::Max(fHistPodielL15c->GetMaximum(),fHistPodieLl16->GetMaximum()) );
    
    pad22->cd();
    fHistPodielL15a->SetTitle("");
    fHistPodielL15a->SetYTitle("");
    fHistPodielL15a->SetXTitle("p_{T} (GeV/c)");
    fHistPodielL15a->GetXaxis()->SetTitleSize(0.085);
    fHistPodielL15a->GetXaxis()->SetLabelSize(0.075);
    fHistPodielL15a->GetYaxis()->SetLabelSize(0.055);
    fHistPodielL15a->GetYaxis()->SetRangeUser(0.9*minl,1.1*maxl);
    fHistPodielL15a->SetMarkerStyle(20);
    fHistPodielL15a->SetMarkerSize(1.2);
    fHistPodielL15a->SetMarkerColor(kMagenta);
    fHistPodielL15a->SetLineColor(kMagenta);
    fHistPodielL15a->DrawCopy();
    
    fHistPodieLl16->SetMarkerSize(1.2);
    fHistPodieLl16->SetMarkerStyle(21);
    fHistPodieLl16->SetMarkerColor(kBlue);
    fHistPodieLl16->SetLineColor(kBlue);
    fHistPodieLl16->DrawCopy("same");
    
    fHistPodielL15c->SetMarkerSize(1.2);
    fHistPodielL15c->SetMarkerStyle(22);
    fHistPodielL15c->SetMarkerColor(kGreen);
    fHistPodielL15c->SetLineColor(kGreen);
    fHistPodielL15c->DrawCopy("same");
    
    TLine *linel = new TLine(4,1,15,1);
    linel->SetLineColor(kRed);
    linel->Draw();
    
    //===============================================
    
    fGraphMCH15a->SetMarkerColor(kMagenta);
    fGraphMCH15a->SetLineColor(kMagenta);
    fGraphMCH15a->SetMarkerStyle(20);
    fGraphMCH15a->SetMarkerSize(1.2);
    
    fGraphMCH15c->SetMarkerColor(kGreen);
    fGraphMCH15c->SetLineColor(kGreen);
    fGraphMCH15c->SetMarkerStyle(22);
    fGraphMCH15c->SetMarkerSize(1.2);
    
    fGraphMCH16->SetMarkerColor(kBlue);
    fGraphMCH16->SetLineColor(kBlue);
    fGraphMCH16->SetMarkerStyle(21);
    fGraphMCH16->SetMarkerSize(1.2);
    
    fHistHNearData->SetMarkerColor(kBlack);
    fHistHNearData->SetLineColor(kBlack);
    fHistHNearData->SetMarkerStyle(23);
    fHistHNearData->SetMarkerSize(1.2);

    TLegend *lg3 = new TLegend(0.2,0.9,0.75,0.8);
    lg3->AddEntry(fHistHNearData,"realne data","pl");
	lg3->AddEntry(fGraphMCH15a,"MC rekonstruovane data PYTHIA8 - Monash","pl");
    lg3->AddEntry(fGraphMCH15c,"MC rekonstruovane data PYTHIA6 - Perugia","pl");
    lg3->AddEntry(fGraphMCH16,"MC rekonstruovane data EPOS - LHC","pl");

    TCanvas *c4 = new TCanvas("c4","",600,800);
	TPad * pad31 = new TPad("pad31","This is pad31",0.001,0.3,0.999,0.999);
	TPad * pad32 = new TPad("pad32","This is pad32",0.001,0.001,0.999,0.3);
	
	pad31->SetMargin(0.1,0.1,0,0.1);  
	pad32->SetMargin(0.1,0.1,0.2,0);
	
	pad31->Draw();
    pad32->Draw();
    pad31->cd();
     
    fGraphMCH15a->GetXaxis()->SetRangeUser(4,15);
    if(Near){
        fGraphMCH15a->SetTitle("Porovnanie zavislosti vytazkov od p_{T}^{trig} pre nabity hadron, Prilahly pik ");
    }else{
        fGraphMCH15a->SetTitle("Porovnanie zavislosti vytazkov od p_{T}^{trig} pre nabity hadron, Protilahly pik ");
    }
    fGraphMCH15a->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphMCH15a->GetYaxis()->SetTitleSize(0.04);
    Double_t MaxGraf = TMath::Max(fHistHNearMC15a->GetMaximum(),TMath::Max(fHistHNearMC15c->GetMaximum(),TMath::Max(fHistHNearData->GetMaximum(),fHistHNearMC16->GetMaximum()) ));
    fGraphMCH15a->GetYaxis()->SetRangeUser(0,1.2*MaxGraf);

    fGraphMCH15a->Draw("ap");
    fHistHNearData->Draw("SAME");
    fGraphMCH15c->Draw("pSAME");
    fGraphMCH16->Draw("pSAME");
    lg3->Draw();

    TH1D * fHistPodielh15a = Podiel(fHistHNearData,fHistHNearMC15a,bins,PtHist,"fHistPodielh15a","fHistPodielh15a");
    TH1D * fHistPodielh15c = Podiel(fHistHNearData,fHistHNearMC15c,bins,PtHist,"fHistPodielh15c","fHistPodielh15c");
    TH1D * fHistPodielh16 = Podiel(fHistHNearData,fHistHNearMC16,bins,PtHist,"fHistPodielh16","fHistPodielh16");
    
    Double_t minh = TMath::Min(fHistPodielh15a->GetMinimum(),TMath::Min(fHistPodielh15c->GetMinimum(), fHistPodielh16->GetMinimum()));
    Double_t maxh = TMath::Max(fHistPodielh15a->GetMaximum(),TMath::Max(fHistPodielh15c->GetMaximum(), fHistPodielh16->GetMaximum()));
    
    pad32->cd();
    fHistPodielh15a->SetTitle("");
    fHistPodielh15a->SetYTitle("");
    fHistPodielh15a->SetXTitle("p_{T} (GeV/c)");
    fHistPodielh15a->GetXaxis()->SetTitleSize(0.085);
    fHistPodielh15a->GetXaxis()->SetLabelSize(0.075);
    fHistPodielh15a->GetYaxis()->SetLabelSize(0.055);
    fHistPodielh15a->GetYaxis()->SetRangeUser(0.9*minh,1.1*maxh);
    fHistPodielh15a->SetMarkerStyle(20);
    fHistPodielh15a->SetMarkerSize(1.2);
    fHistPodielh15a->SetMarkerColor(kMagenta);
    fHistPodielh15a->SetLineColor(kMagenta);
    fHistPodielh15a->DrawCopy();
    
    fHistPodielh16->SetMarkerSize(1.2);
    fHistPodielh16->SetMarkerStyle(21);
    fHistPodielh16->SetMarkerColor(kBlue);
    fHistPodielh16->SetLineColor(kBlue);
    fHistPodielh16->DrawCopy("same");
    
    fHistPodielh15c->SetMarkerSize(1.2);
    fHistPodielh15c->SetMarkerStyle(22);
    fHistPodielh15c->SetMarkerColor(kGreen);
    fHistPodielh15c->SetLineColor(kGreen);
    fHistPodielh15c->DrawCopy("same");
    
    TLine *lineh = new TLine(4,1,15,1);
    lineh->SetLineColor(kRed);
    lineh->Draw();
    
  /*  TCanvas *ccc = new TCanvas;
    fGraphDataLambda->SetTitle("Zavyslost vytazkov od p_{T}^{trig} pre prilahly pik");
    fGraphDataLambda->GetXaxis()->SetTitle("p_{T} trigg");
    fGraphDataLambda->SetMarkerColor(kGreen);
    fGraphDataLambda->SetLineColor(kGreen);
    fGraphDataLambda->SetMarkerStyle(21);
    fGraphDataLambda->Draw("ap");
    fGraphDataH->SetMarkerColor(kRed);
    fGraphDataH->SetLineColor(kRed);
    fGraphDataH->SetMarkerStyle(29);
    fGraphDataK0->SetMarkerColor(kBlue);
    fGraphDataK0->SetLineColor(kBlue);
    fGraphDataH->Draw("psame");
    fGraphDataK0->Draw("psame");
    TLegend *lg4 = new TLegend(0.2,0.9,0.75,0.8);
    lg4->AddEntry(fGraphDataLambda,"trigger - #Lambda + #bar{#Lambda}","pl");
    lg4->AddEntry(fGraphDataH,"trigger - nabity hadron","pl");
    lg4->AddEntry(fGraphDataK0,"trigger - K_{0}^{S}","pl");
    lg4->Draw();*/
    
}
