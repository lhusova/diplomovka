void SetGraf(TGraphErrors *gr, Int_t mstyle, Float_t msize, Color_t mcolor,Float_t opacity, Color_t lcolor, Int_t fstyle)
{
    gr->SetMarkerStyle(mstyle);
    gr->SetMarkerSize(msize);
    gr->SetMarkerColorAlpha(mcolor,opacity);
    gr->SetLineColor(lcolor);
    gr->SetFillStyle(fstyle);
};

void SystErr(){
    
    gROOT->Reset();
    
    gROOT->SetStyle("Plain");
    gStyle->SetPalette(1);
    //gStyle->SetOptTitle(0);
    gStyle->SetOptStat(1);
    gStyle->SetTitleX(0.09);
    
    TFile * inFilex = TFile::Open("Vytazky_minBias_data.root");
    
    TGraphErrors* fGraphHHAway = (TGraphErrors*) inFilex->Get("fGraphHHAway");
    TGraphErrors* fGraphHHNear = (TGraphErrors*) inFilex->Get("fGraphHHNear");
    TGraphErrors* fGraphHHAwaySyst = (TGraphErrors*) inFilex->Get("fGraphHHAwaySyst");
    TGraphErrors* fGraphHHNearSyst = (TGraphErrors*) inFilex->Get("fGraphHHNearSyst");
    TGraphErrors* fGraphHHAwayLow = (TGraphErrors*) inFilex->Get("fGraphHHAwayLow");
    TGraphErrors* fGraphHHAwayLowSyst = (TGraphErrors*) inFilex->Get("fGraphHHAwayLowSyst");
    TGraphErrors* fGraphHHAwayMiddle = (TGraphErrors*) inFilex->Get("fGraphHHAwayMiddle");
    TGraphErrors* fGraphHHAwayMiddleSyst = (TGraphErrors*) inFilex->Get("fGraphHHAwayMiddleSyst");
    TGraphErrors* fGraphHHAwayHigh = (TGraphErrors*) inFilex->Get("fGraphHHAwayHigh");
    TGraphErrors* fGraphHHAwayHighSyst = (TGraphErrors*) inFilex->Get("fGraphHHAwayHighSyst");
    TGraphErrors* fGraphHHNearLow = (TGraphErrors*) inFilex->Get("fGraphHHNearLow");
    TGraphErrors* fGraphHHNearLowSyst = (TGraphErrors*) inFilex->Get("fGraphHHNearLowSyst");
    TGraphErrors* fGraphHHNearMiddle = (TGraphErrors*) inFilex->Get("fGraphHHNearMiddle");
    TGraphErrors* fGraphHHNearMiddleSyst = (TGraphErrors*) inFilex->Get("fGraphHHNearMiddleSyst");
    TGraphErrors* fGraphHHNearHigh = (TGraphErrors*) inFilex->Get("fGraphHHNearHigh");
    TGraphErrors* fGraphHHNearHighSyst = (TGraphErrors*) inFilex->Get("fGraphHHNearHighSyst");
    TGraphErrors* fGraphIcpNear = (TGraphErrors*) inFilex->Get("fGraphIcpNear");
    TGraphErrors* fGraphIcpNearSyst = (TGraphErrors*) inFilex->Get("fGraphIcpNearSyst");
    TGraphErrors* fGraphIcpAway = (TGraphErrors*) inFilex->Get("fGraphIcpAway");
    TGraphErrors* fGraphIcpAwaySyst = (TGraphErrors*) inFilex->Get("fGraphIcpAwaySyst");
    TGraphErrors* fGraphK0Away= (TGraphErrors*) inFilex->Get("fGraphK0Away");
    TGraphErrors* fGraphK0Near = (TGraphErrors*) inFilex->Get("fGraphK0Near");
    TGraphErrors* fGraphK0AwaySyst = (TGraphErrors*) inFilex->Get("fGraphK0AwaySyst");
    TGraphErrors* fGraphK0NearSyst= (TGraphErrors*) inFilex->Get("fGraphK0NearSyst");
    TGraphErrors* fGraphLamAway = (TGraphErrors*) inFilex->Get("fGraphLamAway");
    TGraphErrors* fGraphLamNear= (TGraphErrors*) inFilex->Get("fGraphLamNear");
    TGraphErrors* fGraphLamAwaySyst = (TGraphErrors*) inFilex->Get("fGraphLamAwaySyst");
    TGraphErrors* fGraphLamNearSyst = (TGraphErrors*) inFilex->Get("fGraphLamNearSyst");
    TGraphErrors* fGraphIcpNearK0Syst= (TGraphErrors*) inFilex->Get("fGraphIcpNearK0Syst");
    TGraphErrors* fGraphIcpAwayK0Syst= (TGraphErrors*) inFilex->Get("fGraphIcpAwayK0Syst");
    TGraphErrors* fGraphIcpNearLamSyst = (TGraphErrors*) inFilex->Get("fGraphIcpNearLamSyst");
    TGraphErrors* fGraphIcpAwayLamSyst = (TGraphErrors*) inFilex->Get("fGraphIcpAwayLamSyst");
    TGraphErrors* fGraphIcpNearK0 = (TGraphErrors*) inFilex->Get("fGraphIcpNearK0");
    TGraphErrors* fGraphIcpAwayK0 = (TGraphErrors*) inFilex->Get("fGraphIcpAwayK0");
    TGraphErrors* fGraphIcpNearLam = (TGraphErrors*) inFilex->Get("fGraphIcpNearLam");
    TGraphErrors* fGraphIcpAwayLam = (TGraphErrors*) inFilex->Get("fGraphIcpAwayLam");
    TGraphErrors* fGraphK0NearHigh = (TGraphErrors*) inFilex->Get("fGraphK0NearHigh");
    TGraphErrors* fGraphK0NearHighSyst = (TGraphErrors*) inFilex->Get("fGraphK0NearHighSyst");
    TGraphErrors* fGraphLamNearHigh= (TGraphErrors*) inFilex->Get("fGraphLamNearHigh");
    TGraphErrors* fGraphLamNearHighSyst = (TGraphErrors*) inFilex->Get("fGraphLamNearHighSyst");
    TGraphErrors* fGraphK0NearMiddle= (TGraphErrors*) inFilex->Get("fGraphK0NearMiddle");
    TGraphErrors* fGraphK0NearMiddleSyst = (TGraphErrors*) inFilex->Get("fGraphK0NearMiddleSyst");
    TGraphErrors* fGraphLamNearMiddle = (TGraphErrors*) inFilex->Get("fGraphLamNearMiddle");
    TGraphErrors* fGraphLamNearMiddleSyst= (TGraphErrors*) inFilex->Get("fGraphLamNearMiddleSyst");
    TGraphErrors* fGraphK0NearLow= (TGraphErrors*) inFilex->Get("fGraphK0NearLow");
    TGraphErrors* fGraphK0NearLowSyst= (TGraphErrors*) inFilex->Get("fGraphK0NearLowSyst");
    TGraphErrors* fGraphLamNearLow= (TGraphErrors*) inFilex->Get("fGraphLamNearLow");
    TGraphErrors* fGraphLamNearLowSyst= (TGraphErrors*) inFilex->Get("fGraphLamNearLowSyst");
    TGraphErrors* fGraphK0AwayLow= (TGraphErrors*) inFilex->Get("fGraphK0AwayLow");
    TGraphErrors* fGraphK0AwayLowSyst= (TGraphErrors*) inFilex->Get("fGraphK0AwayLowSyst");
    TGraphErrors* fGraphLamAwayLow= (TGraphErrors*) inFilex->Get("fGraphLamAwayLow");
    TGraphErrors* fGraphLamAwayLowSyst = (TGraphErrors*) inFilex->Get("fGraphLamAwayLowSyst");
    TGraphErrors* fGraphLamAwayMiddle= (TGraphErrors*) inFilex->Get("fGraphLamAwayMiddle");
    TGraphErrors* fGraphLamAwayMiddleSyst = (TGraphErrors*) inFilex->Get("fGraphLamAwayMiddleSyst");
    TGraphErrors* fGraphK0AwayMiddle= (TGraphErrors*) inFilex->Get("fGraphK0AwayMiddle");
    TGraphErrors* fGraphK0AwayMiddleSyst = (TGraphErrors*) inFilex->Get("fGraphK0AwayMiddleSyst");
    TGraphErrors* fGraphK0AwayHigh= (TGraphErrors*) inFilex->Get("fGraphK0AwayHigh");
    TGraphErrors* fGraphK0AwayHighSyst= (TGraphErrors*) inFilex->Get("fGraphK0AwayHighSyst");
    TGraphErrors* fGraphLamAwayHigh= (TGraphErrors*) inFilex->Get("fGraphLamAwayHigh");
    TGraphErrors* fGraphLamAwayHighSyst= (TGraphErrors*) inFilex->Get("fGraphLamAwayHighSyst");
    
    // ICP pomer
    
    SetGraf(fGraphIcpNear,29,1.8,kRed-3,1,kRed-3,0);
    SetGraf(fGraphIcpNearSyst,29,1.8,kRed-3,1,kRed-3,0);
    SetGraf(fGraphIcpAway,29,1.8,kRed-3,1,kRed-3,0);
    SetGraf(fGraphIcpAwaySyst,29,1.8,kRed-3,1,kRed-3,0);
    
    SetGraf(fGraphIcpNearK0,23,1.8,kBlue-3,1,kBlue-3,0);
    SetGraf(fGraphIcpNearK0Syst,23,1.8,kBlue-3,1,kBlue-3,0);
    SetGraf(fGraphIcpAwayK0,23,1.8,kBlue-3,1,kBlue-3,0);
    SetGraf(fGraphIcpAwayK0Syst,23,1.8,kBlue-3,1,kBlue-3,0);
    
    SetGraf(fGraphIcpNearLam,23,1.8,kGreen-3,1,kGreen-3,0);
    SetGraf(fGraphIcpNearLamSyst,23,1.8,kGreen-3,1,kGreen-3,0);
    SetGraf(fGraphIcpAwayLam,23,1.8,kGreen-3,1,kGreen-3,0);
    SetGraf(fGraphIcpAwayLamSyst,23,1.8,kGreen-3,1,kGreen-3,0);
    
    TCanvas *canIcp = new TCanvas;
    TPad * pad1 = new TPad("pad1","This is pad1",0.001,0.001,0.5,0.999);
    TPad * pad2 = new TPad("pad2","This is pad2",0.5,0.001,0.999,0.999);
    
    pad1->SetMargin(0.1,0.,0.1,0.05);
    pad2->SetMargin(0.,0.1,0.1,0.05);
    
    pad1->Draw();
    pad2->Draw();
    
    pad1->cd();
    fGraphIcpNear->SetTitle("Nearside peak");
   // fGraphIcpNear->SetTitle("Prilahly pik");
    fGraphIcpNear->GetYaxis()->SetTitle("I_{CP} (0-10%) / (50-100%)");
    fGraphIcpNear->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphIcpNear->GetYaxis()->SetTitleOffset(1.2);
    fGraphIcpNear->GetYaxis()->SetRangeUser(0.,2.);
    fGraphIcpNear->Draw("ap");
    fGraphIcpNearSyst->Draw("e2 same");
    //fGraphIcpNearK0->Draw("p same");
    //fGraphIcpNearK0Syst->Draw("e2 same");
    //fGraphIcpNearLam->Draw("p same");
    //fGraphIcpNearLamSyst->Draw("e2 same");
    //TLegend *lgIcp = new TLegend();
    //lgIcp->AddEntry(fGraphIcpNear,"h-h","pl");
    //lgIcp->AddEntry(fGraphIcpNearK0,"K_{S}^{0}-h","pl");
    //lgIcp->AddEntry(fGraphIcpNearLam,"(#Lambda+#bar{#Lambda})-h","pl");
    TF1 * fconst1 = new TF1("fconst1","1",0.,16.);
    fconst1->SetLineColor(kBlack);
    fconst1->SetLineWidth(3);
    fconst1->SetLineStyle(7);
    fconst1->Draw("same");
    
    pad2->cd();
    fGraphIcpAway->SetTitle("Awayside paek");
    //fGraphIcpAway->SetTitle("Protilahly pik");
    fGraphIcpAway->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphIcpAway->GetYaxis()->SetRangeUser(0.,2.);
    fGraphIcpAway->Draw("ap");
    fGraphIcpAwaySyst->Draw("e2 same");
   // fGraphIcpAwayK0->Draw("p same");
   // fGraphIcpAwayK0Syst->Draw("e2 same");
   // fGraphIcpAwayLam->Draw("p same");
   // fGraphIcpAwayLamSyst->Draw("e2 same");
    fconst1->Draw("same");
   // lgIcp->Draw();
    
    
    // vytazky near hh
    TCanvas *cYieldNearH = new TCanvas;
    SetGraf(fGraphHHNear,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphHHNearSyst,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphHHNearLow,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphHHNearLowSyst,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphHHNearMiddle,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphHHNearMiddleSyst,23,1.,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphHHNearHigh,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphHHNearHighSyst,21,1.5,kGreen-3,0.7,kGreen-3,0);
    
    TLegend * lgHhNear = new TLegend(0.2,0.9,0.75,0.8);
    lgHhNear->AddEntry(fGraphHHNearHigh,"0-10%","pl");
    lgHhNear->AddEntry(fGraphHHNearMiddle,"10-50%","pl");
    lgHhNear->AddEntry(fGraphHHNearLow,"50-100%","pl");
    lgHhNear->AddEntry(fGraphHHNearSyst,"min bias","pl");
    
    //fGraphHHNearLow->SetTitle("Yield dependace on p^{trig}_{T}, h-h nearside peak");
    fGraphHHNearLow->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik pre h-h");
    fGraphHHNearLow->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphHHNearLow->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphHHNearLow->GetYaxis()->SetRangeUser(0.,0.35);
    fGraphHHNearLow->Draw("ap");
    fGraphHHNearLowSyst->Draw("e2 same");
    fGraphHHNearMiddle->Draw("p same");
    fGraphHHNearMiddleSyst->Draw("e2 same");
    fGraphHHNearHigh->Draw("p same");
    fGraphHHNearHighSyst->Draw("e2 same");
    fGraphHHNear->Draw("p same");
    fGraphHHNearSyst->Draw("e2 same");
    lgHhNear->Draw();
    
    // vytazky away hh
    TCanvas *cYieldAwayH = new TCanvas;
    SetGraf(fGraphHHAway,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphHHAwaySyst,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphHHAwayLow,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphHHAwayLowSyst,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphHHAwayMiddle,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphHHAwayMiddleSyst,23,1.,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphHHAwayHigh,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphHHAwayHighSyst,21,1.5,kGreen-3,0.7,kGreen-3,0);
    
    TLegend * lgHhAway = new TLegend(0.2,0.9,0.75,0.8);
    lgHhAway->AddEntry(fGraphHHAwayHigh,"0-10%","pl");
    lgHhAway->AddEntry(fGraphHHAwayMiddle,"10-50%","pl");
    lgHhAway->AddEntry(fGraphHHAwayLow,"50-100%","pl");
    lgHhAway->AddEntry(fGraphHHAwaySyst,"min bias","pl");
    
    //fGraphHHAwayLow->SetTitle("Yield dependace on p^{trig}_{T}, h-h awayside peak");
    fGraphHHAwayLow->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik pre h-h");
    fGraphHHAwayLow->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphHHAwayLow->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphHHAwayLow->GetYaxis()->SetRangeUser(0.,0.35);
    fGraphHHAwayLow->Draw("ap");
    fGraphHHAwayLowSyst->Draw("e2 same");
    fGraphHHAwayMiddle->Draw("p same");
    fGraphHHAwayMiddleSyst->Draw("e2 same");
    fGraphHHAwayHigh->Draw("p same");
    fGraphHHAwayHighSyst->Draw("e2 same");
    fGraphHHAway->Draw("p same");
    fGraphHHAwaySyst->Draw("e2 same");
    lgHhAway->Draw();
    
    // vytazky near Kh
    TCanvas *cYieldNearK = new TCanvas;
    SetGraf(fGraphK0Near,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphK0NearSyst,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphK0NearLow,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphK0NearLowSyst,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphK0NearMiddle,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphK0NearMiddleSyst,23,1.,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphK0NearHigh,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphK0NearHighSyst,21,1.5,kGreen-3,0.7,kGreen-3,0);
    
    TLegend * lgKhNear = new TLegend(0.2,0.9,0.75,0.8);
    lgKhNear->AddEntry(fGraphK0NearHigh,"0-10%","pl");
    lgKhNear->AddEntry(fGraphK0NearMiddle,"10-50%","pl");
    lgKhNear->AddEntry(fGraphK0NearLow,"50-100%","pl");
    lgKhNear->AddEntry(fGraphK0NearSyst,"min bias","pl");
    
    fGraphK0NearLow->SetTitle("Yield dependace on p^{trig}_{T}, K^{0}_{S}-h nearside peak");
   // fGraphK0NearLow->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik pre K^{0}_{S}-h");
    fGraphK0NearLow->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphK0NearLow->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphK0NearLow->GetYaxis()->SetRangeUser(0.,0.35);
    fGraphK0NearLow->Draw("ap");
    fGraphK0NearLowSyst->Draw("e2 same");
    fGraphK0NearMiddle->Draw("p same");
    fGraphK0NearMiddleSyst->Draw("e2 same");
    fGraphK0NearHigh->Draw("p same");
    fGraphK0NearHighSyst->Draw("e2 same");
    fGraphK0Near->Draw("p same");
    fGraphK0NearSyst->Draw("e2 same");
    lgKhNear->Draw();
    
    // vytazky away Kh
    TCanvas *cYieldAwayK = new TCanvas;
    SetGraf(fGraphK0Away,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphK0AwaySyst,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphK0AwayLow,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphK0AwayLowSyst,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphK0AwayMiddle,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphK0AwayMiddleSyst,23,1.,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphK0AwayHigh,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphK0AwayHighSyst,21,1.5,kGreen-3,0.7,kGreen-3,0);
    
    TLegend * lgKhAway = new TLegend(0.2,0.9,0.75,0.8);
    lgKhAway->AddEntry(fGraphK0AwayHigh,"0-10%","pl");
    lgKhAway->AddEntry(fGraphK0AwayMiddle,"10-50%","pl");
    lgKhAway->AddEntry(fGraphK0AwayLow,"50-100%","pl");
    lgKhAway->AddEntry(fGraphK0AwaySyst,"min bias","pl");
    
    fGraphK0AwayLow->SetTitle("Yield dependace on p^{trig}_{T}, K^{0}_{S}-h awayside peak");
    //fGraphK0AwayLow->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik pre K^{0}_{S}-h");
    fGraphK0AwayLow->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphK0AwayLow->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphK0AwayLow->GetYaxis()->SetRangeUser(0.,0.35);
    fGraphK0AwayLow->Draw("ap");
    fGraphK0AwayLowSyst->Draw("e2 same");
    fGraphK0AwayMiddle->Draw("p same");
    fGraphK0AwayMiddleSyst->Draw("e2 same");
    fGraphK0AwayHigh->Draw("p same");
    fGraphK0AwayHighSyst->Draw("e2 same");
    fGraphK0Away->Draw("p same");
    fGraphK0AwaySyst->Draw("e2 same");
    lgKhAway->Draw();
    
    // vytazky near Lh
    TCanvas *cYieldNearLam = new TCanvas;
    SetGraf(fGraphLamNear,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphLamNearSyst,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphLamNearLow,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphLamNearLowSyst,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphLamNearMiddle,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphLamNearMiddleSyst,23,1.,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphLamNearHigh,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphLamNearHighSyst,21,1.5,kGreen-3,0.7,kGreen-3,0);
    
    TLegend * lgLhNear = new TLegend(0.2,0.9,0.75,0.8);
    lgLhNear->AddEntry(fGraphLamNearHigh,"0-10%","pl");
    lgLhNear->AddEntry(fGraphLamNearMiddle,"10-50%","pl");
    lgLhNear->AddEntry(fGraphLamNearLow,"50-100%","pl");
    lgLhNear->AddEntry(fGraphLamNearSyst,"min bias","pl");
    
    fGraphLamNearLow->SetTitle("Yield dependace on p^{trig}_{T}, (#Lambda+#bar{#Lambda})-h nearside peak");
    //fGraphLamNearLow->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik pre (#Lambda+#bar{#Lambda})-h");
    fGraphLamNearLow->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphLamNearLow->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphLamNearLow->GetYaxis()->SetRangeUser(0.,0.5);
    fGraphLamNearLow->Draw("ap");
    fGraphLamNearLowSyst->Draw("e2 same");
    fGraphLamNearMiddle->Draw("p same");
    fGraphLamNearMiddleSyst->Draw("e2 same");
    fGraphLamNearHigh->Draw("p same");
    fGraphLamNearHighSyst->Draw("e2 same");
    fGraphLamNear->Draw("p same");
    fGraphLamNearSyst->Draw("e2 same");
    lgLhNear->Draw();
    
    // vytazky away Lh
    TCanvas *cYieldAwayLam = new TCanvas;
    SetGraf(fGraphLamAway,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphLamAwaySyst,29,1.5,kBlack,0.7,kBlack,0);
    SetGraf(fGraphLamAwayLow,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphLamAwayLowSyst,22,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphLamAwayMiddle,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphLamAwayMiddleSyst,23,1.,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphLamAwayHigh,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphLamAwayHighSyst,21,1.5,kGreen-3,0.7,kGreen-3,0);
    
    TLegend * lgLhAway = new TLegend(0.2,0.9,0.75,0.8);
    lgLhAway->AddEntry(fGraphLamAwayHigh,"0-10%","pl");
    lgLhAway->AddEntry(fGraphLamAwayMiddle,"10-50%","pl");
    lgLhAway->AddEntry(fGraphLamAwayLow,"50-100%","pl");
    lgLhAway->AddEntry(fGraphLamAwaySyst,"min bias","pl");
    
    fGraphLamAwayLow->SetTitle("Yield dependace on p^{trig}_{T}, (#Lambda+#bar{#Lambda})-h awayside peak");
    //fGraphLamAwayLow->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik pre (#Lambda+#bar{#Lambda})-h");
    fGraphLamAwayLow->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphLamAwayLow->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphLamAwayLow->GetYaxis()->SetRangeUser(0.,0.5);
    fGraphLamAwayLow->Draw("ap");
    fGraphLamAwayLowSyst->Draw("e2 same");
    fGraphLamAwayMiddle->Draw("p same");
    fGraphLamAwayMiddleSyst->Draw("e2 same");
    fGraphLamAwayHigh->Draw("p same");
    fGraphLamAwayHighSyst->Draw("e2 same");
    fGraphLamAway->Draw("p same");
    fGraphLamAwaySyst->Draw("e2 same");
    lgLhAway->Draw();
    
    //vytazky min bias near
/*    TCanvas *cYieldnearMinBias = new TCanvas;
    SetGraf(fGraphK0Near,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphK0NearSyst,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphLamNear,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphLamNearSyst,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphHHNear,29,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphHHNearSyst,29,1.5,kRed-3,0.7,kRed-3,0);
    
    TLegend * lgNearMinBias = new TLegend(0.2,0.9,0.75,0.8);
    lgNearMinBias->AddEntry(fGraphK0Near,"K^{0}_{S}-h","pl");
    lgNearMinBias->AddEntry(fGraphLamNear,"(#Lambda+#bar{#Lambda})-h","pl");
    lgNearMinBias->AddEntry(fGraphHHNear,"h-h","pl");
    
    fGraphK0Near->SetTitle("Yield dependace on p^{trig}_{T}, nearside peak");
    //fGraphK0Near->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik");
    fGraphK0Near->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphK0Near->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphK0Near->GetYaxis()->SetRangeUser(0.,0.5);
    fGraphK0Near->Draw("ap");
    fGraphK0NearSyst->Draw("e2 same");
    fGraphLamNear->Draw("p same");
    fGraphLamNearSyst->Draw("e2 same");
    fGraphHHNearSyst->Draw("e2 same");
    fGraphHHNear->Draw("p same");
    lgNearMinBias->Draw();
    
    //vytazky min bias away
    TCanvas *cYieldawayMinBias = new TCanvas;
    SetGraf(fGraphK0Away,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphK0AwaySyst,23,1.5,kBlue-3,0.7,kBlue-3,0);
    SetGraf(fGraphLamAway,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphLamAwaySyst,21,1.5,kGreen-3,0.7,kGreen-3,0);
    SetGraf(fGraphHHAway,29,1.5,kRed-3,0.7,kRed-3,0);
    SetGraf(fGraphHHAwaySyst,29,1.5,kRed-3,0.7,kRed-3,0);
    
    TLegend * lgAwayMinBias = new TLegend(0.2,0.9,0.75,0.8);
    lgAwayMinBias->AddEntry(fGraphK0Away,"K^{0}_{S}-h","pl");
    lgAwayMinBias->AddEntry(fGraphLamAway,"(#Lambda+#bar{#Lambda})-h","pl");
    lgAwayMinBias->AddEntry(fGraphHHAway,"h-h","pl");
    
    fGraphK0Away->SetTitle("Yield dependace on p^{trig}_{T}, awayside peak");
    //fGraphK0Away->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik");
    fGraphK0Away->GetXaxis()->SetTitle("p_{T}^{trig} (GeV/c)");
    fGraphK0Away->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
    fGraphK0Away->GetYaxis()->SetRangeUser(0.,0.5);
    fGraphK0Away->Draw("ap");
    fGraphK0AwaySyst->Draw("e2 same");
    fGraphLamAway->Draw("p same");
    fGraphLamAwaySyst->Draw("e2 same");
    fGraphHHAway->Draw("p same");
    fGraphHHAwaySyst->Draw("e2 same");
    lgAwayMinBias->Draw();*/
}
