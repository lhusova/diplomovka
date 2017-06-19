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
#include <AliAODEvent.h>
#include <AliAODInputHandler.h>
#include "AliAnalysisTaskMyTask.h"
#include <TMath.h>
#include <AliMultiEventInputHandler.h>
#include <AliPIDResponse.h>
#include <AliAODPid.h>
#include <THnSparse.h>
#include <AliAODVertex.h>

//class AliPIDResponse;
class AliAnalysisTaskMyTask;    // your analysis class

using namespace std;            // std namespace: so you can do things like 'cout'

ClassImp(AliAnalysisTaskMyTask) // classimp: necessary for root

AliAnalysisTaskMyTask::AliAnalysisTaskMyTask() : AliAnalysisTaskSE(), 
    fAOD(0), fPIDResponse(0), fOutputList(0), //fHistPt(0), fHistLambdaPhi(0), fHistLambdaHadron(0), fHistK0Hadron(0), fHistPocetLambda(0), 
   //fHistPocetK0(0),  fHistPocetAntiLambda(0), fHistAntiLambdaHadron(0),
	fHistK0MassPtCut(0),fHistAntiLambdaMassPtCut(0), fHistLambdaMassPtCut(0),
	fHistKorelacie(0), fHistV0Multiplicity(0), fHistRadiusBefore(0),fHistRadiusAfter(0)
{
    // default constructor, don't allocate memory here!
    // this is used by root for IO purposes, it needs to remain empty
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::AliAnalysisTaskMyTask(const char* name) : AliAnalysisTaskSE(name),
    fAOD(0), fPIDResponse(0), fOutputList(0), //fHistPt(0), fHistLambdaHadron(0), fHistK0Hadron(0), fHistPocetLambda(0), fHistPocetK0(0), 
//	fHistLambdaPhi(0),fHistAntiLambdaHadron(0), fHistPocetAntiLambda(0),
	fHistLambdaMassPtCut(0), fHistK0MassPtCut(0),  fHistAntiLambdaMassPtCut(0),
	fHistKorelacie(0), fHistV0Multiplicity(0), fHistRadiusBefore(0),fHistRadiusAfter(0)
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
	Float_t kPtBins[] = {0,1,2,5,10};
	Int_t kMassBins = 500;
	Float_t kMassMinK = 0.;
	Float_t kMassMaxK = 1.;

	Float_t kMassMinLambda = 0.8;
	Float_t kMassMaxLambda = 2.;

	Float_t kMassBinsK[kMassBins];
	Float_t kMassBinsLambda[kMassBins];

	kMassBinsK[0] = kMassMinK;
	kMassBinsLambda[0] = kMassMinLambda;
	
	for (Int_t i=0; i<kMassBins; i++){
		kMassBinsK[i+1] = kMassBinsK[i] + (kMassMaxK-kMassMinK)/kMassBins;
		kMassBinsLambda[i+1] = kMassBinsLambda[i] + (kMassMaxLambda-kMassMinLambda)/kMassBins;
	}

	Int_t kNCuts = 14;
	Float_t kCuts[kNCuts];
	kCuts[0]=0;
	for (Int_t i=0; i<kNCuts; i++){
		kCuts[i+1]=kCuts[i]+1;
	}

	Int_t bins[6]= {5,5,72,50,20,3};
	Double_t min[6] = {2.,1., -kPi/2, -1., -10., 0.};
	Double_t max[6] = {15., 15., -kPi/2+2*kPi, 1., 10., 3.};


	
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
   /* fHistPt = new TH1F("fHistPt", "fHistPt", 100, 0, 10);       // create your histogra
    fOutputList->Add(fHistPt);          // don't forget to add it to the list! the list will be written to file, so if you want
                                        // your histogram in the output file, add it to the list!
    
    fHistLambdaPhi = new TH1D("fHistLambdaPhi", "Phi lambda", 144, 0, 2*kPi);    
    fOutputList->Add(fHistLambdaPhi);                        
    fHistLambdaHadron = new TH1D("fHistLambdaHadron", "Uhlove korelacie #Lambda-hadron", 72, -kPi/2, -kPi/2+2*kPi); 
    fOutputList->Add(fHistLambdaHadron); 
    fHistPocetLambda = new TH1D("fHistPocetLambda", "Pocet trigger castic #Lambda", 1, 0, 2);
    fOutputList->Add(fHistPocetLambda); 
    fHistK0Hadron = new TH1D("fHistK0Hadron", "Uhlove korelacie K^{0}-hadron", 72, -kPi/2, -kPi/2+2*kPi);                                    
    fOutputList->Add(fHistK0Hadron); 
    fHistPocetK0 = new TH1D("fHistPocetK0", "Pocet trigger castic K^{0}", 1, 0, 2);
    fOutputList->Add(fHistPocetK0); 
	fHistAntiLambdaHadron = new TH1D("fHistAntiLambdaHadron", "Uhlove korelacie Anti- #Lambda-hadron", 72, -kPi/2, -kPi/2+2*kPi); 
    fOutputList->Add(fHistAntiLambdaHadron); 
    fHistPocetAntiLambda = new TH1D("fHistPocetAntiLambda", "Pocet trigger castic Anti- #Lambda", 1, 0, 2);
    fOutputList->Add(fHistPocetAntiLambda); */
    
    fHistK0MassPtCut = new TH3F ("fHistK0MassPtCut", "fHistK0MassPtCut", kMassBins, kMassBinsK, 4, kPtBins, kNCuts, kCuts);
    fHistLambdaMassPtCut = new TH3F("fHistLambdaMassPtCut", "fHistLambdaMassPtCut", kMassBins, kMassBinsLambda, 4, kPtBins, kNCuts, kCuts);
	fHistAntiLambdaMassPtCut = new TH3F("fHistAntiLambdaMassPtCut", "fHistAntiLambdaMassPtCut", kMassBins, kMassBinsLambda, 4, kPtBins, kNCuts, kCuts);
    fOutputList->Add(fHistK0MassPtCut); 
    fOutputList->Add(fHistLambdaMassPtCut); 
	fOutputList->Add(fHistAntiLambdaMassPtCut); 

	fHistKorelacie = new THnSparseF ("fHistKorelacie","fHistKorelacie", 6, bins, min, max);
	fOutputList->Add(fHistKorelacie); 

	fHistV0Multiplicity = new TH1D ("fHistV0Multiplicity", "fHistV0Multiplicity", 100, 0, 200);
	fOutputList->Add(fHistV0Multiplicity); 

	fHistRadiusBefore = new TH1D ("fHistRadiusBefore", "fHistRadiusBefore", 100, 0, 1);
	fHistRadiusAfter = new TH1D ("fHistRadiusAfter", "fHistRadiusAfter", 100, 0, 1);

	fOutputList->Add(fHistRadiusBefore); 
	fOutputList->Add(fHistRadiusAfter); 
    
    PostData(1, fOutputList);           // postdata will notify the analysis manager of changes / updates to the 
                                        // fOutputList object. the manager will in the end take care of writing your output to file
                                        // so it needs to know what's in the output
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::UserExec(Option_t *)
{
	const Double_t kPi = TMath::Pi();
	
    // user exec
    // this function is called once for each event
    // the manager will take care of reading the events from file, and with the static function InputEvent() you 
    // have access to the current event. 
    // once you return from the UserExec function, the manager will retrieve the next event from the chain
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    AliAODInputHandler *inEvMain = (AliAODInputHandler *) mgr->GetInputEventHandler();
    AliAODEvent *fAOD = (AliAODEvent *) inEvMain -> GetEvent();    // get an event (called fAOD) from the input file
    fPIDResponse = inEvMain-> GetPIDResponse();                                                   
														// there's another event format (ESD) which works in a similar wya
                                                        // but is more cpu/memory unfriendly. for now, we'll stick with aod's
    if(!fAOD) return;                                   // if the pointer to the event is empty (getting it failed) skip this event
        // example part: i'll show how to loop over the tracks in an event 
        // and extract some information from them which we'll store in a histogram
    Int_t iTracks(fAOD->GetNumberOfTracks());           // see how many tracks there are in the event
    Int_t iV0(fAOD->GetNumberOfV0s());                  // see how many V0 there are in the event

	fHistV0Multiplicity->Fill(iV0);

	AliAODVertex *myPrimVertex = fAOD->GetPrimaryVertex();
	if (!myPrimVertex) return;
	Double_t lPVz = myPrimVertex->GetZ();		//poloha prim. vertexu, z-ova zlozka
    
    for(Int_t i=0; i < iTracks; i++) {                 // loop ove rall these tracks
        AliAODTrack* track = static_cast<AliAODTrack*>(fAOD->GetTrack(i));         // get a track (type AliAODTrack) from the event
        if(!track) continue;                            // if we failed, skip this track
        Double_t phiTrack = track->Phi();
		Double_t etaTrack = track->Eta();
       // fHistPt->Fill(track->Pt());                     // plot the pt value of the track in a histogram
        
        for(Int_t j=0; j < iV0; j++) { 
			AliAODv0* V0 = static_cast<AliAODv0*>(fAOD->GetV0(j));
			if(!V0) continue; 
			Double_t massK0=V0->MassK0Short(); // da mi hodnotu invariantnej hmotnosti pre hypotezu rozpadu K0
			Double_t massLambda=V0->MassLambda();
			Double_t massAntilambda=V0->MassAntiLambda();
			
			Double_t phiV0 = V0->Phi(); 
			Double_t etaV0 = V0->Eta(); 
			Double_t deltaPhi = phiV0 - phiTrack;
			if(deltaPhi>1.5*kPi) deltaPhi-= 2*kPi;   //trik aby som videla dobre dva piky na delta phi histograme
			if(deltaPhi<-0.5*kPi) deltaPhi+= 2*kPi;
			
			Double_t deltaEta = etaV0 - etaTrack;
			
			Bool_t k0 = ((massK0>0.)&&(massK0<1.));
			Bool_t Lambda = ((massLambda>0.8)&&(massLambda<2));
			Bool_t Antilambda = ((massAntilambda>0.8)&&(massAntilambda<2));
			
			Double_t ptTrig = V0->Pt();
			Double_t ptAssoc = track->Pt();	
			Bool_t korelacie = ((ptTrig > 2) && (ptTrig < 15) && (ptAssoc < ptTrig) && (ptAssoc > 1));	// velmi prisne podmienky, V0 maju nizsiu pt do 15, hlavne lambdy (vsetky maju pt<4)
			//Bool_t korelacie = (ptAssoc < ptTrig);//&&(ptTrig > 4));
			
			// removing autocorrelations 
            //----------------------------------
            const AliAODTrack *myTrackPos;
			const AliAODTrack *myTrackNeg;
            AliAODTrack *myTrackNegTest=dynamic_cast<AliAODTrack *>(V0->GetDaughter(1));
            AliAODTrack *myTrackPosTest=dynamic_cast<AliAODTrack *>(V0->GetDaughter(0));
  
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
 
            Int_t negID = myTrackNeg->GetID(); 
            Int_t posID = myTrackPos->GetID();
            Int_t atrID = track->GetID();
  
            if ((TMath::Abs(negID)+1)==(TMath::Abs(atrID))) continue;
            if ((TMath::Abs(posID)+1)==(TMath::Abs(atrID))) continue;
            
            //----------------------------------

			// preparations for daughter's PID cut------------------------------
	        Float_t nSigmaPosPion   = 0.;
    	    Float_t nSigmaNegPion   = 0.;
        	Float_t nSigmaPosProton = 0.;
 			Float_t nSigmaNegProton = 0.;
  
          	const AliAODPid *pPid = myTrackPos->GetDetPid();
          	const AliAODPid *nPid = myTrackNeg->GetDetPid();
  
          	if (pPid)
          	{
            	Double_t pdMom = pPid->GetTPCmomentum();
              	if (pdMom<1.)
              	{
                	nSigmaPosPion = fPIDResponse->NumberOfSigmasTPC(myTrackPos, AliPID::kPion);
                  	nSigmaPosProton = fPIDResponse->NumberOfSigmasTPC(myTrackPos, AliPID::kProton);
              	}
          	}
  
          	if (nPid)
         	{
              	Double_t ndMom = nPid->GetTPCmomentum();
              	if (ndMom<1.)
            	{
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
			

			if(!IsMyGoodPrimaryTrack(track)) continue; // aplikujem cut na preudorapiditu tracku
			
			if (k0&&cutK0Pid) {
				
				fHistK0MassPtCut->Fill(massK0,ptTrig,0.5);
				
				if(!IsMyGoodNumberOfTPCCrossedRows(track)) continue; // aplikujem cut crossed rows
				fHistK0MassPtCut->Fill(massK0,ptTrig,1.5);
				
				if(!IsMyGoodFinableRatio(track)) continue;  // aplikujem cut finable ratio
				fHistK0MassPtCut->Fill(massK0,ptTrig,2.5);
				
				if(!IsMyGoodNegV0(V0)) continue;    //cut na vzdialenost neg dcery od PV
				fHistK0MassPtCut->Fill(massK0,ptTrig,3.5);
				
				if(!IsMyGoodPosV0(V0)) continue;    //cut na vzdialenost pos dcery od PV
				fHistK0MassPtCut->Fill(massK0,ptTrig,4.5);
				
				if(!IsMyGoodV0Daughter(V0)) continue;  //DCA V0 daughters
				fHistK0MassPtCut->Fill(massK0,ptTrig,5.5);
				
				fHistRadiusBefore->Fill(V0->RadiusV0());

				if(!IsMyGoodV0Radius(V0)) continue;  //V0 2D Decay Radius
				fHistK0MassPtCut->Fill(massK0,ptTrig,6.5);
				fHistRadiusAfter->Fill(V0->RadiusV0());
				 
				if(!IsMyGoodV0AngleK0(V0)) continue;  //V0 Cosine of Pointing Angle
				fHistK0MassPtCut->Fill(massK0,ptTrig,7.5); 
				
				if(!IsMyGoodV0RapidityK0(V0)) continue; //Rapidity
				fHistK0MassPtCut->Fill(massK0,ptTrig,8.5); 
				
				if(!(V0->GetOnFlyStatus())) continue;  //Offline or On-The-Fly
				fHistK0MassPtCut->Fill(massK0,ptTrig,9.5); 
				
				if(!IsMyGoodLifeTimeK0(V0)) continue;  //Proper Lifetime (mL/p)
				fHistK0MassPtCut->Fill(massK0,ptTrig,10.5); 

				if(!IsMyGoodPID(myTrackPos,myTrackNeg)) continue; //TPC dE/dx selection (Real Data Only)
				fHistK0MassPtCut->Fill(massK0,ptTrig,11.5); 

				if(!IsMyGoodTPCRefit(track)) continue; 
				fHistK0MassPtCut->Fill(massK0,ptTrig,12.5); 

				if(!IsMyGoodV0(V0)) continue;
				fHistK0MassPtCut->Fill(massK0,ptTrig,13.5); 
				
				if (korelacie) {
					//fHistK0Hadron->Fill(deltaPhi); // plnenie histogramu pre korelacie
					//fHistPocetK0->Fill(1);
					Double_t korelacieK0[6] = {ptTrig, ptAssoc, deltaPhi, deltaEta, lPVz, 0.5};
					fHistKorelacie->Fill(korelacieK0);
				}
			}
			if (Lambda&&cutLambdaPid){
				 
				 
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,0.5);

				 if(!IsMyGoodNumberOfTPCCrossedRows(track)) continue; // aplikujem cut crossed rows
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,1.5);
				
				 if(!IsMyGoodFinableRatio(track)) continue;  // aplikujem cut finable ratio
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,2.5);
				
				 if(!IsMyGoodNegV0(V0)) continue;
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,3.5);
				
				 if(!IsMyGoodPosV0(V0)) continue;
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,4.5);
				 
				 if(!IsMyGoodV0Daughter(V0)) continue;
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,5.5);
				 
				 if(!IsMyGoodV0Radius(V0)) continue;  
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,6.5); 
				 
				 if(!IsMyGoodV0AngleLambda(V0)) continue;
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,7.5);
				 
				 if(!IsMyGoodV0RapidityLambda(V0)) continue; 
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,8.5);  
				 
				 if(!(V0->GetOnFlyStatus())) continue;  //Offline or On-The-Fly
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,9.5); 
				 
				 if(!IsMyGoodLifeTimeLambda(V0)) continue;
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,10.5); 
				
				 if(!IsMyGoodPID(myTrackPos,myTrackNeg)) continue; //TPC dE/dx selection (Real Data Only)
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,11.5); 

				 if(!IsMyGoodTPCRefit(track)) continue; 
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,12.5); 

				 if(!IsMyGoodV0(V0)) continue;
				 fHistLambdaMassPtCut->Fill(massLambda,ptTrig,13.5); 
				 
				 if (korelacie) {
					//fHistLambdaHadron->Fill(deltaPhi);
				 	//fHistLambdaPhi->Fill(phiV0);
				 	//fHistPocetLambda->Fill(1);
					Double_t korelacieLambda[6] = {ptTrig, ptAssoc, deltaPhi, deltaEta, lPVz, 1.5};
					fHistKorelacie->Fill(korelacieLambda);
				 }
				 
			 }

			 if (Antilambda&&cutAntiLambdaPid){
				 				 
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,0.5);

				 if(!IsMyGoodNumberOfTPCCrossedRows(track)) continue; // aplikujem cut crossed rows
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,1.5);
				
				 if(!IsMyGoodFinableRatio(track)) continue;  // aplikujem cut finable ratio
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,2.5);
				
				 if(!IsMyGoodNegV0(V0)) continue;
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,3.5);
				
				 if(!IsMyGoodPosV0(V0)) continue;
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,4.5);
				 
				 if(!IsMyGoodV0Daughter(V0)) continue;
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,5.5);
				 
				 if(!IsMyGoodV0Radius(V0)) continue;  
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,6.5); 
				 
				 if(!IsMyGoodV0AngleLambda(V0)) continue;
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,7.5);
				 
				 if(!IsMyGoodV0RapidityLambda(V0)) continue; 
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,8.5);  
				 
				 if(!(V0->GetOnFlyStatus())) continue;  //Offline or On-The-Fly
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,9.5); 
				 
				 if(!IsMyGoodLifeTimeLambda(V0)) continue;
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,10.5); 
				
				 if(!IsMyGoodPID(myTrackPos,myTrackNeg)) continue; //TPC dE/dx selection (Real Data Only)
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,11.5); 

				 if(!IsMyGoodTPCRefit(track)) continue; 
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,12.5); 

				 if(!IsMyGoodV0(V0)) continue;
				 fHistAntiLambdaMassPtCut->Fill(massAntilambda,ptTrig,13.5); 
				 
				 if (korelacie) {
					//fHistAntiLambdaHadron->Fill(deltaPhi);
				 	//fHistPocetAntiLambda->Fill(1);
					Double_t korelacieAntiLambda[6] = {ptTrig, ptAssoc, deltaPhi, deltaEta, lPVz, 2.5};
					fHistKorelacie->Fill(korelacieAntiLambda);
				 }
				 
			 }
			
		}
    }                                                   // continue until all the tracks are processed
    
   
   
    
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
          if (TMath::Abs(t->Eta())>0.8) return kFALSE;
		  if (!t->TestFilterBit(768)) return kFALSE;
  
          return kTRUE;
 }
 //____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodNegV0(const AliAODv0 *t) 
{
		//DCA Negative Track to PV
		if(t->DcaNegToPrimVertex()<=0.060) return kFALSE;
		
		return kTRUE;
}
 //____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodPosV0(const AliAODv0 *t) 
{
		//DCA Positive Track to PV
		if(t->DcaPosToPrimVertex()<=0.060) return kFALSE;
		
		return kTRUE;
}
 //____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0Daughter(const AliAODv0 *t) 
{
		//DCA V0 daughters
		if(t->DcaV0Daughters()>=1.0) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0Radius(const AliAODv0 *t) 
{
		//V0 2D Decay Radius
		if(t->RadiusV0()<=0.5) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0AngleK0(const AliAODv0 *t) 
{
		//V0 Cosine of Pointing Angle
		if(TMath::Cos(t->OpenAngleV0())<=0.97) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0AngleLambda(const AliAODv0 *t) 
{
		//V0 Cosine of Pointing Angle
		if(TMath::Cos(t->OpenAngleV0())<=0.995) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0RapidityLambda(const AliAODv0 *t) 
{
		//Rapidity
		if(TMath::Abs(t->RapLambda())>=0.5) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0RapidityK0(const AliAODv0 *t) 
{
		//Rapidity
		if(TMath::Abs(t->RapK0Short())>=0.5) return kFALSE;
		
		return kTRUE;
}

//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodLifeTimeK0(const AliAODv0 *t) 
{
		//Proper Lifetime (mL/p)
		
		Double_t *tParentVertexPosition = new Double_t[3];
		tParentVertexPosition[0]=(t->DecayVertexV0X());
		tParentVertexPosition[1]=(t->DecayVertexV0Y());
		tParentVertexPosition[2]=(t->DecayVertexV0Z());
		
		if(t->DecayLengthV0(tParentVertexPosition)>=20) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodLifeTimeLambda(const AliAODv0 *t) 
{
		//Proper Lifetime (mL/p)
		
		Double_t *tParentVertexPosition = new Double_t[3];
		tParentVertexPosition[0]=t->DecayVertexV0X();
		tParentVertexPosition[1]=t->DecayVertexV0Y();
		tParentVertexPosition[2]=t->DecayVertexV0Z();
		
		if(t->DecayLengthV0(tParentVertexPosition)>=30) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodNumberOfTPCCrossedRows(const AliAODTrack *t) 
{
		//Number of TPC Crossed Rows

		Float_t nCrossedRowsTPC = t->GetTPCClusterInfo(2,1);
		if (nCrossedRowsTPC < 70) return kFALSE;
		
		return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodFinableRatio(const AliAODTrack *t) 
{
		//Findable Ratio
		Float_t nCrossedRowsTPC = t->GetTPCClusterInfo(2,1);
		if (nCrossedRowsTPC < 70) return kFALSE;
		Int_t findable=t->GetTPCNclsF();
		if (findable <= 0) return kFALSE;
		if (nCrossedRowsTPC/findable < 0.8) return kFALSE;
		
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
Bool_t AliAnalysisTaskMyTask::IsMyGoodTPCRefit(const AliAODTrack *t) {
	// TPC refit
 	if (!t->IsOn(AliAODTrack::kTPCrefit)) return kFALSE;
	
	return kTRUE;
}
//____________________________________________________________________________
Bool_t AliAnalysisTaskMyTask::IsMyGoodV0(const AliAODv0 *t) {
	
	//Competing V 0 Rejection

	Double_t massL = t->MassLambda();
	Double_t massK = t->MassK0Short();
	Double_t massAl = t->MassAntiLambda();
	if ((massK>0.47)&&(massK<0.53)&&(massL>1.10)&&(massL<1.13)) return kFALSE;
	if ((massK>0.47)&&(massK<0.53)&&(massAl>1.10)&&(massAl<1.13)) return kFALSE;

	return kTRUE;
}

