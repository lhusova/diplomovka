Double_t fitf(Double_t *x, Double_t *par)
{
    if (TMath::Abs(x[0]) < 0.33) {
        TF1::RejectPoint();
        return 0;
    }
    
    Double_t arg = 0;
    if (par[2]) arg = (x[0] - par[1])/par[2];
    
    Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
    return fitval;
}

void sirkaPiku(){
    
    TFile *g =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_1MultBin_hh_0-2Pt.root");
    TFile *f =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_1MultBin_hh_3-5Pt.root");
    
    TFile *g2 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_2MultBin_hh_0-2Pt.root");
    TFile *f2 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_2MultBin_hh_3-5Pt.root");
    
    TFile *g3 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_3MultBin_hh_0-2Pt.root");
    TFile *f3 =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphData_03_3MultBin_hh_3-5Pt.root");
    
    char name[20];
    TCanvas *canLam = new TCanvas;
    canLam->Divide(3,6);
    
    Double_t rms[3][6];
    Double_t rmsErr[3][6];
    Double_t sigma[3][6];
    
    TFile *fNewFile = TFile::Open("GusFit.root","RECREATE");
    
    for (Int_t j=0;j<6;j++){
        for(Int_t iMult=0;iMult<3;iMult++){
            
            sprintf(name,"projPhi_%d_%d_%d",3,j+1,iMult+1);
            TH1D* fHistProjPhi = 0x0;
            if(iMult==0){
                if (j<3) fHistProjPhi = (TH1D*) g->Get(name);
                else fHistProjPhi = (TH1D*) f->Get(name);
            }
            if(iMult==1){
                if (j<3) fHistProjPhi = (TH1D*) g2->Get(name);
                else fHistProjPhi = (TH1D*) f2->Get(name);
            }
            if(iMult==2){
                if (j<3) fHistProjPhi = (TH1D*) g3->Get(name);
                else fHistProjPhi = (TH1D*) f3->Get(name);
            }
            
            fHistProjPhi->GetXaxis()->SetRangeUser(-1,1);
            
            rms[iMult][j] = fHistProjPhi->GetRMS();
            rmsErr[iMult][j] = fHistProjPhi->GetRMSError();
            
            canLam->cd(j*3+iMult+1);
            fHistProjPhi->DrawCopy();
            
            Double_t par[6];
            TF1 *func = new TF1("fitf",fitf,-1,1,3);
            func->SetParameters(0,0,1);
            fHistProjPhi->Fit("fitf");
            
            TF1 *fg2    = new TF1("fg2","gaus",-0.6,0.6);
            fg2->SetParameter(1,0);
            fHistProjPhi->Fit(fg2,"R+");

           TF1 *total = new TF1("total","gaus(0)+gaus(3)",-1,1);
            func->GetParameters(&par[0]);
            fg2->GetParameters(&par[3]);
            total->SetParameters(par);
            fHistProjPhi->Fit(total,"R+");
            Printf("chi2 %g\n",total->GetChisquare());
            
            sigma[iMult][j] = total->GetParameter(2);
            
            fHistProjPhi->Write();
            
            
           delete total;
            delete func;
           delete fg2;
          //  delete fg3;*/
            
            delete fHistProjPhi;
            
        }
        
    }
    
    Double_t PtGraph[6] = {4.5, 5.5, 6.5, 8, 10, 13};
    Double_t PtHist[6+1] = {4, 5, 6, 7, 9, 11, 15};
    Double_t PtError[6] = {0.5, 0.5, 0.5, 1, 1, 2};
    
    TGraphErrors *fGraphHadronRMSNear1 = new TGraphErrors(6,PtGraph,rms[0],PtError,rmsErr[0]);
    TGraphErrors *fGraphHadronRMSNear2 = new TGraphErrors(6,PtGraph,rms[1],PtError,rmsErr[1]);
    TGraphErrors *fGraphHadronRMSNear3 = new TGraphErrors(6,PtGraph,rms[2],PtError,rmsErr[2]);
    
    fGraphHadronRMSNear1->SetTitle("Zavislost sirky prilahleho piku pre h-h od p_{T} a multiplicity (RMS)");
    fGraphHadronRMSNear1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    fGraphHadronRMSNear1->GetYaxis()->SetTitle("sirka piku");
    
    fGraphHadronRMSNear1->SetMarkerStyle(21);
    fGraphHadronRMSNear1->SetMarkerSize(1.5);
    fGraphHadronRMSNear1->SetMarkerColor(kBlue);
    fGraphHadronRMSNear1->SetLineColor(kBlue);
    fGraphHadronRMSNear2->SetMarkerStyle(22);
    fGraphHadronRMSNear2->SetMarkerSize(1.5);
    fGraphHadronRMSNear2->SetMarkerColor(kRed);
    fGraphHadronRMSNear2->SetLineColor(kRed);
    fGraphHadronRMSNear3->SetMarkerStyle(23);
    fGraphHadronRMSNear3->SetMarkerSize(1.5);
    fGraphHadronRMSNear3->SetMarkerColor(kBlack);
    fGraphHadronRMSNear3->SetLineColor(kBlack);
    TLegend * lgHhNear = new TLegend(0.2,0.9,0.75,0.8);
    lgHhNear->AddEntry(fGraphHadronRMSNear1,"0-10%","pl");
    lgHhNear->AddEntry(fGraphHadronRMSNear2,"10-50%","pl");
    lgHhNear->AddEntry(fGraphHadronRMSNear3,"50-100%","pl");
    TCanvas *cYieldNearH = new TCanvas;
    fGraphHadronRMSNear1->Draw("ap");
    fGraphHadronRMSNear2->Draw("psame");
    fGraphHadronRMSNear3->Draw("psame");
    lgHhNear->Draw();
    
    TGraph *fGraphHadronSigmaNear1 = new TGraphErrors(6,PtGraph,sigma[0]);
    TGraph *fGraphHadronSigmaNear2 = new TGraphErrors(6,PtGraph,sigma[1]);
    TGraph *fGraphHadronSigmaNear3 = new TGraphErrors(6,PtGraph,sigma[2]);
    
    fGraphHadronSigmaNear1->SetTitle("Zavislost sirky prilahleho piku pre h-h od p_{T} a multiplicity (sigma)");
    fGraphHadronSigmaNear1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    fGraphHadronSigmaNear1->GetYaxis()->SetTitle("sirka piku");
    
    fGraphHadronSigmaNear1->SetMarkerStyle(21);
    fGraphHadronSigmaNear1->SetMarkerSize(1.5);
    fGraphHadronSigmaNear1->SetMarkerColor(kBlue);
    fGraphHadronSigmaNear1->SetLineColor(kBlue);
    fGraphHadronSigmaNear2->SetMarkerStyle(22);
    fGraphHadronSigmaNear2->SetMarkerSize(1.5);
    fGraphHadronSigmaNear2->SetMarkerColor(kRed);
    fGraphHadronSigmaNear2->SetLineColor(kRed);
    fGraphHadronSigmaNear3->SetMarkerStyle(23);
    fGraphHadronSigmaNear3->SetMarkerSize(1.5);
    fGraphHadronSigmaNear3->SetMarkerColor(kBlack);
    fGraphHadronSigmaNear3->SetLineColor(kBlack);
    TLegend * lgHhSigmaNear = new TLegend(0.2,0.9,0.75,0.8);
    lgHhSigmaNear->AddEntry(fGraphHadronSigmaNear1,"0-10%","pl");
    lgHhSigmaNear->AddEntry(fGraphHadronSigmaNear2,"10-50%","pl");
    lgHhSigmaNear->AddEntry(fGraphHadronSigmaNear3,"50-100%","pl");
    TCanvas *cYieldSigmaNearH = new TCanvas;
    fGraphHadronSigmaNear1->Draw("ap");
    fGraphHadronSigmaNear2->Draw("psame");
    fGraphHadronSigmaNear3->Draw("psame");
    lgHhSigmaNear->Draw();
    
    
  /*  const Int_t np = 49;
    Float_t x[np] = {1.913521, 1.953769, 2.347435, 2.883654, 3.493567,
        4.047560, 4.337210, 4.364347, 4.563004, 5.054247,
        5.194183, 5.380521, 5.303213, 5.384578, 5.563983,
        5.728500, 5.685752, 5.080029, 4.251809, 3.372246,
        2.207432, 1.227541, 0.8597788,0.8220503,0.8046592,
        0.7684097,0.7469761,0.8019787,0.8362375,0.8744895,
        0.9143721,0.9462768,0.9285364,0.8954604,0.8410891,
        0.7853871,0.7100883,0.6938808,0.7363682,0.7032954,
        0.6029015,0.5600163,0.7477068,1.188785, 1.938228,
        2.602717, 3.472962, 4.465014, 5.177035};
    
    TH1F *h = new TH1F("h","Example of several fits in subranges",np,85,134);
    h->SetMaximum(7);
    
    for (int i=0;i<np;i++) {
        h->SetBinContent(i+1,x[i]);
    }
    
    Double_t par[9];
    TF1 *fg1    = new TF1("fg1","gaus",85,95);
    TF1 *fg2    = new TF1("fg2","gaus",98,108);
    TF1 *fg3    = new TF1("fg3","gaus",110,121);
    TF1 *total = new TF1("total","gaus(0)+gaus(3)+gaus(6)",85,125);
    total->SetLineColor(2);
    h->Fit(fg1,"R");
    h->Fit(fg2,"R+");
    h->Fit(fg3,"R+");
    fg1->GetParameters(&par[0]);
    fg2->GetParameters(&par[3]);
    fg3->GetParameters(&par[6]);
    total->SetParameters(par);
    h->Fit(total,"R+");
    
    TCanvas* vv = new TCanvas;
    h->DrawCopy();*/
    
    fNewFile->Close();
}

