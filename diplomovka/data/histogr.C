void histogr(){

    gStyle->SetOptStat(0000000000);
    TFile *fK0 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/MC_closure_nove/McClosure15a+c_nove_K0.root");
    TFile *fLam =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/MC_closure_nove/McClosure15a+c_nove_Lam.root");
    TFile *fhh =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/MC_closure_nove/McClosure15a+c_nove_hh.root");
    TFile *fdata =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphDataFeb_nove.root");
    
    TH1D ** fHistDeltaPhi = new TH1D*[6];
    TH1D ** fHistDeltaEta = new TH1D*[6];
    char namephi[50];
    char nameeta[50];
    
    for(Int_t i=0; i<6;i++){
        //sprintf(namephi,"hnamePom2%d",i);
        sprintf(namephi,"2dproj_2_pt_%i_py",i);
        fHistDeltaPhi[i]= (TH1D*) fdata->Get(namephi);

        //sprintf(nameeta,"hnameEta2%d",i);
        sprintf(nameeta,"2dproj_1_pt_%i_py",i);
        fHistDeltaEta[i]= (TH1D*) fdata->Get(nameeta);
        
    }
    
    
    TCanvas *canvasK0phi = new TCanvas;
    canvasK0phi->Divide(2,3);
    
    TCanvas *canvasK0eta = new TCanvas;
    canvasK0eta->Divide(2,3);
    
    for(Int_t i=0;i<6;i++){
      /* fHistDeltaPhi[i]->SetXTitle("#Delta #phi");
        fHistDeltaPhi[i]->SetYTitle("gen/rec");
        fHistDeltaPhi[i]->GetXaxis()->SetTitleSize(0.055);
        fHistDeltaPhi[i]->GetXaxis()->SetTitleOffset(0.75);
        fHistDeltaPhi[i]->GetXaxis()->SetLabelSize(0.045);
        fHistDeltaPhi[i]->GetYaxis()->SetLabelSize(0.045);
        fHistDeltaPhi[i]->GetYaxis()->SetTitleSize(0.055);
        fHistDeltaPhi[i]->GetYaxis()->SetRangeUser(0.9,1.1);
        
        fHistDeltaEta[i]->SetXTitle("#Delta #eta");
        fHistDeltaEta[i]->SetYTitle("gen/rec");
        fHistDeltaEta[i]->GetXaxis()->SetTitleSize(0.055);
        fHistDeltaEta[i]->GetXaxis()->SetTitleOffset(0.75);
        fHistDeltaEta[i]->GetXaxis()->SetLabelSize(0.045);
        fHistDeltaEta[i]->GetYaxis()->SetLabelSize(0.045);
        fHistDeltaEta[i]->GetYaxis()->SetTitleSize(0.045);
        fHistDeltaEta[i]->GetYaxis()->SetRangeUser(0.9,1.1);
        
        if (i==0){
            fHistDeltaPhi[i]->SetTitle("4 GeV/c < p_{T}^{trig} < 5 GeV/c");
            fHistDeltaEta[i]->SetTitle("4 GeV/c < p_{T}^{trig} < 5 GeV/c");
        }
        if (i==1) {
            fHistDeltaPhi[i]->SetTitle("5 GeV/c < p_{T}^{trig} < 6 GeV/c");
            fHistDeltaEta[i]->SetTitle("5 GeV/c < p_{T}^{trig} < 6 GeV/c");
        }
        if (i==2) {
            fHistDeltaPhi[i]->SetTitle("6 GeV/c < p_{T}^{trig} < 7 GeV/c");
            fHistDeltaEta[i]->SetTitle("6 GeV/c < p_{T}^{trig} < 7 GeV/c");
        }
        if (i==3) {
            fHistDeltaPhi[i]->SetTitle("7 GeV/c < p_{T}^{trig} < 9 GeV/c");
            fHistDeltaEta[i]->SetTitle("7 GeV/c < p_{T}^{trig} < 9 GeV/c");
        }
        if (i==4) {
            fHistDeltaPhi[i]->SetTitle("9 GeV/c < p_{T}^{trig} < 11 GeV/c");
            fHistDeltaEta[i]->SetTitle("9 GeV/c < p_{T}^{trig} < 11 GeV/c");
        }
        if (i==5) {
            fHistDeltaPhi[i]->SetTitle("11 GeV/c < p_{T}^{trig} < 15 GeV/c");
            fHistDeltaEta[i]->SetTitle("11 GeV/c < p_{T}^{trig} < 15 GeV/c");
        }*/
        canvasK0phi->cd(i+1);
        fHistDeltaPhi[i]->DrawCopy();
        
        canvasK0eta->cd(i+1);
        fHistDeltaEta[i]->DrawCopy();
    }
        
    TGraphErrors *fGraphK0phi = (TGraphErrors*) fK0 ->Get("Graph;1");
    TGraphErrors *fGraphK0eta = (TGraphErrors*) fK0 ->Get("Graph;2");
    
    TGraphErrors *fGraphlamphi = (TGraphErrors*) fLam ->Get("Graph;3");
    TGraphErrors *fGraphlameta = (TGraphErrors*) fLam ->Get("Graph;4");
    
    TGraphErrors *fGraphhhphi = (TGraphErrors*) fhh ->Get("Graph;5");
    TGraphErrors *fGraphhheta = (TGraphErrors*) fhh ->Get("Graph;6");

    
    fGraphK0phi->SetMarkerColor(kGreen);
    fGraphK0phi->SetMarkerStyle(20);
    fGraphK0phi->SetLineColor(kGreen);
    fGraphK0phi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    fGraphK0phi->GetYaxis()->SetTitle("hodnota fitu");
    fGraphK0phi->GetYaxis()->SetRangeUser(0.5,1.25);
    fGraphK0phi->SetTitle("Zavislost fitu od p_{T} pre #Delta #phi projekciu");
    
    fGraphK0eta->SetMarkerColor(kGreen);
    fGraphK0eta->SetMarkerStyle(20);
    fGraphK0eta->SetLineColor(kGreen);
    fGraphK0eta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    fGraphK0eta->GetYaxis()->SetTitle("hodnota fitu");
    fGraphK0eta->GetYaxis()->SetRangeUser(0.5,1.25);
    fGraphK0eta->SetTitle("Zavislost fitu od p_{T} pre #Delta #eta projekciu");
    
    fGraphlamphi->SetMarkerColor(kBlue);
    fGraphlamphi->SetMarkerStyle(21);
    fGraphlamphi->SetLineColor(kBlue);
    
    fGraphlameta->SetMarkerColor(kBlue);
    fGraphlameta->SetMarkerStyle(21);
    fGraphlameta->SetLineColor(kBlue);
    
    fGraphhhphi->SetMarkerColor(kRed);
    fGraphhhphi->SetMarkerStyle(22);
    fGraphhhphi->SetLineColor(kRed);
    
    fGraphhheta->SetMarkerColor(kRed);
    fGraphhheta->SetMarkerStyle(22);
    fGraphhheta->SetLineColor(kRed);
    
    TLegend *fLegendPhi = new TLegend(0.2,0.9,0.75,0.8);
    fLegendPhi->AddEntry(fGraphK0phi,"Triger K^{0}_{S}","pl");
    fLegendPhi->AddEntry(fGraphlamphi,"Triger #Lambda a #bar{#Lambda}","pl");
    fLegendPhi->AddEntry(fGraphhhphi,"Triger nabity hadron","pl");
    
    TLegend *fLegendEta = new TLegend(0.2,0.9,0.75,0.8);
    fLegendEta->AddEntry(fGraphK0eta,"Triger K^{0}_{S}","pl");
    fLegendEta->AddEntry(fGraphlameta,"Triger #Lambda a #bar{#Lambda}","pl");
    fLegendEta->AddEntry(fGraphhheta,"Triger nabity hadron","pl");

    TCanvas *CanPhi = new TCanvas;
    fGraphK0phi->Draw("ap");
    fGraphlamphi->Draw("pSAME");
    fGraphhhphi->Draw("pSAME");
    fLegendPhi->Draw();
    
    TCanvas *CanEta = new TCanvas;
    fGraphK0eta->Draw("ap");
    fGraphlameta->Draw("pSAME");
    fGraphhheta->Draw("pSAME");
    fLegendEta->Draw();
    
}
