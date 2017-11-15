#include <TH1D.h>

void MC(){

	TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMC2016_01.root");
    //TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/AnalysisResults.root");
	TList *list = g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy

    TH3D *fHistMCPtAs = (TH3D*)list->FindObject("fHistMCPtAs");
    TH3D *fHistRCPtAs = (TH3D*)list->FindObject("fHistRCPtAs");
    
    THnSparseF *fHistGenV0 = (THnSparseF*)list->FindObject("fHistGenV0");
    THnSparseF *fHistRecV0 = (THnSparseF*)list->FindObject("fHistRecV0");

    TCanvas *c1 = new TCanvas("c1","",600,800);
	pad1 = new TPad("pad1","This is pad1",0.001,0.3,0.999,0.999);
	pad2 = new TPad("pad2","This is pad2",0.001,0.001,0.999,0.3);
	Printf ("x %d y %d z %d\n",fHistRCPtAs->GetXaxis()->GetNbins(),fHistRCPtAs->GetYaxis()->GetNbins(),fHistRCPtAs->GetZaxis()->GetNbins());
	pad1->SetMargin(0.1,0.1,0,0.1);  
	pad2->SetMargin(0.1,0.1,0.2,0);
	
	pad1->Draw();
    pad2->Draw();
    
    fHistMCPtAs->RebinZ(4);
    fHistMCPtAs->RebinY(2);
    fHistRCPtAs->RebinZ(4);
    fHistRCPtAs->RebinY(2);
    
    //fHistMCPtAs->Sumw2();
    TH1D *fHistMCPtAsPojX = fHistMCPtAs->ProjectionX();
    fHistMCPtAsPojX->SetName("fHistMCPtAsPojX");
    fHistMCPtAsPojX->SetMarkerStyle(23);
    fHistMCPtAsPojX->SetMarkerSize(1.5);
    fHistMCPtAsPojX->SetMarkerColor(kMagenta);
    
    fHistMCPtAsPojX->SetYTitle("#");
    fHistMCPtAsPojX->SetTitle("Rozdelenie p_{T} pre MC a rekostruovane MC drahy");

    //fHistRCPtAs->Sumw2();
    TH1D* fHistRCPtAsProjX = fHistRCPtAs->ProjectionX();
    fHistRCPtAsProjX->SetName("fHistRCPtAsProjX");
    fHistRCPtAsProjX->SetMarkerStyle(23);
    fHistRCPtAsProjX->SetMarkerSize(1.5);
    fHistRCPtAsProjX->SetMarkerColor(kBlue);

    TLegend *lg1 = new TLegend(0.2,0.9,0.75,0.8);
	lg1->AddEntry(fHistMCPtAsPojX,"MC generovane drahy","pl");
	lg1->AddEntry(fHistRCPtAsProjX,"rekonstruovane MC drahy","pl");

    pad1->cd();
    pad1->SetLogy();
    fHistMCPtAsPojX->SetStats(kFALSE);
    fHistMCPtAsPojX->DrawCopy();
    fHistRCPtAsProjX->DrawCopy("same");
    lg1->Draw();

    pad2->cd();
    fHistRCPtAsProjX->Divide(fHistMCPtAsPojX);
    fHistRCPtAsProjX->SetXTitle("p_{T} (GeV)");
    fHistRCPtAsProjX->SetTitle("");
    fHistRCPtAsProjX->SetYTitle("");
    fHistRCPtAsProjX->SetStats(kFALSE);
    fHistRCPtAsProjX->DrawCopy();

    TF1 *f1 = new TF1("fiting","[0]",0,15);
    f1->SetParameter(0,0.8);
    //f1->Draw();
    fHistRCPtAsProjX->Fit("fiting");

    TCanvas *cK0 = new TCanvas("c2","",600,800);
    padK01 = new TPad("padK01","This is padK01",0.001,0.3,0.999,0.999);
    padK02 = new TPad("padK02","This is padK02",0.001,0.001,0.999,0.3);
    
    padK01->SetMargin(0.1,0.1,0,0.1);
    padK02->SetMargin(0.1,0.1,0.2,0);
    
    padK01->Draw();
    padK02->Draw();
    
    padK01->cd();
    
    fHistGenV0->GetAxis(2)->SetRange(1,1);
    TH1D *histV0GenK0 = fHistGenV0->Projection(0);
    histV0GenK0->SetName("histV0GenK0");
    histV0GenK0->SetMarkerStyle(23);
    histV0GenK0->SetMarkerSize(1.5);
    histV0GenK0->SetMarkerColor(kMagenta);
    histV0GenK0->SetLineColor(kMagenta);
    //histV0GenK0->SetAxisRange(0,6000,"y");
    histV0GenK0->SetTitle("ucinnost rekonstrukcie K^0_{S}");
    histV0GenK0->DrawCopy();
    
    
    fHistRecV0->GetAxis(2)->SetRange(1,1);
    TH1D *histV0RecK0 = fHistRecV0->Projection(0);
    histV0RecK0->SetName("histV0RecK0");
    histV0RecK0->SetMarkerStyle(23);
    histV0RecK0->SetMarkerSize(1.5);
    histV0RecK0->SetMarkerColor(kBlue);
    histV0RecK0->SetLineColor(kBlue);
    histV0RecK0->DrawCopy("same");
    
    TLegend *lg2 = new TLegend(0.2,0.9,0.75,0.8);
    lg2->AddEntry(histV0GenK0,"MC generovane K0","pl");
    lg2->AddEntry(histV0RecK0,"rekonstruovane MC K0","pl");
    lg2->Draw();
    
  
    padK02->cd();
    histV0RecK0->Divide(histV0GenK0);
    histV0RecK0->SetXTitle("p_{T} (GeV)");
    histV0RecK0->SetTitle("");
    histV0RecK0->SetYTitle("");
    histV0RecK0->SetStats(kFALSE);
    histV0RecK0->DrawCopy();
    
    fHistRecV0->GetAxis(2)->SetRange(-1,0);
    fHistGenV0->GetAxis(2)->SetRange(-1,0);
    
    TCanvas *cLam = new TCanvas("c3","",600,800);
    padLam1 = new TPad("padLam1","This is padLam1",0.001,0.3,0.999,0.999);
    padLam2 = new TPad("padLam2","This is padLam2",0.001,0.001,0.999,0.3);
    
    padLam1->SetMargin(0.1,0.1,0,0.1);
    padLam2->SetMargin(0.1,0.1,0.2,0);
    
    padLam1->Draw();
    padLam2->Draw();
    
    padLam1->cd();
    
    fHistGenV0->GetAxis(2)->SetRange(2,2);
    TH1D *histV0GenLam = fHistGenV0->Projection(0);
    histV0GenLam->SetName("histV0GenLam");
    histV0GenLam->SetMarkerStyle(23);
    histV0GenLam->SetMarkerSize(1.5);
    histV0GenLam->SetMarkerColor(kMagenta);
    histV0GenLam->SetLineColor(kMagenta);
    //histV0GenLam->SetAxisRange(0,4000,"y");
    histV0GenLam->SetTitle("ucinnost rekonstrukcie  #Lambda + #bar{#Lambda}");
    histV0GenLam->DrawCopy();
    
    
    fHistRecV0->GetAxis(2)->SetRange(2,2);
    TH1D *histV0RecLam = fHistRecV0->Projection(0);
    histV0RecLam->SetName("histV0RecLam");
    histV0RecLam->SetMarkerStyle(23);
    histV0RecLam->SetMarkerSize(1.5);
    histV0RecLam->SetMarkerColor(kBlue);
    histV0RecLam->SetLineColor(kBlue);
    histV0RecLam->DrawCopy("same");
    
    TLegend *lg3 = new TLegend(0.2,0.9,0.75,0.8);
    lg3->AddEntry(histV0GenLam,"MC generovane #Lambda + #bar{#Lambda}","pl");
    lg3->AddEntry(histV0RecLam,"rekonstruovane MC #Lambda + #bar{#Lambda}","pl");
    lg3->Draw();
    
    
    padLam2->cd();
    histV0RecLam->Divide(histV0GenLam);
    histV0RecLam->SetXTitle("p_{T} (GeV)");
    histV0RecLam->SetTitle("");
    histV0RecLam->SetYTitle("");
    histV0RecLam->SetStats(kFALSE);
    histV0RecLam->DrawCopy();
    
    TFile *fNewFile = TFile::Open("Efiiciency.root","RECREATE");
    fHistRCPtAs->Divide(fHistMCPtAs);
    TCanvas * cccc = new TCanvas;
    fHistRCPtAs->DrawCopy("colz");
    fHistRCPtAs->Write();
    
    fHistGenV0->GetAxis(2)->SetRange(1,1);
    TH3D *fHistGenV03DK0 = fHistGenV0->Projection(0,1,3);
    fHistGenV03DK0->SetName("fHistGenV03DK0");
    fHistRecV0->GetAxis(2)->SetRange(1,1);
    TH3D *fHistRecV03DK0 = fHistRecV0->Projection(0,1,3);
    fHistRecV03DK0->SetName("fHistRecV03DK0");
    fHistRecV03DK0->Divide(fHistGenV03DK0);
    fHistGenV03DK0->Write();
    
    fHistGenV0->GetAxis(2)->SetRange(-1,0);
    fHistRecV0->GetAxis(2)->SetRange(-1,0);
    
    fHistGenV0->GetAxis(2)->SetRange(2,2);
    TH3D *fHistGenV03DLam = fHistGenV0->Projection(0,1,3);
    fHistGenV03DLam->SetName("fHistGenV03DLam");
    fHistRecV0->GetAxis(2)->SetRange(2,2);
    TH3D *fHistRecV03DLam = fHistRecV0->Projection(0,1,3);
    fHistRecV03DLam->SetName("fHistRecV03DLam");
    fHistRecV03DLam->Divide(fHistGenV03DLam);
    fHistRecV03DLam->Write();
    
    fNewFile->Close();
}
