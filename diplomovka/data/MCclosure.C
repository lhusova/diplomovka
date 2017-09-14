void MCclosure (

    TFile *g = new TFile("/home/lhusova/diplomovka/data/vysledky/AnalysisResultsMC_05.root");
    TList *list = g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
    
    THnSparse *fHistKorelacie = (THnSparse*)list->FindObject("fHistKorelacie");
    THnSparse *fHistMCKorelacie = (THnSparse*)list->FindObject("fHistMCKorelacie");

    const Int_t nPtBins = 6;
    const Int_t nTig =3;

)