#include <TLegend.h>
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
    
    TFile *fileK0Mix =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphMC_2015c_07_averageMixingK0.root");
    TFile *fileLamMix =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphMC_2015c_07_averageMixingLam.root");
    TFile *filehhMix =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphMC_2015c_07_averageMixingHH.root");
    
   TH2D* fHist2DhhHighMultipl = (TH2D*)g->Get("2dproj_0_2_0");
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
    char name3[20];
    
    char nameTrigg1[20];
    char nameTrigg2[20];
    char nameTrigg3[20];
    
    TH1D* fHist1DhhHighMultiplTrigg = (TH1D*)g->Get("1dtrigg_0_2_0");
    TH1D* fHist1DKhHighMultiplTrigg = (TH1D*)gK->Get("1dtrigg_0_0_0");
    TH1D* fHist1DLhHighMultiplTrigg = (TH1D*)gL->Get("1dtrigg_0_1_0");
    
    TH1D* fHist1DhhMidleMultiplTrigg = (TH1D*)g2->Get("1dtrigg_1_2_0");
    TH1D* fHist1DKhMidleMultiplTrigg = (TH1D*)gK2->Get("1dtrigg_1_0_0");
    TH1D* fHist1DLhMidleMultiplTrigg = (TH1D*)gL2->Get("1dtrigg_1_1_0");
    
    TH1D* fHist1DhhLowMultiplTrigg = (TH1D*)g3->Get("1dtrigg_2_2_0");
    TH1D* fHist1DKhLowMultiplTrigg = (TH1D*)gK3->Get("1dtrigg_2_0_0");
    TH1D* fHist1DLhLowMultiplTrigg = (TH1D*)gL3->Get("1dtrigg_2_1_0");
    
    for(Int_t j=0;j<3;j++){
        for(Int_t i=1;i<6;i++){
            sprintf(name1,"2dproj_0_%d_%d",j,i);
            sprintf(name2,"2dproj_1_%d_%d",j,i);
            sprintf(name3,"2dproj_2_%d_%d",j,i);
            sprintf(nameTrigg1,"1dtrigg_0_%d_%d",j,i);
            sprintf(nameTrigg2,"1dtrigg_1_%d_%d",j,i);
            sprintf(nameTrigg3,"1dtrigg_2_%d_%d",j,i);
            TH2D * tmp = 0x0;
            TH2D * tmp2 = 0x0;
            TH2D * tmp3 = 0x0;
            TH1D * tmpTrigg = 0x0;
            TH1D * tmpTrigg2 = 0x0;
            TH1D * tmpTrigg3 = 0x0;
            if(j==2){
                if(i<3) {
                    tmp =(TH2D*)g->Get(name1);
                    tmp2 =(TH2D*)g2->Get(name2);
                    tmp3 =(TH2D*)g3->Get(name3);
                    tmpTrigg = (TH1D*)g->Get(nameTrigg1);
                    tmpTrigg2 = (TH1D*)g2->Get(nameTrigg2);
                    tmpTrigg3 = (TH1D*)g3->Get(nameTrigg3);
                }
                else {
                    tmp =(TH2D*)f->Get(name1);
                    tmp2 =(TH2D*)f2->Get(name2);
                    tmp3 =(TH2D*)f3->Get(name3);
                    tmpTrigg = (TH1D*)f->Get(nameTrigg1);
                    tmpTrigg2 = (TH1D*)f2->Get(nameTrigg2);
                    tmpTrigg3 = (TH1D*)f3->Get(nameTrigg3);
                }
                fHist2DhhHighMultipl->Add(tmp);
                fHist2DhhMidleMultipl->Add(tmp2);
                fHist2DhhLowMultipl->Add(tmp3);
                
                fHist1DhhHighMultiplTrigg->Add(tmpTrigg);
                fHist1DhhMidleMultiplTrigg->Add(tmpTrigg2);
                fHist1DhhLowMultiplTrigg->Add(tmpTrigg3);
                
            }
            if(j==0){
                if(i<3) {
                    tmp =(TH2D*)gK->Get(name1);
                    tmp2 =(TH2D*)gK2->Get(name2);
                    tmp3 =(TH2D*)gK3->Get(name3);
                    tmpTrigg = (TH1D*)gK->Get(nameTrigg1);
                    tmpTrigg2 = (TH1D*)gK2->Get(nameTrigg2);
                    tmpTrigg3 = (TH1D*)gK3->Get(nameTrigg3);
                }
                else {
                    tmp =(TH2D*)fK->Get(name1);
                    tmp2 =(TH2D*)fK2->Get(name2);
                    tmp3 =(TH2D*)fK3->Get(name3);
                    tmpTrigg = (TH1D*)fK->Get(nameTrigg1);
                    tmpTrigg2 = (TH1D*)fK2->Get(nameTrigg2);
                    tmpTrigg3 = (TH1D*)fK3->Get(nameTrigg3);
                }
                fHist2DKhHighMultipl->Add(tmp);
                fHist2DKhMidleMultipl->Add(tmp2);
                fHist2DKhLowMultipl->Add(tmp3);
                
                fHist1DKhHighMultiplTrigg->Add(tmpTrigg);
                fHist1DKhMidleMultiplTrigg->Add(tmpTrigg2);
                fHist1DKhLowMultiplTrigg->Add(tmpTrigg3);
            }
            if(j==1){
                if(i<3) {
                    tmp =(TH2D*)gL->Get(name1);
                    tmp2 =(TH2D*)gL2->Get(name2);
                    tmp3 =(TH2D*)gL3->Get(name3);
                    tmpTrigg = (TH1D*)gL->Get(nameTrigg1);
                    tmpTrigg2 = (TH1D*)gL2->Get(nameTrigg2);
                    tmpTrigg3 = (TH1D*)gL3->Get(nameTrigg3);
                }
                else {
                    tmp =(TH2D*)fL->Get(name1);
                    tmp2 =(TH2D*)fL2->Get(name2);
                    tmp3 =(TH2D*)fL3->Get(name3);
                    tmpTrigg = (TH1D*)fL->Get(nameTrigg1);
                    tmpTrigg2 = (TH1D*)fL2->Get(nameTrigg2);
                    tmpTrigg3 = (TH1D*)fL3->Get(nameTrigg3);
                }
                fHist2DLhHighMultipl->Add(tmp);
                fHist2DLhMidleMultipl->Add(tmp2);
                fHist2DLhLowMultipl->Add(tmp3);
                
                fHist1DLhHighMultiplTrigg->Add(tmpTrigg);
                fHist1DLhMidleMultiplTrigg->Add(tmpTrigg2);
                fHist1DLhLowMultiplTrigg->Add(tmpTrigg3);
            }
            delete tmp;
            delete tmp2;
            delete tmp3;
            
            delete tmpTrigg;
            delete tmpTrigg2;
            delete tmpTrigg3;
        }
    }
    
    TCanvas *cHighMul = new TCanvas;
    fHist2DhhHighMultipl->SetTitle("Korelacna funkcia pre hh, 0-10%");
    fHist2DhhHighMultipl->SetYTitle("#Delta #phi");
    fHist2DhhHighMultipl->SetXTitle("#Delta #eta");
    fHist2DhhHighMultipl->Scale(1./fHist1DhhHighMultiplTrigg->GetBinContent(4));
    fHist2DhhHighMultipl->DrawCopy("lego2z");
    
 /*   TCanvas *cHighMulHighPt = new TCanvas;
    fHist2DhhHighMultiplHighPt->SetTitle("Korelacna funkcia pre hh, 0-10%, 4<p_{T}^{trig}<5 GeV/c");
    fHist2DhhHighMultiplHighPt->SetYTitle("#Delta #phi");
    fHist2DhhHighMultiplHighPt->SetXTitle("#Delta #eta");
    fHist2DhhHighMultiplHighPt->DrawCopy("lego2z");*/
    
    TCanvas *cMediumMul = new TCanvas;
    fHist2DhhMidleMultipl->SetTitle("Korelacna funkcia pre hh, 10-50%");
    fHist2DhhMidleMultipl->SetYTitle("#Delta #phi");
    fHist2DhhMidleMultipl->SetXTitle("#Delta #eta");
    fHist2DhhMidleMultipl->Scale(1./fHist1DhhMidleMultiplTrigg->GetBinContent(4));
    fHist2DhhMidleMultipl->DrawCopy("lego2z");
    
    /*TCanvas *cMidleMulHighPt = new TCanvas;
    fHist2DhhMidleMultiplHighPt->SetTitle("Korelacna funkcia pre hh, 10-50%, 4<p_{T}^{trig}<5 GeV/c");
    fHist2DhhMidleMultiplHighPt->SetYTitle("#Delta #phi");
    fHist2DhhMidleMultiplHighPt->SetXTitle("#Delta #eta");
    fHist2DhhMidleMultiplHighPt->DrawCopy("lego2z");*/
    
    TCanvas *cLowMul = new TCanvas;
    fHist2DhhLowMultipl->SetTitle("Korelacna funkcia pre hh, 50-100%");
    fHist2DhhLowMultipl->SetYTitle("#Delta #phi");
    fHist2DhhLowMultipl->SetXTitle("#Delta #eta");
    fHist2DhhLowMultipl->Scale(1./fHist1DhhLowMultiplTrigg->GetBinContent(4));
    fHist2DhhLowMultipl->DrawCopy("lego2z");
    
  /*  TCanvas *cLowMulHighPt = new TCanvas;
    fHist2DhhLowMultiplHighPt->SetTitle("Korelacna funkcia pre hh, 50-100%, 4<p_{T}^{trig}<5 GeV/c");
    fHist2DhhLowMultiplHighPt->SetYTitle("#Delta #phi");
    fHist2DhhLowMultiplHighPt->SetXTitle("#Delta #eta");
    fHist2DhhLowMultiplHighPt->DrawCopy("lego2z");*/
    
    TCanvas *cHighMulRozdiel = new TCanvas;
   // Double_t maxHighMultipl = fHist2DhhHighMultipl->GetMaximum();
   // Double_t maxLowMultipl = fHist2DhhLowMultipl->GetMaximum();
   // Double_t scale = maxHighMultipl/maxLowMultipl;
   // fHist2DhhLowMultipl->Scale(scale);
    fHist2DhhHighMultipl->Add(fHist2DhhLowMultipl,-1);
    fHist2DhhHighMultipl->SetTitle("0-10% po odciatni 50-100% pre korelacie h-h");
    fHist2DhhHighMultipl->DrawCopy("lego2z");
    
  /*  TCanvas *cHighMulK0 = new TCanvas;
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
    fHist2DLhHighMultipl->DrawCopy("lego2z");*/
    
    // ----------- vytazky -------------
