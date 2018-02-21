/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* $Id$ */

#ifndef AliAnalysisTaskMyTask_H
#define AliAnalysisTaskMyTask_H

#include "AliAnalysisTaskSE.h"
#include "AliEventPoolManager.h"

class AliPIDResponse;
class AliEventPoolManager;
class THnSparse;

class AliAnalysisTaskMyTask : public AliAnalysisTaskSE  
{
    public:
                                AliAnalysisTaskMyTask();
                                AliAnalysisTaskMyTask(const char *name);
        virtual                 ~AliAnalysisTaskMyTask();

        virtual void            UserCreateOutputObjects();
        virtual void            UserExec(Option_t* option);
        virtual void            Terminate(Option_t* option);
        
        Bool_t 					IsMyGoodPrimaryTrack(const AliAODTrack* aodtrack);
		Bool_t 					IsMyGoodV0AngleLambda(const AliAODv0 *t, AliAODVertex *pv); 
	    Bool_t 					IsMyGoodV0AngleK0(const AliAODv0 *t, AliAODVertex *pv); 
		Bool_t					IsMyGoodV0RapidityK0(const AliAODv0 *t); 
		Bool_t					IsMyGoodV0RapidityLambda(const AliAODv0 *t); 
		Bool_t 					IsMyGoodLifeTimeK0(Double_t x,Double_t y, Double_t z, const AliAODv0 *V0); 
		Bool_t 					IsMyGoodLifeTimeLambda(Double_t x,Double_t y, Double_t z, const AliAODv0 *V0);  
        Bool_t                  IsMyGoodPID(const AliAODTrack *TrackPos, const AliAODTrack *TrackNeg);
        Bool_t                  IsMyGoodDaughterTrack(const AliAODTrack *t)  ;
	    Bool_t                  IsMyGoodV0(const AliAODv0 *v0,const AliAODTrack* myTrackPos, const AliAODTrack* myTrackNeg, Int_t oSta);

        Int_t                   GetOStatus() { return fOStatus; }

        void                    SetMCAnalysis(Bool_t var) {fAnalysisMC=var;}
        void                    SetPtTrigMin(Double_t var) {fPtTrigMin=var;}
        void                    SetPtAsocMin(Double_t var) {fPtAsocMin=var;}
        void                    Corelations(TObjArray *triggers, TObjArray *associated, THnSparse * fHistKor, Double_t lPVz,THnSparse* fHistNumOfTrig,Bool_t hh,Bool_t V0h,Float_t perc, Int_t multipl);
        void                    CorelationsMixing(TObjArray *triggers, TObjArray *bgTracks, THnSparse * fHistKor, Double_t lPVz,Float_t perc, Int_t multipl);
    private:
        AliAODEvent*            fAOD;           		//! input event
        AliPIDResponse*         fPIDResponse;           //!
        TList*                  fOutputList;    		//! output list
        TH3F*					fHistLambdaMassPtCut;	//!
        TH3F*					fHistK0MassPtCut;		//!
        TH3F*                   fHistAntiLambdaMassPtCut; //!
        THnSparse*              fHistKorelacie;             //!
        THnSparse*              fHistdPhidEtaMix;           //!
        TH1D*                   fHistV0Multiplicity;         //!
        TH2D*                   fHistMultVtxz;              //!
        TH1D*                   fHistEtaAssoc;              //!
        TH1D*                   fHistEtaTrigg;              //!
        TH1D*                   fHistPhiAssoc;              //!
        TH1D*                   fHistPhiTrigg;              //!
        TH3D*                   fHistMCPtAs;            //!
        TH3D*                   fHistRCPtAs;            //!
        THnSparse*              fHistNumberOfTriggers;  //!
        THnSparse*              fHistMCKorelacie;       //!
        THnSparse*              fHistMCMixingRec;       //!

        Bool_t          			  fFillMixed;  // enable event mixing (default: ON)
        Int_t           			  fMixingTracks;      // size of track buffer for event mixing
        Int_t                         fCentrOrMult; // Multiplicity of Event for D eff
        AliEventPoolManager*          fPoolMgr;         //! event pool manager
        AliEventPool*                 fPool; //!
        Bool_t                        fAnalysisMC; //! enable MC study
        Int_t                         fOStatus; //
        Double_t                      fPtTrigMin; //
        Double_t                      fPtAsocMin; //

        THnSparse*              fHistKorelacieMCrec; //!  
        THnSparse*              fHistNumberOfTriggersGen;  //!
        THnSparse*              fHistNumberOfTriggersRec;  //!
    
        THnSparse* fHistRecV0; //!
        THnSparse* fHistGenV0; //!
    
        TH3D*                   fHistMCPtTrigg;            //!
        TH3D*                   fHistRCPtTrigg;            //!
        TH1D*                   fHistSelection;            //!
        TH3D*                   fHistPhiEtaGen;            //!
        TH3D*                   fHistPhiEtaRec;            //!
        TH1F*                   fHistMultipPercentile;     //!
        TH1F*                   fHistMultiplicity;         //!

