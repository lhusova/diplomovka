/*void myFit(const Int_t ntrig, const Int_t nPtBin, const char nameFit, Double_t min, Double_t max, TH1D *hist, Double_t* hodnoty, Double_t *chyby){
    TF1 * fitPhi1 = new TF1(nameFit," [0]",min, max);
    fitPhi->SetParameter(0,1);
    hist->Fit(fitPhi1);
    hodnoty[ntrig][nPtBin]=fitPhi->GetParameter(0);
    chyby[ntrig][nPtBin]=fitPhi->GetParError(0);
    
    
}*/

void vyslHist(){
    gStyle->SetOptStat(0000000000);
    const Double_t kPi = TMath::Pi();
    TFile *f1 = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/McClosure15c_07_K0.root");
    TFile *f2 = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/McClosure15c_07_Lam.root");
    TFile *f3 = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/McClosure15c_07_hh.root");
   // TFile *f4 = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/McClosure10.root");
   // TFile *f5 = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/McClosure11.root");
   // TFile *f6 = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/McClosure12.root");
    
    TH1D *fHisthPhi01 = (TH1D *) f3->Get("hnamePom20");
    TH1D *fHisthPhi02 = (TH1D *) f3->Get("hnamePom21");
    TH1D *fHisthPhi03 = (TH1D *) f3->Get("hnamePom22");
    
    TH1D *fHisthEta01 = (TH1D *) f3->Get("hnameEta20");
    TH1D *fHisthEta02 = (TH1D *) f3->Get("hnameEta21");
    TH1D *fHisthEta03 = (TH1D *) f3->Get("hnameEta22");
    
    TH1D *fHistK0Phi01 = (TH1D *) f1->Get("hnamePom00");
    TH1D *fHistK0Phi02 = (TH1D *) f1->Get("hnamePom01");
    TH1D *fHistK0Phi03 = (TH1D *) f1->Get("hnamePom02");
    
    TH1D *fHistK0Eta01 = (TH1D *) f1->Get("hnameEta00");
    TH1D *fHistK0Eta02 = (TH1D *) f1->Get("hnameEta01");
    TH1D *fHistK0Eta03 = (TH1D *) f1->Get("hnameEta02");
    
    TH1D *fHistLamEta01 = (TH1D *) f2->Get("hnameEta10");
    TH1D *fHistLamEta02 = (TH1D *) f2->Get("hnameEta11");
    TH1D *fHistLamEta03 = (TH1D *) f2->Get("hnameEta12");
    
    TH1D *fHistLmaPhi01 = (TH1D *) f2->Get("hnamePom10");
    TH1D *fHistLamPhi02 = (TH1D *) f2->Get("hnamePom11");
    TH1D *fHistLamPhi03 = (TH1D *) f2->Get("hnamePom12");
    
    TH1D *fHistK0Phi04 = (TH1D *) f1->Get("hnamePom03");
    TH1D *fHistK0Phi05 = (TH1D *) f1->Get("hnamePom04");
    TH1D *fHistK0Phi06 = (TH1D *) f1->Get("hnamePom05");
    
    TH1D *fHistK0Eta04 = (TH1D *) f1->Get("hnameEta03");
    TH1D *fHistK0Eta05 = (TH1D *) f1->Get("hnameEta04");
    TH1D *fHistK0Eta06 = (TH1D *) f1->Get("hnameEta05");
    
    TH1D *fHistLamEta04 = (TH1D *) f2->Get("hnameEta13");
    TH1D *fHistLamEta05 = (TH1D *) f2->Get("hnameEta14");
    TH1D *fHistLamEta06 = (TH1D *) f2->Get("hnameEta15");
    
    TH1D *fHistLamPhi04 = (TH1D *) f2->Get("hnamePom13");
    TH1D *fHistLamPhi05 = (TH1D *) f2->Get("hnamePom14");
    TH1D *fHistLamPhi06 = (TH1D *) f2->Get("hnamePom15");
    
    TH1D *fHisthPhi04 = (TH1D *) f3->Get("hnamePom23");
    TH1D *fHisthPhi05 = (TH1D *) f3->Get("hnamePom24");
    TH1D *fHisthPhi06 = (TH1D *) f3->Get("hnamePom25");
    
    TH1D *fHisthEta04 = (TH1D *) f3->Get("hnameEta23");
    TH1D *fHisthEta05 = (TH1D *) f3->Get("hnameEta24");
    TH1D *fHisthEta06 = (TH1D *) f3->Get("hnameEta25");
    
    const Int_t nTig = 3;
    const Int_t nPtBins =6;
    
    Double_t fitPhiHodnoty[nTig][nPtBins];
    Double_t fitPhiChyby[nTig][nPtBins];
    Double_t fitEtaHodnoty[nTig][nPtBins];
    Double_t fitEtaChyby[nTig][nPtBins];
    Double_t ptBins[nPtBins]={4.5,5.5,6.5,8,10,13.5};
    Double_t ptBinsChyby[nPtBins]={0.5,0.5,0.5,1,1,2.5};
    TFile *fNewFile = TFile::Open("McClosureVysledky.root","RECREATE");
    TCanvas *cc = new TCanvas;
    cc->Divide(2,3);
    cc->cd(1);
    fHisthPhi01->SetTitle("h-h korelacie, 4 < p_{T}^{trig} < 5 GeV/c");
    fHisthPhi01->SetXTitle("#Delta #phi");
    fHisthPhi01->SetYTitle("rek./gen.");
    fHisthPhi01->DrawCopy();
    //myFit(0,0,"fitphi1",-kPi/2,-kPi/2+2*kPi,fHisthPhi01,fitPhiHodnoty,fitPhiChyby);
    TF1 * fitPhi1 = new TF1("fit1"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhi1->SetParameter(0,1);
    fHisthPhi01->Fit(fitPhi1);
    fitPhiHodnoty[2][0]=fitPhi1->GetParameter(0);
    fitPhiChyby[2][0]=fitPhi1->GetParError(0);
    fHisthPhi01->Write();
    
    cc->cd(2);
    fHisthPhi02->SetTitle("h-h korelacie, 5 < p_{T}^{trig} < 6 GeV/c");
    fHisthPhi02->SetXTitle("#Delta #phi");
    fHisthPhi02->SetYTitle("rek./gen.");
    fHisthPhi02->DrawCopy();
    TF1 * fitPhi2 = new TF1("fit2"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhi2->SetParameter(0,1);
    fHisthPhi02->Fit(fitPhi2);
    fitPhiHodnoty[2][1]=fitPhi2->GetParameter(0);
    fitPhiChyby[2][1]=fitPhi2->GetParError(0);
    fHisthPhi02->Write();
    
    cc->cd(3);
    fHisthPhi03->SetTitle("h-h korelacie, 6 < p_{T}^{trig} < 7 GeV/c");
    fHisthPhi03->SetXTitle("#Delta #phi");
    fHisthPhi03->SetYTitle("rek./gen.");
    fHisthPhi03->DrawCopy();
    TF1 * fitPhi3 = new TF1("fit3"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhi3->SetParameter(0,1);
    fHisthPhi03->Fit(fitPhi3);
    fitPhiHodnoty[2][2]=fitPhi3->GetParameter(0);
    fitPhiChyby[2][2]=fitPhi3->GetParError(0);
    fHisthPhi03->Write();
    
    cc->cd(4);
    fHisthPhi04->SetTitle("h-h korelacie, 7 < p_{T}^{trig} < 9 GeV/c");
    fHisthPhi04->SetXTitle("#Delta #phi");
    fHisthPhi04->SetYTitle("rek./gen.");
    fHisthPhi04->DrawCopy();
    TF1 * fitPhi4 = new TF1("fit4"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhi4->SetParameter(0,1);
    fHisthPhi04->Fit(fitPhi4);
    fitPhiHodnoty[2][3]=fitPhi4->GetParameter(0);
    fitPhiChyby[2][3]=fitPhi4->GetParError(0);
    fHisthPhi04->Write();
    
    cc->cd(5);
    fHisthPhi05->SetTitle("h-h korelacie, 9 < p_{T}^{trig} < 11 GeV/c");
    fHisthPhi05->SetXTitle("#Delta #phi");
    fHisthPhi05->SetYTitle("rek./gen.");
    fHisthPhi05->DrawCopy();
    TF1 * fitPhi5 = new TF1("fit5"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhi5->SetParameter(0,1);
    fHisthPhi05->Fit(fitPhi5);
    fitPhiHodnoty[2][4]=fitPhi5->GetParameter(0);
    fitPhiChyby[2][4]=fitPhi5->GetParError(0);
    fHisthPhi05->Write();
    
    cc->cd(6);
    fHisthPhi06->SetTitle("h-h korelacie, 11 < p_{T}^{trig} < 15 GeV/c");
    fHisthPhi06->SetXTitle("#Delta #phi");
    fHisthPhi06->SetYTitle("rek./gen.");
    fHisthPhi06->DrawCopy();
    TF1 * fitPhi6 = new TF1("fit6"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhi6->SetParameter(0,1);
    fHisthPhi06->Fit(fitPhi6);
    fitPhiHodnoty[2][5]=fitPhi6->GetParameter(0);
    fitPhiChyby[2][5]=fitPhi6->GetParError(0);
    fHisthPhi06->Write();
    
    TGraphErrors * hPhi = new TGraphErrors(nPtBins,ptBins,fitPhiHodnoty[2],ptBinsChyby,fitPhiChyby[2]);
    TCanvas *graphhhPhi = new TCanvas;
    hPhi->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger h, phi projekcia");
    hPhi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    hPhi->GetYaxis()->SetTitle("hodnota fitu");
    hPhi->GetYaxis()->SetRangeUser(0.9,1.1);
    hPhi->SetMarkerStyle(29);
    hPhi->SetMarkerColor(kRed);
    hPhi->SetLineColor(kRed);
    hPhi->SetMarkerSize(1.8);
    hPhi->Draw("ap");
    hPhi->Write();
    
    TCanvas *ccLam = new TCanvas;
    ccLam->Divide(2,3);
    ccLam->cd(1);
    fHisthEta01->SetTitle("h-h korelacie, 4 < p_{T}^{trig} < 5 GeV/c");
    fHisthEta01->SetXTitle("#Delta #eta");
    fHisthEta01->SetYTitle("rek./gen.");
    fHisthEta01->DrawCopy();
    TF1 * fitEta1 = new TF1("fitEta1"," [0]",-1.5, 1.5);
    fitEta1->SetParameter(0,1);
    fHisthEta01->Fit(fitEta1);
    fitEtaHodnoty[2][0]=fitEta1->GetParameter(0);
    fitEtaChyby[2][0]=fitEta1->GetParError(0);
    fHisthEta01->Write();
    
    ccLam->cd(2);
    fHisthEta02->SetTitle("h-h korelacie, 5 < p_{T}^{trig} < 6 GeV/c");
    fHisthEta02->SetXTitle("#Delta #eta");
    fHisthEta02->SetYTitle("rek./gen.");
    fHisthEta02->DrawCopy();
    TF1 * fitEta2 = new TF1("fitEta2"," [0]",-1.5, 1.5);
    fitEta2->SetParameter(0,1);
    fHisthEta02->Fit(fitEta2);
    fitEtaHodnoty[2][1]=fitEta2->GetParameter(0);
    fitEtaChyby[2][1]=fitEta2->GetParError(0);
    fHisthEta02->Write();
    
    ccLam->cd(3);
    fHisthEta03->SetTitle("h-h korelacie, 6 < p_{T}^{trig} < 7 GeV/c");
    fHisthEta03->SetXTitle("#Delta #eta");
    fHisthEta03->SetYTitle("rek./gen.");
    fHisthEta03->DrawCopy();
    TF1 * fitEta3 = new TF1("fitEta3"," [0]",-1.5, 1.5);
    fitEta3->SetParameter(0,1);
    fHisthEta03->Fit(fitEta3);
    fitEtaHodnoty[2][2]=fitEta3->GetParameter(0);
    fitEtaChyby[2][2]=fitEta3->GetParError(0);
    fHisthEta03->Write();
    
    ccLam->cd(4);
    fHisthEta04->SetTitle("h-h korelacie, 7 < p_{T}^{trig} < 9 GeV/c");
    fHisthEta04->SetXTitle("#Delta #eta");
    fHisthEta04->SetYTitle("rek./gen.");
    fHisthEta04->DrawCopy();
    TF1 * fitEta4 = new TF1("fitEta4"," [0]",-1.5, 1.5);
    fitEta4->SetParameter(0,1);
    fHisthEta04->Fit(fitEta3);
    fitEtaHodnoty[2][3]=fitEta4->GetParameter(0);
    fitEtaChyby[2][3]=fitEta4->GetParError(0);
    fHisthEta04->Write();
    
    ccLam->cd(5);
    fHisthEta05->SetTitle("h-h korelacie, 9 < p_{T}^{trig} < 11 GeV/c");
    fHisthEta05->SetXTitle("#Delta #eta");
    fHisthEta05->SetYTitle("rek./gen.");
    fHisthEta05->DrawCopy();
    TF1 * fitEta5 = new TF1("fitEta5"," [0]",-1.5, 1.5);
    fitEta5->SetParameter(0,1);
    fHisthEta05->Fit(fitEta5);
    fitEtaHodnoty[2][4]=fitEta5->GetParameter(0);
    fitEtaChyby[2][4]=fitEta5->GetParError(0);
    fHisthEta05->Write();
   
    ccLam->cd(6);
    fHisthEta06->SetTitle("h-h korelacie, 11 < p_{T}^{trig} < 15 GeV/c");
    fHisthEta06->SetXTitle("#Delta #eta");
    fHisthEta06->SetYTitle("rek./gen.");
    fHisthEta06->DrawCopy();
    TF1 * fitEta6 = new TF1("fitEta6"," [0]",-1.5, 1.5);
    fitEta6->SetParameter(0,1);
    fHisthEta06->Fit(fitEta6);
    fitEtaHodnoty[2][5]=fitEta6->GetParameter(0);
    fitEtaChyby[2][5]=fitEta6->GetParError(0);
    fHisthEta06->Write();
    
    TGraphErrors * hEta = new TGraphErrors(nPtBins,ptBins,fitEtaHodnoty[2],ptBinsChyby,fitEtaChyby[2]);
    TCanvas *graphhEta = new TCanvas;
    hEta->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger h, eta projekcia");
    hEta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    hEta->GetYaxis()->SetTitle("hodnota fitu");
    hEta->GetYaxis()->SetRangeUser(0.9,1.1);
    hEta->SetMarkerStyle(29);
    hEta->SetMarkerColor(kRed);
    hEta->SetLineColor(kRed);
    hEta->SetMarkerSize(1.8);
    hEta->Draw("ap");
    hEta->Write();
    
    TCanvas *ccK0Phi = new TCanvas;
    ccK0Phi->Divide(2,3);
    ccK0Phi->cd(1);
    fHistK0Phi01->SetTitle("K^{0}_{S}-h korelacie, 4 < p_{T}^{trig} < 5 GeV/c");
    fHistK0Phi01->SetXTitle("#Delta #phi");
    fHistK0Phi01->SetYTitle("rek./gen.");
    fHistK0Phi01->DrawCopy();
    TF1 * fitPhiK01 = new TF1("fitK01"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiK01->SetParameter(0,1);
    fHistK0Phi01->Fit(fitPhiK01);
    fitPhiHodnoty[0][0]=fitPhiK01->GetParameter(0);
    fitPhiChyby[0][0]=fitPhiK01->GetParError(0);
    fHistK0Phi01->Write();
    
    ccK0Phi->cd(2);
    fHistK0Phi02->SetTitle("K^{0}_{S}-h korelacie, 5 < p_{T}^{trig} < 6 GeV/c");
    fHistK0Phi02->SetXTitle("#Delta #phi");
    fHistK0Phi02->SetYTitle("rek./gen.");
    fHistK0Phi02->DrawCopy();
    TF1 * fitPhiK02 = new TF1("fitK02"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiK02->SetParameter(0,1);
    fHistK0Phi02->Fit(fitPhiK02);
    fitPhiHodnoty[0][1]=fitPhiK02->GetParameter(0);
    fitPhiChyby[0][1]=fitPhiK02->GetParError(0);
    fHistK0Phi02->Write();
    
    ccK0Phi->cd(3);
    fHistK0Phi03->SetTitle("K^{0}_{S}-h korelacie, 6 < p_{T}^{trig} < 7 GeV/c");
    fHistK0Phi03->SetXTitle("#Delta #phi");
    fHistK0Phi03->SetYTitle("rek./gen.");
    fHistK0Phi03->DrawCopy();
    TF1 * fitPhiK03 = new TF1("fitK03"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiK03->SetParameter(0,1);
    fHistK0Phi03->Fit(fitPhiK03);
    fitPhiHodnoty[0][2]=fitPhiK03->GetParameter(0);
    fitPhiChyby[0][2]=fitPhiK03->GetParError(0);
    fHistK0Phi03->Write();
    
    ccK0Phi->cd(4);
    fHistK0Phi04->SetTitle("K^{0}_{S}-h korelacie, 7 < p_{T}^{trig} < 9 GeV/c");
    fHistK0Phi04->SetXTitle("#Delta #phi");
    fHistK0Phi04->SetYTitle("rek./gen.");
    fHistK0Phi04->DrawCopy();
    TF1 * fitPhiK04 = new TF1("fitK04"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiK04->SetParameter(0,1);
    fHistK0Phi04->Fit(fitPhiK04);
    fitPhiHodnoty[0][3]=fitPhiK04->GetParameter(0);
    fitPhiChyby[0][3]=fitPhiK04->GetParError(0);
    fHistK0Phi04->Write();
    
    ccK0Phi->cd(5);
    fHistK0Phi05->SetTitle("K^{0}_{S}-h korelacie, 9 < p_{T}^{trig} < 11 GeV/c");
    fHistK0Phi05->SetXTitle("#Delta #phi");
    fHistK0Phi05->SetYTitle("rek./gen.");
    fHistK0Phi05->DrawCopy();
    TF1 * fitPhiK05 = new TF1("fitK05"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiK05->SetParameter(0,1);
    fHistK0Phi05->Fit(fitPhiK05);
    fitPhiHodnoty[0][4]=fitPhiK05->GetParameter(0);
    fitPhiChyby[0][4]=fitPhiK05->GetParError(0);
    fHistK0Phi05->Write();

    ccK0Phi->cd(6);
    fHistK0Phi06->SetTitle("K^{0}_{S}-h korelacie, 11 < p_{T}^{trig} < 15 GeV/c");
    fHistK0Phi06->SetXTitle("#Delta #phi");
    fHistK0Phi06->SetYTitle("rek./gen.");
    fHistK0Phi06->DrawCopy();
    TF1 * fitPhiK06 = new TF1("fitK06"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiK06->SetParameter(0,1);
    fHistK0Phi06->Fit(fitPhiK06);
    fitPhiHodnoty[0][5]=fitPhiK06->GetParameter(0);
    fitPhiChyby[0][5]=fitPhiK06->GetParError(0);
    fHistK0Phi06->Write();
    
    TGraphErrors * k0Phi = new TGraphErrors(nPtBins,ptBins,fitPhiHodnoty[0],ptBinsChyby,fitPhiChyby[0]);
    TCanvas *graphK0Phi = new TCanvas;
    k0Phi->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger K_{0}_{S}, phi projekcia");
    k0Phi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    k0Phi->GetYaxis()->SetTitle("hodnota fitu");
    k0Phi->SetMarkerStyle(23);
    k0Phi->SetMarkerColor(kBlue);
    k0Phi->SetLineColor(kBlue);
    k0Phi->SetMarkerSize(1.8);
    k0Phi->Draw("ap");
    k0Phi->Write();
    
    TCanvas *ccK0Eta = new TCanvas;
    ccK0Eta->Divide(2,3);
    ccK0Eta->cd(1);
    fHistK0Eta01->SetTitle("K^{0}_{S}-h korelacie, 4 < p_{T}^{trig} < 5 GeV/c");
    fHistK0Eta01->SetXTitle("#Delta #eta");
    fHistK0Eta01->SetYTitle("rek./gen.");
    fHistK0Eta01->DrawCopy();
    TF1 * fitEtaK01 = new TF1("fitEtaK01"," [0]",-1, 1);
    fitEtaK01->SetParameter(0,1);
    fHistK0Eta01->Fit(fitEtaK01);
    fitEtaHodnoty[0][0]=fitEtaK01->GetParameter(0);
    fitEtaChyby[0][0]=fitEtaK01->GetParError(0);
    fHistK0Eta01->Write();
    
    ccK0Eta->cd(2);
    fHistK0Eta02->SetTitle("K^{0}_{S}-h korelacie, 5 < p_{T}^{trig} < 6 GeV/c");
    fHistK0Eta02->SetXTitle("#Delta #eta");
    fHistK0Eta02->SetYTitle("rek./gen.");
    fHistK0Eta02->DrawCopy();
    TF1 * fitEtaK02 = new TF1("fitEtaK02"," [0]",-1, 1);
    fitEtaK02->SetParameter(0,1);
    fHistK0Eta02->Fit(fitEtaK02);
    fitEtaHodnoty[0][1]=fitEtaK02->GetParameter(0);
    fitEtaChyby[0][1]=fitEtaK02->GetParError(0);
    fHistK0Eta02->Write();
    
    ccK0Eta->cd(3);
    fHistK0Eta03->SetTitle("K^{0}_{S}-h korelacie, 6 < p_{T}^{trig} < 7 GeV/c");
    fHistK0Eta03->SetXTitle("#Delta #eta");
    fHistK0Eta03->SetYTitle("rek./gen.");
    fHistK0Eta03->DrawCopy();
    TF1 * fitEtaK03 = new TF1("fitEtaK03"," [0]",-1, 1);
    fitEtaK03->SetParameter(0,1);
    fHistK0Eta03->Fit(fitEtaK03);
    fitEtaHodnoty[0][2]=fitEtaK03->GetParameter(0);
    fitEtaChyby[0][2]=fitEtaK03->GetParError(0);
    fHistK0Eta03->Write();
  
    ccK0Eta->cd(4);
    fHistK0Eta04->SetTitle("K^{0}_{S}-h korelacie, 7 < p_{T}^{trig} < 9 GeV/c");
    fHistK0Eta04->SetXTitle("#Delta #eta");
    fHistK0Eta04->SetYTitle("rek./gen.");
    fHistK0Eta04->DrawCopy();
    TF1 * fitEtaK04 = new TF1("fitEtaK04"," [0]",-1, 1);
    fitEtaK04->SetParameter(0,1);
    fHistK0Eta04->Fit(fitEtaK04);
    fitEtaHodnoty[0][3]=fitEtaK04->GetParameter(0);
    fitEtaChyby[0][3]=fitEtaK04->GetParError(0);
    fHistK0Eta04->Write();
    
    ccK0Eta->cd(5);
    fHistK0Eta05->SetTitle("K^{0}_{S}-h korelacie, 9 < p_{T}^{trig} < 11 GeV/c");
    fHistK0Eta05->SetXTitle("#Delta #eta");
    fHistK0Eta05->SetYTitle("rek./gen.");
    fHistK0Eta05->DrawCopy();
    TF1 * fitEtaK05 = new TF1("fitEtaK05"," [0]",-1, 1);
    fitEtaK05->SetParameter(0,1);
    fHistK0Eta05->Fit(fitEtaK05);
    fitEtaHodnoty[0][4]=fitEtaK05->GetParameter(0);
    fitEtaChyby[0][4]=fitEtaK05->GetParError(0);
    fHistK0Eta05->Write();
    
    ccK0Eta->cd(6);
    fHistK0Eta06->SetTitle("K^{0}_{S}-h korelacie, 11 < p_{T}^{trig} < 15 GeV/c");
    fHistK0Eta06->SetXTitle("#Delta #eta");
    fHistK0Eta06->SetYTitle("rek./gen.");
    fHistK0Eta06->DrawCopy();
    TF1 * fitEtaK06 = new TF1("fitEtaK06"," [0]",-1, 1);
    fitEtaK06->SetParameter(0,1);
    fHistK0Eta06->Fit(fitEtaK06);
    fitEtaHodnoty[0][5]=fitEtaK06->GetParameter(0);
    fitEtaChyby[0][5]=fitEtaK06->GetParError(0);
    fHistK0Eta06->Write();
    
    TGraphErrors * k0Eta = new TGraphErrors(nPtBins,ptBins,fitEtaHodnoty[0],ptBinsChyby,fitEtaChyby[0]);
    TCanvas *graphK0Eta = new TCanvas;
    k0Eta->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger K_{0}_{S}, eta projekcia");
    k0Eta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    k0Eta->GetYaxis()->SetTitle("hodnota fitu");
    k0Eta->SetMarkerStyle(23);
    k0Eta->SetMarkerColor(kBlue);
    k0Eta->SetLineColor(kBlue);
    k0Eta->SetMarkerSize(1.8);
    k0Eta->Draw("ap");
    k0Eta->Write();
    
    TCanvas *ccLamPhi = new TCanvas;
    ccLamPhi->Divide(2,3);
    ccLamPhi->cd(1);
    fHistLmaPhi01->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 4 < p_{T}^{trig} < 5 GeV/c");
    fHistLmaPhi01->SetXTitle("#Delta #phi");
    fHistLmaPhi01->SetYTitle("rek./gen.");
    fHistLmaPhi01->DrawCopy();
    TF1 * fitPhiLam1 = new TF1("fitLam1"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiLam1->SetParameter(0,1);
    fHistLmaPhi01->Fit(fitPhiLam1);
    fitPhiHodnoty[1][0]=fitPhiLam1->GetParameter(0);
    fitPhiChyby[1][0]=fitPhiLam1->GetParError(0);
    fHistLmaPhi01->Write();
    
    ccLamPhi->cd(2);
    fHistLamPhi02->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 5 < p_{T}^{trig} < 6 GeV/c");
    fHistLamPhi02->SetXTitle("#Delta #phi");
    fHistLamPhi02->SetYTitle("rek./gen.");
    fHistLamPhi02->DrawCopy();
    TF1 * fitPhiLam2 = new TF1("fitLam2"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiLam2->SetParameter(0,1);
    fHistLamPhi02->Fit(fitPhiLam2);
    fitPhiHodnoty[1][1]=fitPhiLam2->GetParameter(0);
    fitPhiChyby[1][1]=fitPhiLam2->GetParError(0);
    fHistLamPhi02->Write();
    
    ccLamPhi->cd(3);
    fHistLamPhi03->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 6 < p_{T}^{trig} < 7 GeV/c");
    fHistLamPhi03->SetXTitle("#Delta #phi");
    fHistLamPhi03->SetYTitle("rek./gen.");
    fHistLamPhi03->DrawCopy();
    TF1 * fitPhiLam3 = new TF1("fitLam3"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiLam3->SetParameter(0,1);
    fHistLamPhi03->Fit(fitPhiLam3);
    fitPhiHodnoty[1][2]=fitPhiLam3->GetParameter(0);
    fitPhiChyby[1][2]=fitPhiLam3->GetParError(0);
    fHistLamPhi03->Write();
    
    ccLamPhi->cd(4);
    fHistLamPhi03->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 7 < p_{T}^{trig} < 9 GeV/c");
    fHistLamPhi03->SetXTitle("#Delta #phi");
    fHistLamPhi03->SetYTitle("rek./gen.");
    fHistLamPhi04->DrawCopy();
    TF1 * fitPhiLam4 = new TF1("fitLam4"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiLam4->SetParameter(0,1);
    fHistLamPhi04->Fit(fitPhiLam4);
    fitPhiHodnoty[1][3]=fitPhiLam4->GetParameter(0);
    fitPhiChyby[1][3]=fitPhiLam4->GetParError(0);
    fHistLamPhi04->Write();
    
    ccLamPhi->cd(5);
    fHistLamPhi05->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 9 < p_{T}^{trig} < 11 GeV/c");
    fHistLamPhi05->SetXTitle("#Delta #phi");
    fHistLamPhi05->SetYTitle("rek./gen.");
    fHistLamPhi05->DrawCopy();
    TF1 * fitPhiLam5 = new TF1("fitLam5"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiLam5->SetParameter(0,1);
    fHistLamPhi05->Fit(fitPhiLam5);
    fitPhiHodnoty[1][4]=fitPhiLam5->GetParameter(0);
    fitPhiChyby[1][4]=fitPhiLam5->GetParError(0);
    fHistLamPhi05->Write();
    
    ccLamPhi->cd(6);
    fHistLamPhi06->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 11 < p_{T}^{trig} < 15 GeV/c");
    fHistLamPhi06->SetXTitle("#Delta #phi");
    fHistLamPhi06->SetYTitle("rek./gen.");
    fHistLamPhi06->DrawCopy();
    TF1 * fitPhiLam6 = new TF1("fitLam6"," [0]",-kPi/2, -kPi/2+2*kPi);
    fitPhiLam6->SetParameter(0,1);
    fHistLamPhi06->Fit(fitPhiLam6);
    fitPhiHodnoty[1][5]=fitPhiLam6->GetParameter(0);
    fitPhiChyby[1][5]=fitPhiLam6->GetParError(0);
    fHistLamPhi06->Write();
    
    TGraphErrors * LamPhi = new TGraphErrors(nPtBins,ptBins,fitPhiHodnoty[1],ptBinsChyby,fitPhiChyby[1]);
    TCanvas *graphLamPhi = new TCanvas;
    LamPhi->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger  #Lambda+#bar{#Lambda}, phi projekcia");
    LamPhi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    LamPhi->GetYaxis()->SetTitle("hodnota fitu");
    LamPhi->SetMarkerStyle(21);
    LamPhi->SetMarkerColor(kGreen);
    LamPhi->SetLineColor(kGreen);
    LamPhi->SetMarkerSize(1.8);
    LamPhi->Draw("ap");
    LamPhi->Write();
    
    TCanvas *ccLamEta = new TCanvas;
    ccLamEta->Divide(2,3);
    ccLamEta->cd(1);
    fHistLamEta01->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 4 < p_{T}^{trig} < 5 GeV/c");
    fHistLamEta01->SetXTitle("#Delta #eta");
    fHistLamEta01->SetYTitle("rek./gen.");
    fHistLamEta01->DrawCopy();
    TF1 * fitEtaLam1 = new TF1("fitEtaLam1"," [0]",-1.5, 1.5);
    fitEtaLam1->SetParameter(0,1);
    fHistLamEta01->Fit(fitEtaLam1);
    fitEtaHodnoty[1][0]=fitEtaLam1->GetParameter(0);
    fitEtaChyby[1][0]=fitEtaLam1->GetParError(0);
    fHistLamEta01->Write();
    
    ccLamEta->cd(2);
    fHistLamEta02->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 5 < p_{T}^{trig} < 6 GeV/c");
    fHistLamEta02->SetXTitle("#Delta #eta");
    fHistLamEta02->SetYTitle("rek./gen.");
    fHistLamEta02->DrawCopy();
    TF1 * fitEtaLam2 = new TF1("fitEtaLam2"," [0]",-1.5, 1.5);
    fitEtaLam2->SetParameter(0,1);
    fHistLamEta02->Fit(fitEtaLam2);
    fitEtaHodnoty[1][1]=fitEtaLam2->GetParameter(0);
    fitEtaChyby[1][1]=fitEtaLam2->GetParError(0);
    fHistLamEta02->Write();
    
    ccLamEta->cd(3);
    fHistLamEta03->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 6 < p_{T}^{trig} < 7 GeV/c");
    fHistLamEta03->SetXTitle("#Delta #eta");
    fHistLamEta03->SetYTitle("rek./gen.");
    fHistLamEta03->DrawCopy();
    TF1 * fitEtaLam3 = new TF1("fitEtaLam3"," [0]",-1.5, 1.5);
    fitEtaLam3->SetParameter(0,1);
    fHistLamEta03->Fit(fitEtaLam3);
    fitEtaHodnoty[1][2]=fitEtaLam2->GetParameter(0);
    fitEtaChyby[1][2]=fitEtaLam2->GetParError(0);
    fHistLamEta03->Write();
    
    ccLamEta->cd(4);
    fHistLamEta04->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 7 < p_{T}^{trig} < 9 GeV/c");
    fHistLamEta04->SetXTitle("#Delta #eta");
    fHistLamEta04->SetYTitle("rek./gen.");
    fHistLamEta04->DrawCopy();
    TF1 * fitEtaLam4 = new TF1("fitEtaLam4"," [0]",-1.5, 1.5);
    fitEtaLam4->SetParameter(0,1);
    fHistLamEta04->Fit(fitEtaLam4);
    fitEtaHodnoty[1][3]=fitEtaLam4->GetParameter(0);
    fitEtaChyby[1][3]=fitEtaLam4->GetParError(0);
    fHistLamEta04->Write();
    
    ccLamEta->cd(5);
    fHistLamEta05->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 9 < p_{T}^{trig} < 11 GeV/c");
    fHistLamEta05->SetXTitle("#Delta #eta");
    fHistLamEta05->SetYTitle("rek./gen.");
    fHistLamEta05->DrawCopy();
    TF1 * fitEtaLam5 = new TF1("fitEtaLam5"," [0]",-1.5, 1.5);
    fitEtaLam5->SetParameter(0,1);
    fHistLamEta05->Fit(fitEtaLam5);
    fitEtaHodnoty[1][4]=fitEtaLam5->GetParameter(0);
    fitEtaChyby[1][4]=fitEtaLam5->GetParError(0);
    fHistLamEta05->Write();
    
    ccLamEta->cd(6);
    fHistLamEta06->SetTitle("(#Lambda+#bar{#Lambda})_{S}-h korelacie, 11 < p_{T}^{trig} < 15 GeV/c");
    fHistLamEta06->SetXTitle("#Delta #eta");
    fHistLamEta06->SetYTitle("rek./gen.");
    fHistLamEta06->DrawCopy();
    TF1 * fitEtaLam6 = new TF1("fitEtaLam6"," [0]",-1.5, 1.5);
    fitEtaLam6->SetParameter(0,1);
    fHistLamEta06->Fit(fitEtaLam6);
    fitEtaHodnoty[1][5]=fitEtaLam6->GetParameter(0);
    fitEtaChyby[1][5]=fitEtaLam6->GetParError(0);
    fHistLamEta06->Write();
    
    TGraphErrors * LamEta = new TGraphErrors(nPtBins,ptBins,fitEtaHodnoty[1],ptBinsChyby,fitEtaChyby[1]);
    TCanvas *graphLamEta = new TCanvas;
    LamEta->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger #Lambda+#bar{#Lambda}, #eta projekcia");
    LamEta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    LamEta->GetYaxis()->SetTitle("hodnota fitu");
    LamEta->SetMarkerStyle(21);
    LamEta->SetMarkerColor(kGreen);
    LamEta->SetLineColor(kGreen);
    LamEta->SetMarkerSize(1.8);
    LamEta->Draw("ap");
    LamEta->Write();
    
    TCanvas *deltaphi = new TCanvas;
    TLegend *fLegendhi = new TLegend(0.2,0.9,0.75,0.8);
    fLegendhi->AddEntry(k0Phi,"Triger K^{0}_{S}","pl");
    fLegendhi->AddEntry(LamPhi,"Triger #Lambda a #bar{#Lambda}","pl");
    fLegendhi->AddEntry(hPhi,"Triger nabity hadron","pl");
    LamPhi->SetTitle("Zavislost hodnoty fitu #phi projekcie od p_{T}^{trig}");
    LamPhi->Draw("ap");
    k0Phi->Draw("psame");
    hPhi->Draw("psame");
    fLegendhi->Draw();
    
    TCanvas *deltaeta = new TCanvas;
    TLegend *fLegendeta = new TLegend(0.2,0.9,0.75,0.8);
    fLegendeta->AddEntry(k0Eta,"Triger K^{0}_{S}","pl");
    fLegendeta->AddEntry(LamEta,"Triger #Lambda a #bar{#Lambda}","pl");
    fLegendeta->AddEntry(hEta,"Triger nabity hadron","pl");
    LamEta->SetTitle("Zavislost hodnoty fitu #eta projekcie od p_{T}^{trig}");
    LamEta->Draw("ap");
    k0Eta->Draw("psame");
    hEta->Draw("psame");
    fLegendeta->Draw();
    
    fNewFile->Close();
}


