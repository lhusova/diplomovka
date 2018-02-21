/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* AliAnaysisTaskMyTask
 *
 * empty task which can serve as a starting point for building an analysis
 * as an example, one histogram is filled
 */

#include <TChain.h>
#include <TH1F.h>
#include <TH3F.h>
#include <TH1D.h>
#include <TList.h>
#include <AliAnalysisTask.h>
#include <AliAnalysisManager.h>
#include "AliAODTrack.h"
#include <AliAODEvent.h>
#include "AliAODv0.h"
#include <AliAODInputHandler.h>
#include "AliAnalysisTaskMyTask.h"
#include <TMath.h>
#include <AliMultiEventInputHandler.h>
#include <AliPIDResponse.h>
#include <AliAODPid.h>
#include <THnSparse.h>
#include <AliAODVertex.h>
#include <AliEventPoolManager.h>
#include <AliMixInputEventHandler.h>
#include "AliAODMCParticle.h"
#include "AliMultSelection.h"
#include "AliPPVsMultUtils.h"

class AliPIDResponse;
class AliAnalysisTaskMyTask;    // your analysis class

using namespace std;            // std namespace: so you can do things like 'cout'

ClassImp(AliAnalysisTaskMyTask) // classimp: necessary for root

AliAnalysisTaskMyTask::AliAnalysisTaskMyTask() : AliAnalysisTaskSE(), 
    fAOD(0), fPIDResponse(0), fOutputList(0), fHistLambdaMassPtCut(0), fHistK0MassPtCut(0), fHistAntiLambdaMassPtCut(0),
	fHistKorelacie(0), fHistdPhidEtaMix(0), fHistV0Multiplicity(0), fHistMultVtxz(0), fHistMCPtAs(0), fHistRCPtAs(0), fHistNumberOfTriggers(0),
    fHistMCMixingRec(0), fFillMixed(kTRUE), fMixingTracks(5000), fCentrOrMult(-1),
	fPoolMgr(0x0), fPool(0x0), fAnalysisMC(kTRUE), fOStatus(1), fPtTrigMin(0), fPtAsocMin(0), fHistKorelacieMCrec(0),
    fHistNumberOfTriggersGen(0),fHistNumberOfTriggersRec(0),fHistRecV0(0),fHistGenV0(0),fHistMCPtTrigg(0),fHistRCPtTrigg(0),fHistSelection(0),
    fHistMultipPercentile(0), fHistMultiplicity(0)
{
    // default constructor, don't allocate memory here!
    // this is used by root for IO purposes, it needs to remain empty
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::AliAnalysisTaskMyTask(const char* name) : AliAnalysisTaskSE(name),
    fAOD(0), fPIDResponse(0), fOutputList(0), fHistLambdaMassPtCut(0), fHistK0MassPtCut(0), fHistAntiLambdaMassPtCut(0),
	fHistKorelacie(0), fHistdPhidEtaMix(0), fHistV0Multiplicity(0), fHistMultVtxz(0), fHistMCPtAs(0), fHistRCPtAs(0),
    fHistNumberOfTriggers(0), fHistMCMixingRec(0), fFillMixed(kTRUE), fMixingTracks(5000), fCentrOrMult(-1),
	fPoolMgr(0x0) ,fPool(0x0), fAnalysisMC(kTRUE), fOStatus(1), fPtTrigMin(0), fPtAsocMin(0), fHistKorelacieMCrec(0),
    fHistNumberOfTriggersGen(0),fHistNumberOfTriggersRec(0), fHistRecV0(0),fHistGenV0(0),fHistMCPtTrigg(0), fHistRCPtTrigg(0), fHistSelection(0),
    fHistMultipPercentile(0), fHistMultiplicity(0)
{
    // constructor
    DefineInput(0, TChain::Class());    // define the input of the analysis: in this case we take a 'chain' of events
                                        // this chain is created by the analysis manager, so no need to worry about it, 
                                        // it does its work automatically
    DefineOutput(1, TList::Class());    // define the ouptut of the analysis: in this case it's a list of histograms 
                                        // you can add more output objects by calling DefineOutput(2, classname::Class())
                                        // if you add more output objects, make sure to call PostData for all of them, and to
                                        // make changes to your AddTask macro!
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::~AliAnalysisTaskMyTask()
{
    // destructor
    if(fOutputList) {
        delete fOutputList;     // at the end of your task, it is deleted from memory by calling this function
    }
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::UserCreateOutputObjects()
{
	const Double_t kPi = TMath::Pi();
	Float_t kPtBins[11] = {0,1,2,3,4,5,6,7,9,11,15};
	Int_t kMassBins = 500;
	Float_t kMassMinK = 0.4;
	Float_t kMassMaxK = 0.6;

	Float_t kMassMinLambda = 0.8;
	Float_t kMassMaxLambda = 1.2;

	Float_t kMassBinsK[kMassBins];
	Float_t kMassBinsLambda[kMassBins];

	kMassBinsK[0] = kMassMinK;
	kMassBinsLambda[0] = kMassMinLambda;
	
	for (Int_t i=0; i<kMassBins; i++){
		kMassBinsK[i+1] = kMassBinsK[i] + (kMassMaxK-kMassMinK)/kMassBins;
		kMassBinsLambda[i+1] = kMassBinsLambda[i] + (kMassMaxLambda-kMassMinLambda)/kMassBins;
	}

	Int_t kNCuts = 11;
	Float_t kCuts[kNCuts];
	kCuts[0]=0;
	for (Int_t i=0; i<kNCuts; i++){
		kCuts[i+1]=kCuts[i]+1;
	}

	Int_t bins[11]= {11,13,144,100,20,7,40,40,72,6,3};
	Double_t min[11] = {fPtTrigMin,fPtAsocMin, -kPi/2, -2., -10., 0.,-1,-1,0.,1,0};
	Double_t max[11] = {15., 15., -kPi/2+2*kPi, 2., 10., 7.,1,1, 2*kPi,300,100};
    
    Int_t binsMix[8] = {11,13,144,100,20,7,6,10};
    Double_t minMix[8] ={fPtTrigMin,fPtAsocMin, -kPi/2, -2., -10., 0.,1,0};
    Double_t maxMix[8] = {15., 15., -kPi/2+2*kPi, 2., 10., 7.,300,100};
    
	Int_t  NofCentBins  = 4;
    Double_t MBins[]={0,3,5,15,60.};
    Double_t * CentrORMultBins = MBins;
	/*Int_t nCentralityBins  = 9;
    Double_t centBins[] = {0.,10.,20.,30.,40.,50.,60.,70.,80.,90.};
    const Double_t* centralityBins = centBins;*/
         
    Int_t NofZVrtxBins  = 20;
    Double_t ZBins[]={-10.0, -9., -8.0, -7., -6.0, -5., -4.0, -3., -2., -1., 0, 1., 2.0 ,3., 4.0, 5., 6.0, 7., 8.0, 9., 10.0};
    Double_t *ZVrtxBins = ZBins;

//Int_t mcbins[3]={5,2,3};
//	Double_t mcmin[3]={2.,0.,0.};
//	Double_t mcmax[3]={15.,250.3.};

	/*Int_t nCentralityBins  = 1;
    Double_t centBins[] = {-2.,0.};
   // const Double_t* centralityBins = centBins;

	//Int_t nMultBins = 9;
	//Double_t multBins[] = { 0, 6, 12, 19, 28, 39, 49, 59, 71, 82 }; */

	Int_t nZvtxBins  = 10;
 	Double_t vertexBins[] = {-10.,-8.,-6.,-4.,-2.,0.,2.,4.,6.,8.,10.};
    const Double_t* zvtxBins = vertexBins;

	Int_t bins2d[7] = {11,20,40,7,72,6,3};
	Double_t mis2d[7] = {fPtTrigMin,-10,-1,0.,0.,1,0};
	Double_t maxs2d[7] = {15.,10,1,7.,2*kPi,300,100};


	
    // create output objects
    //
    // this function is called ONCE at the start of your analysis (RUNTIME)
    // here you ceate the histograms that you want to use 
    //
    // the histograms are in this case added to a tlist, this list is in the end saved
    // to an output file
    //
    fOutputList = new TList();          // this is a list which will contain all of your histograms
                                        // at the end of the analysis, the contents of this list are written
                                        // to the output file
    fOutputList->SetOwner(kTRUE);       // memory stuff: the list is owner of all objects it contains and will delete them
                                        // if requested (dont worry about this now)

    // example of a histogram
    
   // Printf("trig min %g, assoc min %g\n",fPtTrigMin,fPtAsocMin);
        
    fHistK0MassPtCut = new TH3F ("fHistK0MassPtCut", "fHistK0MassPtCut", kMassBins, kMassBinsK, 10, kPtBins, kNCuts, kCuts);
    fHistLambdaMassPtCut = new TH3F("fHistLambdaMassPtCut", "fHistLambdaMassPtCut", kMassBins, kMassBinsLambda, 10, kPtBins, kNCuts, kCuts);
	fHistAntiLambdaMassPtCut = new TH3F("fHistAntiLambdaMassPtCut", "fHistAntiLambdaMassPtCut", kMassBins, kMassBinsLambda, 10, kPtBins, kNCuts, kCuts);
    fOutputList->Add(fHistK0MassPtCut); 
    fOutputList->Add(fHistLambdaMassPtCut); 
	fOutputList->Add(fHistAntiLambdaMassPtCut); 

	fHistKorelacie = new THnSparseF ("fHistKorelacie","fHistKorelacie", 11, bins, min, max);
	fHistdPhidEtaMix = new THnSparseF ("fHistdPhidEtaMix", "fHistdPhidEtaMix", 8, binsMix, minMix, maxMix);
	fOutputList->Add(fHistKorelacie); 
	fOutputList->Add(fHistdPhidEtaMix);
    
    fHistMCMixingRec = new THnSparseF ("fHistMCMixingRec", "fHistMCMixingRec", 8, binsMix, minMix, maxMix);
    fOutputList->Add(fHistMCMixingRec);
    fHistMCMixingRec->Sumw2();

    fHistMCKorelacie = new THnSparseF ("fHistMCKorelacie","fHistMCKorelacie", 11, bins, min, max);
    fOutputList->Add(fHistMCKorelacie);
    fHistKorelacieMCrec = new THnSparseF ("fHistKorelacieMCrec","fHistKorelacieMCrec", 11, bins, min, max);
    fOutputList->Add(fHistKorelacieMCrec);

    Double_t varBins1[4] = {0.,10.,50.,100.};
    Double_t varBins2[7] = {1.,3.,6.,9.,14.,24.,300.};
    fHistKorelacieMCrec->GetAxis(9)->Set(6, varBins2);
    fHistKorelacieMCrec->GetAxis(10)->Set(3, varBins1);
    
    fHistMCKorelacie->GetAxis(9)->Set(6, varBins2);
    fHistMCKorelacie->GetAxis(10)->Set(3, varBins1);
    fHistKorelacie->GetAxis(9)->Set(6, varBins2);
    fHistKorelacie->GetAxis(10)->Set(3, varBins1);
    
    fHistdPhidEtaMix->GetAxis(6)->Set(6, varBins2);
    fHistdPhidEtaMix->GetAxis(7)->Set(3, varBins1);
    
    fHistMCMixingRec->GetAxis(6)->Set(6, varBins2);
    fHistMCMixingRec->GetAxis(7)->Set(3, varBins1);

	fHistV0Multiplicity = new TH1D ("fHistV0Multiplicity", "fHistV0Multiplicity", 60, 0, 60);
	fOutputList->Add(fHistV0Multiplicity); 

	fHistMultVtxz = new TH2D ("fHistMultVtxz","fHistMultVtxz",NofCentBins,MBins,NofZVrtxBins,ZBins);
	fOutputList->Add(fHistMultVtxz);

	fHistMCPtAs = new TH3D("fHistMCPtAs","fHistMCPtAs",13,fPtAsocMin,15,20,-10,10,40,-1,1);
	fOutputList->Add(fHistMCPtAs);
	fHistRCPtAs = new TH3D("fHistRCPtAs","fHistRCPtAs",13,fPtAsocMin,15,20,-10,10,40,-1,1);
	fOutputList->Add(fHistRCPtAs);
    
    fHistMCPtTrigg = new TH3D("fHistMCPtTrigg","fHistMCPtTrigg",11,fPtTrigMin,15,20,-10,10,40,-1,1);
    fOutputList->Add(fHistMCPtTrigg);
    fHistRCPtTrigg = new TH3D("fHistRCPtTrigg","fHistRCPtTrigg",11,fPtTrigMin,15,20,-10,10,40,-1,1);
    fOutputList->Add(fHistRCPtTrigg);
    
    Int_t binsTrig[4]={11,20,3,40};
    Double_t mintrig[4]={4,-10,0,-1};
    Double_t maxtrig[4]={15,10,3,1};
    fHistGenV0 = new THnSparseF("fHistGenV0","fHistGenV0",4,binsTrig,mintrig,maxtrig);
    fOutputList->Add(fHistGenV0);
    fHistGenV0->Sumw2();
    fHistRecV0 = new THnSparseF("fHistRecV0","fHistRecV0",4,binsTrig,mintrig,maxtrig);
    fOutputList->Add(fHistRecV0);
    fHistRecV0->Sumw2();

	fHistNumberOfTriggers = new THnSparseF("fHistNumberOfTriggers","fHistNumberOfTriggers",7,bins2d,mis2d, maxs2d);
	fOutputList->Add(fHistNumberOfTriggers);
    fHistNumberOfTriggers->Sumw2();
    fHistNumberOfTriggersGen = new THnSparseF("fHistNumberOfTriggersGen","fHistNumberOfTriggersGen",7,bins2d,mis2d, maxs2d);
    fOutputList->Add(fHistNumberOfTriggersGen);
    fHistNumberOfTriggersGen->Sumw2();
    fHistNumberOfTriggersRec = new THnSparseF("fHistNumberOfTriggersRec","fHistNumberOfTriggersRec",7,bins2d,mis2d, maxs2d);
    fOutputList->Add(fHistNumberOfTriggersRec);
    fHistNumberOfTriggersRec->Sumw2();
    
    fHistNumberOfTriggersGen->GetAxis(5)->Set(6, varBins2);
    fHistNumberOfTriggersGen->GetAxis(6)->Set(3, varBins1);
    fHistNumberOfTriggersRec->GetAxis(5)->Set(6, varBins2);
    fHistNumberOfTriggersRec->GetAxis(6)->Set(3, varBins1);
    fHistNumberOfTriggers->GetAxis(5)->Set(6, varBins2);
    fHistNumberOfTriggers->GetAxis(6)->Set(3, varBins1);
    
    fHistSelection = new TH1D("fHistSelection","fHistSelection",2,0,2);
    fOutputList->Add(fHistSelection);
    
    fHistMultipPercentile = new TH1F("fHistMultipPercentile","fHistMultipPercentile",10,0,100);
    fHistMultiplicity = new TH1F("fHistMultiplicity","fHistMultiplicity",6,varBins2);
    fOutputList->Add(fHistMultipPercentile);
    fOutputList->Add(fHistMultiplicity);
    fHistMultiplicity->Sumw2();
    fHistMultipPercentile->Sumw2();
    
	//fHistRCPtMultiTrig = new THnSparse("fHistRCPtMultiTrig","fHistRCPtMultiTrig",3,mcbins,mcmin, mcmin);
	//fOutputList->Add(fHistRCPtMultiTrig); 
    
    PostData(1, fOutputList);           // postdata will notify the analysis manager of changes / updates to the 
                                        // fOutputList object. the manager will in the end take care of writing your output to file
                                        // so it needs to know what's in the output
	// Settings for event mixing -------------------------------------
    Int_t trackDepth = fMixingTracks;
    Int_t poolSize   = 200;  // Maximum number of events, ignored in the present implemented of AliEventPoolManager
  
    //fPoolMgr = new AliEventPoolManager(poolSize, trackDepth, nCentralityBins, centBins, nZvtxBins, vertexBins);
     fPoolMgr = new AliEventPoolManager(poolSize, trackDepth, NofCentBins, MBins, NofZVrtxBins, ZBins);
     fPoolMgr->SetTargetValues(trackDepth, 0.1, 5);
	//----------------------------------------------
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::UserExec(Option_t *)
{
	const Double_t kPi = TMath::Pi();
   // Printf("====== new event ======\n");
    // user exec
    // this function is called once for each event
    // the manager will take care of reading the events from file, and with the static function InputEvent() you 
    // have access to the current event. 
    // once you return from the UserExec function, the manager will retrieve the next event from the chain
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    AliAODInputHandler *inEvMain = (AliAODInputHandler *) mgr->GetInputEventHandler();
    //AliAODEvent * - nema to tam byt, lebo uz je to definovane v haderi
    fAOD = (AliAODEvent *) inEvMain -> GetEvent();    // get an event (called fAOD) from the input file
    fPIDResponse = (AliPIDResponse *) inEvMain-> GetPIDResponse();
    if(!fAOD) return;                                   // if the pointer to the ,event is empty (getting it failed) skip this event
        // example part: i'll show how to loop over the tracks in an event 
        // and extract some information from them which we'll store in a histogram

		// physics selection
    fHistSelection->Fill(0.5);
	UInt_t maskIsSelected = inEvMain->IsEventSelected();

	//  data trigger selection
	Bool_t isSelected = (maskIsSelected & AliVEvent::kINT7); //pp
    //Bool_t isSelected = AliVEvent::kMB; //pp 2010
	// Bool_t isSelected = ((maskIsSelected & AliVEvent::kMB) || (maskIsSelected & AliVEvent::kCentral) || (maskIsSelected & AliVEvent::kSemiCentral)); //PbPb

	if (!isSelected) return;
    fHistSelection->Fill(1.5);

	AliAODVertex *myPrimVertex = fAOD->GetPrimaryVertex();
	if (!myPrimVertex) return;
	Double_t lPVz = myPrimVertex->GetZ();		//poloha prim. vertexu, z-ova zlozka

	if (TMath::Abs(lPVz)>=10) return;
	Double_t lPVx = myPrimVertex->GetX();
	Double_t lPVy = myPrimVertex->GetY();

    Int_t iTracks(fAOD->GetNumberOfTracks());           // see how many tracks there are in the event
    Int_t iV0(fAOD->GetNumberOfV0s());                  // see how many V0 there are in the event

	fHistV0Multiplicity->Fill(iV0);

	// Multiplicity definition
    Float_t lPercentile = 302;
    AliMultSelection *MultSelection = 0x0;
    MultSelection = (AliMultSelection * ) fAOD->FindListObject("MultSelection");
    if( !MultSelection) {
        //If you get this warning (and lPercentiles 300) please check that the AliMultSelectionTask actually ran (before your task)
        AliWarning("AliMultSelection object not found!");
    }else{
        lPercentile = MultSelection->GetMultiplicityPercentile("V0M");
    }
    //Printf ("muliplicita percentile %f\n",lPercentile);
    
    Int_t multip = 302;
    
    multip = AliPPVsMultUtils::GetStandardReferenceMultiplicity( fAOD );
    
    fHistMultipPercentile->Fill(lPercentile);
    fHistMultiplicity->Fill(multip);
   // Printf ("muliplicita utils %d \n",multip);

    TObjArray *mcTracksSel = new TObjArray;
    TObjArray *mcTracksTrigSel = new TObjArray;
    TObjArray *mcTracksV0Sel = new TObjArray;
    TObjArray *selectedMCTracks = new TObjArray;
    TObjArray *selectedMCassoc = new TObjArray;
    TObjArray *selectedMCtrig= new TObjArray;
    TObjArray *selectedMCV0Triggersrec = new TObjArray;
    TClonesArray *mcArray = new TClonesArray;

	//=========== MC loop ===============================
    
	if(fAnalysisMC){
        //Printf("zaciatok eventu +++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        AliAODMCHeader *aodMCheader = (AliAODMCHeader*)fAOD->FindListObject(AliAODMCHeader::StdBranchName());
        Float_t vzMC = aodMCheader->GetVtxZ();
        if (TMath::Abs(vzMC) >= 7.) return;
 	     //retrieve MC particles from event
        mcArray = (TClonesArray*)fAOD->FindListObject(AliAODMCParticle::StdBranchName());
        if(!mcArray){
            Printf("No MC particle branch found");
            return;
        }

		Int_t nMCAllTracks = mcArray->GetEntriesFast();
 		TObjArray *mcTracks = new TObjArray;
		mcTracks->SetOwner(kTRUE);
 

		for (Int_t i = 0; i < nMCAllTracks; i++){ 
 			AliAODMCParticle *mcTrack = (AliAODMCParticle*)mcArray->At(i);
 			if (!mcTrack) {
				Error("ReadEventAODMC", "Could not receive particle %d", i);
				continue;
 			}
 			mcTracks->Add(mcTrack);
 		}

		Int_t nMCTracks = mcTracks->GetEntriesFast(); 
		fHistMCPtAs->Sumw2();
        fHistMCPtTrigg->Sumw2();
		
		for (Int_t iMC = 0; iMC<nMCTracks; iMC++){
			AliAODMCParticle *mcTrack = (AliAODMCParticle*)mcTracks->At(iMC);
			if (!mcTrack) {
				Error("ReadEventAODMC", "Could not receive particle %d", iMC);
				continue;
			}
 			// track cuts for generated particles
			Double_t mcTrackEta = mcTrack->Eta();
			Double_t mcTrackPt = mcTrack->Pt();
			Bool_t TrIsPrim = mcTrack->IsPhysicalPrimary();
			Bool_t TrEtaMax = TMath::Abs(mcTrackEta)<0.8;
			Bool_t TrPtMin = mcTrackPt>fPtAsocMin; 
			Bool_t TrCharge = (mcTrack->Charge())!=0;
            
			if (TrIsPrim && TrEtaMax && TrPtMin && TrCharge) {
               
                fHistMCPtAs->Fill(mcTrackPt,lPVz,mcTrackEta);
                mcTracksSel->Add(new AliV0ChBasicParticle(mcTrack->Eta(),mcTrack->Phi(),mcTrack->Pt(),4,mcTrack->GetLabel(),mcTrack->GetLabel()));
                if (mcTrackPt>fPtTrigMin) {
                    mcTracksTrigSel->Add(new AliV0ChBasicParticle(mcTrack->Eta(),mcTrack->Phi(),mcTrack->Pt(),4,mcTrack->GetLabel()));
                    fHistMCPtTrigg->Fill(mcTrackPt,lPVz,mcTrackEta);
                }
            }

            //--- MC closure test - selection of V0 ----

            Int_t mcMotherPdg = 0;
            Int_t mcPartPdg = mcTrack->GetPdgCode();
            
            if ((mcPartPdg != 310) && (mcPartPdg != 3122) && (mcPartPdg != (-3122))) continue; // keep only Lambdas and K0S
            
            Int_t mother  = mcTrack->GetMother();
            Int_t motherPDG = static_cast<AliAODMCParticle*>(mcArray->At(mother))->PdgCode();
            
            if (TMath::Abs(motherPDG) == 3312 || TMath::Abs(motherPDG) == 3334 ) { // removing Lambdas from Xi and Omega

                continue;
            }

            Bool_t IsK0 = mcPartPdg==310;
            Bool_t IsLambda = mcPartPdg==3122;
            Bool_t IsAntiLambda = mcPartPdg==-3122;

            IsK0 = IsK0 && (mcTrack->IsPhysicalPrimary());
            IsLambda = IsLambda && (mcTrack->IsPhysicalPrimary());
            IsAntiLambda = IsAntiLambda && (mcTrack->IsPhysicalPrimary());
            
            AliAODMCParticle* daughter0 = 0x0;
            AliAODMCParticle* daughter1 = 0x0;
            Int_t dau0 = mcTrack->GetDaughter(0);
            if (dau0>0) daughter0 = (AliAODMCParticle*) mcTracks->At(dau0);
            Int_t dau1 = mcTrack->GetDaughter(1);
            if (dau1>0) daughter1 = (AliAODMCParticle*) mcTracks->At(dau1);
            
            Int_t labelPos = -1;
            Int_t labelNeg = -1;
            if(!daughter0||!daughter1) continue;
            if(daughter0->Charge()<0){
                labelPos = daughter1->GetLabel();
                labelNeg = daughter0->GetLabel();
            }else{
                labelPos = daughter0->GetLabel();
                labelNeg = daughter1->GetLabel();
            }

            //MC V0 cuts 
            //Printf("V0 mother %d pt %g eta %g \n",mcTrack->GetMother(), mcTrack->Pt(),mcTrack->Eta());

            if (TMath::Abs(mcTrack->Eta())<0.8 && mcTrack->Pt()>fPtTrigMin){
               // Printf("pdg gen %d label gen %d \n",mcPartPdg, mcTrack->GetLabel());
                if(IsK0) {
                    mcTracksV0Sel->Add(new AliV0ChBasicParticle(mcTrack->Eta(),mcTrack->Phi(),mcTrack->Pt(),1,mcTrack->GetLabel(),labelPos-1,labelNeg-1));
                    Double_t v0effic[4]={mcTrack->Pt(),lPVz,0.5,mcTrack->Eta()};
                    fHistGenV0->Fill(v0effic);
                }
                if(IsLambda) {
                    mcTracksV0Sel->Add(new AliV0ChBasicParticle(mcTrack->Eta(),mcTrack->Phi(),mcTrack->Pt(),2,mcTrack->GetLabel(),labelPos-1,labelNeg-1));
                    Double_t v0effic[4]={mcTrack->Pt(),lPVz,1.5,mcTrack->Eta()};
                    fHistGenV0->Fill(v0effic);
                }
                if(IsAntiLambda) {
                    mcTracksV0Sel->Add(new AliV0ChBasicParticle(mcTrack->Eta(),mcTrack->Phi(),mcTrack->Pt(),3,mcTrack->GetLabel(),labelPos-1,labelNeg-1));
                    Double_t v0effic[4]={mcTrack->Pt(),lPVz,2.5,mcTrack->Eta()};
                    fHistGenV0->Fill(v0effic);
                }
                
            } 

		}
        // MC closure test corellations
      
      //V0-h
      fHistMCKorelacie->Sumw2();
      Corelations(mcTracksV0Sel,mcTracksSel,fHistMCKorelacie, lPVz, fHistNumberOfTriggersGen,kFALSE,kTRUE,lPercentile,multip);

      //h-h
      Corelations(mcTracksTrigSel,mcTracksSel,fHistMCKorelacie, lPVz,fHistNumberOfTriggersGen, kTRUE, kFALSE,lPercentile,multip);

        //reconstructed part. 
		Int_t nTracks = fAOD->GetNumberOfTracks();

		for (Int_t i = 0; i < nTracks; i++)
 	    {
 	         AliAODTrack* tr = dynamic_cast<AliAODTrack*>(fAOD->GetTrack(i));
 	         if(!tr) AliFatal("Not a standard AOD"); 
 	         selectedMCTracks->Add(tr);
 	     }

		Int_t nRecTracks = selectedMCTracks->GetEntriesFast(); 

		fHistRCPtAs->Sumw2();
        fHistRCPtTrigg->Sumw2();

		for (Int_t i = 0; i < nRecTracks; i++){
       		AliAODTrack* tras = (AliAODTrack*)selectedMCTracks->At(i);
       		if ((tras->Pt())<fPtAsocMin) continue;
        	if (!(IsMyGoodPrimaryTrack(tras))) continue;
        	Int_t AssocLabel = tras->GetLabel();
            if ((tras->Charge())==0) continue;
            
        	if (AssocLabel<=0) continue;
            AliAODMCParticle* mcTrack = static_cast<AliAODMCParticle*>(mcArray->At(AssocLabel));
        	Bool_t isPhyPrim = static_cast<AliAODMCParticle*>(mcArray->At(AssocLabel))->IsPhysicalPrimary();
            Double_t mcPt = tras->Pt();
            Double_t genPt = static_cast<AliAODMCParticle*>(mcArray->At(AssocLabel))->Pt();
            Double_t mcPhi = tras->Phi();
            Double_t genPhi = static_cast<AliAODMCParticle*>(mcArray->At(AssocLabel))->Phi();
            Double_t mcEta = tras->Eta();
            Double_t genEta = static_cast<AliAODMCParticle*>(mcArray->At(AssocLabel))->Eta();
        	if (isPhyPrim) {
                
                fHistRCPtAs->Fill(genPt,lPVz,genEta);
                selectedMCassoc->Add(new AliV0ChBasicParticle(mcEta,mcPhi,mcPt,4,tras->GetLabel(),tras->GetID()));
                if (mcPt>fPtTrigMin) {
                    selectedMCtrig->Add(new AliV0ChBasicParticle(mcEta,mcPhi,mcPt,4,tras->GetLabel()));
                    fHistRCPtTrigg->Fill(genPt,lPVz,genEta);
                }
                
            }

      }

    }

	//=========== end of MC loop ==========

	TObjArray * selectedTracks = new TObjArray;
	selectedTracks->SetOwner(kTRUE);

	TObjArray * selectedAssociatedTracks = new TObjArray;
	selectedAssociatedTracks->SetOwner(kTRUE);
	TObjArray * selectedTriggerTracks = new TObjArray;
	selectedTriggerTracks->SetOwner(kTRUE);
    
    for(Int_t i=0; i < iTracks; i++) {                 // loop ove rall these tracks
        AliAODTrack* track = static_cast<AliAODTrack*>(fAOD->GetTrack(i));         // get a track (type AliAODTrack) from the event
        if(!track) continue;                            // if we failed, skip this track
        
        if(!IsMyGoodPrimaryTrack(track)) continue;           // aplikujem cut na preudorapiditu tracku 
	   
		selectedTracks->Add(track);
        if(track->Pt()>fPtAsocMin) selectedAssociatedTracks-> Add(new AliV0ChBasicParticle(track->Eta(), track->Phi(), track->Pt(), 4, 0,track->GetID()));
        if(track->Pt()>fPtTrigMin) selectedTriggerTracks-> Add(new AliV0ChBasicParticle(track->Eta(), track->Phi(), track->Pt(), 4,0,track->GetID()));
	}

    TObjArray * selectedV0 = new TObjArray;
	selectedV0->SetOwner(kTRUE); 
	TObjArray * selectedV0Triggers = new TObjArray;
	selectedV0Triggers->SetOwner(kTRUE); 
	TObjArray * selectedV0Assoc = new TObjArray;
	selectedV0Assoc->SetOwner(kTRUE);   
	
	Int_t iSelTracks = selectedTracks->GetEntries(); 

    Int_t motherLabelPrevious[iV0];
    
	for (Int_t i=0; i<iV0/*iSelV0*/; i++){
        AliAODv0* V0 = static_cast<AliAODv0*>(fAOD->GetV0(i));
        if(!V0) continue;
        
        Double_t massK0=V0->MassK0Short(); // da mi hodnotu invariantnej hmotnosti pre hypotezu rozpadu K0
        Double_t massLambda=V0->MassLambda();
        Double_t massAntilambda=V0->MassAntiLambda();

        Double_t ptTrig = V0->Pt();

        Bool_t k0 = ((massK0>0.48)&&(massK0<0.52));
        Bool_t Lambda = ((massLambda>1.1)&&(massLambda<1.13));
        Bool_t Antilambda = ((massAntilambda>1.1)&&(massAntilambda<1.13));

        // PID cut--------------------------
        Float_t nSigmaPosPion   = 0.;
        Float_t nSigmaNegPion   = 0.;
        Float_t nSigmaPosProton = 0.;
        Float_t nSigmaNegProton = 0.;

        const AliAODTrack *myTrackPos;
        const AliAODTrack *myTrackNeg;
        AliVTrack *trackNegTest=dynamic_cast<AliVTrack *>(V0->GetDaughter(1));
        AliVTrack *trackPosTest=dynamic_cast<AliVTrack *>(V0->GetDaughter(0));

        AliAODTrack * myTrackNegTest = (AliAODTrack*) trackNegTest;
        AliAODTrack * myTrackPosTest = (AliAODTrack*) trackPosTest;
  
        if (!myTrackPosTest || !myTrackNegTest) {
            Printf("strange analysis::UserExec:: Error:Could not retreive one of the daughter track\n");
            continue;
        }
 
        if( myTrackPosTest->Charge() ==1){
            myTrackPos = myTrackPosTest;
            myTrackNeg = myTrackNegTest;
        }
 
        if( myTrackPosTest->Charge() ==-1){
            myTrackPos = myTrackNegTest;
            myTrackNeg = myTrackPosTest;
        }
  
        
        Int_t oStatus = GetOStatus();
        if(!IsMyGoodV0(V0,myTrackPos,myTrackNeg,oStatus)) continue;
        
        const AliAODPid *pPid = myTrackPos->GetDetPid();
        const AliAODPid *nPid = myTrackNeg->GetDetPid();
  
        if (pPid){
            Double_t pdMom = pPid->GetTPCmomentum();
            if (pdMom<1.){
                nSigmaPosPion = fPIDResponse->NumberOfSigmasTPC(myTrackPos, AliPID::kPion);
                nSigmaPosProton = fPIDResponse->NumberOfSigmasTPC(myTrackPos, AliPID::kProton);
            }
        }
              
  
        if (nPid){
            Double_t ndMom = nPid->GetTPCmomentum();
            if (ndMom<1.){
                nSigmaNegPion = fPIDResponse->NumberOfSigmasTPC(myTrackPos, AliPID::kPion);
                nSigmaNegProton = fPIDResponse->NumberOfSigmasTPC(myTrackPos, AliPID::kProton);
            }
        }

            
                  
        Bool_t bpPion = TMath::Abs(nSigmaPosPion) <= 3.;
        Bool_t bpProton = TMath::Abs(nSigmaPosProton) <= 3.;
        Bool_t bnPion = TMath::Abs(nSigmaNegPion) <= 3.;
        Bool_t bnProton = TMath::Abs(nSigmaNegProton) <= 3.;
  
        Bool_t cutK0Pid = (bpPion && bnPion);
        Bool_t cutLambdaPid = (bpProton && bnPion);
        Bool_t cutAntiLambdaPid = (bpPion && bnProton);
        //--------------------------------------------------

        /*  Bool_t cutK0Pid = 1; //PbPb
            Bool_t cutLambdaPid = 1;
            Bool_t cutAntiLambdaPid = 1;*/

        if (k0&&cutK0Pid) fHistK0MassPtCut->Fill(massK0,ptTrig,0.5);
        if (Lambda&&cutLambdaPid) fHistLambdaMassPtCut->Fill(massLambda,ptTrig,0.5);
        if (Antilambda&&cutAntiLambdaPid) fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,0.5);

        if(!IsMyGoodPID(myTrackPos,myTrackNeg)) continue; //TPC dE/dx selection (Real Data Only)  // nerobim tento cut zbytocne trikrat?????
        
        if (k0&&cutK0Pid) fHistK0MassPtCut->Fill(massK0,ptTrig,1.5);
        if (Lambda&&cutLambdaPid) fHistLambdaMassPtCut->Fill(massLambda,ptTrig,1.5);
        if (Antilambda&&cutAntiLambdaPid) fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,1.5);
                
        if (k0&&cutK0Pid){
            if (TMath::Abs(massLambda-1.115683)<0.03) continue;
            fHistK0MassPtCut->Fill(massK0,ptTrig,2.5);

            if(!IsMyGoodV0AngleK0(V0,myPrimVertex)) continue;  //V0 Cosine of Pointing Angle
            fHistK0MassPtCut->Fill(massK0,ptTrig,3.5);
            
            //Printf("eta V0 %g\n", V0->Eta());
            if(!IsMyGoodV0RapidityK0(V0)) continue; //Rapidity
            fHistK0MassPtCut->Fill(massK0,ptTrig,4.5);
                                
            if(!IsMyGoodLifeTimeK0(lPVx,lPVy,lPVz,V0)) continue;  //Proper Lifetime (mL/p)
            fHistK0MassPtCut->Fill(massK0,ptTrig,5.5);
            
            if(fAnalysisMC){
                AliAODTrack *daughter1= static_cast<AliAODTrack*> (V0->GetDaughter(1));
                AliAODTrack *daughter0= static_cast<AliAODTrack*> (V0->GetDaughter(0));
                if (daughter1->GetLabel()<0||daughter0->GetLabel()<0) continue;
                Int_t mcmother1 = static_cast<AliAODMCParticle*>(mcArray->At(daughter1->GetLabel()))->GetMother();
                Int_t mcmother0 = static_cast<AliAODMCParticle*>(mcArray->At(daughter0->GetLabel()))->GetMother();

                if(mcmother1!=mcmother0) continue;
                Int_t pdgK0 = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->PdgCode();
                Int_t pdgD1 = static_cast<AliAODMCParticle*>(mcArray->At(daughter1->GetLabel()))->PdgCode();
                Int_t pdgD0 = static_cast<AliAODMCParticle*>(mcArray->At(daughter0->GetLabel()))->PdgCode();
                
                Bool_t isPhyPrim = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->IsPhysicalPrimary();
                if(!isPhyPrim) continue;
                
                if (pdgK0!=310) continue;
                
                if (( pdgD0!=211 && pdgD1!=-211 )&&( pdgD0!=-211 && pdgD1!=211 )) continue;
                
              //  Double_t V0mcPt = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Pt();
              //  if(V0mcPt>fPtTrigMin) Printf ("label %d, pdg V0 %d, i %d \n",mcmother1,pdgK0,i);
                Bool_t isGen = kFALSE;
                Int_t genLabel;
                
                for(Int_t iV0Gen=0; iV0Gen <mcTracksV0Sel->GetEntries();iV0Gen++){
                    AliV0ChBasicParticle *gen = (AliV0ChBasicParticle*) mcTracksV0Sel->At(iV0Gen);
                    genLabel= gen->MyLabel();
                    
                    if(mcmother1==genLabel){
                       
                       motherLabelPrevious[i]=mcmother1;
                       isGen = kTRUE; // je to dobry check; mam menej rec ako gen; TODO: je mozne urobit to efektivnejsie??
                       break;
                    }
                   

                }
                
                for(Int_t iLab=0;iLab<i;iLab++){
                    
                    if(motherLabelPrevious[iLab]==mcmother1){
                        
                        isGen=kFALSE;
                        break;
                    }
                    
                }
                
               if(isGen){
                  
                   
                       Double_t V0mcPt = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Pt();
                       Double_t V0mcEta = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Eta();
                       Double_t V0mcPhi = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Phi();
                       Int_t V0Motherlabel = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->GetMother();
                       Int_t V0label = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->GetLabel();
                       if(V0mcPt>fPtTrigMin) {
                          // Printf ("label %d\n ",mcmother1);
                           selectedMCV0Triggersrec-> Add(new AliV0ChBasicParticle(V0->Eta(), V0->Phi(), V0->Pt(), 1,0,myTrackPos->GetID(),myTrackNeg->GetID()));
                           Double_t v0effic[4]={V0mcPt,lPVz,0.5,V0mcEta};
                           fHistRecV0->Fill(v0effic);
                           fHistK0MassPtCut->Fill(massK0,ptTrig,6.5);
                       }
                   
               }
            }
            if(V0->Pt()>fPtAsocMin) selectedV0Assoc-> Add(new AliV0ChBasicParticle(V0->Eta(), V0->Phi(), V0->Pt(), 1,0,myTrackPos->GetID(),myTrackNeg->GetID()));
            if(V0->Pt()>fPtTrigMin) selectedV0Triggers-> Add(new AliV0ChBasicParticle(V0->Eta(), V0->Phi(), V0->Pt(), 1,0,myTrackPos->GetID(),myTrackNeg->GetID()));

        }

        if (Lambda&&cutLambdaPid){
            if (TMath::Abs(massK0-0.497614)<0.04) continue;
            fHistLambdaMassPtCut->Fill(massLambda,ptTrig,2.5);

            if(!IsMyGoodV0AngleLambda(V0,myPrimVertex)) continue;
            fHistLambdaMassPtCut->Fill(massLambda,ptTrig,3.5);
        
            if(!IsMyGoodV0RapidityLambda(V0)) continue; 
            fHistLambdaMassPtCut->Fill(massLambda,ptTrig,4.5);
                
            if(!IsMyGoodLifeTimeLambda(lPVx,lPVy,lPVz,V0)) continue;
            fHistLambdaMassPtCut->Fill(massLambda,ptTrig,5.5);

            
            if(fAnalysisMC){
                AliAODTrack *daughter1= static_cast<AliAODTrack*> (V0->GetDaughter(1));
                AliAODTrack *daughter0= static_cast<AliAODTrack*> (V0->GetDaughter(0));
                if (daughter1->GetLabel()<0||daughter0->GetLabel()<0) continue;
                Int_t mcmother1 = static_cast<AliAODMCParticle*>(mcArray->At(daughter1->GetLabel()))->GetMother();
                Int_t mcmother0 = static_cast<AliAODMCParticle*>(mcArray->At(daughter0->GetLabel()))->GetMother();

                if(mcmother1!=mcmother0) continue;
                Int_t pdgLam = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->PdgCode();
                Int_t pdgD1 = static_cast<AliAODMCParticle*>(mcArray->At(daughter1->GetLabel()))->PdgCode();
                Int_t pdgD0 = static_cast<AliAODMCParticle*>(mcArray->At(daughter0->GetLabel()))->PdgCode();
                
                Bool_t isPhyPrim = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->IsPhysicalPrimary();
                
                if(!isPhyPrim) continue;
                
                //Printf ("label %d, pdg V0 %d, dcera %d, dcera %d \n ",mcmother1,pdgLam,pdgD1,pdgD0);
                if (pdgLam!=3122) continue;
                if ((pdgD0!=2212 && pdgD1!=-211 )&&(pdgD0!=-211 && pdgD1!=2212)) continue;
               // Printf("OK\n");
               // Double_t V0mcPt = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Pt();
                //if(V0mcPt>fPtTrigMin) Printf("label %d, pdg V0 %d \n",mcmother1,pdgLam);
                Bool_t isGen = kFALSE;
                for(Int_t iV0Gen=0; iV0Gen <mcTracksV0Sel->GetEntries();iV0Gen++){
                    AliV0ChBasicParticle *gen = (AliV0ChBasicParticle*) mcTracksV0Sel->At(iV0Gen);
                    Int_t genLabel = gen->MyLabel();
                    
                    if(mcmother1==genLabel){
                         motherLabelPrevious[i]=mcmother1;
                        
                        isGen=kTRUE; 
                        break;
                    }

                }
                for(Int_t iLab=0;iLab<i;iLab++){
                    
                    if(motherLabelPrevious[iLab]==mcmother1){
                        
                        isGen=kFALSE;
                        break;
                    }
                    
                }

               if(isGen){
                   //Printf ("label %d\n ",mcmother1);
                   
                   
                       Double_t V0mcPt = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Pt();
                       Double_t V0mcEta = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Eta();
                       Double_t V0mcPhi = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Phi();
                       Int_t V0Motherlabel = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->GetMother();
                       Int_t V0label = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->GetLabel();
                       if(V0mcPt>fPtTrigMin) {
                           selectedMCV0Triggersrec-> Add(new AliV0ChBasicParticle(V0->Eta(), V0->Phi(), V0->Pt(), 2,0,myTrackPos->GetID(),myTrackNeg->GetID()));
                           Double_t v0effic[4]={V0mcPt,lPVz,1.5,V0mcEta};
                           fHistRecV0->Fill(v0effic);
                           fHistLambdaMassPtCut->Fill(massLambda,ptTrig,6.5);
                       }
                   
               }
            }
            if(V0->Pt()>fPtAsocMin) selectedV0Assoc-> Add(new AliV0ChBasicParticle(V0->Eta(), V0->Phi(), V0->Pt(), 2,0,myTrackPos->GetID(),myTrackNeg->GetID()));
            if(V0->Pt()>fPtTrigMin) selectedV0Triggers-> Add(new AliV0ChBasicParticle(V0->Eta(), V0->Phi(), V0->Pt(), 2,0,myTrackPos->GetID(),myTrackNeg->GetID()));
        }
            
        if (Antilambda&&cutAntiLambdaPid){
            if (TMath::Abs(massK0-0.497614)<0.04) continue;
            fHistAntiLambdaMassPtCut->Fill(massLambda,ptTrig,2.5);

            if(!IsMyGoodV0AngleLambda(V0, myPrimVertex)) continue;
            fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,3.5);

            if(!IsMyGoodV0RapidityLambda(V0)) continue; 
            fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,4.5);
                
            if(!IsMyGoodLifeTimeLambda(lPVx,lPVy,lPVz,V0)) continue;
            fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,5.5);

            
            if(fAnalysisMC){
                AliAODTrack *daughter1= static_cast<AliAODTrack*> (V0->GetDaughter(1));
                AliAODTrack *daughter0= static_cast<AliAODTrack*> (V0->GetDaughter(0));
                if (daughter1->GetLabel()<0||daughter0->GetLabel()<0) continue;
                Int_t mcmother1 = static_cast<AliAODMCParticle*>(mcArray->At(daughter1->GetLabel()))->GetMother();
                Int_t mcmother0 = static_cast<AliAODMCParticle*>(mcArray->At(daughter0->GetLabel()))->GetMother();

                if(mcmother1!=mcmother0) continue;
               
                Int_t pdgALam = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->PdgCode();
                Int_t pdgD1 = static_cast<AliAODMCParticle*>(mcArray->At(daughter1->GetLabel()))->PdgCode();
                Int_t pdgD0 = static_cast<AliAODMCParticle*>(mcArray->At(daughter0->GetLabel()))->PdgCode();
                
                Bool_t isPhyPrim = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->IsPhysicalPrimary();
                if(!isPhyPrim) continue;
                
                if (pdgALam!=-3122) continue;
                if ((pdgD0!=-2212 && pdgD1!=211 )&&(pdgD0!=211 && pdgD1!=-2212 )) continue;
                
                Bool_t isGen = kFALSE;
                for(Int_t iV0Gen=0; iV0Gen <mcTracksV0Sel->GetEntries();iV0Gen++){
                    AliV0ChBasicParticle *gen = (AliV0ChBasicParticle*) mcTracksV0Sel->At(iV0Gen);
                    Int_t genLabel = gen->MyLabel();
                  
                    if(mcmother1==genLabel){
                        motherLabelPrevious[i]=mcmother1;
                        isGen=kTRUE; 
                        break;
                    }

                }
                
                for(Int_t iLab=0;iLab<i;iLab++){
                    
                    if(motherLabelPrevious[iLab]==mcmother1){
                        
                        isGen=kFALSE;
                        break;
                    }
                    
                }
                
               if(isGen){
                   
                       Double_t V0mcPt = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Pt();
                       Double_t V0mcEta = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Eta();
                       Double_t V0mcPhi = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->Phi();
                       Int_t V0Motherlabel = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->GetMother();
                       Int_t V0label = static_cast<AliAODMCParticle*>(mcArray->At(mcmother0))->GetLabel();
                       if(V0mcPt>fPtTrigMin) {
                           selectedMCV0Triggersrec-> Add(new AliV0ChBasicParticle(V0->Eta(), V0->Phi(), V0->Pt(), 3,0,myTrackPos->GetID(),myTrackNeg->GetID()));
                           Double_t v0effic[4]={V0mcPt,lPVz,2.5,V0mcEta};
                           fHistRecV0->Fill(v0effic);
                           fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,6.5);
                       }

                   
               }
            }
            if(V0->Pt()>fPtAsocMin) selectedV0Assoc-> Add(new AliV0ChBasicParticle(V0->Eta(), V0->Phi(), V0->Pt(), 3,0,myTrackPos->GetID(),myTrackNeg->GetID()));
            if(V0->Pt()>fPtTrigMin) selectedV0Triggers-> Add(new AliV0ChBasicParticle(V0->Eta(), V0->Phi(), V0->Pt(), 3,0,myTrackPos->GetID(),myTrackNeg->GetID()));
        }


    }

	Int_t iV0Trigger = selectedV0Triggers->GetEntries();
	Int_t iTrackAssoc = selectedAssociatedTracks->GetEntries();

	// Corelation ==========================================

    
    if(fAnalysisMC){
        //V0-h MC rec
        fHistKorelacieMCrec->Sumw2();
        //Printf("trig rec %d, track %d, assoc rec %d\n",selectedMCV0Triggersrec->GetEntriesFast(),selectedMCtrig->GetEntriesFast(),selectedMCassoc->GetEntriesFast());
        Corelations(selectedMCV0Triggersrec,selectedMCassoc,fHistKorelacieMCrec, lPVz, fHistNumberOfTriggersRec,kFALSE,kTRUE,lPercentile,multip);

        //h-h MC rec
        Corelations(selectedMCtrig,selectedMCassoc,fHistKorelacieMCrec, lPVz, fHistNumberOfTriggersRec,kTRUE,kFALSE,lPercentile,multip);
    }
	fHistKorelacie->Sumw2();

    //Data V0-h
    Corelations(selectedV0Triggers,selectedAssociatedTracks,fHistKorelacie,lPVz,fHistNumberOfTriggers,kFALSE,kTRUE,lPercentile,multip);
	
	// Corelation h-V0 ==========================================

	Int_t iV0Assoc = selectedV0Assoc->GetEntries();
	Int_t iTrackTrig = selectedTriggerTracks->GetEntries();                                                  
    
	/*for(Int_t i=0; i<iTrackTrig; i++){
		AliV0ChBasicParticle* trackTrig = (AliV0ChBasicParticle*) selectedTriggerTracks->At(i);
		
		Float_t phiTrig = trackTrig->Phi();
		Float_t etaTrig = trackTrig->Eta();
		Float_t ptTrig = trackTrig->Pt();
		Short_t candidate = trackTrig->WhichCandidate();

		Double_t tiggers[2] = {ptTrig,candidate-0.5};
		fHistNumberOfTriggers->Fill(tiggers);
		
		
		for (Int_t j=0; j<iV0Assoc; j++){
			AliV0ChBasicParticle* V0Assoc = (AliV0ChBasicParticle*) selectedV0Assoc->At(j);
			
			Float_t phiAssoc = V0Assoc->Phi();
			Float_t etaAssoc = V0Assoc->Eta();
			Float_t ptAssoc = V0Assoc->Pt();
			Short_t candidate = V0Assoc->WhichCandidate();

			Float_t deltaPhi = phiTrig - phiAssoc;
			Float_t deltaEta = etaTrig - etaAssoc;
			if(deltaPhi>(1.5*kPi)) deltaPhi-= 2*kPi;   //trik aby som videla dobre dva piky na delta phi histograme
			if(deltaPhi<(-0.5*kPi)) deltaPhi+= 2*kPi;

			if(ptTrig<ptAssoc) continue;

			if (candidate==1){
				Double_t korelacieK0[6] = {ptTrig, ptAssoc, deltaPhi, deltaEta, lPVz, 4.5};
				fHistKorelacie->Fill(korelacieK0);
			} 

			if (candidate==2){
				Double_t korelacieLambda[6] = {ptTrig, ptAssoc, deltaPhi, deltaEta, lPVz, 5.5};
				fHistKorelacie->Fill(korelacieLambda);
			}

			if (candidate==3){
				Double_t korelacieAntiLambda[6] = {ptTrig, ptAssoc, deltaPhi, deltaEta, lPVz, 6.5};
				fHistKorelacie->Fill(korelacieAntiLambda);
			}


		}

	}*/

	// Corelation h-h ==========================================
    Corelations(selectedTriggerTracks,selectedAssociatedTracks,fHistKorelacie,lPVz,fHistNumberOfTriggers,kFALSE,kFALSE,lPercentile,multip);


 	// Mixing ==============================================

    Double_t count = -1, mineta = -0.8, maxeta = 0.8;
    AliAODTracklets* tracklets = fAOD->GetTracklets();
    Int_t nTr=tracklets->GetNumberOfTracklets();
    for(Int_t iTr=0; iTr<nTr; iTr++){
        Double_t theta=tracklets->GetTheta(iTr);
        Double_t eta=-TMath::Log(TMath::Tan(theta/2.));
        if(eta>mineta && eta<maxeta) count++;
    };
    
    fCentrOrMult = count;
    if (fCentrOrMult<0) return;

    fHistMultVtxz->Fill(fCentrOrMult,lPVz);
	 
	fHistdPhidEtaMix->Sumw2();

	
	fPool = fPoolMgr->GetEventPool(fCentrOrMult, lPVz);
    if (!fPool) {
        AliWarning(Form("No pool found for centrality = %d, zVtx = %f", fCentrOrMult, lPVz));
        return;
    }
 	Int_t nMix = fPool->GetCurrentNEvents();
	if (fPool->IsReady() || fPool->NTracksInPool() > fMixingTracks / 5 || nMix >= 5)
	{
		
 		for (Int_t jMix=0; jMix<nMix; jMix++)
 		{// loop through mixing events
 			TObjArray* bgTracks = fPool->GetEvent(jMix);
            if(fAnalysisMC) {
                
                CorelationsMixing(selectedMCV0Triggersrec,bgTracks,fHistMCMixingRec,lPVz,lPercentile,multip);
                CorelationsMixing(selectedMCtrig,bgTracks,fHistMCMixingRec,lPVz,lPercentile,multip);
            }
 			for (Int_t i=0; i<selectedV0Triggers->GetEntriesFast(); i++)
 			{// loop through selected V0 particles
 				AliV0ChBasicParticle* trigV0 = (AliV0ChBasicParticle*) selectedV0Triggers->At(i);
 				Double_t trigPhiV0 = trigV0->Phi();
 				Double_t trigEtaV0 = trigV0->Eta();
 				Double_t trigPtV0 = trigV0->Pt();
 				Short_t trigCV0 = trigV0->WhichCandidate();
				Double_t trigTypeV0 = trigCV0-0.5;


 				for (Int_t j=0; j<bgTracks->GetEntriesFast(); j++)
 				{ // mixing tracks loop 
 					AliAODTrack* assoc = (AliAODTrack*) bgTracks->At(j);
 					// be careful tracks may have bigger pt than v0s.
 					if ( ( (assoc->Pt())>=trigPtV0 )||( (assoc->Pt())<fPtAsocMin )) continue;

					if(!IsMyGoodPrimaryTrack(assoc)) continue;           // aplikujem cut na preudorapiditu tracku

 					Double_t dEtaMixV0h = trigEtaV0 - assoc->Eta();
 					Double_t dPhiMixV0h = trigPhiV0 - assoc->Phi();
 					if (dPhiMixV0h > (1.5*kPi)) dPhiMixV0h -= 2.0*kPi;
 					if (dPhiMixV0h < (-0.5*kPi)) dPhiMixV0h += 2.0*kPi;
					 
 					Double_t spMixV0h[8] = {trigPtV0, assoc->Pt(), dPhiMixV0h, dEtaMixV0h, lPVz, trigTypeV0, static_cast<Double_t> (multip),lPercentile};
 					fHistdPhidEtaMix->Fill(spMixV0h);

					
                          
                } // end of mixing track loop

        	}

			for(Int_t i=0; i<iTrackTrig;i++){
				AliV0ChBasicParticle* trigh = (AliV0ChBasicParticle*) selectedTriggerTracks->At(i);

				Double_t trigPhih = trigh->Phi();
 				Double_t trigEtah = trigh->Eta();
 				Double_t trigPth = trigh->Pt();
				
				 	for (Int_t j=0; j<bgTracks->GetEntriesFast(); j++){
						 AliAODTrack* assoc = (AliAODTrack*) bgTracks->At(j);

						if (( (assoc->Pt())>=trigPth ) || ( (assoc->Pt())<fPtAsocMin )) continue;

						if(!IsMyGoodPrimaryTrack(assoc)) continue;           // aplikujem cut na preudorapiditu tracku

						Double_t dEtaMixhh = trigEtah - assoc->Eta();
 						Double_t dPhiMixhh = trigPhih - assoc->Phi();
 						if (dPhiMixhh > (1.5*kPi)) dPhiMixhh -= 2.0*kPi;
 						if (dPhiMixhh < (-0.5*kPi)) dPhiMixhh += 2.0*kPi;
					 
 						Double_t spMixhh[8] = {trigPth, assoc->Pt(), dPhiMixhh, dEtaMixhh, lPVz, 3.5, static_cast<Double_t> (multip),lPercentile};
 						fHistdPhidEtaMix->Fill(spMixhh);
					 }


			}

		 }
	}
	TObjArray* cloneArray = (TObjArray *)selectedTracks->Clone();
	cloneArray->SetOwner(kTRUE);
	fPool->UpdatePool(cloneArray);
    
    PostData(1, fOutputList);                           // stream the results the analysis of this event to
                                                        // the output manager which will take care of writing
                                                        // it to a file
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::Terminate(Option_t *)
{
    // terminate
    // called at the END of the analysis (when all events are processed)
}
//_____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodPrimaryTrack(const AliAODTrack *t)
 {
          // Pseudorapidity cut
          if (TMath::Abs(t->Eta())>=0.8) return kFALSE;
		  if (!t->TestFilterBit(768)) return kFALSE;
  
          return kTRUE;
 }
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0AngleK0(const AliAODv0 *t, AliAODVertex *pv) 
{
		//V0 Cosine of Pointing Angle
	    if(t->CosPointingAngle(pv)<=0.97) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0AngleLambda(const AliAODv0 *t, AliAODVertex *pv) 
{
		//V0 Cosine of Pointing Angle
		if(t->CosPointingAngle(pv)<=0.995) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0RapidityLambda(const AliAODv0 *t) 
{
		//Rapidity
		//if(TMath::Abs(t->RapLambda())>=0.5) return kFALSE;
    //Pseudorap
    if(TMath::Abs(t->Eta())>=0.8) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0RapidityK0(const AliAODv0 *t) 
{
		//Rapidity
		//if(TMath::Abs(t->RapK0Short())>=0.5) return kFALSE;
    //Pseudorap
    if(TMath::Abs(t->Eta())>=0.8) return kFALSE;
		
		return kTRUE;
}

//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodLifeTimeK0(Double_t x,Double_t y, Double_t z, const AliAODv0 *V0) 
{
		//Proper Lifetime (mL/p)
		
		Double_t *tParentVertexPosition = new Double_t[3];
		tParentVertexPosition[0]= x;
		tParentVertexPosition[1]= y;
		tParentVertexPosition[2]= z;

		Double_t lenght = V0->DecayLengthV0(tParentVertexPosition);
		Double_t momentum = TMath::Sqrt(TMath::Power(V0->Px(),2)+TMath::Power(V0->Py(),2)+TMath::Power(V0->Pz(),2));
		Double_t mass = V0->MassK0Short();
		Double_t lifetime = (mass*lenght)/momentum;
		
		if(lifetime>=20) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodLifeTimeLambda(Double_t x,Double_t y, Double_t z, const AliAODv0 *V0) 
{
		//Proper Lifetime (mL/p)
		
		Double_t *tParentVertexPosition = new Double_t[3];
		tParentVertexPosition[0]= x;
		tParentVertexPosition[1]= y;
		tParentVertexPosition[2]= z;

		Double_t lenght = V0->DecayLengthV0(tParentVertexPosition);
		Double_t momentum = TMath::Sqrt(TMath::Power(V0->Px(),2)+TMath::Power(V0->Py(),2)+TMath::Power(V0->Pz(),2));
		Double_t mass = V0->MassLambda();
		Double_t lifetime = (mass*lenght)/momentum;
		
		if(lifetime>=30) return kFALSE;
		
		return kTRUE;
}

//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodPID(const AliAODTrack *TrackPos, const AliAODTrack *TrackNeg) {
	
	//TPC dE/dx selection
	Float_t dedxnegative = fPIDResponse->NumberOfSigmasTPC(TrackPos, AliPID::kPion);
	Float_t dedxpositive = fPIDResponse->NumberOfSigmasTPC(TrackNeg, AliPID::kPion);

	if(dedxnegative>=5) return kFALSE;
	if(dedxpositive>=5) return kFALSE;

	return kTRUE;

}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodDaughterTrack(const AliAODTrack *t) {
	// TPC refit
 	if (!t->IsOn(AliAODTrack::kTPCrefit)) return kFALSE;
	Float_t nCrossedRowsTPC = t->GetTPCClusterInfo(2,1);
	if (nCrossedRowsTPC < 70) return kFALSE;
	Int_t findable=t->GetTPCNclsF();
	if (findable <= 0) return kFALSE;
	if (nCrossedRowsTPC/findable < 0.8) return kFALSE;
		
	return kTRUE;
	
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0(const AliAODv0 *v0,const AliAODTrack* myTrackPos, const AliAODTrack* myTrackNeg, Int_t oSta) {
	if (!v0) {
         AliError(Form("ERROR: Could not retrieve aodV0"));
         return kFALSE;
	}

	if (oSta==1) {if (v0->GetOnFlyStatus()) return kFALSE;}
	if (oSta==3) {if (!v0->GetOnFlyStatus()) return kFALSE;}
    
    if (oSta==2){         
	    if (v0->GetOnFlyStatus()){
			return kTRUE;
 	    } else {
			return kFALSE;
	    }
	}
    if (oSta==4){
	    if (!v0->GetOnFlyStatus()){
 			return kTRUE;
        } else {
 			return kFALSE;
 		}
	}

/*	// Get daughters and check them  // je to zbytocne
    AliAODTrack *myTrackNegTest=dynamic_cast<AliAODTrack *>(v0->GetDaughter(1));
	AliAODTrack *myTrackPosTest=dynamic_cast<AliAODTrack *>(v0->GetDaughter(0));
          
 	if (!myTrackPosTest || !myTrackNegTest) {
		Printf("strange analysis::UserExec:: Error:Could not retreive one of the daughter track\n");
 		return kFALSE;
 	}
  
 	if( myTrackPosTest->Charge() ==1){
 		myTrackPos = myTrackPosTest;
    	myTrackNeg = myTrackNegTest;
 	}
  
 	if( myTrackPosTest->Charge() ==-1){
		myTrackPos = myTrackNegTest;
 		myTrackNeg = myTrackPosTest;
 	}*/
  
 	// Track cuts for daughter tracks
   	if ( !(IsMyGoodDaughterTrack(myTrackPos)) || !(IsMyGoodDaughterTrack(myTrackNeg)) ) return kFALSE;

	//DCA Negative Track to PV
	if(v0->DcaNegToPrimVertex()<=0.060) return kFALSE;
	//DCA Positive Track to PV
	if(v0->DcaPosToPrimVertex()<=0.060) return kFALSE;
	//DCA V0 daughters
	if(v0->DcaV0Daughters()>=1.0) return kFALSE;
	//V0 2D Decay Radius
	if(v0->RadiusV0()<=0.5) return kFALSE;
	
	return kTRUE;
}
//____________________________________________________________________________
void AliAnalysisTaskMyTask::Corelations(TObjArray *triggers, TObjArray *associated, THnSparse * fHistKor, Double_t lPVz, THnSparse* fHistNumOfTrig,Bool_t hhMC,Bool_t V0h,Float_t perc, Int_t multipl){

    const Double_t kPi = TMath::Pi();
    Int_t nAssoc = associated->GetEntriesFast();
    Int_t nTrig = triggers->GetEntriesFast();

    for (Int_t i=0; i<nTrig; i++){
        AliV0ChBasicParticle* trig = (AliV0ChBasicParticle*)  triggers->At(i);
        
        Double_t triggers[7]={trig->Pt(),lPVz,trig->Eta(),trig->WhichCandidate()-0.5,trig->Phi(),static_cast<Double_t> (multipl),perc};
        //Printf("mul tri %d \n",multipl);
        fHistNumOfTrig->Fill(triggers);
        for (Int_t j=0; j<nAssoc; j++){
            AliV0ChBasicParticle* assoc = (AliV0ChBasicParticle*)  associated->At(j);

            Double_t deltaEta = trig->Eta() - assoc->Eta();
            Double_t deltaPhi = trig->Phi() - assoc->Phi();
            if (deltaPhi > (1.5*kPi)) deltaPhi -= 2.0*kPi;
            if (deltaPhi < (-0.5*kPi)) deltaPhi += 2.0*kPi;

            if(trig->Pt()<=assoc->Pt()) continue;
            
            if(V0h){
                
                Int_t negID = trig->GetIDNeg();
                Int_t posID = trig->GetIDPos();
                Int_t atrID = assoc->GetIDCh();
                
                if ((TMath::Abs(negID)+1)==(TMath::Abs(atrID))) continue; // preco tam je +1 pri dcerach?
                if ((TMath::Abs(posID)+1)==(TMath::Abs(atrID))) continue;
                //Printf( "id + %d , id - %d, id ch %d\n", posID, negID,atrID);
            }

            Int_t labelTrig = -2;
            Int_t labelAssoc =0;
            if(hhMC){
                labelTrig=trig->MyLabel();
                labelAssoc=assoc->MyLabel();
                
            }
            
            if(labelTrig==labelAssoc) continue; // robi to velky rozdiel v pocte trackov korelacii , divne, nemam teraz rozdiel
            
            Double_t korel[11] = {trig->Pt(),assoc->Pt(),deltaPhi,deltaEta, lPVz,trig->WhichCandidate()-0.5, trig->Eta(),assoc->Eta(),assoc->Phi(),static_cast<Double_t> (multipl),perc};
            fHistKor->Fill(korel);
            }
    }
    

}

//____________________________________________________________________________
void AliAnalysisTaskMyTask::CorelationsMixing(TObjArray *triggers, TObjArray *bgTracks, THnSparse * fHistKor, Double_t lPVz, Float_t perc, Int_t multipl){

    const Double_t kPi = TMath::Pi();
    Int_t nAssoc = bgTracks->GetEntriesFast();
    Int_t nTrig = triggers->GetEntriesFast();

    for (Int_t i=0; i<nTrig; i++){
        AliV0ChBasicParticle* trig = (AliV0ChBasicParticle*)  triggers->At(i);
        for (Int_t j=0; j<nAssoc; j++){
             AliAODTrack* assoc = (AliAODTrack*) bgTracks->At(j);

             if (( (assoc->Pt())>=trig->Pt() ) || ( (assoc->Pt())<fPtAsocMin )) continue;

             if(!IsMyGoodPrimaryTrack(assoc)) continue; 

             Double_t   deltaEta = trig->Eta() - assoc->Eta();
             Double_t   deltaPhi = trig->Phi() - assoc->Phi();
             Double_t   assocPt = assoc->Pt();

            if (deltaPhi > (1.5*kPi)) deltaPhi -= 2.0*kPi;
            if (deltaPhi < (-0.5*kPi)) deltaPhi += 2.0*kPi;
            //Printf("delta phi %g\n", deltaPhi);
            //Printf("deltaEta %g\n", deltaEta);
            
            Double_t korel[8] = {trig->Pt(),assocPt,deltaPhi,deltaEta, lPVz,trig->WhichCandidate()-0.5,static_cast<Double_t> (multipl),perc };
            fHistKor->Fill(korel);
        }
    }
    

}