        AliAnalysisTaskMyTask(const AliAnalysisTaskMyTask&); // not implemented
        AliAnalysisTaskMyTask& operator=(const AliAnalysisTaskMyTask&); // not implemented

        ClassDef(AliAnalysisTaskMyTask, 1);
};

class AliV0ChBasicParticle : public AliVParticle
{
    public:
      AliV0ChBasicParticle(Float_t eta, Float_t phi, Float_t pt, Short_t candidate)
        : fEta(eta), fPhi(phi), fpT(pt), fCandidate(candidate)
      {
      }
    /*AliV0ChBasicParticle(Float_t eta, Float_t phi, Float_t pt, Short_t candidate, Int_t iDh)
    : fEta(eta), fPhi(phi), fpT(pt), fCandidate(candidate),fIDh(iDh)
    {
    }
    AliV0ChBasicParticle(Float_t eta, Float_t phi, Float_t pt, Short_t candidate,Int_t idpos, Int_t idneg)
    : fEta(eta), fPhi(phi), fpT(pt), fCandidate(candidate), fIDpos(idpos), fIDneg(idneg)
    {
    }*/
      AliV0ChBasicParticle(Float_t eta, Float_t phi, Float_t pt, Short_t candidate, Int_t label)
        : fEta(eta), fPhi(phi), fpT(pt), fCandidate(candidate), fLabel(label)
      {
      }
    AliV0ChBasicParticle(Float_t eta, Float_t phi, Float_t pt, Short_t candidate, Int_t label,Int_t iDh)
    : fEta(eta), fPhi(phi), fpT(pt), fCandidate(candidate), fLabel(label), fIDh(iDh)
    {
    }
    AliV0ChBasicParticle(Float_t eta, Float_t phi, Float_t pt, Short_t candidate, Int_t label,Int_t idpos, Int_t idneg)
    : fEta(eta), fPhi(phi), fpT(pt), fCandidate(candidate), fLabel(label), fIDpos(idpos), fIDneg(idneg)
    {
    }
     virtual ~AliV0ChBasicParticle() {}
  
      // kinematics
      virtual Double_t Px() const { AliFatal("Not implemented"); return 0; }
      virtual Double_t Py() const { AliFatal("Not implemented"); return 0; }
      virtual Double_t Pz() const { AliFatal("Not implemented"); return 0; }
      virtual Double_t Pt() const { return fpT; }
      virtual Double_t P() const { AliFatal("Not implemented"); return 0; }
      virtual Bool_t   PxPyPz(Double_t[3]) const { AliFatal("Not implemented"); return 0; }
  
      virtual Double_t Xv() const { AliFatal("Not implemented"); return 0; }
      virtual Double_t Yv() const { AliFatal("Not implemented"); return 0; }
      virtual Double_t Zv() const { AliFatal("Not implemented"); return 0; }
      virtual Bool_t   XvYvZv(Double_t[3]) const { AliFatal("Not implemented"); return 0; }
  
      virtual Double_t OneOverPt()  const { AliFatal("Not implemented"); return 0; }
      virtual Double_t Phi()        const { return fPhi; }
      virtual Double_t Theta()      const { AliFatal("Not implemented"); return 0; }
  
  
      virtual Double_t E()          const { AliFatal("Not implemented"); return 0; }
      virtual Double_t M()          const { AliFatal("Not implemented"); return 0; }
  
      virtual Double_t Eta()        const { return fEta; }
      virtual Double_t Y()          const { AliFatal("Not implemented"); return 0; }
  
      virtual Short_t Charge()      const { AliFatal("Not implemented"); return 0; }
      virtual Int_t   GetLabel()    const { AliFatal("Not implemented"); return 0; }
      // PID
      virtual Int_t   PdgCode()     const { AliFatal("Not implemented"); return 0; }
      virtual const Double_t *PID() const { AliFatal("Not implemented"); return 0; }
  
      virtual Short_t WhichCandidate()      const { return fCandidate; }
    Int_t   MyLabel()             const { return fLabel; }
    Int_t   GetIDCh()             const { return fIDh; }
    Int_t   GetIDPos()            const { return fIDpos; }
    Int_t   GetIDNeg()            const { return fIDneg; }
  
      private:
      Double_t fEta;      // eta
      Double_t fPhi;      // phi
      Double_t fpT;       // pT
      Short_t fCandidate;   // V0 candidate: 1 - K0, 2 - Lambda, 3 - Antilambda, 4 - ChTrack
      Int_t fLabel;   // Label
    Int_t fIDh;   // Label
    Int_t fIDpos;   // Label
    Int_t fIDneg;   // Label
  
      ClassDef( AliV0ChBasicParticle, 1) // class required for event mixing
 };

#endif
