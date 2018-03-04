void GraphMult(){
    gStyle->SetOptStat(0000000000);
    TFile *g =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_1MultBin_hh_0-2Pt.root");
    TFile *f =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_1MultBin_hh_3-5Pt.root");

    TFile *g2 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_2MultBin_hh_0-2Pt.root");
    TFile *f2 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_2MultBin_hh_3-5Pt.root");
    
    TFile *g3 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_3MultBin_hh_0-2Pt.root");
    TFile *f3 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_3MultBin_hh_3-5Pt.root");
  
    TFile *gK =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_1MultBin_Kh_0-2Pt.root");
    TFile *fK =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_1MultBin_Kh_3-5Pt.root");
    
    TFile *gK2 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_2MultBin_Kh_0-2Pt.root");
    TFile *fK2 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_2MultBin_Kh_3-5Pt.root");
    
    TFile *gK3 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_3MultBin_Kh_0-2Pt.root");
    TFile *fK3 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_3MultBin_Kh_3-5Pt.root");
    
    TFile *gL =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_1MultBin_Lh_0-2Pt.root");
    TFile *fL =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_1MultBin_Lh_3-5Pt.root");
    
    TFile *gL2 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_2MultBin_Lh_0-2Pt.root");
    TFile *fL2 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_2MultBin_Lh_3-5Pt.root");
    
    TFile *gL3 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_3MultBin_Lh_0-2Pt.root");
    TFile *fL3 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_3MultBin_Lh_3-5Pt.root");
    
  /* TH2D* fHist2DhhHighMultipl = (TH2D*)g->Get("2dproj_0_2_0");
    TH2D* fHist2DhhHighMultiplHighPt = (TH2D*)g->Get("2dproj_0_2_0");
    fHist2DhhHighMultiplHighPt->SetName("fHist2DhhHighMultiplHighPt");
    TH2D* fHist2DKhHighMultipl = (TH2D*)gK->Get("2dproj_0_0_0");
    TH2D* fHist2DLhHighMultipl = (TH2D*)gL->Get("2dproj_0_1_0");
    char name1[20];
    
    TH2D* fHist2DhhMidleMultipl = (TH2D*)g2->Get("2dproj_1_2_0");
    TH2D* fHist2DhhMidleMultiplHighPt = (TH2D*)g2->Get("2dproj_1_2_0");
    fHist2DhhMidleMultiplHighPt->SetName("fHist2DhhMidleMultiplHighPt");
    TH2D* fHist2DKhMidleMultipl = (TH2D*)gK2->Get("2dproj_1_0_0");
    TH2D* fHist2DLhMidleMultipl = (TH2D*)gL2->Get("2dproj_1_1_0");
    char name2[20];
    
    TH2D* fHist2DhhLowMultipl = (TH2D*)g3->Get("2dproj_2_2_0");
    TH2D* fHist2DhhLowMultiplHighPt = (TH2D*)g3->Get("2dproj_2_2_0");
    fHist2DhhLowMultiplHighPt->SetName("fHist2DhhLowMultiplHighPt");
    TH2D* fHist2DKhLowMultipl = (TH2D*)gK3->Get("2dproj_2_0_0");
    TH2D* fHist2DLhLowMultipl = (TH2D*)gL3->Get("2dproj_2_1_0");
    char name3[20];*/
   /* for(Int_t j=0;j<3;j++){
        for(Int_t i=1;i<6;i++){
            sprintf(name1,"2dproj_0_%d_%d",j,i);
            sprintf(name2,"2dproj_1_%d_%d",j,i);
            sprintf(name3,"2dproj_2_%d_%d",j,i);
            TH2D * tmp = 0x0;
            TH2D * tmp2 = 0x0;
            TH2D * tmp3 = 0x0;
            if(j==2){
                if(i<3) {
                    tmp =(TH2D*)g->Get(name1);
                    tmp2 =(TH2D*)g2->Get(name2);
                    tmp3 =(TH2D*)g3->Get(name3);
                }
                else {
                    tmp =(TH2D*)f->Get(name1);
                    tmp2 =(TH2D*)f2->Get(name2);
                    tmp3 =(TH2D*)f3->Get(name3);
                }
                fHist2DhhHighMultipl->Add(tmp);
                fHist2DhhMidleMultipl->Add(tmp2);
                fHist2DhhLowMultipl->Add(tmp3);
            }
            if(j==0){
                if(i<3) {
                    tmp =(TH2D*)gK->Get(name1);
                    tmp2 =(TH2D*)gK2->Get(name2);
                    tmp3 =(TH2D*)gK3->Get(name3);
                }
                else {
                    tmp =(TH2D*)fK->Get(name1);
                    tmp2 =(TH2D*)fK2->Get(name2);
                    tmp3 =(TH2D*)fK3->Get(name3);
                }
                fHist2DKhHighMultipl->Add(tmp);
                fHist2DKhMidleMultipl->Add(tmp2);
                fHist2DKhLowMultipl->Add(tmp3);
            }
            if(j==1){
                if(i<3) {
                    tmp =(TH2D*)gL->Get(name1);
                    tmp2 =(TH2D*)gL2->Get(name2);
                    tmp3 =(TH2D*)gL3->Get(name3);
                }
                else {
                    tmp =(TH2D*)fL->Get(name1);
                    tmp2 =(TH2D*)fL2->Get(name2);
                    tmp3 =(TH2D*)fL3->Get(name3);
                }
                fHist2DLhHighMultipl->Add(tmp);
                fHist2DLhMidleMultipl->Add(tmp2);
                fHist2DLhLowMultipl->Add(tmp3);
            }
            delete tmp;
            delete tmp2;
            delete tmp3;
        }
    }
    
    TCanvas *cHighMul = new TCanvas;
    fHist2DhhHighMultipl->SetTitle("Korelacna funkcia pre hh, 0-10%");
    fHist2DhhHighMultipl->SetYTitle("#Delta #phi");
    fHist2DhhHighMultipl->SetXTitle("#Delta #eta");
    fHist2DhhHighMultipl->DrawCopy("lego2z");
    
    TCanvas *cHighMulHighPt = new TCanvas;
    fHist2DhhHighMultiplHighPt->SetTitle("Korelacna funkcia pre hh, 0-10%, 4<p_{T}^{trig}<5 GeV/c");
    fHist2DhhHighMultiplHighPt->SetYTitle("#Delta #phi");
    fHist2DhhHighMultiplHighPt->SetXTitle("#Delta #eta");
    fHist2DhhHighMultiplHighPt->DrawCopy("lego2z");
    
    TCanvas *cMediumMul = new TCanvas;
    fHist2DhhMidleMultipl->SetTitle("Korelacna funkcia pre hh, 10-50%");
    fHist2DhhMidleMultipl->SetYTitle("#Delta #phi");
    fHist2DhhMidleMultipl->SetXTitle("#Delta #eta");
    fHist2DhhMidleMultipl->DrawCopy("lego2z");
    
    TCanvas *cMidleMulHighPt = new TCanvas;
    fHist2DhhMidleMultiplHighPt->SetTitle("Korelacna funkcia pre hh, 10-50%, 4<p_{T}^{trig}<5 GeV/c");
    fHist2DhhMidleMultiplHighPt->SetYTitle("#Delta #phi");
    fHist2DhhMidleMultiplHighPt->SetXTitle("#Delta #eta");
    fHist2DhhMidleMultiplHighPt->DrawCopy("lego2z");
    
    TCanvas *cLowMul = new TCanvas;
    fHist2DhhLowMultipl->SetTitle("Korelacna funkcia pre hh, 50-100%");
    fHist2DhhLowMultipl->SetYTitle("#Delta #phi");
    fHist2DhhLowMultipl->SetXTitle("#Delta #eta");
    fHist2DhhLowMultipl->DrawCopy("lego2z");
    
    TCanvas *cLowMulHighPt = new TCanvas;
    fHist2DhhLowMultiplHighPt->SetTitle("Korelacna funkcia pre hh, 50-100%, 4<p_{T}^{trig}<5 GeV/c");
    fHist2DhhLowMultiplHighPt->SetYTitle("#Delta #phi");
    fHist2DhhLowMultiplHighPt->SetXTitle("#Delta #eta");
    fHist2DhhLowMultiplHighPt->DrawCopy("lego2z");
    
    TCanvas *cHighMulRozdiel = new TCanvas;
    fHist2DhhHighMultipl->Add(fHist2DhhLowMultipl,-1);
    fHist2DhhHighMultipl->SetTitle("0-10% po odciatni 50-100%");
    fHist2DhhHighMultipl->DrawCopy("lego2z");
    
    TCanvas *cHighMulK0 = new TCanvas;
    fHist2DKhHighMultipl->SetTitle("Korelacna funkcia pre Kh, 0-10%");
    fHist2DKhHighMultipl->SetYTitle("#Delta #phi");
    fHist2DKhHighMultipl->SetXTitle("#Delta #eta");
    fHist2DKhHighMultipl->DrawCopy("lego2z");
    
    TCanvas *cMediumMulK0 = new TCanvas;
    fHist2DKhMidleMultipl->SetTitle("Korelacna funkcia pre Kh, 10-50%");
    fHist2DKhMidleMultipl->SetYTitle("#Delta #phi");
    fHist2DKhMidleMultipl->SetXTitle("#Delta #eta");
    fHist2DKhMidleMultipl->DrawCopy("lego2z");
    
    TCanvas *cLowMulK0 = new TCanvas;
    fHist2DKhLowMultipl->SetTitle("Korelacna funkcia pre Kh, 50-100%");
    fHist2DKhLowMultipl->SetYTitle("#Delta #phi");
    fHist2DKhLowMultipl->SetXTitle("#Delta #eta");
    fHist2DKhLowMultipl->DrawCopy("lego2z");
    
    TCanvas *cHighMulRozdielK0 = new TCanvas;
    fHist2DKhHighMultipl->Add(fHist2DKhLowMultipl,-1);
    fHist2DKhHighMultipl->SetTitle("0-10% po odciatni 50-100% pre K-h");
    fHist2DKhHighMultipl->DrawCopy("lego2z");
    
    TCanvas *cHighMullam = new TCanvas;
    fHist2DLhHighMultipl->SetTitle("Korelacna funkcia pre Lh, 0-10%");
    fHist2DLhHighMultipl->SetYTitle("#Delta #phi");
    fHist2DLhHighMultipl->SetXTitle("#Delta #eta");
    fHist2DLhHighMultipl->DrawCopy("lego2z");
    
    TCanvas *cMediumMulLam = new TCanvas;
    fHist2DLhMidleMultipl->SetTitle("Korelacna funkcia pre Lh, 10-50%");
    fHist2DLhMidleMultipl->SetYTitle("#Delta #phi");
    fHist2DLhMidleMultipl->SetXTitle("#Delta #eta");
    fHist2DLhMidleMultipl->DrawCopy("lego2z");
    
    TCanvas *cLowMulLam = new TCanvas;
    fHist2DLhLowMultipl->SetTitle("Korelacna funkcia pre Lh, 50-100%");
    fHist2DLhLowMultipl->SetYTitle("#Delta #phi");
    fHist2DLhLowMultipl->SetXTitle("#Delta #eta");
    fHist2DLhLowMultipl->DrawCopy("lego2z");
    
    TCanvas *cHighMulRozdielLam = new TCanvas;
    fHist2DLhHighMultipl->Add(fHist2DLhLowMultipl,-1);
    fHist2DLhHighMultipl->SetTitle("0-10% po odciatni 50-100% pre L-h");
    fHist2DLhHighMultipl->DrawCopy("lego2z");
    */
    // ----------- vytazky -------------
    
    TH1D* fHistYieldNearLow = (TH1D*) g->Get("fHistHadronNear1");
    TH1D* fHistYieldNearHigh = (TH1D*) f->Get("fHistHadronNear1");
    TH1D* fHistYieldNearLow2 = (TH1D*) g2->Get("fHistHadronNear2");
    TH1D* fHistYieldNearHigh2 = (TH1D*) f2->Get("fHistHadronNear2");
    TH1D* fHistYieldNearLow3 = (TH1D*) g3->Get("fHistHadronNear3");
    TH1D* fHistYieldNearHigh3 = (TH1D*) f3->Get("fHistHadronNear3");
 
    fHistYieldNearLow2->SetBinContent(4,0);
    fHistYieldNearHigh2->SetBinContent(3,0);
    fHistYieldNearLow->Add(fHistYieldNearHigh);
    fHistYieldNearLow2->Add(fHistYieldNearHigh2);
    fHistYieldNearLow3->Add(fHistYieldNearHigh3);
    fHistYieldNearLow->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik pre h-h");
    fHistYieldNearLow->SetXTitle("p_{T} (GeV/c)");
    fHistYieldNearLow->SetYTitle("Y_{J}^{#Delta#phi}");
    fHistYieldNearLow->GetYaxis()->SetRangeUser(0.,0.35);
    fHistYieldNearLow->SetMarkerStyle(21);
    fHistYieldNearLow->SetMarkerSize(1.5);
    fHistYieldNearLow->SetMarkerColor(kBlue);
    fHistYieldNearLow->SetLineColor(kBlue);
    fHistYieldNearLow2->SetMarkerStyle(22);
    fHistYieldNearLow2->SetMarkerSize(1.5);
    fHistYieldNearLow2->SetMarkerColor(kRed);
    fHistYieldNearLow2->SetLineColor(kRed);
    fHistYieldNearLow3->SetMarkerStyle(23);
    fHistYieldNearLow3->SetMarkerSize(1.5);
    fHistYieldNearLow3->SetMarkerColor(kBlack);
    fHistYieldNearLow3->SetLineColor(kBlack);
    TLegend * lgHhNear = new TLegend(0.2,0.9,0.75,0.8);
    lgHhNear->AddEntry(fHistYieldNearLow,"0-10%");
    lgHhNear->AddEntry(fHistYieldNearLow2,"10-50%");
    lgHhNear->AddEntry(fHistYieldNearLow3,"50-100%");
    TCanvas *cYieldNearH = new TCanvas;
    fHistYieldNearLow->DrawCopy();
    fHistYieldNearLow2->DrawCopy("same");
    fHistYieldNearLow3->DrawCopy("same");
    lgHhNear->Draw();
    
    TH1D* fHistYieldAwayLow = (TH1D*) g->Get("fHistHadronAway1");
    TH1D* fHistYieldAwayHigh = (TH1D*) f->Get("fHistHadronAway1");
    TH1D* fHistYieldAwayLow2 = (TH1D*) g2->Get("fHistHadronAway2");
    TH1D* fHistYieldAwayHigh2 = (TH1D*) f2->Get("fHistHadronAway2");
    TH1D* fHistYieldAwayLow3 = (TH1D*) g3->Get("fHistHadronAway3");
    TH1D* fHistYieldAwayHigh3 = (TH1D*) f3->Get("fHistHadronAway3");

    Double_t error = fHistYieldAwayHigh3->GetBinError(5);
    fHistYieldAwayLow->Add(fHistYieldAwayHigh);
    fHistYieldAwayLow2->Add(fHistYieldAwayHigh2);
    fHistYieldAwayLow3->Add(fHistYieldAwayHigh3);
    fHistYieldAwayLow->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik pre h-h");
    fHistYieldAwayLow->GetYaxis()->SetRangeUser(0,0.35);
    fHistYieldAwayLow->SetXTitle("p_{T} (GeV/c)");
    fHistYieldAwayLow->SetYTitle("Y_{J}^{#Delta#phi}");
    fHistYieldAwayLow->SetMarkerStyle(21);
    fHistYieldAwayLow->SetMarkerSize(1.5);
    fHistYieldAwayLow->SetMarkerColor(kBlue);
    fHistYieldAwayLow->SetLineColor(kBlue);
    fHistYieldAwayLow2->SetMarkerStyle(22);
    fHistYieldAwayLow2->SetMarkerSize(1.5);
    fHistYieldAwayLow2->SetMarkerColor(kRed);
    fHistYieldAwayLow2->SetLineColor(kRed);
    fHistYieldAwayLow3->SetMarkerStyle(23);
    fHistYieldAwayLow3->SetMarkerSize(1.5);
    fHistYieldAwayLow3->SetMarkerColor(kBlack);
    fHistYieldAwayLow3->SetLineColor(kBlack);
    fHistYieldAwayLow3->SetBinError(5,error);
    TLegend * lgHhAway = new TLegend(0.2,0.9,0.75,0.8);
    lgHhAway->AddEntry(fHistYieldAwayLow,"0-10%");
    lgHhAway->AddEntry(fHistYieldAwayLow2,"10-50%");
    lgHhAway->AddEntry(fHistYieldAwayLow3,"50-100%");
    TCanvas *cYieldAwayH = new TCanvas;
    fHistYieldAwayLow->DrawCopy();
    fHistYieldAwayLow2->DrawCopy("same");
    fHistYieldAwayLow3->DrawCopy("same");
    lgHhAway->Draw();
    
    TH1D* fHistYieldNearKLow = (TH1D*) gK->Get("fHistK0Near1");
    TH1D* fHistYieldNearKHigh = (TH1D*) fK->Get("fHistK0Near1");
    TH1D* fHistYieldNearKLow2 = (TH1D*) gK2->Get("fHistK0Near2");
    TH1D* fHistYieldNearKHigh2 = (TH1D*) fK2->Get("fHistK0Near2");
    TH1D* fHistYieldNearKLow3 = (TH1D*) gK3->Get("fHistK0Nea3r");
    TH1D* fHistYieldNearKHigh3 = (TH1D*) fK3->Get("fHistK0Nea3r");
    
    Double_t errorK0Near = fHistYieldNearKLow2->GetBinError(1);
    fHistYieldNearKLow->Add(fHistYieldNearKHigh);
    fHistYieldNearKLow2->Add(fHistYieldNearKHigh2);
    fHistYieldNearKLow3->Add(fHistYieldNearKHigh3);
    fHistYieldNearKLow->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik pre K^{0}_{S}-h");
    fHistYieldNearKLow->GetYaxis()->SetRangeUser(0,0.35);
    fHistYieldNearKLow->SetXTitle("p_{T} (GeV/c)");
    fHistYieldNearKLow->SetYTitle("Y_{J}^{#Delta#phi}");
    fHistYieldNearKLow->SetMarkerStyle(21);
    fHistYieldNearKLow->SetMarkerSize(1.5);
    fHistYieldNearKLow->SetMarkerColor(kBlue);
    fHistYieldNearKLow->SetLineColor(kBlue);
    fHistYieldNearKLow2->SetMarkerStyle(22);
    fHistYieldNearKLow2->SetMarkerSize(1.5);
    fHistYieldNearKLow2->SetMarkerColor(kRed);
    fHistYieldNearKLow2->SetLineColor(kRed);
    fHistYieldNearKLow3->SetMarkerStyle(23);
    fHistYieldNearKLow3->SetMarkerSize(1.5);
    fHistYieldNearKLow3->SetMarkerColor(kBlack);
    fHistYieldNearKLow3->SetLineColor(kBlack);
    fHistYieldNearKLow2->SetBinError(1,errorK0Near);
    TLegend * lgKhNear = new TLegend(0.2,0.9,0.75,0.8);
    lgKhNear->AddEntry(fHistYieldNearKLow,"0-10%");
    lgKhNear->AddEntry(fHistYieldNearKLow2,"10-50%");
    lgKhNear->AddEntry(fHistYieldNearKLow3,"50-100%");
    TCanvas *cYieldNearK = new TCanvas;
    fHistYieldNearKLow->DrawCopy();
    fHistYieldNearKLow2->DrawCopy("same");
    fHistYieldNearKLow3->DrawCopy("same");
    lgKhNear->Draw();
    
    TH1D* fHistYieldAwayKLow = (TH1D*) gK->Get("fHistK0Away1");
    TH1D* fHistYieldAwayKHigh = (TH1D*) fK->Get("fHistK0Away1");
    TH1D* fHistYieldAwayKLow2 = (TH1D*) gK2->Get("fHistK0Away2");
    TH1D* fHistYieldAwayKHigh2 = (TH1D*) fK2->Get("fHistK0Away2");
    TH1D* fHistYieldAwayKLow3 = (TH1D*) gK3->Get("fHistK0Away3");
    TH1D* fHistYieldAwayKHigh3 = (TH1D*) fK3->Get("fHistK0Away3");
    
    Double_t errorK0Away = fHistYieldAwayKLow2->GetBinError(3);
    fHistYieldAwayKLow->SetBinContent(5,0);
    fHistYieldAwayKLow->Add(fHistYieldAwayKHigh);
    fHistYieldAwayKLow2->Add(fHistYieldAwayKHigh2);
    fHistYieldAwayKLow3->Add(fHistYieldAwayKHigh3);
    fHistYieldAwayKLow->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik pre K^{0}_{S}-h");
    fHistYieldAwayKLow->GetYaxis()->SetRangeUser(0,0.4);
    fHistYieldAwayKLow->SetXTitle("p_{T} (GeV/c)");
    fHistYieldAwayKLow->SetYTitle("Y_{J}^{#Delta#phi}");
    fHistYieldAwayKLow->SetMarkerStyle(21);
    fHistYieldAwayKLow->SetMarkerSize(1.5);
    fHistYieldAwayKLow->SetMarkerColor(kBlue);
    fHistYieldAwayKLow->SetLineColor(kBlue);
    fHistYieldAwayKLow2->SetMarkerStyle(22);
    fHistYieldAwayKLow2->SetMarkerSize(1.5);
    fHistYieldAwayKLow2->SetMarkerColor(kRed);
    fHistYieldAwayKLow2->SetLineColor(kRed);
    fHistYieldAwayKLow3->SetMarkerStyle(23);
    fHistYieldAwayKLow3->SetMarkerSize(1.5);
    fHistYieldAwayKLow3->SetMarkerColor(kBlack);
    fHistYieldAwayKLow3->SetLineColor(kBlack);
    fHistYieldAwayKLow2->SetBinError(3,errorK0Away);
    TLegend * lgKhAway = new TLegend(0.2,0.9,0.75,0.8);
    lgKhAway->AddEntry(fHistYieldAwayKLow,"0-10%");
    lgKhAway->AddEntry(fHistYieldAwayKLow2,"10-50%");
    lgKhAway->AddEntry(fHistYieldAwayKLow3,"50-100%");
    TCanvas *cYieldAwayK = new TCanvas;
    fHistYieldAwayKLow->DrawCopy();
    fHistYieldAwayKLow2->DrawCopy("same");
    fHistYieldAwayKLow3->DrawCopy("same");
    lgKhAway->Draw();
    
    TH1D* fHistYieldNearLamLow = (TH1D*) gL->Get("fHistLambdaNear1");
    TH1D* fHistYieldNearLamHigh = (TH1D*) fL->Get("fHistLambdaNear1");
    TH1D* fHistYieldNearLamLow2 = (TH1D*) gL2->Get("fHistLambdaNear2");
    TH1D* fHistYieldNearLamHigh2 = (TH1D*) fL2->Get("fHistLambdaNear2");
    TH1D* fHistYieldNearLamLow3 = (TH1D*) gL3->Get("fHistLambdaNear3");
    TH1D* fHistYieldNearLamHigh3 = (TH1D*) fL3->Get("fHistLambdaNear3");
    
    fHistYieldNearLamLow2->SetBinContent(5,0);
    fHistYieldNearLamLow2->SetBinContent(6,0);
    fHistYieldNearLamHigh2->SetBinContent(1,0);
    fHistYieldNearLamHigh2->SetBinContent(2,0);
    fHistYieldNearLamHigh2->SetBinContent(3,0);
    fHistYieldNearLamLow3->SetBinContent(4,0);
    fHistYieldNearLamLow->Add(fHistYieldNearLamHigh);
    fHistYieldNearLamLow2->Add(fHistYieldNearLamHigh2);
    fHistYieldNearLamLow3->Add(fHistYieldNearLamHigh3);
    fHistYieldNearLamLow->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik pre (#Lambda+#bar{#Lambda})-h");
    fHistYieldNearLamLow->SetXTitle("p_{T} (GeV/c)");
    fHistYieldNearLamLow->SetYTitle("Y_{J}^{#Delta#phi}");
    fHistYieldNearLamLow->GetYaxis()->SetRangeUser(0.,1);
    fHistYieldNearLamLow->SetMarkerStyle(21);
    fHistYieldNearLamLow->SetMarkerSize(1.5);
    fHistYieldNearLamLow->SetMarkerColor(kBlue);
    fHistYieldNearLamLow->SetLineColor(kBlue);
    fHistYieldNearLamLow2->SetMarkerStyle(22);
    fHistYieldNearLamLow2->SetMarkerSize(1.5);
    fHistYieldNearLamLow2->SetMarkerColor(kRed);
    fHistYieldNearLamLow2->SetLineColor(kRed);
    fHistYieldNearLamLow3->SetMarkerStyle(23);
    fHistYieldNearLamLow3->SetMarkerSize(1.5);
    fHistYieldNearLamLow3->SetMarkerColor(kBlack);
    fHistYieldNearLamLow3->SetLineColor(kBlack);
    TLegend * lgLamhNear = new TLegend(0.2,0.9,0.75,0.8);
    lgLamhNear->AddEntry(fHistYieldNearLamLow,"0-10%");
    lgLamhNear->AddEntry(fHistYieldNearLamLow2,"10-50%");
    lgLamhNear->AddEntry(fHistYieldNearLamLow3,"50-100%");
    TCanvas *cYieldNearLam = new TCanvas;
    fHistYieldNearLamLow->DrawCopy();
    fHistYieldNearLamLow2->DrawCopy("same");
    fHistYieldNearLamLow3->DrawCopy("same");
    lgLamhNear->Draw();
    
    TH1D* fHistYieldAwayLamLow = (TH1D*) gL->Get("fHistLambdaAway1");
    TH1D* fHistYieldAwayLamHigh = (TH1D*) fL->Get("fHistLambdaAway1");
    TH1D* fHistYieldAwayLamLow2 = (TH1D*) gL2->Get("fHistLambdaAway2");
    TH1D* fHistYieldAwayLamHigh2 = (TH1D*) fL2->Get("fHistLambdaAway2");
    TH1D* fHistYieldAwayLamLow3 = (TH1D*) gL3->Get("fHistLambdaAway3");
    TH1D* fHistYieldAwayLamHigh3 = (TH1D*) fL3->Get("fHistLambdaAway3");
    
    fHistYieldAwayLamLow->Add(fHistYieldAwayLamHigh);
    fHistYieldAwayLamLow2->Add(fHistYieldAwayLamHigh2);
    fHistYieldAwayLamLow3->Add(fHistYieldAwayLamHigh3);
    fHistYieldAwayLamLow->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik pre (#Lambda+#bar{#Lambda})-h");
    fHistYieldAwayLamLow->GetYaxis()->SetRangeUser(0,1);
    fHistYieldAwayLamLow->SetXTitle("p_{T} (GeV/c)");
    fHistYieldAwayLamLow->SetYTitle("Y_{J}^{#Delta#phi}");
    fHistYieldAwayLamLow->SetMarkerStyle(21);
    fHistYieldAwayLamLow->SetMarkerSize(1.5);
    fHistYieldAwayLamLow->SetMarkerColor(kBlue);
    fHistYieldAwayLamLow->SetLineColor(kBlue);
    fHistYieldAwayLamLow2->SetMarkerStyle(22);
    fHistYieldAwayLamLow2->SetMarkerSize(1.5);
    fHistYieldAwayLamLow2->SetMarkerColor(kRed);
    fHistYieldAwayLamLow2->SetLineColor(kRed);
    fHistYieldAwayLamLow3->SetMarkerStyle(23);
    fHistYieldAwayLamLow3->SetMarkerSize(1.5);
    fHistYieldAwayLamLow3->SetMarkerColor(kBlack);
    fHistYieldAwayLamLow3->SetLineColor(kBlack);
    //fHistYieldAwayKLow2->SetBinError(3,errorK0Away);
    TLegend * lgLamhAway = new TLegend(0.2,0.9,0.75,0.8);
    lgLamhAway->AddEntry(fHistYieldAwayLamLow,"0-10%");
    lgLamhAway->AddEntry(fHistYieldAwayLamLow2,"10-50%");
    lgLamhAway->AddEntry(fHistYieldAwayLamLow3,"50-100%");
    TCanvas *cYieldAwayLam = new TCanvas;
    fHistYieldAwayLamLow->DrawCopy();
    fHistYieldAwayLamLow2->DrawCopy("same");
    fHistYieldAwayLamLow3->DrawCopy("same");
    lgLamhAway->Draw();
    
    // ------ vytazky pre min bias -----------
  /*  const Int_t nPtBins = 6;
    const Int_t nTig =3;
    char nameMinBias[20];
    char bezpoz[100];
    char titleprojphi[50];
    char nameprojphi[50];
    char nametrigg[50];
    const Double_t kPi = TMath::Pi();
    
    TH2D ** fHistProj2D = new TH2D* [nTig*nPtBins];
    TH1D ** fHistTrigg = new TH1D* [nTig*nPtBins];
    TH1D ** fHistProjPhi = new TH1D* [nTig*nPtBins];
    
    Double_t yieldnear[nTig][nPtBins];
    Double_t yieldaway[nTig][nPtBins];
    Double_t yieldnearerror[nTig][nPtBins];
    Double_t yieldawayerror[nTig][nPtBins];
    Double_t poz;
    
    TCanvas *e = new TCanvas;
    e->Divide(nTig,nPtBins);
    TCanvas *canK = new TCanvas;
    canK->Divide(2,3);
    
    TCanvas *canLam = new TCanvas;
    canLam->Divide(2,3);
    TCanvas *canH = new TCanvas;
    canH->Divide(2,3);
    for(Int_t i=0;i<nTig;i++){
        for(Int_t j=0;j<1nPtBins;j++){
            for(Int_t iMult=0; iMult<3; iMult++ ){
                sprintf(nameMinBias,"2dproj_%d_%d_%d;1",iMult,i,j);
                sprintf(nameprojphi,"1dtrigg_%d_%d_%d;1",iMult,i,j);
                TH2D* tmp = 0x0;
                TH1D* tmpTrig = 0x0;
                if (iMult==0){
                    if(i==0){
                        if(j<3)tmp = (TH2D*) gK ->Get(nameMinBias);
                        else tmp = (TH2D*) fK ->Get(nameMinBias);
                    }
                    if(i==1){
                        if(j<3)tmp = (TH2D*) gL ->Get(nameMinBias);
                        else tmp = (TH2D*) fL ->Get(nameMinBias);
                    }
                    if(i==2){
                        if(j<3)tmp = (TH2D*) g ->Get(nameMinBias);
                        if(j<3)tmpTrig = (TH1D*) g ->Get(nameprojphi);
                        else tmp = (TH2D*) f ->Get(nameMinBias);
                    }
                }
                if (iMult==1){
                    if(i==0){
                        if(j<3)tmp = (TH2D*) gK2 ->Get(nameMinBias);
                        else tmp = (TH2D*) fK2 ->Get(nameMinBias);
                    }
                    if(i==1){
                        if(j<3)tmp = (TH2D*) gL2 ->Get(nameMinBias);
                        else tmp = (TH2D*) fL2 ->Get(nameMinBias);
                    }
                    if(i==2){
                        if(j<3)tmp = (TH2D*) g ->Get(nameMinBias);
                        if(j<3)tmpTrig = (TH1D*) g ->Get(nameprojphi);
                        else tmp = (TH2D*) f2 ->Get(nameMinBias);
                    }
                }
                if (iMult==2){
                    if(i==0){
                        if(j<3)tmp = (TH2D*) gK3 ->Get(nameMinBias);
                        else tmp = (TH2D*) fK3 ->Get(nameMinBias);
                    }
                    if(i==1){
                        if(j<3)tmp = (TH2D*) gL3 ->Get(nameMinBias);
                        else tmp = (TH2D*) fL3 ->Get(nameMinBias);
                    }
                    if(i==2){
                        if(j<3)tmp = (TH2D*) g ->Get(nameMinBias);
                        if(j<3)tmpTrig = (TH1D*) g ->Get(nameprojphi);
                        else tmp = (TH2D*) f3 ->Get(nameMinBias);
                    }
                }
                if(iMult==0) {
                    fHistProj2D[i*nPtBins+j] = (TH2D*) tmp->Clone();
                    fHistTrigg[i*nPtBins+j] = (TH1D*) tmpTrig->Clone();
                } else {
                    fHistProj2D[i*nPtBins+j]->Add(tmp);
                    fHistTrigg[i*nPtBins+j]->Add(tmpTrig);
                }
                delete tmp;
                delete tmpTrig;
            }
            
            if(i==0) fHistProj2D[i*nPtBins+j]->Scale(1./fHistTrigg[i*nPtBins+j]->GetBinContent(1));
            if(i==1) fHistProj2D[i*nPtBins+j]->Scale(1./(fHistTrigg[i*nPtBins+j]->GetBinContent(2)+fHistTrigg[i*nPtBins+j]->GetBinContent(3)));
            if(i==2) fHistProj2D[i*nPtBins+j]->Scale(1./fHistTrigg[i*nPtBins+j]->GetBinContent(4));
            
            
            fHistProj2D[i*nPtBins+j]->SetAxisRange(-1,1,"x");
            Double_t binWidthPhi = fHistProj2D[i*nPtBins+j]->GetYaxis()->GetBinWidth(2);
            Double_t binWidthEta = fHistProj2D[i*nPtBins+j]->GetXaxis()->GetBinWidth(2);
            
           // fHistProj2D[i*nPtBins+j]->Scale(binWidthPhi*binWidthEta);
            
            fHistProjPhi[i*nPtBins+j]=(TH1D *)fHistProj2D[i*nPtBins+j]->ProjectionY();

            fHistProjPhi[i*nPtBins+j]->SetXTitle("#Delta #Phi");
            fHistProjPhi[i*nPtBins+j]->SetYTitle("# parov / # trigger castic");
            sprintf(titleprojphi,"Rozdelenie #Delta #Phi pre trigger %d pre pt bin %d", i+1,j+1);
            fHistProjPhi[i*nPtBins+j]->SetTitle(titleprojphi);
            sprintf(nameprojphi,"projPhi_%d_%d",i+1,j+1);
            fHistProjPhi[i*nPtBins+j]->SetName(nameprojphi);
            e->cd(i*nPtBins+j+1);
            fHistProjPhi[i*nPtBins+j]->DrawCopy();
            
            Double_t val1 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) );
            Double_t val2 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) +1);
            Double_t val3 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) -1);
            Double_t val4 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1));
            Double_t val5 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1)+1);
            Double_t val6 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1)-1);
            
            
            poz = (val1+val2+val3+val4+val5+val6)/6;
            cout << poz<< endl;
            
            TF1 *fFuncBack = new TF1("fFuncBack"," [0]",-kPi/2, -kPi/2+2*kPi);
            fFuncBack->SetParameter(0,poz);
            fHistProjPhi[i*nPtBins+j]->Add(fFuncBack,-1);
            
            Double_t max = fHistProjPhi[i*nPtBins+j]->GetMaximum();
            fHistProjPhi[i*nPtBins+j]->SetAxisRange(0.,max*1.1,"y");
            fHistProjPhi[i*nPtBins+j]->SetXTitle("#Delta #phi");
            fHistProjPhi[i*nPtBins+j]->SetYTitle("pocet parov / pocet trigrovacich castic");
            fHistProjPhi[i*nPtBins+j]->GetXaxis()->SetTitleOffset(0.4);
            fHistProjPhi[i*nPtBins+j]->GetXaxis()->SetTitleSize(0.08);
            fHistProjPhi[i*nPtBins+j]->GetXaxis()->SetLabelSize(0.055);
            fHistProjPhi[i*nPtBins+j]->GetYaxis()->SetTitleOffset(0.7);
            fHistProjPhi[i*nPtBins+j]->GetYaxis()->SetTitleSize(0.055);
            fHistProjPhi[i*nPtBins+j]->GetYaxis()->SetLabelSize(0.055);
            fHistProjPhi[i*nPtBins+j]->GetYaxis()->SetLabelOffset(0.004);
            
            if (i==0){
                if(j==0) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 4 GeV/c<p_{T}^{trig}<5 GeV/c");
                if(j==1) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 5 GeV/c<p_{T}^{trig}<6 GeV/c");
                if(j==2) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 6 GeV/c<p_{T}^{trig}<7 GeV/c");
                if(j==3) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 7 GeV/c<p_{T}^{trig}<9 GeV/c");
                if(j==4) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 9 GeV/c<p_{T}^{trig}<11 GeV/c");
                if(j==5) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger K^{0}_{S} po odcitani pozadia, 11 GeV/c<p_{T}^{trig}<15 GeV/c");
                fHistProjPhi[i*nPtBins+j]->SetTitle(bezpoz);
                canK->cd(j+1);
                fHistProjPhi[i*nPtBins+j]->DrawCopy();
            }
            
            if (i==1) {
                if(j==0) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 4 GeV/c<p_{T}^{trig}<5 GeV/c");
                if(j==1) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 5 GeV/c<p_{T}^{trig}<6 GeV/c");
                if(j==2) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 6 GeV/c<p_{T}^{trig}<7 GeV/c");
                if(j==3) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 7 GeV/c<p_{T}^{trig}<9 GeV/c");
                if(j==4) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 9 GeV/c<p_{T}^{trig}<11 GeV/c");
                if(j==5) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger #Lambda a #bar{#Lambda} po odcitani pozadia, 11 GeV/c<p_{T}^{trig}<15 GeV/c");
                fHistProjPhi[i*nPtBins+j]->SetTitle(bezpoz);
                canLam->cd(j+1);
                fHistProjPhi[i*nPtBins+j]->DrawCopy();
            }
            
            
            if (i==2){
                if(j==0) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 4 GeV/c<p_{T}^{trig}<5 GeV/c");
                if(j==1) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 5 GeV/c<p_{T}^{trig}<6 GeV/c");
                if(j==2) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 6 GeV/c<p_{T}^{trig}<7 GeV/c");
                if(j==3) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 7 GeV/c<p_{T}^{trig}<9 GeV/c");
                if(j==4) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 9 GeV/c<p_{T}^{trig}<11 GeV/c");
                if(j==5) sprintf(bezpoz,"Rozdelenie #Delta #phi pre trigger h po odcitani pozadia, 11 GeV/c<p_{T}^{trig}<15 GeV/c");
                fHistProjPhi[i*nPtBins+j]->SetTitle(bezpoz);
                canH->cd(j+1);
                fHistProjPhi[i*nPtBins+j]->DrawCopy();
            }
            
            Int_t minnear = (fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-0.9);
            Int_t maxnear = (fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(0.9);
            Double_t widthnear = fHistProjPhi[i*nPtBins+j]->GetBinWidth(maxnear);
            Double_t integralnear =0.;
            Double_t errornear =0.;
            
            for(Int_t k=minnear; k<maxnear; k++){
                integralnear+= fHistProjPhi[+i*nPtBins+j]->GetBinContent(k);
                errornear+= TMath::Power(fHistProjPhi[+i*nPtBins+j]->GetBinError(k),2);
            }
            
            yieldnearerror[i][j] = TMath::Sqrt(errornear);
            yieldnearerror[i][j] = yieldnearerror[i][j] *widthnear;
            integralnear=integralnear*widthnear;
            yieldnear[i][j] = integralnear;
            
            Int_t minaway = (fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(kPi-1.5);
            Int_t maxaway = (fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(kPi+1.5);
            Double_t widthaway = fHistProjPhi[i*nPtBins+j]->GetBinWidth(maxaway);
            Double_t integralaway =0.;
            Double_t erroralaway =0.;
            
            for(Int_t k=minaway; k<maxaway; k++){
                integralaway+= fHistProjPhi[i*nPtBins+j]->GetBinContent(k);
                erroralaway+= TMath::Power(fHistProjPhi[i*nPtBins+j]->GetBinError(k),2);
            }
            
            yieldawayerror[i][j] = TMath::Sqrt(erroralaway);
            yieldawayerror[i][j] = yieldawayerror[i][j] *widthaway;
            integralaway=integralaway*widthaway;
            yieldaway[i][j] = integralaway;
            
            
            cout << "yield near side  = "<< yieldnear[i][j] << "  yield away side = " << yieldaway[i][j] << endl;
            delete fFuncBack;
            
        }
        
    }
    Double_t PtHist[nPtBins+1] = {4, 5, 6, 7, 9, 11, 15};
    Double_t PtGraph[nPtBins] = {4.5, 5.5, 6.5, 8, 10, 13};
    TH1D *fHistK0Near = new TH1D("fHistK0Near","fHistK0Near",nPtBins,PtHist);
      TH1D *fHistLambdaNear = new TH1D("fHistLambdaNear","fHistLambdaNear",nPtBins,PtHist);
     TH1D *fHistHadronNear = new TH1D("fHistHadronNear","fHistHadronNear",nPtBins,PtHist);
     
     TH1D *fHistK0Away = new TH1D("fHistK0Away","fHistK0Away",nPtBins,PtHist);
     TH1D *fHistLambdaAway = new TH1D("fHistLambdaAway","fHistLambdaAway",nPtBins,PtHist);
     TH1D *fHistHadronAway = new TH1D("fHistHadronAway","fHistHadronAway",nPtBins,PtHist);
     
     for(Int_t i=0; i<nPtBins; i++ ){
     
     fHistK0Near->Fill(PtGraph[i], yieldnear[0][i]);
     fHistK0Near->SetBinError(i+1,yieldnearerror[0][i]);
     
     fHistLambdaNear->Fill(PtGraph[i], yieldnear[1][i]);
     fHistLambdaNear->SetBinError(i+1,yieldnearerror[1][i]);
     
     fHistHadronNear->Fill(PtGraph[i], yieldnear[2][i]);
     fHistHadronNear->SetBinError(i+1,yieldnearerror[2][i]);
     
     fHistK0Away->Fill(PtGraph[i], yieldaway[0][i]);
     fHistK0Away->SetBinError(i+1,yieldawayerror[0][i]);
     
     fHistLambdaAway->Fill(PtGraph[i], yieldaway[1][i]);
     fHistLambdaAway->SetBinError(i+1,yieldawayerror[1][i]);
     
     fHistHadronAway->Fill(PtGraph[i], yieldaway[2][i]);
     fHistHadronAway->SetBinError(i+1,yieldawayerror[2][i]);
     
     }
     
     fHistK0Near->SetMarkerStyle(23);
     fHistK0Near->SetMarkerColor(kBlue);
     fHistK0Near->SetMarkerSize(1.8);
     fHistK0Near->SetLineColor(kBlue);
     fHistK0Near->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik");
     fHistK0Near->GetXaxis()->SetTitle("p_{T} (GeV/c)");
     fHistK0Near->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
     fHistK0Near->GetYaxis()->SetRangeUser(-0.1,1);
     
     fHistLambdaNear->SetMarkerStyle(21);
     fHistLambdaNear->SetMarkerColor(kGreen);
     fHistLambdaNear->SetMarkerSize(1.8);
     fHistLambdaNear->SetLineColor(kGreen);
     
     fHistHadronNear->SetMarkerStyle(29);
     fHistHadronNear->SetMarkerColor(kRed);
     fHistHadronNear->SetMarkerSize(1.8);
     fHistHadronNear->SetLineColor(kRed);
     
     TLegend *fLegendNear = new TLegend(0.2,0.9,0.75,0.8);
     fLegendNear->AddEntry(fHistK0Near,"Triger K^{0}_{S}","pl");
     fLegendNear->AddEntry(fHistLambdaNear,"Triger #Lambda a #bar{#Lambda}","pl");
     fLegendNear->AddEntry(fHistHadronNear,"Triger nabity hadron","pl");
     
     TCanvas * cannear = new TCanvas();
     fHistK0Near->DrawCopy();
     fHistLambdaNear->DrawCopy("same");
     fHistHadronNear->DrawCopy("same");
     fLegendNear->Draw();
     
     fHistK0Away->SetMarkerStyle(23);
     fHistK0Away->SetMarkerColor(kBlue);
     fHistK0Away->SetMarkerSize(1.8);
     fHistK0Away->SetLineColor(kBlue);
     fHistK0Away->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik");
     fHistK0Away->GetXaxis()->SetTitle("p_{T} (GeV/c)");
     fHistK0Away->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
     fHistK0Away->GetYaxis()->SetRangeUser(-0.1,1);
     
     fHistLambdaAway->SetMarkerStyle(21);
     fHistLambdaAway->SetMarkerColor(kGreen);
     fHistLambdaAway->SetMarkerSize(1.8);
     fHistLambdaAway->SetLineColor(kGreen);
     
     fHistHadronAway->SetMarkerStyle(29);
     fHistHadronAway->SetMarkerColor(kRed);
     fHistHadronAway->SetMarkerSize(1.8);
     fHistHadronAway->SetLineColor(kRed);
     
     TLegend *fLegendAway = new TLegend(0.2,0.9,0.75,0.8);
     fLegendAway->AddEntry(fHistK0Away,"Triger K^{0}_{S}","pl");
     fLegendAway->AddEntry(fHistLambdaAway,"Triger #Lambda a #bar{#Lambda}","pl");
     fLegendAway->AddEntry(fHistHadronAway,"Triger nabity hadron","pl");
     
     TCanvas * canaway = new TCanvas();
     fHistK0Away->DrawCopy();
     fHistLambdaAway->DrawCopy("same");
     fHistHadronAway->DrawCopy("same");
     fLegendAway->Draw();
     
     TFile *fFile = TFile::Open("Vytazky_minBias_data.root","RECREATE");
     fHistK0Near->Write();
     fHistLambdaNear->Write();
     fHistHadronNear->Write();
     fHistK0Away->Write();
     fHistLambdaAway->Write();
     fHistHadronAway->Write();
     fFile->Close();*/
}
