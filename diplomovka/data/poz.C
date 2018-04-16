
void poz(){

    gStyle->SetOptStat(0000000000);
    gStyle->SetPalette(kRainBow);

    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsPt24_05.root"); //DataNajnovsie03.root");
	TList *list = (TList*)g->Get("MyTask/MyOutputContainer");

    THnSparse *fHistdPhidEtaMix = (THnSparse*)list->FindObject("fHistdPhidEtaMix");

    //fHistdPhidEtaMix->GetAxis(5)->SetRange(4,4);
    //fHistdPhidEtaMix->GetAxis(0)->SetRange(1,1);
   TH2D *fHistDelPhiDelEtaMix = (TH2D*)fHistdPhidEtaMix->Projection(2,3);
    fHistDelPhiDelEtaMix->SetName("mix");
   //fHistDelPhiDelEtaMix->RebinX(2);
   //fHistDelPhiDelEtaMix->RebinY(2);
   fHistDelPhiDelEtaMix->SetTitle("Kombinatoricke pozadie");
   fHistDelPhiDelEtaMix->SetYTitle("#Delta #Phi");
   fHistDelPhiDelEtaMix->SetXTitle("#Delta #eta");
   fHistDelPhiDelEtaMix->SetAxisRange(-1,1,"x");
   fHistDelPhiDelEtaMix->Scale(1./fHistDelPhiDelEtaMix->GetMaximum());

   TCanvas *c = new TCanvas;
   fHistDelPhiDelEtaMix->DrawCopy("lego2z");
    
    THnSparse *fHistdPhidEta = (THnSparse*)list->FindObject("fHistKorelacie");
    fHistdPhidEta->GetAxis(5)->SetRange(4,4);
    TH2D *fHistDelPhiDelEta = (TH2D*)fHistdPhidEta->Projection(2,3);
    fHistDelPhiDelEta->SetName("cor");
   // fHistDelPhiDelEta->RebinX(2);
   // fHistDelPhiDelEta->RebinY(2);
    fHistDelPhiDelEta->SetTitle("Korelacna funkcia");
    fHistDelPhiDelEta->SetYTitle("#Delta #Phi");
    fHistDelPhiDelEta->SetXTitle("#Delta #eta");
    fHistDelPhiDelEta->SetAxisRange(-1,1,"x");
   // fHistDelPhiDelEta->Divide(fHistDelPhiDelEtaMix);
    
    TCanvas *cc = new TCanvas;
    fHistDelPhiDelEta->DrawCopy("lego2z");

}
