void GraphMult(){
    gStyle->SetOptStat(0000000000);
    TFile *g =  TFile::Open("/Users/lhusova/git/diplomovka/diplomovka/data/GraphMC2015a_nove.root");
    
    TGraphErrors *fGraphK0Near1 = (TGraphErrors*) g->Get("fGraphK0Near1");
    TGraphErrors *fGraphK0Near2 = (TGraphErrors*) g->Get("fGraphK0Near2");
    TGraphErrors *fGraphK0Near3 = (TGraphErrors*) g->Get("fGraphK0Near3");
    
    fGraphK0Near1->SetTitle("Zaviskost vytazkov od p_{T}^{trig} pre K_{0}^{S} pre jednotlive multiplicitne biny");
    
    fGraphK0Near2->SetMarkerSize(1.8);
    fGraphK0Near2->SetMarkerStyle(21);
    fGraphK0Near2->SetMarkerColor(kRed);
    fGraphK0Near2->SetLineColor(kRed);
    
    fGraphK0Near3->SetMarkerSize(1.8);
    fGraphK0Near3->SetMarkerStyle(22);
    fGraphK0Near3->SetMarkerColor(kGreen);
    fGraphK0Near3->SetLineColor(kGreen);
    
    TLegend *lgK0Near = new TLegend(0.2,0.9,0.75,0.8);
    lgK0Near->AddEntry(fGraphK0Near1,"0-10%","pl");
    lgK0Near->AddEntry(fGraphK0Near2,"10-50% ","pl");
    lgK0Near->AddEntry(fGraphK0Near3,"50-100% ","pl");

    TCanvas * canK0Near = new TCanvas;
    fGraphK0Near1->Draw("ap");
    fGraphK0Near2->Draw("pSAME");
    fGraphK0Near3->Draw("pSAME");
    lgK0Near->Draw();

}
