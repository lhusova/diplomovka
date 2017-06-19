#include <TH1D.h>

void MC(){

	TFile *g = new TFile("/home/lhusova/diplomovka/data/vysledky/AnalysisResultsMC_05.root");
	TList *list = g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy

    TH1D *fHistMCPtAs = (TH1D*)list->FindObject("fHistMCPtAs");
    TH1D *fHistRCPtAs = (TH1D*)list->FindObject("fHistRCPtAs");

    TCanvas *c1 = new TCanvas("c1","",600,800);
	pad1 = new TPad("pad1","This is pad1",0.001,0.3,0.999,0.999);
	pad2 = new TPad("pad2","This is pad2",0.001,0.001,0.999,0.3);
	
	pad1->SetMargin(0.1,0.1,0,0.1);  
	pad2->SetMargin(0.1,0.1,0.2,0);
	
	pad1->Draw();
    pad2->Draw();
    
    fHistMCPtAs->Sumw2();
    fHistMCPtAs->SetMarkerStyle(23);
    fHistMCPtAs->SetMarkerSize(1.5);
    fHistMCPtAs->SetMarkerColor(kMagenta);
    
    fHistMCPtAs->SetYTitle("#");
    fHistMCPtAs->SetTitle("Rozdelenie p_{T} pre MC a rekostruovane MC drahy");

    fHistRCPtAs->Sumw2();
    fHistRCPtAs->SetMarkerStyle(23);
    fHistRCPtAs->SetMarkerSize(1.5);
    fHistRCPtAs->SetMarkerColor(kBlue);

    TLegend *lg1 = new TLegend(0.2,0.9,0.75,0.8);
	lg1->AddEntry(fHistMCPtAs,"MC generovane drahy","pl");
	lg1->AddEntry(fHistRCPtAs,"rekonstruovane MC drahy","pl");

    pad1->cd();
    pad1->SetLogy();
    fHistMCPtAs->SetStats(kFALSE);
    fHistMCPtAs->DrawCopy();
    fHistRCPtAs->DrawCopy("same");    
    lg1->Draw();

    pad2->cd();
    fHistRCPtAs->Divide(fHistMCPtAs);
    fHistRCPtAs->SetXTitle("p_{T} (GeV)");
    fHistRCPtAs->SetTitle("");
    fHistRCPtAs->SetYTitle("");
    fHistRCPtAs->SetStats(kFALSE);
    fHistRCPtAs->DrawCopy();

    TF1 *f1 = new TF1("fiting","[0]",0,15);
    f1->SetParameter(0,0.8);
    //f1->Draw();
    fHistRCPtAs->Fit("fiting");    



    

}