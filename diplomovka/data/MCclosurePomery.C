#include <TH1D.h>
#include <TH2D.h>
#include <THnSparse.h>
#include <stdio.h>
#include <TFile.h>
#include "TMath.h"

void MyRebinXY(TH2D* newhist,TH2D* oldhist, Int_t rebinx, Int_t rebiny ){
    Int_t oldxbins = oldhist->GetXaxis()->GetNbins();
    Double_t minx = oldhist->GetXaxis()->GetXmin();
    Double_t maxx = oldhist->GetXaxis()->GetXmax();
    Int_t oldybins = oldhist->GetYaxis()->GetNbins();
    Double_t miny = oldhist->GetYaxis()->GetXmin();
    Double_t maxy = oldhist->GetYaxis()->GetXmax();
    
    Double_t oldCont[oldxbins][oldybins];
    Double_t oldErr[oldxbins][oldybins];
    
    for (Int_t i=0; i<oldxbins; i++) {
        for (Int_t j=0; j<oldybins; j++) {
            oldCont[i][j]=oldhist->GetBinContent(i,j);
            oldErr[i][i]=oldhist->GetBinError(i,j);
        }
    }
    
    Int_t nbinsx = oldxbins/rebinx;
    if(nbinsx*rebinx!=oldxbins) Warning("Rebin", "rebinx=%d is not an exact divider of nbinsx=%d.",rebinx,nbinsx);
    Double_t binsx[nbinsx];
    Double_t sirkaBinux = (maxx-minx)/nbinsx;
    for(Int_t i=0;i<nbinsx+1; i++){
        if(i==0) binsx[i]=minx;
        else binsx[i]= binsx[i-1]+sirkaBinux;
       // Printf("binsx[i] %g\n",binsx[i]);
    }
    newhist->GetXaxis()->Set(nbinsx,binsx);
    
    
    Int_t nbinsy = oldybins/rebiny;
    if(nbinsy*rebiny!=oldybins) Warning("Rebin", "rebiny=%d is not an exact divider of nbinsy=%d.",rebiny,nbinsy);
    Double_t binsy[nbinsy];
    Double_t sirkaBinuy = (maxy-miny)/nbinsy;
    for(Int_t i=0;i<nbinsy+1; i++){
        if(i==0) binsy[i]=miny;
        else binsy[i]= binsy[i-1]+sirkaBinuy;
      //  Printf("binsy[i] %g\n",binsy[i]);
    }
    newhist->GetYaxis()->Set(nbinsy,binsy);
    
    //TH2D * newhist = new TH2D(name, title, nbinsx, minx, maxx, nbinsy, miny, maxy);
    //Printf("nbinsx %d,minx %g, maxx %g, nbinsy %d, miny%g, maxy %g\n", nbinsx, minx, maxx, nbinsy, miny, maxy);
    
    for (Int_t i=0;i<nbinsx;i++){
        for (Int_t j=0; j<nbinsy;j++){
            Double_t newCont = 0.;
            Int_t summedBins =0;
            Double_t newError = 0;
            for (Int_t k=0;k<rebinx;k++){
                for(Int_t l=0;l<rebiny;l++){
                    
                    if (oldCont[rebinx*i+k][rebiny*j+l]!=0){
                       // Printf("oldCont %g\n",oldCont);
                        newCont+=oldCont[rebinx*i+k][rebiny*j+l];
                        summedBins+=1;
                        newError+=TMath::Power(oldErr[rebinx*i+k][rebiny*j+l],2);
                    }
                }
                //Printf("summedBins %d\n",summedBins);
               //if(newCont!=0)
                if (summedBins!=0) {
                    //Printf(" newCont %g summedBins %d newCont/summedBins %f \n",newCont, summedBins, newCont/summedBins);
                    newhist->SetBinContent(i+1,j+1,newCont/summedBins);
                }
                else newhist->Fill(i+1,j+1,0);
                if (summedBins!=0) newError=TMath::Sqrt(newError)/summedBins;
                else newError=0;
                newhist->SetBinError(i+1,j+1,newError);
            }
            
            
        }
        
    }
    

};