/*
    TH1D* fHistYieldNearLow = (TH1D*) g->Get("fHistHadronNear1");
    TH1D* fHistYieldNearHigh = (TH1D*) f->Get("fHistHadronNear1");
    TH1D* fHistYieldNearLow2 = (TH1D*) g2->Get("fHistHadronNear2");
    TH1D* fHistYieldNearHigh2 = (TH1D*) f2->Get("fHistHadronNear2");
    TH1D* fHistYieldNearLow3 = (TH1D*) g3->Get("fHistHadronNear3");
    TH1D* fHistYieldNearHigh3 = (TH1D*) f3->Get("fHistHadronNear3");
    
    fHistYieldNearLow->Sumw2();
    fHistYieldNearHigh->Sumw2();
    fHistYieldNearLow2->Sumw2();
    fHistYieldNearHigh2->Sumw2();
    fHistYieldNearLow3->Sumw2();
    fHistYieldNearHigh3->Sumw2();
 
    fHistYieldNearLow2->SetBinContent(4,0);
    fHistYieldNearHigh2->SetBinContent(3,0);
    fHistYieldNearLow->Add(fHistYieldNearHigh);
    fHistYieldNearLow2->Add(fHistYieldNearHigh2);
    fHistYieldNearLow3->Add(fHistYieldNearHigh3);
    fHistYieldNearLow->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik pre h-h");
    fHistYieldNearLow->SetXTitle("p_{T}^{trig} (GeV/c)");
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
    
    fHistYieldAwayLow->Sumw2();
    fHistYieldAwayHigh->Sumw2();
    fHistYieldAwayLow2->Sumw2();
    fHistYieldAwayHigh2->Sumw2();
    fHistYieldAwayLow3->Sumw2();
    fHistYieldAwayHigh3->Sumw2();

    Double_t error = fHistYieldAwayHigh3->GetBinError(5);
    fHistYieldAwayLow->Add(fHistYieldAwayHigh);
    fHistYieldAwayLow2->Add(fHistYieldAwayHigh2);
    fHistYieldAwayLow3->Add(fHistYieldAwayHigh3);
    fHistYieldAwayLow->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik pre h-h");
    fHistYieldAwayLow->GetYaxis()->SetRangeUser(0,0.35);
    fHistYieldAwayLow->SetXTitle("p_{T}^{trig} (GeV/c)");
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
    
    fHistYieldNearKLow->Sumw2();
    fHistYieldNearKHigh->Sumw2();
    fHistYieldNearKLow2->Sumw2();
    fHistYieldNearKHigh2->Sumw2();
    fHistYieldNearKLow3->Sumw2();
    fHistYieldNearKHigh3->Sumw2();
    
    Double_t errorK0Near = fHistYieldNearKLow2->GetBinError(1);
    fHistYieldNearKLow->Add(fHistYieldNearKHigh);
    fHistYieldNearKLow2->Add(fHistYieldNearKHigh2);
    fHistYieldNearKLow3->Add(fHistYieldNearKHigh3);
    fHistYieldNearKLow->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik pre K^{0}_{S}-h");
    fHistYieldNearKLow->GetYaxis()->SetRangeUser(0,0.35);
    fHistYieldNearKLow->SetXTitle("p_{T}^{trig} (GeV/c)");
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
    fHistYieldAwayKLow->GetYaxis()->SetRangeUser(0,0.35);
    fHistYieldAwayKLow->SetXTitle("p_{T}^{trig} (GeV/c)");
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
    fHistYieldAwayLamLow->SetXTitle("p_{T}^{trig} (GeV/c)");
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

    TCanvas *canIcp = new TCanvas;
    TPad * pad1 = new TPad("pad1","This is pad1",0.001,0.001,0.5,0.999);
    TPad * pad2 = new TPad("pad2","This is pad2",0.5,0.001,0.999,0.999);
    
    pad1->SetMargin(0.1,0.,0.1,0.05);
    pad2->SetMargin(0.,0.1,0.1,0.05);
    
    pad1->Draw();
    pad2->Draw();
    
   // canIcp->Divide(2,1);
   // canIcp->cd(1);
    pad1->cd();
    fHistYieldNearLow->Divide(fHistYieldNearLow3);
    fHistYieldNearLamLow->Divide(fHistYieldNearLamLow3);
    fHistYieldNearKLow->Divide(fHistYieldNearKLow3);
    fHistYieldNearLow->GetYaxis()->SetRangeUser(0,2.5);
    
    fHistYieldNearLamLow->SetMarkerStyle(21);
    fHistYieldNearLamLow->SetMarkerColor(kGreen);
    fHistYieldNearLamLow->SetMarkerSize(1.8);
    fHistYieldNearLamLow->SetLineColor(kGreen);
    
    fHistYieldNearLow->SetMarkerStyle(29);
    fHistYieldNearLow->SetMarkerColor(kRed);
    fHistYieldNearLow->SetMarkerSize(1.8);
    fHistYieldNearLow->SetLineColor(kRed);
    
    fHistYieldNearKLow->SetMarkerStyle(23);
    fHistYieldNearKLow->SetMarkerColor(kBlue);
    fHistYieldNearKLow->SetMarkerSize(1.8);
    fHistYieldNearKLow->SetLineColor(kBlue);
    
    fHistYieldNearLow->SetTitle("Prilahly pik");
    fHistYieldNearLow->SetYTitle("I_{CP}(0-10% / 50-100%)");
    fHistYieldNearLow->GetYaxis()->SetTitleOffset(1.2);
    fHistYieldNearLow->DrawCopy();
    fHistYieldNearLamLow->DrawCopy("same");
    fHistYieldNearKLow->DrawCopy("same");
  //  canIcp->cd(2);
    pad2->cd();
    fHistYieldAwayLow->Divide(fHistYieldAwayLow3);
    fHistYieldAwayLamLow->Divide(fHistYieldAwayLamLow3);
    fHistYieldAwayKLow->Divide(fHistYieldAwayKLow3);
    
    fHistYieldAwayLamLow->SetMarkerStyle(21);
    fHistYieldAwayLamLow->SetMarkerColor(kGreen);
    fHistYieldAwayLamLow->SetMarkerSize(1.8);
    fHistYieldAwayLamLow->SetLineColor(kGreen);

    fHistYieldAwayLow->SetMarkerStyle(29);
    fHistYieldAwayLow->SetMarkerColor(kRed);
    fHistYieldAwayLow->SetMarkerSize(1.8);
    fHistYieldAwayLow->SetLineColor(kRed);
    
    fHistYieldAwayKLow->SetMarkerStyle(23);
    fHistYieldAwayKLow->SetMarkerColor(kBlue);
    fHistYieldAwayKLow->SetMarkerSize(1.8);
    fHistYieldAwayKLow->SetLineColor(kBlue);
    
    fHistYieldAwayLow->GetYaxis()->SetRangeUser(0,2.5);
    fHistYieldAwayLow->SetTitle("Protilahly pik");
    fHistYieldAwayLow->SetYTitle("");
    
    TLegend *legIcp = new TLegend;
    legIcp->AddEntry(fHistYieldAwayLow,"h-h","pl");
    legIcp->AddEntry(fHistYieldAwayLamLow,"(#Lambda+#bar{#Lambda})-h","pl");
    legIcp->AddEntry(fHistYieldAwayKLow,"K^{0}_{S}-h","pl");
    fHistYieldAwayLow->DrawCopy();
    fHistYieldAwayLamLow->DrawCopy("same");
    fHistYieldAwayKLow->DrawCopy("same");
    legIcp->Draw();
    
    //------- vytazky v zav od multiplicity -------
    const Double_t multbins[4] = {0,10,50,100};
    Double_t ptBins[7]={4,5,6,7,9,11,15};
    Int_t color[6]={1,2,3,4,6,49};
    Int_t marker[6]={20,21,22,29,33,34};
    char leg [20];
    
    TH1D *fHistK0Near = new TH1D[6];
    TCanvas *cK0NearMulti = new TCanvas;
    
    for(Int_t j=0;j<6;j++){
        fHistK0Near[j].SetBins(3,multbins);
        
        fHistK0Near[j].SetBinContent(1,fHistYieldNearKLow->GetBinContent(j+1));
        fHistK0Near[j].SetBinError(1,fHistYieldNearKLow->GetBinError(j+1));
        
        fHistK0Near[j].SetBinContent(2,fHistYieldNearKLow2->GetBinContent(j+1));
        fHistK0Near[j].SetBinError(2,fHistYieldNearKLow2->GetBinError(j+1));
        
        fHistK0Near[j].SetBinContent(3,fHistYieldNearKLow3->GetBinContent(j+1));
        fHistK0Near[j].SetBinError(3,fHistYieldNearKLow3->GetBinError(j+1));
        
        fHistK0Near[j].SetLineColor(color[j]);
        fHistK0Near[j].SetMarkerColor(color[j]);
        fHistK0Near[j].SetMarkerStyle(marker[j]);
        fHistK0Near[j].SetMarkerSize(1.8);
        
        sprintf(leg,"%g < p_{T}^{trig} < %g GeV/c",ptBins[j],ptBins[j+1]);
        fHistK0Near[j].SetTitle(leg);
        if(j==0) {
            fHistK0Near[j].GetYaxis()->SetRangeUser(0,0.6);
            fHistK0Near[j].SetXTitle("Multiplicita (%)");
            fHistK0Near[j].SetYTitle("Y^{#Delta#phi}_{J}");
            fHistK0Near[j].DrawCopy();
        }
        else fHistK0Near[j].DrawCopy("same");
    }
    cK0NearMulti->BuildLegend();
    
    TH1D *fHistK0Away = new TH1D[6];
    TCanvas *cK0AwayMulti = new TCanvas;
    
    for(Int_t j=0;j<6;j++){
        fHistK0Away[j].SetBins(3,multbins);
        
        fHistK0Away[j].SetBinContent(1,fHistYieldAwayKLow->GetBinContent(j+1));
        fHistK0Away[j].SetBinError(1,fHistYieldAwayKLow->GetBinError(j+1));
        
        fHistK0Away[j].SetBinContent(2,fHistYieldAwayKLow2->GetBinContent(j+1));
        fHistK0Away[j].SetBinError(2,fHistYieldAwayKLow2->GetBinError(j+1));
        
        fHistK0Away[j].SetBinContent(3,fHistYieldAwayKLow3->GetBinContent(j+1));
        fHistK0Away[j].SetBinError(3,fHistYieldAwayKLow3->GetBinError(j+1));
        
        fHistK0Away[j].SetLineColor(color[j]);
        fHistK0Away[j].SetMarkerColor(color[j]);
        fHistK0Away[j].SetMarkerStyle(marker[j]);
        fHistK0Away[j].SetMarkerSize(1.8);
        
        sprintf(leg,"%g < p_{T}^{trig} < %g GeV/c",ptBins[j],ptBins[j+1]);
        fHistK0Away[j].SetTitle(leg);
        if(j==0) {
            fHistK0Away[j].GetYaxis()->SetRangeUser(0,0.4);
            fHistK0Away[j].SetXTitle("Multiplicita (%)");
            fHistK0Away[j].SetYTitle("Y^{#Delta#phi}_{J}");
            fHistK0Away[j].DrawCopy();
        }
        else fHistK0Away[j].DrawCopy("same");
    }
    cK0AwayMulti->BuildLegend();


    TH1D *fHistLamNear = new TH1D[6];
    TCanvas *cLamNearMulti = new TCanvas;
    
    for(Int_t j=0;j<6;j++){
        fHistLamNear[j].SetBins(3,multbins);
        
        fHistLamNear[j].SetBinContent(1,fHistYieldNearLamLow->GetBinContent(j+1));
        fHistLamNear[j].SetBinError(1,fHistYieldNearLamLow->GetBinError(j+1));
        
        fHistLamNear[j].SetBinContent(2,fHistYieldNearLamLow2->GetBinContent(j+1));
        fHistLamNear[j].SetBinError(2,fHistYieldNearLamLow2->GetBinError(j+1));
        
        fHistLamNear[j].SetBinContent(3,fHistYieldNearLamLow3->GetBinContent(j+1));
        fHistLamNear[j].SetBinError(3,fHistYieldNearLamLow3->GetBinError(j+1));
        
        fHistLamNear[j].SetLineColor(color[j]);
        fHistLamNear[j].SetMarkerColor(color[j]);
        fHistLamNear[j].SetMarkerStyle(marker[j]);
        fHistLamNear[j].SetMarkerSize(1.8);
        
        sprintf(leg,"%g < p_{T}^{trig} < %g GeV/c",ptBins[j],ptBins[j+1]);
        fHistLamNear[j].SetTitle(leg);
        if(j==0) {
            fHistLamNear[j].GetYaxis()->SetRangeUser(0,0.6);
            fHistLamNear[j].SetXTitle("Multiplicita (%)");
            fHistLamNear[j].SetYTitle("Y^{#Delta#phi}_{J}");
            fHistLamNear[j].DrawCopy();
        }
        else fHistLamNear[j].DrawCopy("same");
    }
    cLamNearMulti->BuildLegend();
    
    TH1D *fHistLambdaAway = new TH1D[6];
    TCanvas *cLamAwayMulti = new TCanvas;
    
    for(Int_t j=0;j<6;j++){
        fHistLambdaAway[j].SetBins(3,multbins);
        
        fHistLambdaAway[j].SetBinContent(1,fHistYieldAwayLamLow->GetBinContent(j+1));
        fHistLambdaAway[j].SetBinError(1,fHistYieldAwayLamLow->GetBinError(j+1));
        
        fHistLambdaAway[j].SetBinContent(2,fHistYieldAwayLamLow2->GetBinContent(j+1));
        fHistLambdaAway[j].SetBinError(2,fHistYieldAwayLamLow2->GetBinError(j+1));
        
        fHistLambdaAway[j].SetBinContent(3,fHistYieldAwayLamLow3->GetBinContent(j+1));
        fHistLambdaAway[j].SetBinError(3,fHistYieldAwayLamLow3->GetBinError(j+1));
        
        fHistLambdaAway[j].SetLineColor(color[j]);
        fHistLambdaAway[j].SetMarkerColor(color[j]);
        fHistLambdaAway[j].SetMarkerStyle(marker[j]);
        fHistLambdaAway[j].SetMarkerSize(1.8);
        
        sprintf(leg,"%g < p_{T}^{trig} < %g GeV/c",ptBins[j],ptBins[j+1]);
        fHistLambdaAway[j].SetTitle(leg);
        if(j==0) {
            fHistLambdaAway[j].GetYaxis()->SetRangeUser(0,0.6);
            fHistLambdaAway[j].SetXTitle("Multiplicita (%)");
            fHistLambdaAway[j].SetYTitle("Y^{#Delta#phi}_{J}");
            fHistLambdaAway[j].DrawCopy();
        }
        else fHistLambdaAway[j].DrawCopy("same");
    }
    cLamAwayMulti->BuildLegend();
    
    TH1D *fHisthhNear = new TH1D[6];
    TCanvas *chhNearMulti = new TCanvas;
    
    for(Int_t j=0;j<6;j++){
        fHisthhNear[j].SetBins(3,multbins);
        
        fHisthhNear[j].SetBinContent(1,fHistYieldNearLow->GetBinContent(j+1));
        fHisthhNear[j].SetBinError(1,fHistYieldNearLow->GetBinError(j+1));
        
        fHisthhNear[j].SetBinContent(2,fHistYieldNearLow2->GetBinContent(j+1));
        fHisthhNear[j].SetBinError(2,fHistYieldNearLow2->GetBinError(j+1));
        
        fHisthhNear[j].SetBinContent(3,fHistYieldNearLow3->GetBinContent(j+1));
        fHisthhNear[j].SetBinError(3,fHistYieldNearLow3->GetBinError(j+1));
        
        fHisthhNear[j].SetLineColor(color[j]);
        fHisthhNear[j].SetMarkerColor(color[j]);
        fHisthhNear[j].SetMarkerStyle(marker[j]);
        fHisthhNear[j].SetMarkerSize(1.8);
        
        sprintf(leg,"%g < p_{T}^{trig} < %g GeV/c",ptBins[j],ptBins[j+1]);
        fHisthhNear[j].SetTitle(leg);
        if(j==0) {
            fHisthhNear[j].GetYaxis()->SetRangeUser(0,0.6);
            fHisthhNear[j].SetXTitle("Multiplicita (%)");
            fHisthhNear[j].SetYTitle("Y^{#Delta#phi}_{J}");
            fHisthhNear[j].DrawCopy();
        }
        else fHisthhNear[j].DrawCopy("same");
    }
    chhNearMulti->BuildLegend();
    
    TH1D *fHisthhAway = new TH1D[6];
    TCanvas *chhAwayMulti = new TCanvas;
    
    for(Int_t j=0;j<6;j++){
        fHisthhAway[j].SetBins(3,multbins);
        
        fHisthhAway[j].SetBinContent(1,fHistYieldAwayLow->GetBinContent(j+1));
        fHisthhAway[j].SetBinError(1,fHistYieldAwayLow->GetBinError(j+1));
        
        fHisthhAway[j].SetBinContent(2,fHistYieldAwayLow2->GetBinContent(j+1));
        fHisthhAway[j].SetBinError(2,fHistYieldAwayLow2->GetBinError(j+1));
        
        fHisthhAway[j].SetBinContent(3,fHistYieldAwayLow3->GetBinContent(j+1));
        fHisthhAway[j].SetBinError(3,fHistYieldAwayLow3->GetBinError(j+1));
        
        fHisthhAway[j].SetLineColor(color[j]);
        fHisthhAway[j].SetMarkerColor(color[j]);
        fHisthhAway[j].SetMarkerStyle(marker[j]);
        fHisthhAway[j].SetMarkerSize(1.8);
        
        sprintf(leg,"%g < p_{T}^{trig} < %g GeV/c",ptBins[j],ptBins[j+1]);
        fHisthhAway[j].SetTitle(leg);
        if(j==0) {
            fHisthhAway[j].GetYaxis()->SetRangeUser(0,0.6);
            fHisthhAway[j].SetXTitle("Multiplicita (%)");
            fHisthhAway[j].SetYTitle("Y^{#Delta#phi}_{J}");
            fHisthhAway[j].DrawCopy();
        }
        else fHisthhAway[j].DrawCopy("same");
    }
    chhAwayMulti->BuildLegend();*/
    
    // ------ vytazky pre min bias -----------
    const Int_t nPtBins = 6;
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
    TH1D ** fHistProjPhiZYAM = new TH1D* [nTig*nPtBins];
    
    TH2D ** fHistProj2DMix = new TH2D* [nTig*nPtBins];
    TH1D ** fHistProjPhiMix = new TH1D* [nTig*nPtBins];
    TH1D ** fHistTriggMix = new TH1D* [nTig*nPtBins];
    
    char nameMix[20];
    char nameMixTrig[20];
    char nameprojphiMix[20];
    char nameMixNew[20];
    char nameMixTrigNew[20];
    
    Double_t yieldnear[nTig][nPtBins];
    Double_t yieldaway[nTig][nPtBins];
    Double_t yieldnearerror[nTig][nPtBins];
    Double_t yieldawayerror[nTig][nPtBins];
    
    Double_t yieldnearZYAM[nTig][nPtBins];
    Double_t yieldawayZYAM[nTig][nPtBins];
    Double_t yieldnearerrorZYAM[nTig][nPtBins];
    Double_t yieldawayerrorZYAM[nTig][nPtBins];
    
    Double_t yieldnearMix[nTig][nPtBins];
    Double_t yieldawayMix[nTig][nPtBins];
    Double_t yieldnearerrorMix[nTig][nPtBins];
    Double_t yieldawayerrorMix[nTig][nPtBins];
    Double_t poz;
    
    TCanvas *e = new TCanvas;
    e->Divide(nTig,nPtBins);
    TCanvas *canK = new TCanvas;
    canK->Divide(2,3);
    
    TFile *fFile = TFile::Open("Vytazky_minBias_data.root","RECREATE");
    
    TCanvas *canLam = new TCanvas;
    canLam->Divide(2,3);
    TCanvas *canH = new TCanvas;
    canH->Divide(2,3);
    for(Int_t i=0;i<3;i++){
        for(Int_t j=0;j<nPtBins;j++){
            sprintf(nameMix,"2dproj_0_%d_%d",i,j);
            sprintf(nameMixTrig,"1dtrigg_0_%d_%d",i,j);
            sprintf(nameMixNew,"2dproj_0_%d_%dMix",i,j);
            sprintf(nameMixTrigNew,"1dtrigg_0_%d_%dMix",i,j);
            if(i==0){
                fHistProj2DMix[i*nPtBins+j] = (TH2D*) fileK0Mix->Get(nameMix);
                fHistProj2DMix[i*nPtBins+j]->SetName(nameMixNew);
                fHistTriggMix[i*nPtBins+j] = (TH1D*) fileK0Mix->Get(nameMixTrig);
                 fHistTriggMix[i*nPtBins+j]->SetName(nameMixTrigNew);
                fHistProj2DMix[i*nPtBins+j]->Scale(1./fHistTriggMix[i*nPtBins+j]->GetBinContent(1));
            }
            if(i==1){
                fHistProj2DMix[i*nPtBins+j] = (TH2D*) fileLamMix->Get(nameMix);
                fHistProj2DMix[i*nPtBins+j]->SetName(nameMixNew);
                fHistTriggMix[i*nPtBins+j] = (TH1D*) fileLamMix->Get(nameMixTrig);
                fHistTriggMix[i*nPtBins+j]->SetName(nameMixTrigNew);
                fHistProj2DMix[i*nPtBins+j]->Scale(1./(fHistTriggMix[i*nPtBins+j]->GetBinContent(2)+fHistTriggMix[i*nPtBins+j]->GetBinContent(3)));
                
            }
            if(i==2){
                fHistProj2DMix[i*nPtBins+j] = (TH2D*) filehhMix->Get(nameMix);
                fHistProj2DMix[i*nPtBins+j]->SetName(nameMixNew);
                fHistTriggMix[i*nPtBins+j] = (TH1D*) filehhMix->Get(nameMixTrig);
                fHistTriggMix[i*nPtBins+j]->SetName(nameMixTrigNew);
                fHistProj2DMix[i*nPtBins+j]->Scale(1./fHistTriggMix[i*nPtBins+j]->GetBinContent(4));
                
            }
            for(Int_t iMult=0; iMult<3; iMult++ ){
                sprintf(nameMinBias,"2dproj_%d_%d_%d;1",iMult,i,j);
                sprintf(nameprojphi,"1dtrigg_%d_%d_%d;1",iMult,i,j);
                TH2D* tmp = 0x0;
                TH1D* tmpTrig = 0x0;
                if (iMult==0){
                    if(i==0){
                        if(j<3){
                            tmp = (TH2D*) gK ->Get(nameMinBias);
                            tmpTrig = (TH1D*) gK ->Get(nameprojphi);
                        } else {
                            tmp = (TH2D*) fK ->Get(nameMinBias);
                            tmpTrig = (TH1D*) fK ->Get(nameprojphi);
                        }
                    }
                    if(i==1){
                        if(j<3){
                            tmp = (TH2D*) gL ->Get(nameMinBias);
                            tmpTrig = (TH1D*) gL ->Get(nameprojphi);
                        } else {
                            tmp = (TH2D*) fL ->Get(nameMinBias);
                            tmpTrig = (TH1D*) fL ->Get(nameprojphi);
                        }
                    }
                    if(i==2){
                        if(j<3){
                            tmp = (TH2D*) g ->Get(nameMinBias);
                            tmpTrig = (TH1D*) g ->Get(nameprojphi);
                        } else {
                            tmp = (TH2D*) f ->Get(nameMinBias);
                            tmpTrig = (TH1D*) f ->Get(nameprojphi);
                        }
                    }
                }
                if (iMult==1){
                    if(i==0){
                        if(j<3){
                            tmp = (TH2D*) gK2 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) gK2 ->Get(nameprojphi);
                        } else {
                            tmp = (TH2D*) fK2 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) fK2 ->Get(nameprojphi);
                        }
                    }
                    if(i==1){
                        if(j<3){
                            tmp = (TH2D*) gL2 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) gL2 ->Get(nameprojphi);
                        } else{
                            tmp = (TH2D*) fL2 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) fL2 ->Get(nameprojphi);
                        }
                    }
                    if(i==2){
                        if(j<3) {
                            tmp = (TH2D*) g2 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) g2 ->Get(nameprojphi);
                        }else {
                            tmp = (TH2D*) f2 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) f2 ->Get(nameprojphi);
                        }
                    }
                }
                if (iMult==2){
                    if(i==0){
                        if(j<3){
                            tmp = (TH2D*) gK3 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) gK3 ->Get(nameprojphi);
                        } else {
                            tmp = (TH2D*) fK3 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) fK3 ->Get(nameprojphi);
                        }
                    }
                    if(i==1){
                        if(j<3){
                            tmp = (TH2D*) gL3 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) gL3 ->Get(nameprojphi);
                        } else {
                            tmp = (TH2D*) fL3 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) fL3 ->Get(nameprojphi);
                        }
                    }
                    if(i==2){
                        if(j<3){
                            tmp = (TH2D*) g3 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) g3 ->Get(nameprojphi);
                        } else {
                            tmp = (TH2D*) f3 ->Get(nameMinBias);
                            tmpTrig = (TH1D*) f3 ->Get(nameprojphi);
                        }
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
        
            if(i==0) Printf("i %d ,j %d, pary %g, trig %g\n", i, j, fHistProj2D[i*nPtBins+j]->Integral(), fHistTrigg[i*nPtBins+j]->GetBinContent(1));
            if(i==1) Printf("i %d ,j %d, pary %g, trig %g\n", i, j, fHistProj2D[i*nPtBins+j]->Integral(), fHistTrigg[i*nPtBins+j]->GetBinContent(2)+fHistTrigg[i*nPtBins+j]->GetBinContent(3));
            if(i==2) Printf("i %d ,j %d, pary %g, trig %g\n", i, j, fHistProj2D[i*nPtBins+j]->Integral(), fHistTrigg[i*nPtBins+j]->GetBinContent(4));
            
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
            fHistProjPhiZYAM[i*nPtBins+j] = (TH1D *) fHistProjPhi[i*nPtBins+j]->Clone();
            //fHistProjPhiZYAM[i*nPtBins+j]->Write();
            e->cd(i*nPtBins+j+1);
            fHistProjPhi[i*nPtBins+j]->DrawCopy();
            
            Double_t val1 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) );
            Double_t val2 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) +1);
            Double_t val3 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) -1);
            Double_t val4 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1));
            Double_t val5 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1)+1);
            Double_t val6 = fHistProjPhi[i*nPtBins+j] -> GetBinContent((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1)-1);
            
            Double_t error1 = fHistProjPhi[i*nPtBins+j] -> GetBinError((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) );
            Double_t error2 = fHistProjPhi[i*nPtBins+j] -> GetBinError((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) +1);
            Double_t error3 = fHistProjPhi[i*nPtBins+j] -> GetBinError((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(1) -1);
            Double_t error4 = fHistProjPhi[i*nPtBins+j] -> GetBinError((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1));
            Double_t error5 = fHistProjPhi[i*nPtBins+j] -> GetBinError((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1)+1);
            Double_t error6 = fHistProjPhi[i*nPtBins+j] -> GetBinError((fHistProjPhi[i*nPtBins+j]->GetXaxis())->FindBin(-1)-1);
            
            
            poz = (val1+val2+val3+val4+val5+val6)/6;
            Double_t errorPoz = TMath::Sqrt(error1*error1+error2*error2+error3*error3+error4*error4+error5*error5+error6*error6)/6;
            Int_t nBinsPhi = fHistProjPhi[i*nPtBins+j] ->GetNbinsX();
            //cout << poz<< endl;
            
            TH1D *fHistpoz = new TH1D("fHistpoz","fHistpoz",nBinsPhi,-kPi/2, -kPi/2+2*kPi );
            fHistpoz->Sumw2();
            for(Int_t l = 0; l<nBinsPhi; l++){
                fHistpoz->SetBinContent(l+1,poz);
                fHistpoz->SetBinError(l+1,errorPoz);
            }
            
            //TF1 *fFuncBack = new TF1("fFuncBack"," [0]",-kPi/2, -kPi/2+2*kPi);
            //fFuncBack->SetParameter(0,poz);
            fHistProjPhi[i*nPtBins+j]->Add(fHistpoz,-1);
            
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
                integralnear+= fHistProjPhi[i*nPtBins+j]->GetBinContent(k);
                errornear+= TMath::Power(fHistProjPhi[i*nPtBins+j]->GetBinError(k),2);
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
            delete fHistpoz;
            
            
            Double_t minPhi = fHistProjPhiZYAM[i*nPtBins+j]->GetMinimum();
            Double_t minPhiErr = fHistProjPhiZYAM[i*nPtBins+j]->GetBinError(fHistProjPhiZYAM[i*nPtBins+j]->GetMinimumBin());
            Int_t nBinsPhiZYAM = fHistProjPhiZYAM[i*nPtBins+j] ->GetNbinsX();
            
            TH1D *fHistpozZYAM = new TH1D ("fHistpozZYAM","fHistpozZYAM",nBinsPhi,-kPi/2, -kPi/2+2*kPi );
            fHistpozZYAM->Sumw2();
            for(Int_t l = 0; l<nBinsPhiZYAM; l++){
                fHistpozZYAM->SetBinContent(l+1,minPhi);
                fHistpozZYAM->SetBinError(l+1,minPhiErr);
            }
            
            //TF1 *fFuncBackZYAM = new TF1("fFuncBackZYAM"," [0]",-kPi/2, -kPi/2+2*kPi);
            //fFuncBackZYAM->SetParameter(0,minPhi);
            fHistProjPhiZYAM[i*nPtBins+j]->Add(fHistpozZYAM,-1);
            
            Double_t integralnearZYAM =0.;
            Double_t errornearZYAM =0.;
            Double_t integralawayZYAM =0.;
            Double_t errorawayZYAM =0.;
            
           for(Int_t k=minnear; k<maxnear; k++){
                integralnearZYAM+= fHistProjPhiZYAM[i*nPtBins+j]->GetBinContent(k);
                errornearZYAM+= TMath::Power(fHistProjPhiZYAM[i*nPtBins+j]->GetBinError(k),2);
            }
            
            yieldnearerrorZYAM[i][j] = TMath::Sqrt(errornearZYAM);
            yieldnearerrorZYAM[i][j] = yieldnearerrorZYAM[i][j] *widthnear;
            yieldnearZYAM[i][j] = integralnearZYAM*widthnear;
            
            for(Int_t k=minaway; k<maxaway; k++){
                integralawayZYAM+= fHistProjPhiZYAM[i*nPtBins+j]->GetBinContent(k);
                errorawayZYAM+= TMath::Power(fHistProjPhiZYAM[i*nPtBins+j]->GetBinError(k),2);
            }
            
            yieldawayerrorZYAM[i][j] = TMath::Sqrt(errorawayZYAM);
            yieldawayerrorZYAM[i][j] = yieldawayerrorZYAM[i][j] *widthaway;
            yieldawayZYAM[i][j] = integralawayZYAM*widthaway;
            
            fHistProj2DMix[i*nPtBins+j]->SetAxisRange(-1,1,"x");
            fHistProjPhiMix[i*nPtBins+j]=(TH1D *)fHistProj2DMix[i*nPtBins+j]->ProjectionY();
            sprintf(nameprojphiMix,"projPhiMix_%d_%d",i+1,j+1);
            fHistProjPhiMix[i*nPtBins+j]->SetName(nameprojphiMix);
            
            Double_t valMix1 = fHistProjPhiMix[i*nPtBins+j] -> GetBinContent((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(1) );
            Double_t valMix2 = fHistProjPhiMix[i*nPtBins+j] -> GetBinContent((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(1) +1);
            Double_t valMix3 = fHistProjPhiMix[i*nPtBins+j] -> GetBinContent((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(1) -1);
            Double_t valMix4 = fHistProjPhiMix[i*nPtBins+j] -> GetBinContent((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(-1));
            Double_t valMix5 = fHistProjPhiMix[i*nPtBins+j] -> GetBinContent((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(-1)+1);
            Double_t valMix6 = fHistProjPhiMix[i*nPtBins+j] -> GetBinContent((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(-1)-1);
            
            Double_t errMix1 = fHistProjPhiMix[i*nPtBins+j] -> GetBinError((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(1) );
            Double_t errMix2 = fHistProjPhiMix[i*nPtBins+j] -> GetBinError((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(1) +1);
            Double_t errMix3 = fHistProjPhiMix[i*nPtBins+j] -> GetBinError((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(1) -1);
            Double_t errMix4 = fHistProjPhiMix[i*nPtBins+j] -> GetBinError((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(-1));
            Double_t errMix5 = fHistProjPhiMix[i*nPtBins+j] -> GetBinError((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(-1)+1);
            Double_t errMix6 = fHistProjPhiMix[i*nPtBins+j] -> GetBinError((fHistProjPhiMix[i*nPtBins+j]->GetXaxis())->FindBin(-1)-1);
            
            Double_t pozMix = (valMix1+valMix2+valMix3+valMix4+valMix5+valMix6)/6;
            Double_t errorPozMix = TMath::Sqrt(errMix1*errMix1+errMix2*errMix2+errMix3*errMix3+errMix4*errMix4+errMix5*errMix5+errMix6*errMix6)/6;
            
          //  TF1 *fFuncBackMix = new TF1("fFuncBackMix"," [0]",-kPi/2, -kPi/2+2*kPi);
            //fFuncBackMix->SetParameter(0,pozMix);
            Int_t nBinsPhiMix = fHistProjPhiZYAM[i*nPtBins+j] ->GetNbinsX();
            
            TH1D *fHistpozMix = new TH1D("fHistpozMix","fHistpozMix",nBinsPhi,-kPi/2, -kPi/2+2*kPi );
            fHistpozMix->Sumw2();
            for(Int_t l = 0; l<nBinsPhiMix; l++){
                fHistpozMix->SetBinContent(l+1,minPhi);
                fHistpozMix->SetBinError(l+1,minPhiErr);
            }
            
            fHistProjPhiMix[i*nPtBins+j]->Add(fHistpozMix,-1);
            //fHistProjPhiMix[i*nPtBins+j]->Write();
            
            Double_t integralnearMix =0.;
            Double_t errornearMix =0.;
            
            for(Int_t k=minnear; k<maxnear; k++){
                integralnearMix+= fHistProjPhiMix[i*nPtBins+j]->GetBinContent(k);
                errornearMix+= TMath::Power(fHistProjPhiMix[i*nPtBins+j]->GetBinError(k),2);
            }
            
            yieldnearerrorMix[i][j] = TMath::Sqrt(errornearMix);
            yieldnearerrorMix[i][j] = yieldnearerrorMix[i][j] *widthnear;
            yieldnearMix[i][j] = integralnearMix*widthnear;
            
            Double_t integralawayMix =0.;
            Double_t erroralawayMix =0.;
            
            for(Int_t k=minaway; k<maxaway; k++){
                integralawayMix+= fHistProjPhiMix[i*nPtBins+j]->GetBinContent(k);
                erroralawayMix+= TMath::Power(fHistProjPhiMix[i*nPtBins+j]->GetBinError(k),2);
            }
            
            yieldawayerrorMix[i][j] = TMath::Sqrt(erroralawayMix);
            yieldawayerrorMix[i][j] = yieldawayerrorMix[i][j] *widthaway;
            yieldawayMix[i][j] = integralawayMix*widthaway;
            
            delete fHistpozZYAM;
            delete fHistpozMix;
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
    
    TH1D *fHistK0NearSyst = new TH1D("fHistK0NearSyst","fHistK0NearSyst",nPtBins,PtHist);
    TH1D *fHistLambdaNearSyst = new TH1D("fHistLambdaNearSyst","fHistLambdaNearSyst",nPtBins,PtHist);
    TH1D *fHistHadronNearSyst = new TH1D("fHistHadronNearSyst","fHistHadronNearSyst",nPtBins,PtHist);
    
    TH1D *fHistK0AwaySyst = new TH1D("fHistK0AwaySyst","fHistK0AwaySyst",nPtBins,PtHist);
    TH1D *fHistLambdaAwaySyst = new TH1D("fHistLambdaAwaySyst","fHistLambdaAwaySyst",nPtBins,PtHist);
    TH1D *fHistHadronAwaySyst = new TH1D("fHistHadronAwaySyst","fHistHadronAwaySyst",nPtBins,PtHist);
    
    TH1D *fHistK0NearMixSyst = new TH1D("fHistK0NearMixSyst","fHistK0NearMixSyst",nPtBins,PtHist);
    TH1D *fHistK0AwayMixSyst = new TH1D("fHistK0AwayMixSyst","fHistK0AwayMixSyst",nPtBins,PtHist);
    
    TH1D *fHistLamNearMixSyst = new TH1D("fHistLamNearMixSyst","fHistLamNearMixSyst",nPtBins,PtHist);
    TH1D *fHistLamAwayMixSyst = new TH1D("fHistLamAwayMixSyst","fHistLamAwayMixSyst",nPtBins,PtHist);
    
    TH1D *fHistHadronNearMixSyst = new TH1D("fHistHadronNearMixSyst","fHistHadronNearMixSyst",nPtBins,PtHist);
    TH1D *fHistHadronAwayMixSyst = new TH1D("fHistHadronAwayMixSyst","fHistHadronAwayMixSyst",nPtBins,PtHist);
    
    TH1D *fHistK0NearMix = new TH1D("fHistK0NearMix","fHistK0NearMix",nPtBins,PtHist);
    TH1D *fHistK0AwayMix = new TH1D("fHistK0AwayMix","fHistK0AwayMix",nPtBins,PtHist);
    
    TH1D *fHistLamNearMix = new TH1D("fHistLamNearMix","fHistLamNearMix",nPtBins,PtHist);
    TH1D *fHistLamAwayMix = new TH1D("fHistLamAwayMix","fHistLamAwayMix",nPtBins,PtHist);
    TH1D *fHistHadronNearMix = new TH1D("fHistHadronNearMix","fHistHadronNearMix",nPtBins,PtHist);
    TH1D *fHistHadronAwayMix = new TH1D("fHistHadronAwayMix","fHistHadronAwayMix",nPtBins,PtHist);
    
    TH1D *fHistK0NearZYAM = new TH1D("fHistK0NearZYAM","fHistK0NearZYAM",nPtBins,PtHist);
    TH1D *fHistK0AwayZYAM = new TH1D("fHistK0AwayZYAM","fHistK0AwayZYAM",nPtBins,PtHist);
    
    TH1D *fHistLamNearZYAM = new TH1D("fHistLamNearZYAM","fHistLamNearZYAM",nPtBins,PtHist);
    TH1D *fHistLamAwayZYAM = new TH1D("fHistLamAwayZYAM","fHistLamAwayZYAM",nPtBins,PtHist);
    
    TH1D *fHistHadronNearZYAM = new TH1D("fHistHadronNearZYAM","fHistHadronNearZYAM",nPtBins,PtHist);
    TH1D *fHistHadronAwayZYAM = new TH1D("fHistHadronAwayZYAM","fHistHadronAwayZYAM",nPtBins,PtHist);
    
    TH1D *fHistK0NearMixBarlow = new TH1D("fHistK0NearMixBarlow","fHistK0NearMixBarlow",nPtBins,PtHist);
    TH1D *fHistK0AwayMixBarlow = new TH1D("fHistK0AwayMixBarlow","fHistK0AwayMixBarlow",nPtBins,PtHist);
    
    TH1D *fHistLamNearMixBarlow = new TH1D("fHistLamNearMixBarlow","fHistLamNearMixBarlow",nPtBins,PtHist);
    TH1D *fHistLamAwayMixBarlow = new TH1D("fHistLamAwayMixBarlow","fHistLamAwayMixBarlow",nPtBins,PtHist);
    TH1D *fHistHadronNearMixBarlow = new TH1D("fHistHadronNearMixBarlow","fHistHadronNearMixBarlow",nPtBins,PtHist);
    TH1D *fHistHadronAwayMixBarlow = new TH1D("fHistHadronAwayMixBarlow","fHistHadronAwayMixBarlow",nPtBins,PtHist);
    
    TH1D *fHistK0NearZYAMBarlow = new TH1D("fHistK0NearZYAM","fHistK0NearZYAMBarlow",nPtBins,PtHist);
    TH1D *fHistK0AwayZYAMBarlow = new TH1D("fHistK0AwayZYAM","fHistK0AwayZYAMBarlow",nPtBins,PtHist);
    
    TH1D *fHistLamNearZYAMBarlow = new TH1D("fHistLamNearZYAMBarlow","fHistLamNearZYAMBarlow",nPtBins,PtHist);
    TH1D *fHistLamAwayZYAMBarlow = new TH1D("fHistLamAwayZYAMBarlow","fHistLamAwayZYAMBarlow",nPtBins,PtHist);
    
    TH1D *fHistHadronNearZYAMBarlow = new TH1D("fHistHadronNearZYAMBarlow","fHistHadronNearZYAMBarlow",nPtBins,PtHist);
    TH1D *fHistHadronAwayZYAMBarlow = new TH1D("fHistHadronAwayZYAMBarlow","fHistHadronAwayZYAMBarlow",nPtBins,PtHist);
    
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
         
         fHistK0NearSyst->Fill(PtGraph[i], TMath::Abs(yieldnearZYAM[0][i]-yieldnear[0][i])/yieldnear[0][i]);
         fHistK0NearSyst->SetBinError(i+1,0);
         
         fHistLambdaNearSyst->Fill(PtGraph[i], TMath::Abs(yieldnearZYAM[1][i]-yieldnear[1][i])/yieldnear[1][i]);
         fHistLambdaNearSyst->SetBinError(i+1,0);
         
         fHistHadronNearSyst->Fill(PtGraph[i], TMath::Abs(yieldnearZYAM[2][i]-yieldnear[2][i])/yieldnear[2][i]);
         fHistHadronNearSyst->SetBinError(i+1,0);
         
         fHistK0AwaySyst->Fill(PtGraph[i], TMath::Abs(yieldawayZYAM[0][i]-yieldaway[0][i])/yieldaway[0][i]);
         fHistK0AwaySyst->SetBinError(i+1,0);
         
         fHistLambdaAwaySyst->Fill(PtGraph[i], TMath::Abs(yieldawayZYAM[1][i]-yieldaway[1][i])/yieldaway[1][i]);
         fHistLambdaAwaySyst->SetBinError(i+1,0);
         
         fHistHadronAwaySyst->Fill(PtGraph[i], TMath::Abs(yieldawayZYAM[2][i]-yieldaway[2][i])/yieldaway[2][i]);
         fHistHadronAwaySyst->SetBinError(i+1, 0);
     
         fHistK0NearMixSyst->Fill(PtGraph[i], TMath::Abs(yieldnearMix[0][i]-yieldnear[0][i])/yieldnear[0][i]);
         fHistK0NearMixSyst->SetBinError(i+1,0);
         
         fHistK0AwayMixSyst->Fill(PtGraph[i], TMath::Abs(yieldawayMix[0][i]-yieldaway[0][i])/yieldaway[0][i]);
         fHistK0AwayMixSyst->SetBinError(i+1,0);
         
         fHistLamNearMixSyst->Fill(PtGraph[i], TMath::Abs(yieldnearMix[1][i]-yieldnear[1][i])/yieldnear[1][i]);
         fHistLamNearMixSyst->SetBinError(i+1,0);
         
         fHistLamAwayMixSyst->Fill(PtGraph[i], TMath::Abs(yieldawayMix[1][i]-yieldaway[1][i])/yieldaway[1][i]);
         fHistLamAwayMixSyst->SetBinError(i+1,0);
         
         fHistHadronNearMixSyst->Fill(PtGraph[i], TMath::Abs(yieldnearMix[2][i]-yieldnear[2][i])/yieldnear[2][i]);
         fHistHadronNearMixSyst->SetBinError(i+1,0);
         
         fHistHadronAwayMixSyst->Fill(PtGraph[i], TMath::Abs(yieldawayMix[2][i]-yieldaway[2][i])/yieldaway[2][i]);
         fHistHadronAwayMixSyst->SetBinError(i+1,0);
         
         fHistK0NearMixBarlow->Fill(PtGraph[i],TMath::Abs(yieldnearMix[0][i]-yieldnear[0][i])/TMath::Sqrt(TMath::Abs(yieldnearerrorMix[0][i]*yieldnearerrorMix[0][i]-yieldnearerror[0][i]*yieldnearerror[0][i])));
         fHistK0NearMixBarlow->SetBinError(i+1,0);
         fHistK0AwayMixBarlow->Fill(PtGraph[i],TMath::Abs(yieldawayMix[0][i]-yieldaway[0][i])/TMath::Sqrt(TMath::Abs(yieldawayerrorMix[0][i]*yieldawayerrorMix[0][i]-yieldawayerror[0][i]*yieldawayerror[0][i])));
         fHistK0AwayMixBarlow->SetBinError(i+1,0);
         
         fHistLamNearMixBarlow->Fill(PtGraph[i],TMath::Abs(yieldnearMix[1][i]-yieldnear[1][i])/TMath::Sqrt(TMath::Abs(yieldnearerrorMix[1][i]*yieldnearerrorMix[1][i]-yieldnearerror[1][i]*yieldnearerror[1][i])));
         fHistLamNearMixBarlow->SetBinError(i+1,0);
         fHistLamAwayMixBarlow->Fill(PtGraph[i],TMath::Abs(yieldawayMix[1][i]-yieldaway[1][i])/TMath::Sqrt(TMath::Abs(yieldawayerrorMix[1][i]*yieldawayerrorMix[1][i]-yieldawayerror[1][i]*yieldawayerror[1][i])));
         fHistLamAwayMixBarlow->SetBinError(i+1,0);
         
         fHistHadronNearMixBarlow->Fill(PtGraph[i],TMath::Abs(yieldnearMix[2][i]-yieldnear[2][i])/TMath::Sqrt(TMath::Abs(yieldnearerrorMix[2][i]*yieldnearerrorMix[2][i]-yieldnearerror[2][i]*yieldnearerror[2][i])));
         fHistHadronNearMixBarlow->SetBinError(i+1,0);
         fHistHadronAwayMixBarlow->Fill(PtGraph[i],TMath::Abs(yieldawayMix[2][i]-yieldaway[2][i])/TMath::Sqrt(TMath::Abs(yieldawayerrorMix[2][i]*yieldawayerrorMix[2][i]-yieldawayerror[2][i]*yieldawayerror[2][i])));
         fHistHadronAwayMixBarlow->SetBinError(i+1,0);
         
         fHistK0NearZYAMBarlow->Fill(PtGraph[i],TMath::Abs(yieldnearZYAM[0][i]-yieldnear[0][i])/TMath::Sqrt(TMath::Abs(yieldnearerrorZYAM[0][i]*yieldnearerrorZYAM[0][i]-yieldnearerror[0][i]*yieldnearerror[0][i])));
         fHistK0NearZYAMBarlow->SetBinError(i+1,0);
         fHistK0AwayZYAMBarlow->Fill(PtGraph[i],TMath::Abs(yieldawayZYAM[0][i]-yieldaway[0][i])/TMath::Sqrt(TMath::Abs(yieldawayerrorZYAM[0][i]*yieldawayerrorZYAM[0][i]-yieldawayerror[0][i]*yieldawayerror[0][i])));
         fHistK0AwayZYAMBarlow->SetBinError(i+1,0);
         
         fHistLamNearZYAMBarlow->Fill(PtGraph[i],TMath::Abs(yieldnearZYAM[1][i]-yieldnear[1][i])/TMath::Sqrt(TMath::Abs(yieldnearerrorZYAM[1][i]*yieldnearerrorZYAM[1][i]-yieldnearerror[1][i]*yieldnearerror[1][i])));
         fHistLamNearZYAMBarlow->SetBinError(i+1,0);
         fHistLamAwayZYAMBarlow->Fill(PtGraph[i],TMath::Abs(yieldawayZYAM[1][i]-yieldaway[1][i])/TMath::Sqrt(TMath::Abs(yieldawayerrorZYAM[1][i]*yieldawayerrorZYAM[1][i]-yieldawayerror[1][i]*yieldawayerror[1][i])));
         fHistLamAwayZYAMBarlow->SetBinError(i+1,0);
         
         fHistHadronNearZYAMBarlow->Fill(PtGraph[i],TMath::Abs(yieldnearZYAM[2][i]-yieldnear[2][i])/TMath::Sqrt(TMath::Abs(yieldnearerrorZYAM[2][i]*yieldnearerrorZYAM[2][i]-yieldnearerror[2][i]*yieldnearerror[2][i])));
         fHistHadronNearZYAMBarlow->SetBinError(i+1,0);
         fHistHadronAwayZYAMBarlow->Fill(PtGraph[i],TMath::Abs(yieldawayZYAM[2][i]-yieldaway[2][i])/TMath::Sqrt(TMath::Abs(yieldawayerrorZYAM[2][i]*yieldawayerrorZYAM[2][i]-yieldawayerror[2][i]*yieldawayerror[2][i])));
         fHistHadronAwayZYAMBarlow->SetBinError(i+1,0);
         
        // Printf("%g %g%g %g \n",yieldnearerrorZYAM[0][i]*yieldnearerrorZYAM[0][i], yieldnearerror[0][i]*yieldnearerror[0][i],yieldawayerrorZYAM[0][i]*yieldawayerrorZYAM[0][i], yieldawayerror[0][i]*yieldawayerror[0][i] );
         
         fHistK0NearMix->Fill(PtGraph[i], yieldnearMix[0][i]);
         fHistK0NearMix->SetBinError(i+1,yieldnearerrorMix[0][i]);
         
         fHistK0AwayMix->Fill(PtGraph[i], yieldawayMix[0][i]);
         fHistK0AwayMix->SetBinError(i+1,yieldawayerrorMix[0][i]);
         
         fHistLamNearMix->Fill(PtGraph[i], yieldnearMix[1][i]);
         fHistLamNearMix->SetBinError(i+1,yieldnearerrorMix[1][i]);
         
         fHistLamAwayMix->Fill(PtGraph[i], yieldawayMix[1][i]);
         fHistLamAwayMix->SetBinError(i+1,yieldawayerrorMix[1][i]);
         
         fHistHadronNearMix->Fill(PtGraph[i], yieldnearMix[2][i]);
         fHistHadronNearMix->SetBinError(i+1,yieldnearerrorMix[2][i]);
         
         fHistHadronAwayMix->Fill(PtGraph[i], yieldawayMix[2][i]);
         fHistHadronAwayMix->SetBinError(i+1,yieldawayerrorMix[2][i]);
         
         fHistK0NearZYAM->Fill(PtGraph[i], yieldnearZYAM[0][i]);
         fHistK0NearZYAM->SetBinError(i+1,yieldnearerrorZYAM[0][i]);
         
         fHistK0AwayZYAM->Fill(PtGraph[i], yieldawayZYAM[0][i]);
         fHistK0AwayZYAM->SetBinError(i+1,yieldawayerrorZYAM[0][i]);
         
         fHistLamNearZYAM->Fill(PtGraph[i], yieldnearZYAM[1][i]);
         fHistLamNearZYAM->SetBinError(i+1,yieldnearerrorZYAM[1][i]);
         
         fHistLamAwayZYAM->Fill(PtGraph[i], yieldawayZYAM[1][i]);
         fHistLamAwayZYAM->SetBinError(i+1,yieldawayerrorZYAM[1][i]);
         
         fHistHadronNearZYAM->Fill(PtGraph[i], yieldnearZYAM[2][i]);
         fHistHadronNearZYAM->SetBinError(i+1,yieldnearerrorZYAM[2][i]);
         
         fHistHadronAwayZYAM->Fill(PtGraph[i], yieldawayZYAM[2][i]);
         fHistHadronAwayZYAM->SetBinError(i+1,yieldawayerrorZYAM[2][i]);
         
     }
     
     fHistK0Near->SetMarkerStyle(23);
     fHistK0Near->SetMarkerColor(kBlue);
     fHistK0Near->SetMarkerSize(1.8);
     fHistK0Near->SetLineColor(kBlue);
    fHistK0Near->GetYaxis()->SetRangeUser(0,0.4);
    fHistK0Near->SetTitle("Zavislost vytazkov od p_{T} pre prilahly pik, min bias");
     fHistK0Near->GetXaxis()->SetTitle("p_{T} (GeV/c)");
     fHistK0Near->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
     
     fHistLambdaNear->SetMarkerStyle(21);
     fHistLambdaNear->SetMarkerColor(kGreen);
     fHistLambdaNear->SetMarkerSize(1.8);
     fHistLambdaNear->SetLineColor(kGreen);
     
     fHistHadronNear->SetMarkerStyle(29);
     fHistHadronNear->SetMarkerColor(kRed);
     fHistHadronNear->SetMarkerSize(1.8);
     fHistHadronNear->SetLineColor(kRed);
    
    fHistK0NearMix->SetMarkerStyle(32);
    fHistK0NearMix->SetMarkerColor(kBlue);
    fHistK0NearMix->SetMarkerSize(1.8);
    fHistK0NearMix->SetLineColor(kBlue);
    
    fHistLamNearMix->SetMarkerStyle(25);
    fHistLamNearMix->SetMarkerColor(kGreen);
    fHistLamNearMix->SetMarkerSize(1.8);
    fHistLamNearMix->SetLineColor(kGreen);
    
    fHistHadronNearMix->SetMarkerStyle(30);
    fHistHadronNearMix->SetMarkerColor(kRed);
    fHistHadronNearMix->SetMarkerSize(1.8);
    fHistHadronNearMix->SetLineColor(kRed);
    
    fHistK0NearZYAM->SetMarkerStyle(35);
    fHistK0NearZYAM->SetMarkerColor(kBlue);
    fHistK0NearZYAM->SetMarkerSize(1.8);
    fHistK0NearZYAM->SetLineColor(kBlue);
    
    fHistLamNearZYAM->SetMarkerStyle(27);
    fHistLamNearZYAM->SetMarkerColor(kGreen);
    fHistLamNearZYAM->SetMarkerSize(1.8);
    fHistLamNearZYAM->SetLineColor(kGreen);
    
    fHistHadronNearZYAM->SetMarkerStyle(46);
    fHistHadronNearZYAM->SetMarkerColor(kRed);
    fHistHadronNearZYAM->SetMarkerSize(1.8);
    fHistHadronNearZYAM->SetLineColor(kRed);
    
   /*  TLegend *fLegendNear = new TLegend(0.2,0.9,0.75,0.8);
     fLegendNear->AddEntry(fHistK0Near,"Triger K^{0}_{S}","pl");
     fLegendNear->AddEntry(fHistLambdaNear,"Triger #Lambda a #bar{#Lambda}","pl");
     fLegendNear->AddEntry(fHistHadronNear,"Triger nabity hadron","pl");*/
    
  /*  fLegendNear->AddEntry(fHistK0NearMix,"Triger K^{0}_{S} , mixing-average","pl");
     fLegendNear->AddEntry(fHistLamNearMix,"Triger #Lambda a #bar{#Lambda}, mixing-average","pl");
    fLegendNear->AddEntry(fHistHadronNearMix,"Triger h, mixing-average","pl");
    fLegendNear->AddEntry(fHistK0NearZYAM,"Triger K^{0}_{S} , pozadie","pl");
    fLegendNear->AddEntry(fHistLamNearZYAM,"Triger #Lambda a #bar{#Lambda}, pozadie","pl");
    fLegendNear->AddEntry(fHistHadronNearZYAM,"Triger h, pozadie","pl");*/
    
     TCanvas * cannear = new TCanvas();
     fHistK0Near->DrawCopy();
     fHistLambdaNear->DrawCopy("same");
     fHistHadronNear->DrawCopy("same");
    fHistK0NearMix->DrawCopy("same");
    fHistLamNearMix->DrawCopy("same");
    fHistK0NearZYAM->DrawCopy("same");
    fHistLamNearZYAM->DrawCopy("Same");
    fHistHadronNearMix->DrawCopy("same");
    fHistHadronNearZYAM->DrawCopy("same");
    // fLegendNear->Draw();
  cannear  ->BuildLegend();
     
     fHistK0Away->SetMarkerStyle(23);
     fHistK0Away->SetMarkerColor(kBlue);
     fHistK0Away->SetMarkerSize(1.8);
     fHistK0Away->SetLineColor(kBlue);
    fHistK0Away->GetYaxis()->SetRangeUser(0,0.4);
     fHistK0Away->SetTitle("Zavislost vytazkov od p_{T} pre protilahly pik, min. bias");
     fHistK0Away->GetXaxis()->SetTitle("p_{T} (GeV/c)");
     fHistK0Away->GetYaxis()->SetTitle("Y_{J}^{#Delta#phi}");
     
     fHistLambdaAway->SetMarkerStyle(21);
     fHistLambdaAway->SetMarkerColor(kGreen);
     fHistLambdaAway->SetMarkerSize(1.8);
     fHistLambdaAway->SetLineColor(kGreen);
     
     fHistHadronAway->SetMarkerStyle(29);
     fHistHadronAway->SetMarkerColor(kRed);
     fHistHadronAway->SetMarkerSize(1.8);
     fHistHadronAway->SetLineColor(kRed);
    
    fHistK0AwayMix->SetMarkerStyle(32);
    fHistK0AwayMix->SetMarkerColor(kBlue);
    fHistK0AwayMix->SetMarkerSize(1.8);
    fHistK0AwayMix->SetLineColor(kBlue);
    
    fHistLamAwayMix->SetMarkerStyle(25);
    fHistLamAwayMix->SetMarkerColor(kGreen);
    fHistLamAwayMix->SetMarkerSize(1.8);
    fHistLamAwayMix->SetLineColor(kGreen);
    
    fHistHadronAwayMix->SetMarkerStyle(30);
    fHistHadronAwayMix->SetMarkerColor(kRed);
    fHistHadronAwayMix->SetMarkerSize(1.8);
    fHistHadronAwayMix->SetLineColor(kRed);
    
    fHistK0AwayZYAM->SetMarkerStyle(35);
    fHistK0AwayZYAM->SetMarkerColor(kBlue);
    fHistK0AwayZYAM->SetMarkerSize(1.8);
    fHistK0AwayZYAM->SetLineColor(kBlue);
    
    fHistLamAwayZYAM->SetMarkerStyle(27);
    fHistLamAwayZYAM->SetMarkerColor(kGreen);
    fHistLamAwayZYAM->SetMarkerSize(1.8);
    fHistLamAwayZYAM->SetLineColor(kGreen);
    
    fHistHadronAwayZYAM->SetMarkerStyle(46);
    fHistHadronAwayZYAM->SetMarkerColor(kRed);
    fHistHadronAwayZYAM->SetMarkerSize(1.8);
    fHistHadronAwayZYAM->SetLineColor(kRed);
     
   /*  TLegend *fLegendAway = new TLegend(0.2,0.9,0.75,0.8);
     fLegendAway->AddEntry(fHistK0Away,"Triger K^{0}_{S}","pl");
     fLegendAway->AddEntry(fHistLambdaAway,"Triger #Lambda a #bar{#Lambda}","pl");
     fLegendAway->AddEntry(fHistHadronAway,"Triger nabity hadron","pl");*/
    
  /*  fLegendAway->AddEntry(fHistK0AwayMix,"Triger K^{0}_{S} , mixing-average","pl");
    fLegendAway->AddEntry(fHistLamAwayMix,"Triger #Lambda a #bar{#Lambda}, mixing-average","pl");
    fLegendAway->AddEntry(fHistHadronAwayMix,"Triger h, mixing-average","pl");
   fLegendAway->AddEntry(fHistK0AwayZYAM,"Triger K^{0}_{S} , pozadie","pl");
    fLegendAway->AddEntry(fHistLamAwayZYAM,"Triger #Lambda a #bar{#Lambda}, pozadie","pl");
    fLegendAway->AddEntry(fHistHadronAwayZYAM,"Triger h, pozadie","pl");*/
     
     TCanvas * canaway = new TCanvas();
     fHistK0Away->DrawCopy();
     fHistLambdaAway->DrawCopy("same");
     fHistHadronAway->DrawCopy("same");
    fHistK0AwayMix->DrawCopy("same");
    fHistLamAwayMix->DrawCopy("same");
    fHistLamAwayZYAM->DrawCopy("same");
    fHistK0AwayZYAM->DrawCopy("same");
    fHistHadronAwayMix->DrawCopy("same");
    fHistHadronAwayZYAM->DrawCopy("same");
    canaway  ->BuildLegend();
   //  fLegendAway->Draw();
  
    TCanvas* canSyst = new TCanvas;
    canSyst->Divide(2);
    canSyst->cd(1);
    TLegend *legNe = new TLegend;
    fHistK0NearSyst->GetYaxis()->SetRangeUser(0,0.4);
    fHistK0NearSyst->SetTitle("Prilahly pik");
    fHistK0NearSyst->SetXTitle("p_{T}^{trig} (GeV)");
    fHistK0NearSyst->SetYTitle("Relativna neistota");
    fHistK0NearSyst->SetLineColor(kBlue);
    fHistLambdaNearSyst->SetLineColor(kGreen);
    fHistHadronNearSyst->SetLineColor(kRed);
    TH1D *histcloneK0ZYAMnear = (TH1D*)fHistK0NearSyst->DrawCopy();
    TH1D *histcloneLamZYAMnear = (TH1D*)fHistLambdaNearSyst->DrawCopy("Same");
    TH1D *histcloneHadrZYAMnear = (TH1D*)fHistHadronNearSyst->DrawCopy("Same");
    legNe->AddEntry(histcloneK0ZYAMnear, "K^{0}_{S}-h","l");
    legNe->AddEntry(histcloneLamZYAMnear, "(#Lambda+#bar{#Lambda})-h","l");
    legNe->AddEntry(histcloneHadrZYAMnear, "h-h","l");
    legNe->Draw();
    
    canSyst->cd(2);
    TLegend *legAw = new TLegend;
    fHistK0AwaySyst->GetYaxis()->SetRangeUser(0,2);
    fHistK0AwaySyst->SetTitle("Protilahly pik");
    fHistK0AwaySyst->SetXTitle("p_{T}^{trig} (GeV)");
    fHistK0AwaySyst->SetYTitle("Relativna neistota");
    fHistK0AwaySyst->SetLineColor(kBlue);
    fHistLambdaAwaySyst->SetLineColor(kGreen);
    fHistHadronAwaySyst->SetLineColor(kRed);
    TH1D *histcloneK0ZYAMaway = (TH1D*) fHistK0AwaySyst->DrawCopy();
    TH1D *histcloneLamZYAMaway = (TH1D*)fHistLambdaAwaySyst->DrawCopy("Same");
    TH1D *histcloneHadrZYAMaway = (TH1D*)fHistHadronAwaySyst->DrawCopy("Same");
    legAw->AddEntry(histcloneK0ZYAMaway, "K^{0}_{S}-h","l");
    legAw->AddEntry(histcloneLamZYAMaway, "(#Lambda+#bar{#Lambda})-h","l");
    legAw->AddEntry(histcloneHadrZYAMaway, "h-h","l");
    legAw->Draw();

    TCanvas* canSystMix = new TCanvas;
    canSystMix->Divide(2);
    canSystMix->cd(1);
    TLegend *legNeMix = new TLegend;
    fHistK0NearMixSyst->GetYaxis()->SetRangeUser(0.,0.5);
    fHistK0NearMixSyst->SetTitle("Prilahly pik");
    fHistK0NearMixSyst->SetXTitle("p_{T}^{trig} (GeV)");
    fHistK0NearMixSyst->SetYTitle("Relativna neistota");
    fHistK0NearMixSyst->SetLineColor(kBlue);
    fHistLamNearMixSyst->SetLineColor(kGreen);
    fHistHadronNearMixSyst->SetLineColor(kRed);
    TH1D *histcloneK0Mixnear = (TH1D*) fHistK0NearMixSyst->DrawCopy();
    TH1D *histcloneLamMixnear = (TH1D*)fHistLamNearMixSyst->DrawCopy("same");
    TH1D *histcloneHadrMixnear = (TH1D*)fHistHadronNearMixSyst->DrawCopy("same");
    legNeMix->AddEntry(histcloneK0Mixnear, "K^{0}_{S}-h","l");
    legNeMix->AddEntry(histcloneLamMixnear, "(#Lambda+#bar{#Lambda})-h","l");
    legNeMix->AddEntry(histcloneHadrMixnear, "h-h","l");
    legNeMix->Draw();
    
    canSystMix->cd(2);
    TLegend *legAwMix = new TLegend();
    fHistK0AwayMixSyst->GetYaxis()->SetRangeUser(0.,0.5);
    fHistK0AwayMixSyst->SetTitle("Protilahly pik");
    fHistK0AwayMixSyst->SetXTitle("p_{T}^{trig} (GeV)");
    fHistK0AwayMixSyst->SetYTitle("Relativna neistota");
    fHistK0AwayMixSyst->SetLineColor(kBlue);
    fHistLamAwayMixSyst->SetLineColor(kGreen);
    fHistHadronAwayMixSyst->SetLineColor(kRed);
    TH1D *histcloneK0Mixaway = (TH1D*) fHistK0AwayMixSyst->DrawCopy();
    legAwMix->AddEntry(histcloneK0Mixaway,"K^{0}_{S}-h","l");
    TH1D *histcloneLamMixaway = (TH1D*)fHistLamAwayMixSyst->DrawCopy("Same");
    legAwMix->AddEntry(histcloneLamMixaway,"(#Lambda+#bar{#Lambda})-h","l");
    TH1D *histcloneHadrMixaway = (TH1D*)fHistHadronAwayMixSyst->DrawCopy("same");
    legAwMix->AddEntry(histcloneHadrMixaway,"h-h","l");
    legAwMix->Draw();
    
    TCanvas* canBarlowZYAM = new TCanvas;
    canBarlowZYAM->Divide(2);
    canBarlowZYAM->cd(1);
    TLegend *legNeZYAMBarlow = new TLegend;
    fHistK0NearZYAMBarlow->SetLineColor(kBlue);
    fHistLamNearZYAMBarlow->SetLineColor(kGreen);
    fHistHadronNearZYAMBarlow->SetLineColor(kRed);
    fHistHadronNearZYAMBarlow->SetTitle("Prilahly pik");
    fHistHadronNearZYAMBarlow->SetXTitle("p_{T}^{trig} (GeV)");
    fHistHadronNearZYAMBarlow->SetYTitle("Relativna neistota");
    fHistHadronNearZYAMBarlow->GetYaxis()->SetRangeUser(0,100);
    TH1D *histcloneHadrZYAMBarlowNear = (TH1D*)fHistHadronNearZYAMBarlow->DrawCopy();
    legNeZYAMBarlow->AddEntry(histcloneHadrZYAMBarlowNear,"h-h","l");
    TH1D *histcloneK0ZYAMBarlowNear = (TH1D*) fHistK0NearZYAMBarlow->DrawCopy("same");
    legNeZYAMBarlow->AddEntry(histcloneK0ZYAMBarlowNear,"K^{0}_{S}-h","l");
    TH1D *histcloneLamZYAMBarlowNear= (TH1D*)fHistLamNearZYAMBarlow->DrawCopy("Same");
    legNeZYAMBarlow->AddEntry(histcloneLamZYAMBarlowNear,"(#Lambda+#bar{#Lambda})-h","l");
    
    legNeZYAMBarlow->Draw();
    
    canBarlowZYAM->cd(2);
    
    TLegend *legAwZYAMBarlow = new TLegend;
    fHistK0AwayZYAMBarlow->SetLineColor(kBlue);
    fHistLamAwayZYAMBarlow->SetLineColor(kGreen);
    fHistHadronAwayZYAMBarlow->SetLineColor(kRed);
    fHistHadronAwayZYAMBarlow->SetTitle("Protilahly pik");
    fHistHadronAwayZYAMBarlow->SetXTitle("p_{T}^{trig} (GeV)");
    fHistHadronAwayZYAMBarlow->SetYTitle("Relativna neistota");
    fHistHadronAwayZYAMBarlow->GetYaxis()->SetRangeUser(0,100);
    TH1D *histcloneHadrZYAMBarlowAway = (TH1D*)fHistHadronAwayZYAMBarlow->DrawCopy();
    legAwZYAMBarlow->AddEntry(histcloneHadrZYAMBarlowAway,"h-h","l");
    TH1D *histcloneK0ZYAMBarlowAway = (TH1D*) fHistK0AwayZYAMBarlow->DrawCopy("same");
    legAwZYAMBarlow->AddEntry(histcloneK0ZYAMBarlowAway,"K^{0}_{S}-h","l");
    TH1D *histcloneLamZYAMBarlowAway = (TH1D*)fHistLamAwayZYAMBarlow->DrawCopy("Same");
    legAwZYAMBarlow->AddEntry(histcloneLamZYAMBarlowAway,"(#Lambda+#bar{#Lambda})-h","l");
    
    legAwZYAMBarlow->Draw();
    
    TCanvas* canBarlowMix = new TCanvas;
    canBarlowMix->Divide(2);
    canBarlowMix->cd(1);
    TLegend *legNeMixBarlow = new TLegend;
    fHistK0NearMixBarlow->SetLineColor(kBlue);
    fHistLamNearMixBarlow->SetLineColor(kGreen);
    fHistHadronNearMixBarlow->SetLineColor(kRed);
    fHistK0NearMixBarlow->SetTitle("Prilahly pik");
    fHistK0NearMixBarlow->SetXTitle("p_{T}^{trig} (GeV)");
    fHistK0NearMixBarlow->SetYTitle("Relativna neistota");
    fHistHadronNearMixBarlow->GetYaxis()->SetRangeUser(0,100);
    TH1D *histcloneHadrBarlowNear = (TH1D*)fHistHadronNearMixBarlow->DrawCopy();
    legNeMixBarlow->AddEntry(histcloneHadrBarlowNear,"h-h","l");
    TH1D *histcloneK0MixBarlowNear = (TH1D*) fHistK0NearMixBarlow->DrawCopy("same");
    legNeMixBarlow->AddEntry(histcloneK0MixBarlowNear,"K^{0}_{S}-h","l");
    TH1D *histcloneLamMixBarlowNear= (TH1D*)fHistLamNearMixBarlow->DrawCopy("Same");
    legNeMixBarlow->AddEntry(histcloneLamMixBarlowNear,"(#Lambda+#bar{#Lambda})-h","l");
    
    legNeMixBarlow->Draw();
    
    canBarlowMix->cd(2);
    
    TLegend *legAwMixBarlow = new TLegend;
    fHistK0AwayMixBarlow->SetLineColor(kBlue);
    fHistLamAwayMixBarlow->SetLineColor(kGreen);
    fHistHadronAwayMixBarlow->SetLineColor(kRed);
    fHistK0AwayMixBarlow->SetTitle("Protilahly pik");
    fHistK0AwayMixBarlow->SetXTitle("p_{T}^{trig} (GeV)");
    fHistK0AwayMixBarlow->SetYTitle("Relativna neistota");
    fHistHadronAwayMixBarlow->GetYaxis()->SetRangeUser(0,100);
    TH1D *histcloneHadrBarlowAway = (TH1D*)fHistHadronAwayMixBarlow->DrawCopy();
    legAwMixBarlow->AddEntry(histcloneHadrBarlowAway,"h-h","l");
    TH1D *histcloneK0MixBarlowAway = (TH1D*) fHistK0AwayMixBarlow->DrawCopy("same");
    legAwMixBarlow->AddEntry(histcloneK0MixBarlowAway,"K^{0}_{S}-h","l");
    TH1D *histcloneLamMixBarlowAway = (TH1D*)fHistLamAwayMixBarlow->DrawCopy("Same");
    legAwMixBarlow->AddEntry(histcloneLamMixBarlowAway,"(#Lambda+#bar{#Lambda})-h","l");
    
    legAwMixBarlow->Draw();
    
     fHistK0Near->Write();
     fHistLambdaNear->Write();
     fHistHadronNear->Write();
     fHistK0Away->Write();
     fHistLambdaAway->Write();
     fHistHadronAway->Write();
     fFile->Close();
}
