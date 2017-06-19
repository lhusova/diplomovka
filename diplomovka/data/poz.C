
void poz(){

    gStyle->SetOptStat(0000000000);

    TFile *g = new TFile("/home/lhusova/diplomovka/data/vysledky/AnalysisResultsPt24_03.root");
	TList *list = g->Get("MyTask/MyOutputContainer");

    THnSparse *fHistdPhidEtaMix = (THnSparse*)list->FindObject("fHistdPhidEtaMix");

   TH2D *fHistDelPhiDelEta = fHistdPhidEtaMix->Projection(2,3);
   //fHistDelPhiDelEta->RebinX(4);
   //fHistDelPhiDelEta->RebinY(4);
   fHistDelPhiDelEta->SetTitle("Tvar kombinatorickeho pozadia");
   fHistDelPhiDelEta->SetYTitle("#Delta #Phi");
   fHistDelPhiDelEta->SetXTitle("#Delta #eta");
   fHistDelPhiDelEta->SetAxisRange(-1,1,"x");
   fHistDelPhiDelEta->Scale(1./fHistDelPhiDelEta->GetMaximum());

   TCanvas *c = new TCanvas;
   fHistDelPhiDelEta->DrawCopy("lego2z");

}