void MCclosurePomery(){
	//gStyle->SetOptStat(0000000000);

    TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResultsMC15c_10Grid.root");
    //TFile *g = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/AnalysisResults.root");
    TList *list = (TList*)g->Get("MyTask/MyOutputContainer"); //histogramy su v Tliste, musim nacitat najprv ten a z neho vybrat histogramy
    
    TFile *gg = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/EfiiciencyMC15c+a_04.root");
    
    TFile *g15a = new TFile("/Users/lhusova/git/diplomovka/diplomovka/data/vysledky/AnalysisResults2015a_Grid04.root");
    TList *list15a = (TList*)g->Get("MyTask/MyOutputContainer");
    
    THnSparse *fHistKorelacieRec = (THnSparse*)list->FindObject("fHistKorelacieMCrec");
    THnSparse *fHistMCKorelacie = (THnSparse*)list->FindObject("fHistMCKorelacie");
    THnSparse *fHistNumberOfTriggersGen = (THnSparse*)list->FindObject("fHistNumberOfTriggersGen");
    THnSparse *fHistNumberOfTriggersRec = (THnSparse*)list->FindObject("fHistNumberOfTriggersRec");
    
    THnSparse *fHistKorelacieRec15a = (THnSparse*)list15a->FindObject("fHistKorelacieMCrec");
    THnSparse *fHistMCKorelacie15a = (THnSparse*)list15a->FindObject("fHistMCKorelacie");
    THnSparse *fHistNumberOfTriggersGen15a = (THnSparse*)list15a->FindObject("fHistNumberOfTriggersGen");
    THnSparse *fHistNumberOfTriggersRec15a = (THnSparse*)list15a->FindObject("fHistNumberOfTriggersRec");
    //THnSparse *fHistMCMixingRec = (THnSparse*)list->FindObject("fHistMCMixingRec");
    
    fHistKorelacieRec->Add(fHistKorelacieRec15a);
    fHistMCKorelacie->Add(fHistMCKorelacie15a);
    fHistNumberOfTriggersGen->Add(fHistNumberOfTriggersGen15a);
    fHistNumberOfTriggersRec->Add(fHistNumberOfTriggersRec15a);
    
    TH3D *fHistRCPtAs = (TH3D*) gg->Get("fHistRCPtAs");
    TH3D *fHistRCPtTrigg = (TH3D*) gg->Get("fHistRCPtTrigg");
    
    TH3D *fHistEff3DK0 = (TH3D*) gg->Get("fHistRecV03DK0");
    TH3D *fHistEff3DLam = (TH3D*) gg->Get("fHistRecV03DLam");
    TH3D *fHistEff3DALam = (TH3D*) gg->Get("fHistRecV03DAntiLam");
    
    TH1D * fHistK0EffPt = (TH1D*) gg->Get("histV0RecK0");
    TH1D * fHistLamEffPt = (TH1D*) gg->Get("histV0RecLam");
    TH1D * fHistALamEffPt = (TH1D*) gg->Get("histV0RecALam");
    TH1D * fHisthadrEffPt = (TH1D*) gg->Get("fHistRCPtAsProjX");
    TH1D * fHistAssocEffPt = (TH1D*) gg->Get("fHistRCPtAsProjX");

    const Double_t kPi = TMath::Pi();
    const Int_t nPtBins = 6;
    const Int_t nTig =3;

   // Printf ("x %d y %d z %d\n",fHistRCPtAs->GetXaxis()->GetNbins(),fHistRCPtAs->GetYaxis()->GetNbins(),fHistRCPtAs->GetZaxis()->GetNbins());
   
    const Int_t nEtaBins = fHistKorelacieRec->GetAxis(7)->GetNbins();
   // Printf("nEtaBins %d\n",nEtaBins);
    const Int_t nVzBins = fHistKorelacieRec->GetAxis(4)->GetNbins();
    const Int_t nPtAssocBins = fHistKorelacieRec->GetAxis(1)->GetNbins();
    const Int_t nPtTrigBins = fHistKorelacieRec->GetAxis(0)->GetNbins();

    THnSparse **fHistCorTypeMC=new THnSparse*[nTig];
    THnSparse **fHistRangePtMC=new THnSparse*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtaMC = new TH2D*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtaMCProj = new TH2D*[nTig*nPtBins];
    char htitle[50];
    char hname[50];
    char hnameMix[50];
    char hnamerec[50];
    TCanvas *cMC = new TCanvas;
    cMC->Divide(nPtBins,nTig);

    THnSparse **fHistCorTyperec=new THnSparse*[nTig];
    THnSparse **fHistMixTyperec=new THnSparse*[nTig];
    THnSparse **fHistRangePtrec=new THnSparse*[nTig*nPtBins];
    //THnSparse **fHistRangePtMixrec=new THnSparse*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtarec = new TH2D*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtarecProj = new TH2D*[nTig*nPtBins];
    TH2D **fHistRangePtProjPhiEtarecTmp = new TH2D*[nTig*11];
    TH2D **fHistRangePtProjPhiEtaMixrec = new TH2D*[nTig*nPtBins];
    TH1D **fHistNumberOfTriggTmp = new TH1D*[nTig*11];
    TH1D **fHistNumberOfTrigg = new TH1D*[nTig*nPtBins];

    TCanvas *cMCrec = new TCanvas;
    cMCrec->Divide(nPtBins,nTig);

    TH1D **fHistProjPhi=new TH1D*[nTig*nPtBins];
    char hnamePom[50]; 
    TH1D **fHistProjEta=new TH1D*[nTig*nPtBins];
    char hnameEta[50]; 


    TCanvas *cpomery = new TCanvas;
    cpomery->Divide(nPtBins,nTig);

    TCanvas *phiMC = new TCanvas;
    phiMC->Divide(nPtBins,nTig);
    TCanvas *etaMC = new TCanvas;
    etaMC->Divide(nPtBins,nTig);

    TCanvas *phiRec = new TCanvas;
    phiRec->Divide(nPtBins,nTig);
    TCanvas *etaRec = new TCanvas;
    etaRec->Divide(nPtBins,nTig);

    TCanvas *cpomeryPhi = new TCanvas;
    cpomeryPhi->Divide(nPtBins,nTig);
    TCanvas *cpomeryEta = new TCanvas;
    cpomeryEta->Divide(nPtBins,nTig);


    TH1D **fHistPartGen = new TH1D*[nPtBins];
    THnSparse **fHistPartCloneGen = new THnSparse*[nPtBins];
    char hnameentgen[50];
    char hname2dvela[50];
    char hname1dvela[50];

    TH1D **fHistPartRec = new TH1D*[nPtBins];
    TH1D **fHistPartRecStare = new TH1D*[nPtBins];
    THnSparse **fHistPartCloneRec = new THnSparse*[11];
    char hnameentrec[50];
    TCanvas *gen=new TCanvas();
    gen->Divide(1,nPtBins);

    TCanvas *rec=new TCanvas();
    rec->Divide(1,nPtBins);
    
    TCanvas *recNove=new TCanvas();
    recNove->Divide(1,nPtBins);
    
    Double_t sclaleAssoc[20][10][13];
    Double_t sclaleTrigg[20][10][11];
    Double_t sclaleK0[20][10][11];
    Double_t sclaleLam[20][10][11];
    Double_t sclaleAntiL[20][10][11];
    
    Double_t effTrigg[4][11];
    Double_t effAssoc[13];
    
    Int_t k3D =0;
    for(Int_t k=0;k<nEtaBins; k++){
        Int_t l3D =0;
       // for (Int_t l=0; l<nVzBins; l++) {
         ///   Printf("l citanie %d \n",l);*/
            for (Int_t m=0; m<nPtAssocBins; m++){
                // Printf("%g %d %d %d \n",fHistRCPtAs->GetBinContent(m+1,l3D+1,k3D+1),k,l,m);
                sclaleAssoc[k3D][l3D][m]=fHistRCPtAs->GetBinContent(m+1,5,k3D+1);
              //  Printf("scale assoc %g \n",sclaleAssoc[k3D][l3D][m]);
               // effAssoc[m]=fHistAssocEffPt->GetBinContent(m+1);
            }
            
            for (Int_t m=0; m<11; m++){
                sclaleTrigg[k3D][l3D][m]=fHistRCPtTrigg->GetBinContent(m+1,5,k3D+1);
                sclaleK0[k3D][l3D][m]=fHistEff3DK0->GetBinContent(m+1,5,k3D+1);
                sclaleLam[k3D][l3D][m]=fHistEff3DLam->GetBinContent(m+1,5,k3D+1);
                sclaleAntiL[k3D][l3D][m]=fHistEff3DALam->GetBinContent(m+1,5,k3D+1);
            }
        
            
            //    effTrigg[0][m] = fHistK0EffPt ->GetBinContent(m+3);
            //    effTrigg[1][m] = fHistLamEffPt ->GetBinContent(m+3);
            //    effTrigg[2][m] =fHistALamEffPt ->GetBinContent(m+3);
            //    effTrigg[3][m] = fHisthadrEffPt ->GetBinContent(m+3);
            //    Printf("m citanie %d\n",m);
                
        
      /*
            l3D+=1;
            l+=1;
        }*/
        
        
        k+=1;
        k3D+=1;
    }
   
    Double_t fitPhiHodnoty[nTig][nPtBins];
    Double_t fitPhiChyby[nTig][nPtBins];
    Double_t fitEtaHodnoty[nTig][nPtBins];
    Double_t fitEtaChyby[nTig][nPtBins];
    Double_t ptBins[nPtBins]={4.5,5.5,6.5,8,10,13.5};
    Double_t ptBinsChyby[nPtBins]={0.5,0.5,0.5,1,1,2.5};

    for(Int_t i=0;i<11;i++){
        fHistPartCloneGen[i]=(THnSparse *)fHistNumberOfTriggersGen->Clone();
        if (i==0) fHistPartCloneGen[i]->GetAxis(0)->SetRange(1,1);
        if (i==1) fHistPartCloneGen[i]->GetAxis(0)->SetRange(2,2);
        if (i==2) fHistPartCloneGen[i]->GetAxis(0)->SetRange(3,3);
        if (i==3) fHistPartCloneGen[i]->GetAxis(0)->SetRange(4,5);
        if (i==4) fHistPartCloneGen[i]->GetAxis(0)->SetRange(6,7);
        if (i==5) fHistPartCloneGen[i]->GetAxis(0)->SetRange(8,11);
        fHistPartGen[i] = fHistPartCloneGen[i]->Projection(3);
        sprintf(hnameentgen,"proj_%dgen",i);
        fHistPartGen[i]->SetName(hnameentgen);

        fHistPartCloneRec[i]=(THnSparse *)fHistNumberOfTriggersRec->Clone();
        //if (i==0)
            fHistPartCloneRec[i]->GetAxis(0)->SetRange(i+1,i+1);
     /*   if (i==1) fHistPartCloneRec[i]->GetAxis(0)->SetRange(2,2);
        if (i==2) fHistPartCloneRec[i]->GetAxis(0)->SetRange(3,3);
        if (i==3) fHistPartCloneRec[i]->GetAxis(0)->SetRange(4,5);
        if (i==4) fHistPartCloneRec[i]->GetAxis(0)->SetRange(6,7);
        if (i==5) fHistPartCloneRec[i]->GetAxis(0)->SetRange(8,11);*/
        fHistPartRec[i] = fHistPartCloneRec[i]->Projection(3);
        sprintf(hnameentrec,"proj_%drec",i);
        fHistPartRec[i]->SetName(hnameentrec);

        gen->cd(i+1);
        fHistPartGen[i]->DrawCopy();
       /* rec->cd(i+1);
        fHistPartRec[i]->DrawCopy();*/

    }
    char nameEff[20];

    
    TFile *fNewFil = TFile::Open("McClosure15c+a_04_Kh_betterBinning_withoutPvz.root","RECREATE");
    for(Int_t i=0;i<1;i++){   // loop cez druhy triggra
        
        if(i==0) fHistMCKorelacie->GetAxis(5)->SetRange(i+1,i+1);
        if(i==1) fHistMCKorelacie->GetAxis(5)->SetRange(i+1,i+2);
        if(i==2) fHistMCKorelacie->GetAxis(5)->SetRange(i+2,i+2);

        if(i==0) fHistKorelacieRec->GetAxis(5)->SetRange(i+1,i+1);
        if(i==1) fHistKorelacieRec->GetAxis(5)->SetRange(i+1,i+2);
        if(i==2) fHistKorelacieRec->GetAxis(5)->SetRange(i+2,i+2);
        
        for(Int_t j=0;j<11;j++){ // loop cez pt triggra
            Printf("j %d\n",j);
            if (j==0) fHistMCKorelacie->GetAxis(0)->SetRange(1,1);
            if (j==1) fHistMCKorelacie->GetAxis(0)->SetRange(2,2);
            if (j==2) fHistMCKorelacie->GetAxis(0)->SetRange(3,3);
            if (j==3) fHistMCKorelacie->GetAxis(0)->SetRange(4,5);
            if (j==5) fHistMCKorelacie->GetAxis(0)->SetRange(6,7);
            if (j==7) fHistMCKorelacie->GetAxis(0)->SetRange(8,11);
            
            if(j<4){
                fHistRangePtProjPhiEtaMC[i*nPtBins+j] = (TH2D *)fHistMCKorelacie->Projection(2,3);
                sprintf(hname,"2dproj_%d_pt_%d",i,j);
                fHistRangePtProjPhiEtaMC[i*nPtBins+j]->SetName(hname);
                sprintf(htitle,"Gen #Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,j);
                fHistRangePtProjPhiEtaMC[i*nPtBins+j]->SetTitle(htitle);
          //      fHistRangePtProjPhiEtaMC[i*nPtBins+j] = MyRebinXY(fHistRangePtProjPhiEtaMCProj[i*nPtBins+j],hname,htitle,2,2);
                fHistRangePtProjPhiEtaMC[i*nPtBins+j]->RebinX(2);
                fHistRangePtProjPhiEtaMC[i*nPtBins+j]->RebinY(4);
            }
            if(j==5){
                fHistRangePtProjPhiEtaMC[i*nPtBins+4] = (TH2D *)fHistMCKorelacie->Projection(2,3);
               // fHistRangePtProjPhiEtaMCProj[i*nPtBins+4]->SetName("MC4");
               // fHistRangePtProjPhiEtaMC[i*nPtBins+4]=(TH2D*)fHistRangePtProjPhiEtaMCProj[i*nPtBins+4]->Clone();
                sprintf(hname,"2dproj_%d_pt_%d",i,4);
                fHistRangePtProjPhiEtaMC[i*nPtBins+4]->SetName(hname);
                sprintf(htitle,"Gen #Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,4);
                fHistRangePtProjPhiEtaMC[i*nPtBins+4]->SetTitle(htitle);
               // MyRebinXY(fHistRangePtProjPhiEtaMC[i*nPtBins+4],fHistRangePtProjPhiEtaMCProj[i*nPtBins+4],4,6);
                
            fHistRangePtProjPhiEtaMC[i*nPtBins+4]->RebinX(2);
            fHistRangePtProjPhiEtaMC[i*nPtBins+4]->RebinY(4);
               // fHistRangePtProjPhiEtaMC[i*nPtBins+4]->Write();
        }
            if(j==7){
                fHistRangePtProjPhiEtaMC[i*nPtBins+5] = (TH2D *)fHistMCKorelacie->Projection(2,3);
                //fHistRangePtProjPhiEtaMCProj[i*nPtBins+5]->SetName("MC5");
               // fHistRangePtProjPhiEtaMC[i*nPtBins+5]=(TH2D*)fHistRangePtProjPhiEtaMCProj[i*nPtBins+5]->Clone();
                sprintf(hname,"2dproj_%d_pt_%d",i,5);
                fHistRangePtProjPhiEtaMC[i*nPtBins+5]->SetName(hname);
                sprintf(htitle,"Gen #Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,5);
                fHistRangePtProjPhiEtaMC[i*nPtBins+5]->SetTitle(htitle);
               // MyRebinXY(fHistRangePtProjPhiEtaMC[i*nPtBins+5],fHistRangePtProjPhiEtaMCProj[i*nPtBins+5],2,3);
                //fHistRangePtProjPhiEtaMC[i*nPtBins+5]->Write();
                fHistRangePtProjPhiEtaMC[i*nPtBins+5]->RebinX(2);
               fHistRangePtProjPhiEtaMC[i*nPtBins+5]->RebinY(4);
            }

            //if (j==0)
                fHistKorelacieRec->GetAxis(0)->SetRange(j+1,j+1);
          /*  if (j==1) fHistKorelacieRec->GetAxis(0)->SetRange(2,2);
            if (j==2) fHistKorelacieRec->GetAxis(0)->SetRange(3,3);
            if (j==3) fHistKorelacieRec->GetAxis(0)->SetRange(4,5);
            if (j==4) fHistKorelacieRec->GetAxis(0)->SetRange(6,7);
            if (j==5) fHistKorelacieRec->GetAxis(0)->SetRange(8,11);*/

           //  sprintf(nameEff,"eff_%d_%d",i,j);
           //  TH1D *fHistEff = (TH1D*) gg->Get(nameEff);

            Int_t l3D = 0;
            Int_t nHist =0;
            Int_t nHistTrig =0;

          /*  for(Int_t l=0;l<nVzBins ; l++){ //loop cez vertex biny
                Printf(" ----------- l %d --------------------- \n",l);

                fHistKorelacieRec->GetAxis(4)->SetRange(l+1,l+2);
                
                fHistPartCloneRec[j]->GetAxis(1)->SetRange(l+1,l+2);*/
                Int_t k3D =0;

                for (Int_t k=0; k<nEtaBins; k++) {//loop cez eta trigg
               
                    fHistKorelacieRec->GetAxis(6)->SetRange(k+1,k+2);
                    
                    fHistPartCloneRec[j]->GetAxis(2)->SetRange(k+1,k+2);
           
           

                    Printf("+++++ k %d ++++++ \n",k );
                    TH1D * proj1DTrigg = (TH1D *)fHistPartCloneRec[j]->Projection(3);
                    sprintf(hname1dvela,"1D_%d_%d",j,k3D);
                    proj1DTrigg->SetName(hname1dvela);
                    
                    Double_t scaleTrigg = fHistRCPtAs->GetBinContent(j+2,5,k3D+1);
                    if(i==0){
                        if(sclaleK0[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(1,proj1DTrigg->GetBinContent(1)/sclaleK0[k3D][l3D][j]);
                       // else proj1DTrigg->SetBinContent(1,proj1DTrigg->GetBinContent(1)/effTrigg[0][j]);
                    }
                    
                    if(i==1){
                        if(sclaleLam[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(2,proj1DTrigg->GetBinContent(2)/sclaleLam[k3D][l3D][j]);
                       // else proj1DTrigg->SetBinContent(2,proj1DTrigg->GetBinContent(2)/effTrigg[1][j]);
                    
                        if(sclaleAntiL[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(3,proj1DTrigg->GetBinContent(3)/sclaleAntiL[k3D][l3D][j]);
                        //else  proj1DTrigg->SetBinContent(3,proj1DTrigg->GetBinContent(3)/effTrigg[2][j]);
                    }
                   
                    if(i==2){
                       // if(sclaleTrigg[k3D][l3D][j]!=0) proj1DTrigg->SetBinContent(4,proj1DTrigg->GetBinContent(4)/sclaleTrigg[k3D][l3D][j]);
                        if(scaleTrigg!=0) proj1DTrigg->SetBinContent(4,proj1DTrigg->GetBinContent(4)/scaleTrigg);
                        //else proj1DTrigg->SetBinContent(4,proj1DTrigg->GetBinContent(4)/effTrigg[3][j]);
                    }
                 
                    if (nHistTrig==0) fHistNumberOfTriggTmp[i*11+j] =(TH1D *)proj1DTrigg->Clone();
                    else fHistNumberOfTriggTmp[i*11+j]->Add(proj1DTrigg);
                    nHistTrig+=1;
                    
                  
                    Int_t n3D =0;
                    for (Int_t n=0; n<nEtaBins; n++) { // loop cez eta assoc
                        Printf("n %d\n",n);
                        fHistKorelacieRec->GetAxis(7)->SetRange(n+1,n+2);
                        
                        for (Int_t m=0; m<j+3; m++){ // loop cez pt assoc
                            
                            fHistKorelacieRec->GetAxis(1)->SetRange(m+1,m+1);
                            
                            TH2D * proj2DRac = (TH2D *)fHistKorelacieRec->Projection(2,3);
                            sprintf(hname2dvela,"2D_%d_%d_%d",m,k3D,n3D);
                            proj2DRac->SetName(hname2dvela);
                            
                            //Printf("max pred kor %g\n", proj2DRac->GetMaximum());
                            Double_t scaleassoc = fHistRCPtAs->GetBinContent(m+1,5,n3D+1);
                            if (scaleassoc!=0) proj2DRac->Scale(1./scaleassoc);
                            //else
                          //  Double_t  sscl = fHistEff->GetBinContent(m+1);
                          //  if (sscl!=0)  proj2DRac->Scale(1./sscl); //effAssoc[m]);
                          /*  if (n==1&&sclaleAssoc[1][l][m]!=0) proj2DRac->Scale(1./sclaleAssoc[1][l3D][m]);
                            if (n==2&&sclaleAssoc[2][l][m]!=0) proj2DRac->Scale(1./sclaleAssoc[2][l3D][m]);
                            if (n==3&&sclaleAssoc[3][l][m]!=0) proj2DRac->Scale(1./sclaleAssoc[3][l3D][m]);
                            if (n==4&&sclaleAssoc[4][l][m]!=0) proj2DRac->Scale(1./sclaleAssoc[4][l3D][m]);
                            if (n==5&&sclaleAssoc[5][l][m]!=0) proj2DRac->Scale(1./sclaleAssoc[5][l3D][m]);
                            if (n==6&&sclaleAssoc[6][l][m]!=0) proj2DRac->Scale(1./sclaleAssoc[6][l3D][m]);
                            if (n==7&&sclaleAssoc[7][l][m]!=0) proj2DRac->Scale(1./sclaleAssoc[7][l3D][m]);
                            if (n==8&&sclaleAssoc[8][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[8][l3D][m]);
                            if (n==9&&sclaleAssoc[9][l3D][m]!=0) proj2DRac->Scale(1./sclaleAssoc[9][l3D][m]);*/

                            
                            if(i==0&&sclaleK0[k3D][l3D][j]!=0) proj2DRac->Scale(1./sclaleK0[k3D][l3D][j]);
                           // if(i==0/*&&sclaleK0[k3D][l3D][j]==0*/) proj2DRac->Scale(1./effTrigg[0][j]);
                            
                            if(i==1&&sclaleLam[k3D][l3D][j]!=0&&sclaleAntiL[k3D][l3D][j]!=0){
                                Double_t scalelamAntilam = (sclaleLam[k3D][l3D][j]+sclaleAntiL[k3D][l3D][j])/2;
                                proj2DRac->Scale(1./scalelamAntilam);
                            }
                          //  if(i==1/*&&(sclaleLam[k3D][l3D][j]==0||sclaleAntiL[k3D][l3D][j]==0)*/) proj2DRac->Scale(1./((effTrigg[2][j]+effTrigg[1][j])/2));

                            if(i==2&&scaleTrigg!=0) proj2DRac->Scale(1./scaleTrigg);
                          //  if(i==2/*&&sclaleTrigg[k3D][l3D][j]==0*/) proj2DRac->Scale(1./effTrigg[3][j]);
                            
                         /*  if(fHistEff->GetBinContent(m+1,l3D+1,n+1)!=0){
                                proj2DRac->Scale(1./fHistEff->GetBinContent(m+1,l3D+1,n+1));
                                Printf("%g\n",fHistEff->GetBinContent(m+1,l3D+1,n+1));
                            }*/
                          //  Printf("max po kor trigg %g\n", proj2DRac->GetMaximum());
                            if (nHist==0) fHistRangePtProjPhiEtarecTmp[i*11+j] =(TH2D *)proj2DRac->Clone();
                            else fHistRangePtProjPhiEtarecTmp[i*11+j]->Add(proj2DRac);
                            nHist+=1;
                            
                            delete proj2DRac;
                            fHistKorelacieRec->GetAxis(1)->SetRange(0,-1);
                            
                        }
            //delete fHistEff;
                        fHistKorelacieRec->GetAxis(7)->SetRange(0,-1);
                        n+=1;
                        n3D+=1;
                        
                    }

                    delete proj1DTrigg;

                    fHistKorelacieRec->GetAxis(6)->SetRange(0,-1);
                   fHistPartCloneRec[j]->GetAxis(2)->SetRange(0,-1);
                    
                    k+=1;
                    k3D+=1;
                    
                }
             /*
                fHistKorelacieRec->GetAxis(4)->SetRange(0,-1);
                fHistPartCloneRec[j]->GetAxis(1)->SetRange(0,-1);
                l3D+=1;
                l+=1;
            }*/
            
            if(j==0||j==1||j==2||j==3){
                fHistNumberOfTrigg[i*nPtBins+j] = (TH1D*) fHistNumberOfTriggTmp[i*11+j] -> Clone();
                fHistRangePtProjPhiEtarecProj[i*nPtBins+j] = (TH2D*)fHistRangePtProjPhiEtarecTmp[i*11+j] ->Clone();
                sprintf(hnamerec,"2dproj_%d_pt_%d",i,j);
                fHistRangePtProjPhiEtarecProj[i*nPtBins+j]->SetName(hnamerec);
            }
            if(j==4){
                fHistNumberOfTrigg[i*nPtBins+j-1]->Add(fHistNumberOfTriggTmp[i*11+j]);
                fHistRangePtProjPhiEtarecProj[i*nPtBins+j-1]->Add(fHistRangePtProjPhiEtarecTmp[i*11+j]);
            }
            
            if(j==5){
                fHistNumberOfTrigg[i*nPtBins+4] = (TH1D*) fHistNumberOfTriggTmp[i*11+j] -> Clone();
                fHistRangePtProjPhiEtarecProj[i*nPtBins+4] = (TH2D*)fHistRangePtProjPhiEtarecTmp[i*11+j] ->Clone();
                sprintf(hnamerec,"2dproj_%d_pt_%d",i,4);
                fHistRangePtProjPhiEtarecProj[i*nPtBins+4]->SetName(hnamerec);
            }
            if(j==6){
                fHistNumberOfTrigg[i*nPtBins+4]->Add(fHistNumberOfTriggTmp[i*11+j]);
                fHistRangePtProjPhiEtarecProj[i*nPtBins+4]->Add(fHistRangePtProjPhiEtarecTmp[i*11+j]);
            }
            if(j==7){
                fHistNumberOfTrigg[i*nPtBins+5] = (TH1D*) fHistNumberOfTriggTmp[i*11+j] -> Clone();
                fHistRangePtProjPhiEtarecProj[i*nPtBins+5] = (TH2D*)fHistRangePtProjPhiEtarecTmp[i*11+j] ->Clone();
                sprintf(hnamerec,"2dproj_%d_pt_%d",i,5);
                fHistRangePtProjPhiEtarecProj[i*nPtBins+5]->SetName(hnamerec);
            }
            if(j==8||j==9||j==10){
                fHistNumberOfTrigg[i*nPtBins+5]->Add(fHistNumberOfTriggTmp[i*11+j]);
                fHistRangePtProjPhiEtarecProj[i*nPtBins+5]->Add(fHistRangePtProjPhiEtarecTmp[i*11+j]);
            }
            
             Printf("nHist %d\n",nHist);
            fHistMCKorelacie->GetAxis(0)->SetRange(0,-1);
            fHistKorelacieRec->GetAxis(0)->SetRange(0,-1);
        }
       
        fHistKorelacieRec->GetAxis(5)->SetRange(0,-1);
        fHistMCKorelacie->GetAxis(5)->SetRange(0,-1);
    }
    for(Int_t i=0;i<1;i++){   // looop cez druhy triggra
        
        for(Int_t j=0;j<6;j++){ // loop cez pt triggra
            
            
            if(i==0) fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Scale(1./(fHistPartGen[j]->GetBinContent(1)));
            if(i==1) fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Scale(1./(fHistPartGen[j]->GetBinContent(2)+fHistPartGen[j]->GetBinContent(3)));
            if(i==2) fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Scale(1./(fHistPartGen[j]->GetBinContent(4)));
            cMC->cd(i*nPtBins+j+1);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->DrawCopy("lego2z");
            
            sprintf(htitle,"Rec #Delta #Phi vs. #Delta #eta pre trigger %d pre pt int %d", i,j);
            sprintf(hnamerec,"2dproj_%d_pt_%d",i,j);

           // Printf("%p\n",fHistRangePtProjPhiEtarecProj[i*nPtBins+j]);
            fHistRangePtProjPhiEtarec[i*nPtBins+j] = (TH2D*)fHistRangePtProjPhiEtarecProj[i*nPtBins+j]->Clone();
           // Printf("%p\n",fHistRangePtProjPhiEtarec[i*nPtBins+j]);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->SetName(hnamerec);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->SetTitle(htitle);
            //MyRebinXY(fHistRangePtProjPhiEtarec[i*nPtBins+j],fHistRangePtProjPhiEtarecProj[i*nPtBins+j],4,6);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->RebinX(2);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->RebinY(4);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->Write();
            
           // fHistRangePtProjPhiEtarec[i*nPtBins+j]->SetTitle(htitle);
           //
            
            if(i==0) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistNumberOfTrigg[i*nPtBins+j]->GetBinContent(1)));
            if(i==1) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistNumberOfTrigg[i*nPtBins+j]->GetBinContent(2)+fHistNumberOfTrigg[i*nPtBins+j]->GetBinContent(3)));
            if(i==2) fHistRangePtProjPhiEtarec[i*nPtBins+j]->Scale(1./(fHistNumberOfTrigg[i*nPtBins+j]->GetBinContent(4)));

            cMCrec->cd(i*nPtBins+j+1);
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->DrawCopy("lego2z");

            Printf("maimum gen %g, max rec %g\n",fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetMaximum(),fHistRangePtProjPhiEtarec[i*nPtBins+j]->GetMaximum());
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Write();
            fHistRangePtProjPhiEtarec[i*nPtBins+j]->Write();
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Divide(fHistRangePtProjPhiEtarec[i*nPtBins+j]);
            fHistRangePtProjPhiEtaMC[i*nPtBins+j]->Write();
            Printf("bin cont %g, nbinsX %d, nBinsy %d \n ", fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(25,12),fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetXaxis()->GetNbins(),fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetYaxis()->GetNbins());
            
           // fHistRangePtProjPhiEtaMC[i*nPtBins+j]->SetAxisRange(-1,1,"x");
            Int_t nBinsEta = fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetXaxis()->GetNbins();
            Int_t minEta = fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetXaxis()->GetXmin();
            Int_t maxEta = fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetXaxis()->GetXmax();
            Int_t nBinsPhi = fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetYaxis()->GetNbins();
            Int_t minPhi = fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetYaxis()->GetXmin();
            Int_t maxPhi = fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetYaxis()->GetXmax();
            
            sprintf(hnamePom,"hnamePom%d%d",i,j);
            fHistProjPhi[i*nPtBins+j]= new TH1D (hnamePom,hnamePom,nBinsPhi,minPhi,maxPhi);
            for (Int_t k=0; k<(nBinsPhi); k++){
                Double_t scalePhi=0.;
                Double_t chybaPhi=0.;
                Double_t hodnotaPhi = 0.;
                for(Int_t l=0; l<(nBinsEta); l++){
                    if(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(l+1,k+1)>0) {
                        scalePhi++;
                        hodnotaPhi+=fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(l+1,k+1);
                        chybaPhi+=TMath::Power(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinError(l+1,k+1),2);
                    }
                }
                if (i==1&&j==5) Printf("scalePhi %g \n", scalePhi);
                if(scalePhi>0) fHistProjPhi[i*nPtBins+j]->SetBinContent(k+1,hodnotaPhi/scalePhi);
                else fHistProjPhi[i*nPtBins+j]->SetBinContent(k+1,0);
                chybaPhi=TMath::Sqrt(chybaPhi);
                if(scalePhi>0) chybaPhi=chybaPhi/scalePhi;
                else chybaPhi=0;
                fHistProjPhi[i*nPtBins+j]->SetBinError(k+1,chybaPhi);
            }
            
            fHistProjPhi[i*nPtBins+j]->Write();

            sprintf(hnameEta,"hnameEta%d%d",i,j);
            fHistProjEta[i*nPtBins+j] = new TH1D (hnameEta,hnameEta,nBinsEta,minEta,maxEta);

            for (Int_t k=0; k<(nBinsEta); k++){
                Double_t hodnotaEta=0.;
                Double_t scaleEta=0.;
                Double_t chybaEta=0.;
                for(Int_t l=0; l<(nBinsPhi); l++){
                    //Printf("%g\n",fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(k+1,l+1));
                    if(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(k+1,l+1)>0) {
                        scaleEta++;
                        chybaEta+=TMath::Power(fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinError(k+1,l+1),2);
                        hodnotaEta+=fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetBinContent(k+1,l+1);
                    }
                    
                }
                //  Printf("scaleEta %g , hodnotaEta %g \n", scaleEta,hodnotaEta);
                
                if(scaleEta>0) fHistProjEta[i*nPtBins+j]->SetBinContent(k+1,(hodnotaEta)/scaleEta);
                else fHistProjEta[i*nPtBins+j]->SetBinContent(k+1,0);
                chybaEta=TMath::Sqrt(chybaEta);
                if (scaleEta>0) chybaEta=chybaEta/scaleEta;
                else chybaEta=0;
                fHistProjEta[i*nPtBins+j]->SetBinError(k+1,chybaEta);
            }
            

            fHistProjEta[i*nPtBins+j]->Write();

            
            Printf("bins eta %d phi %d \n",nBinsEta,nBinsPhi);
           

            

            

           // fHistProjPhi[i*nPtBins+j]->Scale(1./scalePhi);
            //fHistProjEta[i*nPtBins+j]->Scale(1./scaleEta);

        /*    TF1 *fitPhi = new TF1("fitphi"," [0]",-kPi/2, -kPi/2+2*kPi);
            fitPhi->SetParameter(0,1);
            cpomeryPhi->cd(i*nPtBins+j+1);
            fHistProjPhi[i*nPtBins+j]->SetAxisRange(0,2,"y");
            fHistProjPhi[i*nPtBins+j]->DrawCopy();
            fHistProjPhi[i*nPtBins+j]->Fit(fitPhi);
            fitPhiHodnoty[i][j]=fitPhi->GetParameter(0);
            fitPhiChyby[i][j]=fitPhi->GetParError(0);
            Printf("phi param %g \n", fitPhi->GetParameter(0));
            fHistProjPhi[i*nPtBins+j]->Write();

            TF1 *fitEta = new TF1("fitEta"," [0]",-1, 1);
            fitEta->SetParameter(0,1);
            cpomeryEta->cd(i*nPtBins+j+1);
            fHistProjEta[i*nPtBins+j]->SetAxisRange(-1.5,1.5,"x");
            fHistProjEta[i*nPtBins+j]->SetAxisRange(0,2,"y");
            fHistProjEta[i*nPtBins+j]->DrawCopy();
            fHistProjEta[i*nPtBins+j]->Fit(fitEta);
            fitEtaHodnoty[i][j]=fitEta->GetParameter(0);
            fitEtaChyby[i][j]=fitEta->GetParError(0);
            Printf("eta param %g \n", fitEta->GetParameter(0));
            fHistProjEta[i*nPtBins+j]->Write();
            
            delete fitPhi;
            delete fitEta;*/
            
           // cpomery->cd(i*nPtBins+j+1);
          //  fHistRangePtProjPhiEtaMC[i*nPtBins+j]->GetXaxis()->SetRangeUser(-1.5,1.5);
            //fHistRangePtProjPhiEtaMC[i*nPtBins+j]->DrawCopy("colz");
            
        }
        
    }
    Printf("a");
   /* TGraphErrors * k0Phi = new TGraphErrors(nPtBins,ptBins,fitPhiHodnoty[0],ptBinsChyby,fitPhiChyby[0]);
    TGraphErrors * k0Eta = new TGraphErrors(nPtBins,ptBins,fitEtaHodnoty[0],ptBinsChyby,fitEtaChyby[0]);
    
    TGraphErrors * LamPhi = new TGraphErrors(nPtBins,ptBins,fitPhiHodnoty[1],ptBinsChyby,fitPhiChyby[1]);
    TGraphErrors * LamEta = new TGraphErrors(nPtBins,ptBins,fitEtaHodnoty[1],ptBinsChyby,fitEtaChyby[1]);
    
    TGraphErrors * hPhi = new TGraphErrors(nPtBins,ptBins,fitPhiHodnoty[2],ptBinsChyby,fitPhiChyby[2]);
    TGraphErrors * hEta = new TGraphErrors(nPtBins,ptBins,fitEtaHodnoty[2],ptBinsChyby,fitEtaChyby[2]);
    Printf("b");
    TCanvas *graphK0Phi = new TCanvas;
    k0Phi->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger K_{0}_{S}, phi projekcia");
    k0Phi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    k0Phi->GetYaxis()->SetTitle("hodnota fitu");
    k0Phi->SetMarkerStyle(23);
    k0Phi->SetMarkerColor(kBlue);
    k0Phi->SetLineColor(kBlue);
    k0Phi->SetMarkerSize(1.8);
    k0Phi->Draw("ap");
    TCanvas *graphK0Eta = new TCanvas;
    k0Eta->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger K_{0}_{S}, eta projekcia");
    k0Eta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    k0Eta->GetYaxis()->SetTitle("hodnota fitu");
    k0Eta->SetMarkerStyle(23);
    k0Eta->SetMarkerColor(kBlue);
    k0Eta->SetLineColor(kBlue);
    k0Eta->SetMarkerSize(1.8);
    k0Eta->Draw("ap");
    Printf("c");
    TCanvas *graphLamPhi = new TCanvas;
    LamPhi->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger  #{Lambda}+#bar{#Lambda}, phi projekcia");
    LamPhi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    LamPhi->GetYaxis()->SetTitle("hodnota fitu");
    LamPhi->SetMarkerStyle(23);
    LamPhi->SetMarkerColor(kBlue);
    LamPhi->SetLineColor(kBlue);
    LamPhi->SetMarkerSize(1.8);
    LamPhi->Draw("ap");
    TCanvas *graphLamEta = new TCanvas;
    LamEta->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger #Lambda+#bar{#Lambda}, eta projekcia");
    LamEta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    LamEta->GetYaxis()->SetTitle("hodnota fitu");
    LamEta->SetMarkerStyle(23);
    LamEta->SetMarkerColor(kBlue);
    LamEta->SetLineColor(kBlue);
    LamEta->SetMarkerSize(1.8);
    LamEta->Draw("ap");
    Printf("d");
    TCanvas *graphhhPhi = new TCanvas;
    hPhi->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger h, phi projekcia");
    hPhi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    hPhi->GetYaxis()->SetTitle("hodnota fitu");
    hPhi->GetYaxis()->SetRangeUser(0.9,1.1);
    hPhi->SetMarkerStyle(23);
    hPhi->SetMarkerColor(kBlue);
    hPhi->SetLineColor(kBlue);
    hPhi->SetMarkerSize(1.8);
    hPhi->Draw("ap");
    TCanvas *graphhEta = new TCanvas;
    hEta->SetTitle("Zavislost hodnoty fitu od p_{T} pre trigger h, eta projekcia");
    hEta->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    hEta->GetYaxis()->SetTitle("hodnota fitu");
    hEta->GetYaxis()->SetRangeUser(0.9,1.1);
    hEta->SetMarkerStyle(23);
    hEta->SetMarkerColor(kBlue);
    hEta->SetLineColor(kBlue);
    hEta->SetMarkerSize(1.8);
    hEta->Draw("ap");
    Printf("e");
    k0Phi->Write();
    k0Eta->Write();
    LamPhi->Write();
    LamEta->Write();
    hPhi->Write();
    hEta->Write();
    Printf("f");*/
    fNewFil->Close();

}

