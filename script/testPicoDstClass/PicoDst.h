//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 25 11:27:22 2016 by ROOT version 6.04/00
// from TTree PicoDst/StPicoDst
// found on file: /Users/danielbrandenburg/bnl/local/data/muonPico/st_mtd_15095014_raw_1000002.picoDst.root
//////////////////////////////////////////////////////////

#ifndef PicoDst_h
#define PicoDst_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TObject.h"
#include "utility"
#include <limits>

class PicoDst {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxEvent = 1;
   const Int_t kMaxEventPlane = 1;
   const Int_t kMaxTracks = 1231;
   const Int_t kMaxEmcTrigger = 32;
   const Int_t kMaxMtdTrigger = 1;
   const Int_t kMaxBTOWHit = 1;
   const Int_t kMaxBTofHit = 1;
   const Int_t kMaxMtdHit = 19;
   const Int_t kMaxEmcPidTraits = 397;
   const Int_t kMaxBTofPidTraits = 632;
   const Int_t kMaxMtdPidTraits = 8;
   const Int_t kMaxV0Ks = 1;
   const Int_t kMaxV0L = 1;
   const Int_t kMaxV0Lbar = 1;

   // Declaration of leaf types
   Int_t           Event_;
   Int_t           Event_mRunId[kMaxEvent];   //[Event_]
   Int_t           Event_mEventId[kMaxEvent];   //[Event_]
   UShort_t        Event_mFillId[kMaxEvent];   //[Event_]
   Float_t         Event_mBField[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertex_mX1[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertex_mX2[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertex_mX3[kMaxEvent];   //[Event_]
   Float_t         Event_mSecondVertex_mX1[kMaxEvent];   //[Event_]
   Float_t         Event_mSecondVertex_mX2[kMaxEvent];   //[Event_]
   Float_t         Event_mSecondVertex_mX3[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertexError_mX1[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertexError_mX2[kMaxEvent];   //[Event_]
   Float_t         Event_mPrimaryVertexError_mX3[kMaxEvent];   //[Event_]
   UInt_t          Event_mTriggerWord[kMaxEvent];   //[Event_]
   UInt_t          Event_mTriggerWordMtd[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultFtpcEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultFtpcWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultNeg[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultPos[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult2NegEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult2PosEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult2NegWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMult2PosWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultHalfNegEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultHalfPosEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultHalfNegWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mRefMultHalfPosWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mGRefMult[kMaxEvent];   //[Event_]
   UShort_t        Event_mNHitsHFT[kMaxEvent][4];   //[Event_]
   UChar_t         Event_mNVpdHitsEast[kMaxEvent];   //[Event_]
   UChar_t         Event_mNVpdHitsWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mNT0[kMaxEvent];   //[Event_]
   Short_t         Event_mVzVpd[kMaxEvent];   //[Event_]
   UInt_t          Event_mZDCx[kMaxEvent];   //[Event_]
   UInt_t          Event_mBBCx[kMaxEvent];   //[Event_]
   Float_t         Event_mBackgroundRate[kMaxEvent];   //[Event_]
   Float_t         Event_mBbcBlueBackgroundRate[kMaxEvent];   //[Event_]
   Float_t         Event_mBbcYellowBackgroundRate[kMaxEvent];   //[Event_]
   Float_t         Event_mBbcEastRate[kMaxEvent];   //[Event_]
   Float_t         Event_mBbcWestRate[kMaxEvent];   //[Event_]
   Float_t         Event_mZdcEastRate[kMaxEvent];   //[Event_]
   Float_t         Event_mZdcWestRate[kMaxEvent];   //[Event_]
   UShort_t        Event_mVpd[kMaxEvent][64];   //[Event_]
   UShort_t        Event_mZdcSumAdcEast[kMaxEvent];   //[Event_]
   UShort_t        Event_mZdcSumAdcWest[kMaxEvent];   //[Event_]
   UShort_t        Event_mZdcSmdEastHorizontal[kMaxEvent][8];   //[Event_]
   UShort_t        Event_mZdcSmdEastVertical[kMaxEvent][8];   //[Event_]
   UShort_t        Event_mZdcSmdWestHorizontal[kMaxEvent][8];   //[Event_]
   UShort_t        Event_mZdcSmdWestVertical[kMaxEvent][8];   //[Event_]
   Float_t         Event_mSpaceCharge[kMaxEvent];   //[Event_]
   UShort_t        Event_mbTofTrayMultiplicity[kMaxEvent];   //[Event_]
   UShort_t        Event_mNumberOfGlobalTracks[kMaxEvent];   //[Event_]
   Float_t         Event_mRanking[kMaxEvent];   //[Event_]
   UShort_t        Event_mNBEMCMatch[kMaxEvent];   //[Event_]
   UShort_t        Event_mNBTOFMatch[kMaxEvent];   //[Event_]
   UShort_t        Event_mBbcAdcEast[kMaxEvent][24];   //[Event_]
   UShort_t        Event_mBbcAdcWest[kMaxEvent][24];   //[Event_]
   UChar_t         Event_mHT_Th[kMaxEvent][4];   //[Event_]
   UChar_t         Event_mJP_Th[kMaxEvent][4];   //[Event_]
   Int_t           EventPlane_;
   UInt_t          EventPlane_fUniqueID[kMaxEventPlane];   //[EventPlane_]
   UInt_t          EventPlane_fBits[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQx_eta_pos[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQy_eta_pos[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQx_eta_neg[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQy_eta_neg[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_eta_pos[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_eta_neg[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mWeight_eta_pos[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mWeight_eta_neg[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQx_chg_pos[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQy_chg_pos[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQx_chg_neg[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQy_chg_neg[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_chg_pos_eta_pos[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_chg_pos_eta_neg[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_chg_neg_eta_pos[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_chg_neg_eta_neg[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mWeight_chg_pos[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mWeight_chg_neg[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQx_ran_1[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQy_ran_1[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQx_ran_2[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mQy_ran_2[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_ran_1_eta_pos[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_ran_1_eta_neg[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_ran_2_eta_pos[kMaxEventPlane];   //[EventPlane_]
   Short_t         EventPlane_mNtrk_ran_2_eta_neg[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mWeight_ran_1[kMaxEventPlane];   //[EventPlane_]
   Float_t         EventPlane_mWeight_ran_2[kMaxEventPlane];   //[EventPlane_]
   Int_t           Tracks_;
   UShort_t        Tracks_mId[kMaxTracks];   //[Tracks_]
   UShort_t        Tracks_mChi2[kMaxTracks];   //[Tracks_]
   Float_t         Tracks_mPMomentum_mX1[kMaxTracks];   //[Tracks_]
   Float_t         Tracks_mPMomentum_mX2[kMaxTracks];   //[Tracks_]
   Float_t         Tracks_mPMomentum_mX3[kMaxTracks];   //[Tracks_]
   UShort_t        Tracks_mDedx[kMaxTracks];   //[Tracks_]
   Char_t          Tracks_mNHitsFit[kMaxTracks];   //[Tracks_]
   Char_t          Tracks_mNHitsMax[kMaxTracks];   //[Tracks_]
   UChar_t         Tracks_mNHitsDedx[kMaxTracks];   //[Tracks_]
   Short_t         Tracks_mNSigmaPion[kMaxTracks];   //[Tracks_]
   Short_t         Tracks_mNSigmaKaon[kMaxTracks];   //[Tracks_]
   Short_t         Tracks_mNSigmaProton[kMaxTracks];   //[Tracks_]
   Short_t         Tracks_mNSigmaElectron[kMaxTracks];   //[Tracks_]
   UInt_t          Tracks_mMap0[kMaxTracks];   //[Tracks_]
   UInt_t          Tracks_mMap1[kMaxTracks];   //[Tracks_]
   Float_t         Tracks_mPar[kMaxTracks][6];   //[Tracks_]
   Float_t         Tracks_mErrMatrix[kMaxTracks][15];   //[Tracks_]
   Short_t         Tracks_mEmcPidTraitsIndex[kMaxTracks];   //[Tracks_]
   Short_t         Tracks_mBTofPidTraitsIndex[kMaxTracks];   //[Tracks_]
   Short_t         Tracks_mMtdPidTraitsIndex[kMaxTracks];   //[Tracks_]
   Int_t           EmcTrigger_;
   UInt_t          EmcTrigger_fUniqueID[kMaxEmcTrigger];   //[EmcTrigger_]
   UInt_t          EmcTrigger_fBits[kMaxEmcTrigger];   //[EmcTrigger_]
   UChar_t         EmcTrigger_mFlag[kMaxEmcTrigger];   //[EmcTrigger_]
   UShort_t        EmcTrigger_mId[kMaxEmcTrigger];   //[EmcTrigger_]
   UShort_t        EmcTrigger_mAdc[kMaxEmcTrigger];   //[EmcTrigger_]
   Int_t           MtdTrigger_;
   UInt_t          MtdTrigger_fUniqueID[kMaxMtdTrigger];   //[MtdTrigger_]
   UInt_t          MtdTrigger_fBits[kMaxMtdTrigger];   //[MtdTrigger_]
   UShort_t        MtdTrigger_mVpdTacSum[kMaxMtdTrigger];   //[MtdTrigger_]
   UShort_t        MtdTrigger_mQTtacSum[kMaxMtdTrigger][4][8];   //[MtdTrigger_]
   UShort_t        MtdTrigger_mMT101Tac[kMaxMtdTrigger][4][2];   //[MtdTrigger_]
   UChar_t         MtdTrigger_mMT101Id[kMaxMtdTrigger][4][2];   //[MtdTrigger_]
   UChar_t         MtdTrigger_mTF201TriggerBit[kMaxMtdTrigger];   //[MtdTrigger_]
   Char_t          MtdTrigger_mShouldHaveRejectEvent[kMaxMtdTrigger];   //[MtdTrigger_]
   Int_t           BTOWHit_;
   UInt_t          BTOWHit_fUniqueID[kMaxBTOWHit];   //[BTOWHit_]
   UInt_t          BTOWHit_fBits[kMaxBTOWHit];   //[BTOWHit_]
   UShort_t        BTOWHit_mId[kMaxBTOWHit];   //[BTOWHit_]
   UShort_t        BTOWHit_mAdc[kMaxBTOWHit];   //[BTOWHit_]
   Short_t         BTOWHit_mE[kMaxBTOWHit];   //[BTOWHit_]
   Int_t           BTofHit_;
   UInt_t          BTofHit_fUniqueID[kMaxBTofHit];   //[BTofHit_]
   UInt_t          BTofHit_fBits[kMaxBTofHit];   //[BTofHit_]
   Short_t         BTofHit_mId[kMaxBTofHit];   //[BTofHit_]
   Int_t           MtdHit_;
   UInt_t          MtdHit_fUniqueID[kMaxMtdHit];   //[MtdHit_]
   UInt_t          MtdHit_fBits[kMaxMtdHit];   //[MtdHit_]
   Short_t         MtdHit_mgChannel[kMaxMtdHit];   //[MtdHit_]
   UChar_t         MtdHit_mTriggerFlag[kMaxMtdHit];   //[MtdHit_]
   Float_t         MtdHit_mLeadingEdgeTime_first[kMaxMtdHit];   //[MtdHit_]
   Float_t         MtdHit_mLeadingEdgeTime_second[kMaxMtdHit];   //[MtdHit_]
   Float_t         MtdHit_mTrailingEdgeTime_first[kMaxMtdHit];   //[MtdHit_]
   Float_t         MtdHit_mTrailingEdgeTime_second[kMaxMtdHit];   //[MtdHit_]
   Int_t           EmcPidTraits_;
   UInt_t          EmcPidTraits_fUniqueID[kMaxEmcPidTraits];   //[EmcPidTraits_]
   UInt_t          EmcPidTraits_fBits[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mTrackIndex[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBEMCId[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBTOWADC0[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBTOWE0[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBTOWE[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBEMCDistZ[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBEMCDistPhi[kMaxEmcPidTraits];   //[EmcPidTraits_]
   UChar_t         EmcPidTraits_mBSMDNEta[kMaxEmcPidTraits];   //[EmcPidTraits_]
   UChar_t         EmcPidTraits_mBSMDNPhi[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBTOWId[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Char_t          EmcPidTraits_mBTOWId23[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBTOWE1[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBTOWE2[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBTOWE3[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBTOWDistEta[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Short_t         EmcPidTraits_mBTOWDistPhi[kMaxEmcPidTraits];   //[EmcPidTraits_]
   Int_t           BTofPidTraits_;
   UInt_t          BTofPidTraits_fUniqueID[kMaxBTofPidTraits];   //[BTofPidTraits_]
   UInt_t          BTofPidTraits_fBits[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mTrackIndex[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofCellId[kMaxBTofPidTraits];   //[BTofPidTraits_]
   UChar_t         BTofPidTraits_mBTofMatchFlag[kMaxBTofPidTraits];   //[BTofPidTraits_]
   UShort_t        BTofPidTraits_mBTof[kMaxBTofPidTraits];   //[BTofPidTraits_]
   UShort_t        BTofPidTraits_mBTofBeta[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofYLocal[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofZLocal[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofHitPosX[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofHitPosY[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Short_t         BTofPidTraits_mBTofHitPosZ[kMaxBTofPidTraits];   //[BTofPidTraits_]
   Int_t           MtdPidTraits_;
   UInt_t          MtdPidTraits_fUniqueID[kMaxMtdPidTraits];   //[MtdPidTraits_]
   UInt_t          MtdPidTraits_fBits[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Short_t         MtdPidTraits_mMtdHitChan[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Short_t         MtdPidTraits_mTrackIndex[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Char_t          MtdPidTraits_mMatchFlag[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Float_t         MtdPidTraits_mDeltaY[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Float_t         MtdPidTraits_mDeltaZ[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Float_t         MtdPidTraits_mDeltaTimeOfFlight[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Float_t         MtdPidTraits_mBeta[kMaxMtdPidTraits];   //[MtdPidTraits_]
   Int_t           V0Ks_;
   Short_t         V0Ks_mIndex2Track[kMaxV0Ks][2];   //[V0Ks_]
 //StThreeVector<float> V0Ks_mMomentum[2][kMaxV0Ks];
   Float_t         V0Ks_mV0Pos_mX1[kMaxV0Ks];   //[V0Ks_]
   Float_t         V0Ks_mV0Pos_mX2[kMaxV0Ks];   //[V0Ks_]
   Float_t         V0Ks_mV0Pos_mX3[kMaxV0Ks];   //[V0Ks_]
   UShort_t        V0Ks_mDcaDaughters[kMaxV0Ks];   //[V0Ks_]
   UShort_t        V0Ks_mDca2Vtx[kMaxV0Ks];   //[V0Ks_]
   Float_t         V0Ks_mM[kMaxV0Ks];   //[V0Ks_]
   Int_t           V0L_;
   Short_t         V0L_mIndex2Track[kMaxV0L][2];   //[V0L_]
 //StThreeVector<float> V0L_mMomentum[2][kMaxV0L];
   Float_t         V0L_mV0Pos_mX1[kMaxV0L];   //[V0L_]
   Float_t         V0L_mV0Pos_mX2[kMaxV0L];   //[V0L_]
   Float_t         V0L_mV0Pos_mX3[kMaxV0L];   //[V0L_]
   UShort_t        V0L_mDcaDaughters[kMaxV0L];   //[V0L_]
   UShort_t        V0L_mDca2Vtx[kMaxV0L];   //[V0L_]
   Float_t         V0L_mM[kMaxV0L];   //[V0L_]
   Int_t           V0Lbar_;
   Short_t         V0Lbar_mIndex2Track[kMaxV0Lbar][2];   //[V0Lbar_]
 //StThreeVector<float> V0Lbar_mMomentum[2][kMaxV0Lbar];
   Float_t         V0Lbar_mV0Pos_mX1[kMaxV0Lbar];   //[V0Lbar_]
   Float_t         V0Lbar_mV0Pos_mX2[kMaxV0Lbar];   //[V0Lbar_]
   Float_t         V0Lbar_mV0Pos_mX3[kMaxV0Lbar];   //[V0Lbar_]
   UShort_t        V0Lbar_mDcaDaughters[kMaxV0Lbar];   //[V0Lbar_]
   UShort_t        V0Lbar_mDca2Vtx[kMaxV0Lbar];   //[V0Lbar_]
   Float_t         V0Lbar_mM[kMaxV0Lbar];   //[V0Lbar_]

   // List of branches
   TBranch        *b_Event_;   //!
   TBranch        *b_Event_mRunId;   //!
   TBranch        *b_Event_mEventId;   //!
   TBranch        *b_Event_mFillId;   //!
   TBranch        *b_Event_mBField;   //!
   TBranch        *b_Event_mPrimaryVertex_mX1;   //!
   TBranch        *b_Event_mPrimaryVertex_mX2;   //!
   TBranch        *b_Event_mPrimaryVertex_mX3;   //!
   TBranch        *b_Event_mSecondVertex_mX1;   //!
   TBranch        *b_Event_mSecondVertex_mX2;   //!
   TBranch        *b_Event_mSecondVertex_mX3;   //!
   TBranch        *b_Event_mPrimaryVertexError_mX1;   //!
   TBranch        *b_Event_mPrimaryVertexError_mX2;   //!
   TBranch        *b_Event_mPrimaryVertexError_mX3;   //!
   TBranch        *b_Event_mTriggerWord;   //!
   TBranch        *b_Event_mTriggerWordMtd;   //!
   TBranch        *b_Event_mRefMultFtpcEast;   //!
   TBranch        *b_Event_mRefMultFtpcWest;   //!
   TBranch        *b_Event_mRefMultNeg;   //!
   TBranch        *b_Event_mRefMultPos;   //!
   TBranch        *b_Event_mRefMult2NegEast;   //!
   TBranch        *b_Event_mRefMult2PosEast;   //!
   TBranch        *b_Event_mRefMult2NegWest;   //!
   TBranch        *b_Event_mRefMult2PosWest;   //!
   TBranch        *b_Event_mRefMultHalfNegEast;   //!
   TBranch        *b_Event_mRefMultHalfPosEast;   //!
   TBranch        *b_Event_mRefMultHalfNegWest;   //!
   TBranch        *b_Event_mRefMultHalfPosWest;   //!
   TBranch        *b_Event_mGRefMult;   //!
   TBranch        *b_Event_mNHitsHFT;   //!
   TBranch        *b_Event_mNVpdHitsEast;   //!
   TBranch        *b_Event_mNVpdHitsWest;   //!
   TBranch        *b_Event_mNT0;   //!
   TBranch        *b_Event_mVzVpd;   //!
   TBranch        *b_Event_mZDCx;   //!
   TBranch        *b_Event_mBBCx;   //!
   TBranch        *b_Event_mBackgroundRate;   //!
   TBranch        *b_Event_mBbcBlueBackgroundRate;   //!
   TBranch        *b_Event_mBbcYellowBackgroundRate;   //!
   TBranch        *b_Event_mBbcEastRate;   //!
   TBranch        *b_Event_mBbcWestRate;   //!
   TBranch        *b_Event_mZdcEastRate;   //!
   TBranch        *b_Event_mZdcWestRate;   //!
   TBranch        *b_Event_mVpd;   //!
   TBranch        *b_Event_mZdcSumAdcEast;   //!
   TBranch        *b_Event_mZdcSumAdcWest;   //!
   TBranch        *b_Event_mZdcSmdEastHorizontal;   //!
   TBranch        *b_Event_mZdcSmdEastVertical;   //!
   TBranch        *b_Event_mZdcSmdWestHorizontal;   //!
   TBranch        *b_Event_mZdcSmdWestVertical;   //!
   TBranch        *b_Event_mSpaceCharge;   //!
   TBranch        *b_Event_mbTofTrayMultiplicity;   //!
   TBranch        *b_Event_mNumberOfGlobalTracks;   //!
   TBranch        *b_Event_mRanking;   //!
   TBranch        *b_Event_mNBEMCMatch;   //!
   TBranch        *b_Event_mNBTOFMatch;   //!
   TBranch        *b_Event_mBbcAdcEast;   //!
   TBranch        *b_Event_mBbcAdcWest;   //!
   TBranch        *b_Event_mHT_Th;   //!
   TBranch        *b_Event_mJP_Th;   //!
   TBranch        *b_EventPlane_;   //!
   TBranch        *b_EventPlane_fUniqueID;   //!
   TBranch        *b_EventPlane_fBits;   //!
   TBranch        *b_EventPlane_mQx_eta_pos;   //!
   TBranch        *b_EventPlane_mQy_eta_pos;   //!
   TBranch        *b_EventPlane_mQx_eta_neg;   //!
   TBranch        *b_EventPlane_mQy_eta_neg;   //!
   TBranch        *b_EventPlane_mNtrk_eta_pos;   //!
   TBranch        *b_EventPlane_mNtrk_eta_neg;   //!
   TBranch        *b_EventPlane_mWeight_eta_pos;   //!
   TBranch        *b_EventPlane_mWeight_eta_neg;   //!
   TBranch        *b_EventPlane_mQx_chg_pos;   //!
   TBranch        *b_EventPlane_mQy_chg_pos;   //!
   TBranch        *b_EventPlane_mQx_chg_neg;   //!
   TBranch        *b_EventPlane_mQy_chg_neg;   //!
   TBranch        *b_EventPlane_mNtrk_chg_pos_eta_pos;   //!
   TBranch        *b_EventPlane_mNtrk_chg_pos_eta_neg;   //!
   TBranch        *b_EventPlane_mNtrk_chg_neg_eta_pos;   //!
   TBranch        *b_EventPlane_mNtrk_chg_neg_eta_neg;   //!
   TBranch        *b_EventPlane_mWeight_chg_pos;   //!
   TBranch        *b_EventPlane_mWeight_chg_neg;   //!
   TBranch        *b_EventPlane_mQx_ran_1;   //!
   TBranch        *b_EventPlane_mQy_ran_1;   //!
   TBranch        *b_EventPlane_mQx_ran_2;   //!
   TBranch        *b_EventPlane_mQy_ran_2;   //!
   TBranch        *b_EventPlane_mNtrk_ran_1_eta_pos;   //!
   TBranch        *b_EventPlane_mNtrk_ran_1_eta_neg;   //!
   TBranch        *b_EventPlane_mNtrk_ran_2_eta_pos;   //!
   TBranch        *b_EventPlane_mNtrk_ran_2_eta_neg;   //!
   TBranch        *b_EventPlane_mWeight_ran_1;   //!
   TBranch        *b_EventPlane_mWeight_ran_2;   //!
   TBranch        *b_Tracks_;   //!
   TBranch        *b_Tracks_mId;   //!
   TBranch        *b_Tracks_mChi2;   //!
   TBranch        *b_Tracks_mPMomentum_mX1;   //!
   TBranch        *b_Tracks_mPMomentum_mX2;   //!
   TBranch        *b_Tracks_mPMomentum_mX3;   //!
   TBranch        *b_Tracks_mDedx;   //!
   TBranch        *b_Tracks_mNHitsFit;   //!
   TBranch        *b_Tracks_mNHitsMax;   //!
   TBranch        *b_Tracks_mNHitsDedx;   //!
   TBranch        *b_Tracks_mNSigmaPion;   //!
   TBranch        *b_Tracks_mNSigmaKaon;   //!
   TBranch        *b_Tracks_mNSigmaProton;   //!
   TBranch        *b_Tracks_mNSigmaElectron;   //!
   TBranch        *b_Tracks_mMap0;   //!
   TBranch        *b_Tracks_mMap1;   //!
   TBranch        *b_Tracks_mPar;   //!
   TBranch        *b_Tracks_mErrMatrix;   //!
   TBranch        *b_Tracks_mEmcPidTraitsIndex;   //!
   TBranch        *b_Tracks_mBTofPidTraitsIndex;   //!
   TBranch        *b_Tracks_mMtdPidTraitsIndex;   //!
   TBranch        *b_EmcTrigger_;   //!
   TBranch        *b_EmcTrigger_fUniqueID;   //!
   TBranch        *b_EmcTrigger_fBits;   //!
   TBranch        *b_EmcTrigger_mFlag;   //!
   TBranch        *b_EmcTrigger_mId;   //!
   TBranch        *b_EmcTrigger_mAdc;   //!
   TBranch        *b_MtdTrigger_;   //!
   TBranch        *b_MtdTrigger_fUniqueID;   //!
   TBranch        *b_MtdTrigger_fBits;   //!
   TBranch        *b_MtdTrigger_mVpdTacSum;   //!
   TBranch        *b_MtdTrigger_mQTtacSum;   //!
   TBranch        *b_MtdTrigger_mMT101Tac;   //!
   TBranch        *b_MtdTrigger_mMT101Id;   //!
   TBranch        *b_MtdTrigger_mTF201TriggerBit;   //!
   TBranch        *b_MtdTrigger_mShouldHaveRejectEvent;   //!
   TBranch        *b_BTOWHit_;   //!
   TBranch        *b_BTOWHit_fUniqueID;   //!
   TBranch        *b_BTOWHit_fBits;   //!
   TBranch        *b_BTOWHit_mId;   //!
   TBranch        *b_BTOWHit_mAdc;   //!
   TBranch        *b_BTOWHit_mE;   //!
   TBranch        *b_BTofHit_;   //!
   TBranch        *b_BTofHit_fUniqueID;   //!
   TBranch        *b_BTofHit_fBits;   //!
   TBranch        *b_BTofHit_mId;   //!
   TBranch        *b_MtdHit_;   //!
   TBranch        *b_MtdHit_fUniqueID;   //!
   TBranch        *b_MtdHit_fBits;   //!
   TBranch        *b_MtdHit_mgChannel;   //!
   TBranch        *b_MtdHit_mTriggerFlag;   //!
   TBranch        *b_MtdHit_mLeadingEdgeTime_first;   //!
   TBranch        *b_MtdHit_mLeadingEdgeTime_second;   //!
   TBranch        *b_MtdHit_mTrailingEdgeTime_first;   //!
   TBranch        *b_MtdHit_mTrailingEdgeTime_second;   //!
   TBranch        *b_EmcPidTraits_;   //!
   TBranch        *b_EmcPidTraits_fUniqueID;   //!
   TBranch        *b_EmcPidTraits_fBits;   //!
   TBranch        *b_EmcPidTraits_mTrackIndex;   //!
   TBranch        *b_EmcPidTraits_mBEMCId;   //!
   TBranch        *b_EmcPidTraits_mBTOWADC0;   //!
   TBranch        *b_EmcPidTraits_mBTOWE0;   //!
   TBranch        *b_EmcPidTraits_mBTOWE;   //!
   TBranch        *b_EmcPidTraits_mBEMCDistZ;   //!
   TBranch        *b_EmcPidTraits_mBEMCDistPhi;   //!
   TBranch        *b_EmcPidTraits_mBSMDNEta;   //!
   TBranch        *b_EmcPidTraits_mBSMDNPhi;   //!
   TBranch        *b_EmcPidTraits_mBTOWId;   //!
   TBranch        *b_EmcPidTraits_mBTOWId23;   //!
   TBranch        *b_EmcPidTraits_mBTOWE1;   //!
   TBranch        *b_EmcPidTraits_mBTOWE2;   //!
   TBranch        *b_EmcPidTraits_mBTOWE3;   //!
   TBranch        *b_EmcPidTraits_mBTOWDistEta;   //!
   TBranch        *b_EmcPidTraits_mBTOWDistPhi;   //!
   TBranch        *b_BTofPidTraits_;   //!
   TBranch        *b_BTofPidTraits_fUniqueID;   //!
   TBranch        *b_BTofPidTraits_fBits;   //!
   TBranch        *b_BTofPidTraits_mTrackIndex;   //!
   TBranch        *b_BTofPidTraits_mBTofCellId;   //!
   TBranch        *b_BTofPidTraits_mBTofMatchFlag;   //!
   TBranch        *b_BTofPidTraits_mBTof;   //!
   TBranch        *b_BTofPidTraits_mBTofBeta;   //!
   TBranch        *b_BTofPidTraits_mBTofYLocal;   //!
   TBranch        *b_BTofPidTraits_mBTofZLocal;   //!
   TBranch        *b_BTofPidTraits_mBTofHitPosX;   //!
   TBranch        *b_BTofPidTraits_mBTofHitPosY;   //!
   TBranch        *b_BTofPidTraits_mBTofHitPosZ;   //!
   TBranch        *b_MtdPidTraits_;   //!
   TBranch        *b_MtdPidTraits_fUniqueID;   //!
   TBranch        *b_MtdPidTraits_fBits;   //!
   TBranch        *b_MtdPidTraits_mMtdHitChan;   //!
   TBranch        *b_MtdPidTraits_mTrackIndex;   //!
   TBranch        *b_MtdPidTraits_mMatchFlag;   //!
   TBranch        *b_MtdPidTraits_mDeltaY;   //!
   TBranch        *b_MtdPidTraits_mDeltaZ;   //!
   TBranch        *b_MtdPidTraits_mDeltaTimeOfFlight;   //!
   TBranch        *b_MtdPidTraits_mBeta;   //!
   TBranch        *b_V0Ks_;   //!
   TBranch        *b_V0Ks_mIndex2Track;   //!
   TBranch        *b_V0Ks_mV0Pos_mX1;   //!
   TBranch        *b_V0Ks_mV0Pos_mX2;   //!
   TBranch        *b_V0Ks_mV0Pos_mX3;   //!
   TBranch        *b_V0Ks_mDcaDaughters;   //!
   TBranch        *b_V0Ks_mDca2Vtx;   //!
   TBranch        *b_V0Ks_mM;   //!
   TBranch        *b_V0L_;   //!
   TBranch        *b_V0L_mIndex2Track;   //!
   TBranch        *b_V0L_mV0Pos_mX1;   //!
   TBranch        *b_V0L_mV0Pos_mX2;   //!
   TBranch        *b_V0L_mV0Pos_mX3;   //!
   TBranch        *b_V0L_mDcaDaughters;   //!
   TBranch        *b_V0L_mDca2Vtx;   //!
   TBranch        *b_V0L_mM;   //!
   TBranch        *b_V0Lbar_;   //!
   TBranch        *b_V0Lbar_mIndex2Track;   //!
   TBranch        *b_V0Lbar_mV0Pos_mX1;   //!
   TBranch        *b_V0Lbar_mV0Pos_mX2;   //!
   TBranch        *b_V0Lbar_mV0Pos_mX3;   //!
   TBranch        *b_V0Lbar_mDcaDaughters;   //!
   TBranch        *b_V0Lbar_mDca2Vtx;   //!
   TBranch        *b_V0Lbar_mM;   //!

   PicoDst(TTree *tree=0);
   virtual ~PicoDst();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PicoDst_cxx
PicoDst::PicoDst(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/Users/danielbrandenburg/bnl/local/data/muonPico/st_mtd_15095014_raw_1000002.picoDst.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/Users/danielbrandenburg/bnl/local/data/muonPico/st_mtd_15095014_raw_1000002.picoDst.root");
      }
      f->GetObject("PicoDst",tree);

   }
   Init(tree);
}

PicoDst::~PicoDst()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PicoDst::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PicoDst::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void PicoDst::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Event", &Event_, &b_Event_);
   fChain->SetBranchAddress("Event.mRunId", Event_mRunId, &b_Event_mRunId);
   fChain->SetBranchAddress("Event.mEventId", Event_mEventId, &b_Event_mEventId);
   fChain->SetBranchAddress("Event.mFillId", Event_mFillId, &b_Event_mFillId);
   fChain->SetBranchAddress("Event.mBField", Event_mBField, &b_Event_mBField);
   fChain->SetBranchAddress("Event.mPrimaryVertex.mX1", Event_mPrimaryVertex_mX1, &b_Event_mPrimaryVertex_mX1);
   fChain->SetBranchAddress("Event.mPrimaryVertex.mX2", Event_mPrimaryVertex_mX2, &b_Event_mPrimaryVertex_mX2);
   fChain->SetBranchAddress("Event.mPrimaryVertex.mX3", Event_mPrimaryVertex_mX3, &b_Event_mPrimaryVertex_mX3);
   fChain->SetBranchAddress("Event.mSecondVertex.mX1", Event_mSecondVertex_mX1, &b_Event_mSecondVertex_mX1);
   fChain->SetBranchAddress("Event.mSecondVertex.mX2", Event_mSecondVertex_mX2, &b_Event_mSecondVertex_mX2);
   fChain->SetBranchAddress("Event.mSecondVertex.mX3", Event_mSecondVertex_mX3, &b_Event_mSecondVertex_mX3);
   fChain->SetBranchAddress("Event.mPrimaryVertexError.mX1", Event_mPrimaryVertexError_mX1, &b_Event_mPrimaryVertexError_mX1);
   fChain->SetBranchAddress("Event.mPrimaryVertexError.mX2", Event_mPrimaryVertexError_mX2, &b_Event_mPrimaryVertexError_mX2);
   fChain->SetBranchAddress("Event.mPrimaryVertexError.mX3", Event_mPrimaryVertexError_mX3, &b_Event_mPrimaryVertexError_mX3);
   fChain->SetBranchAddress("Event.mTriggerWord", Event_mTriggerWord, &b_Event_mTriggerWord);
   fChain->SetBranchAddress("Event.mTriggerWordMtd", Event_mTriggerWordMtd, &b_Event_mTriggerWordMtd);
   fChain->SetBranchAddress("Event.mRefMultFtpcEast", Event_mRefMultFtpcEast, &b_Event_mRefMultFtpcEast);
   fChain->SetBranchAddress("Event.mRefMultFtpcWest", Event_mRefMultFtpcWest, &b_Event_mRefMultFtpcWest);
   fChain->SetBranchAddress("Event.mRefMultNeg", Event_mRefMultNeg, &b_Event_mRefMultNeg);
   fChain->SetBranchAddress("Event.mRefMultPos", Event_mRefMultPos, &b_Event_mRefMultPos);
   fChain->SetBranchAddress("Event.mRefMult2NegEast", Event_mRefMult2NegEast, &b_Event_mRefMult2NegEast);
   fChain->SetBranchAddress("Event.mRefMult2PosEast", Event_mRefMult2PosEast, &b_Event_mRefMult2PosEast);
   fChain->SetBranchAddress("Event.mRefMult2NegWest", Event_mRefMult2NegWest, &b_Event_mRefMult2NegWest);
   fChain->SetBranchAddress("Event.mRefMult2PosWest", Event_mRefMult2PosWest, &b_Event_mRefMult2PosWest);
   fChain->SetBranchAddress("Event.mRefMultHalfNegEast", Event_mRefMultHalfNegEast, &b_Event_mRefMultHalfNegEast);
   fChain->SetBranchAddress("Event.mRefMultHalfPosEast", Event_mRefMultHalfPosEast, &b_Event_mRefMultHalfPosEast);
   fChain->SetBranchAddress("Event.mRefMultHalfNegWest", Event_mRefMultHalfNegWest, &b_Event_mRefMultHalfNegWest);
   fChain->SetBranchAddress("Event.mRefMultHalfPosWest", Event_mRefMultHalfPosWest, &b_Event_mRefMultHalfPosWest);
   fChain->SetBranchAddress("Event.mGRefMult", Event_mGRefMult, &b_Event_mGRefMult);
   fChain->SetBranchAddress("Event.mNHitsHFT[4]", Event_mNHitsHFT, &b_Event_mNHitsHFT);
   fChain->SetBranchAddress("Event.mNVpdHitsEast", Event_mNVpdHitsEast, &b_Event_mNVpdHitsEast);
   fChain->SetBranchAddress("Event.mNVpdHitsWest", Event_mNVpdHitsWest, &b_Event_mNVpdHitsWest);
   fChain->SetBranchAddress("Event.mNT0", Event_mNT0, &b_Event_mNT0);
   fChain->SetBranchAddress("Event.mVzVpd", Event_mVzVpd, &b_Event_mVzVpd);
   fChain->SetBranchAddress("Event.mZDCx", Event_mZDCx, &b_Event_mZDCx);
   fChain->SetBranchAddress("Event.mBBCx", Event_mBBCx, &b_Event_mBBCx);
   fChain->SetBranchAddress("Event.mBackgroundRate", Event_mBackgroundRate, &b_Event_mBackgroundRate);
   fChain->SetBranchAddress("Event.mBbcBlueBackgroundRate", Event_mBbcBlueBackgroundRate, &b_Event_mBbcBlueBackgroundRate);
   fChain->SetBranchAddress("Event.mBbcYellowBackgroundRate", Event_mBbcYellowBackgroundRate, &b_Event_mBbcYellowBackgroundRate);
   fChain->SetBranchAddress("Event.mBbcEastRate", Event_mBbcEastRate, &b_Event_mBbcEastRate);
   fChain->SetBranchAddress("Event.mBbcWestRate", Event_mBbcWestRate, &b_Event_mBbcWestRate);
   fChain->SetBranchAddress("Event.mZdcEastRate", Event_mZdcEastRate, &b_Event_mZdcEastRate);
   fChain->SetBranchAddress("Event.mZdcWestRate", Event_mZdcWestRate, &b_Event_mZdcWestRate);
   fChain->SetBranchAddress("Event.mVpd[64]", Event_mVpd, &b_Event_mVpd);
   fChain->SetBranchAddress("Event.mZdcSumAdcEast", Event_mZdcSumAdcEast, &b_Event_mZdcSumAdcEast);
   fChain->SetBranchAddress("Event.mZdcSumAdcWest", Event_mZdcSumAdcWest, &b_Event_mZdcSumAdcWest);
   fChain->SetBranchAddress("Event.mZdcSmdEastHorizontal[8]", Event_mZdcSmdEastHorizontal, &b_Event_mZdcSmdEastHorizontal);
   fChain->SetBranchAddress("Event.mZdcSmdEastVertical[8]", Event_mZdcSmdEastVertical, &b_Event_mZdcSmdEastVertical);
   fChain->SetBranchAddress("Event.mZdcSmdWestHorizontal[8]", Event_mZdcSmdWestHorizontal, &b_Event_mZdcSmdWestHorizontal);
   fChain->SetBranchAddress("Event.mZdcSmdWestVertical[8]", Event_mZdcSmdWestVertical, &b_Event_mZdcSmdWestVertical);
   fChain->SetBranchAddress("Event.mSpaceCharge", Event_mSpaceCharge, &b_Event_mSpaceCharge);
   fChain->SetBranchAddress("Event.mbTofTrayMultiplicity", Event_mbTofTrayMultiplicity, &b_Event_mbTofTrayMultiplicity);
   fChain->SetBranchAddress("Event.mNumberOfGlobalTracks", Event_mNumberOfGlobalTracks, &b_Event_mNumberOfGlobalTracks);
   fChain->SetBranchAddress("Event.mRanking", Event_mRanking, &b_Event_mRanking);
   fChain->SetBranchAddress("Event.mNBEMCMatch", Event_mNBEMCMatch, &b_Event_mNBEMCMatch);
   fChain->SetBranchAddress("Event.mNBTOFMatch", Event_mNBTOFMatch, &b_Event_mNBTOFMatch);
   fChain->SetBranchAddress("Event.mBbcAdcEast[24]", Event_mBbcAdcEast, &b_Event_mBbcAdcEast);
   fChain->SetBranchAddress("Event.mBbcAdcWest[24]", Event_mBbcAdcWest, &b_Event_mBbcAdcWest);
   fChain->SetBranchAddress("Event.mHT_Th[4]", Event_mHT_Th, &b_Event_mHT_Th);
   fChain->SetBranchAddress("Event.mJP_Th[4]", Event_mJP_Th, &b_Event_mJP_Th);
   fChain->SetBranchAddress("EventPlane", &EventPlane_, &b_EventPlane_);
   fChain->SetBranchAddress("EventPlane.fUniqueID", EventPlane_fUniqueID, &b_EventPlane_fUniqueID);
   fChain->SetBranchAddress("EventPlane.fBits", EventPlane_fBits, &b_EventPlane_fBits);
   fChain->SetBranchAddress("EventPlane.mQx_eta_pos", EventPlane_mQx_eta_pos, &b_EventPlane_mQx_eta_pos);
   fChain->SetBranchAddress("EventPlane.mQy_eta_pos", EventPlane_mQy_eta_pos, &b_EventPlane_mQy_eta_pos);
   fChain->SetBranchAddress("EventPlane.mQx_eta_neg", EventPlane_mQx_eta_neg, &b_EventPlane_mQx_eta_neg);
   fChain->SetBranchAddress("EventPlane.mQy_eta_neg", EventPlane_mQy_eta_neg, &b_EventPlane_mQy_eta_neg);
   fChain->SetBranchAddress("EventPlane.mNtrk_eta_pos", EventPlane_mNtrk_eta_pos, &b_EventPlane_mNtrk_eta_pos);
   fChain->SetBranchAddress("EventPlane.mNtrk_eta_neg", EventPlane_mNtrk_eta_neg, &b_EventPlane_mNtrk_eta_neg);
   fChain->SetBranchAddress("EventPlane.mWeight_eta_pos", EventPlane_mWeight_eta_pos, &b_EventPlane_mWeight_eta_pos);
   fChain->SetBranchAddress("EventPlane.mWeight_eta_neg", EventPlane_mWeight_eta_neg, &b_EventPlane_mWeight_eta_neg);
   fChain->SetBranchAddress("EventPlane.mQx_chg_pos", EventPlane_mQx_chg_pos, &b_EventPlane_mQx_chg_pos);
   fChain->SetBranchAddress("EventPlane.mQy_chg_pos", EventPlane_mQy_chg_pos, &b_EventPlane_mQy_chg_pos);
   fChain->SetBranchAddress("EventPlane.mQx_chg_neg", EventPlane_mQx_chg_neg, &b_EventPlane_mQx_chg_neg);
   fChain->SetBranchAddress("EventPlane.mQy_chg_neg", EventPlane_mQy_chg_neg, &b_EventPlane_mQy_chg_neg);
   fChain->SetBranchAddress("EventPlane.mNtrk_chg_pos_eta_pos", EventPlane_mNtrk_chg_pos_eta_pos, &b_EventPlane_mNtrk_chg_pos_eta_pos);
   fChain->SetBranchAddress("EventPlane.mNtrk_chg_pos_eta_neg", EventPlane_mNtrk_chg_pos_eta_neg, &b_EventPlane_mNtrk_chg_pos_eta_neg);
   fChain->SetBranchAddress("EventPlane.mNtrk_chg_neg_eta_pos", EventPlane_mNtrk_chg_neg_eta_pos, &b_EventPlane_mNtrk_chg_neg_eta_pos);
   fChain->SetBranchAddress("EventPlane.mNtrk_chg_neg_eta_neg", EventPlane_mNtrk_chg_neg_eta_neg, &b_EventPlane_mNtrk_chg_neg_eta_neg);
   fChain->SetBranchAddress("EventPlane.mWeight_chg_pos", EventPlane_mWeight_chg_pos, &b_EventPlane_mWeight_chg_pos);
   fChain->SetBranchAddress("EventPlane.mWeight_chg_neg", EventPlane_mWeight_chg_neg, &b_EventPlane_mWeight_chg_neg);
   fChain->SetBranchAddress("EventPlane.mQx_ran_1", EventPlane_mQx_ran_1, &b_EventPlane_mQx_ran_1);
   fChain->SetBranchAddress("EventPlane.mQy_ran_1", EventPlane_mQy_ran_1, &b_EventPlane_mQy_ran_1);
   fChain->SetBranchAddress("EventPlane.mQx_ran_2", EventPlane_mQx_ran_2, &b_EventPlane_mQx_ran_2);
   fChain->SetBranchAddress("EventPlane.mQy_ran_2", EventPlane_mQy_ran_2, &b_EventPlane_mQy_ran_2);
   fChain->SetBranchAddress("EventPlane.mNtrk_ran_1_eta_pos", EventPlane_mNtrk_ran_1_eta_pos, &b_EventPlane_mNtrk_ran_1_eta_pos);
   fChain->SetBranchAddress("EventPlane.mNtrk_ran_1_eta_neg", EventPlane_mNtrk_ran_1_eta_neg, &b_EventPlane_mNtrk_ran_1_eta_neg);
   fChain->SetBranchAddress("EventPlane.mNtrk_ran_2_eta_pos", EventPlane_mNtrk_ran_2_eta_pos, &b_EventPlane_mNtrk_ran_2_eta_pos);
   fChain->SetBranchAddress("EventPlane.mNtrk_ran_2_eta_neg", EventPlane_mNtrk_ran_2_eta_neg, &b_EventPlane_mNtrk_ran_2_eta_neg);
   fChain->SetBranchAddress("EventPlane.mWeight_ran_1", EventPlane_mWeight_ran_1, &b_EventPlane_mWeight_ran_1);
   fChain->SetBranchAddress("EventPlane.mWeight_ran_2", EventPlane_mWeight_ran_2, &b_EventPlane_mWeight_ran_2);
   fChain->SetBranchAddress("Tracks", &Tracks_, &b_Tracks_);
   fChain->SetBranchAddress("Tracks.mId", Tracks_mId, &b_Tracks_mId);
   fChain->SetBranchAddress("Tracks.mChi2", Tracks_mChi2, &b_Tracks_mChi2);
   fChain->SetBranchAddress("Tracks.mPMomentum.mX1", Tracks_mPMomentum_mX1, &b_Tracks_mPMomentum_mX1);
   fChain->SetBranchAddress("Tracks.mPMomentum.mX2", Tracks_mPMomentum_mX2, &b_Tracks_mPMomentum_mX2);
   fChain->SetBranchAddress("Tracks.mPMomentum.mX3", Tracks_mPMomentum_mX3, &b_Tracks_mPMomentum_mX3);
   fChain->SetBranchAddress("Tracks.mDedx", Tracks_mDedx, &b_Tracks_mDedx);
   fChain->SetBranchAddress("Tracks.mNHitsFit", Tracks_mNHitsFit, &b_Tracks_mNHitsFit);
   fChain->SetBranchAddress("Tracks.mNHitsMax", Tracks_mNHitsMax, &b_Tracks_mNHitsMax);
   fChain->SetBranchAddress("Tracks.mNHitsDedx", Tracks_mNHitsDedx, &b_Tracks_mNHitsDedx);
   fChain->SetBranchAddress("Tracks.mNSigmaPion", Tracks_mNSigmaPion, &b_Tracks_mNSigmaPion);
   fChain->SetBranchAddress("Tracks.mNSigmaKaon", Tracks_mNSigmaKaon, &b_Tracks_mNSigmaKaon);
   fChain->SetBranchAddress("Tracks.mNSigmaProton", Tracks_mNSigmaProton, &b_Tracks_mNSigmaProton);
   fChain->SetBranchAddress("Tracks.mNSigmaElectron", Tracks_mNSigmaElectron, &b_Tracks_mNSigmaElectron);
   fChain->SetBranchAddress("Tracks.mMap0", Tracks_mMap0, &b_Tracks_mMap0);
   fChain->SetBranchAddress("Tracks.mMap1", Tracks_mMap1, &b_Tracks_mMap1);
   fChain->SetBranchAddress("Tracks.mPar[6]", Tracks_mPar, &b_Tracks_mPar);
   fChain->SetBranchAddress("Tracks.mErrMatrix[15]", Tracks_mErrMatrix, &b_Tracks_mErrMatrix);
   fChain->SetBranchAddress("Tracks.mEmcPidTraitsIndex", Tracks_mEmcPidTraitsIndex, &b_Tracks_mEmcPidTraitsIndex);
   fChain->SetBranchAddress("Tracks.mBTofPidTraitsIndex", Tracks_mBTofPidTraitsIndex, &b_Tracks_mBTofPidTraitsIndex);
   fChain->SetBranchAddress("Tracks.mMtdPidTraitsIndex", Tracks_mMtdPidTraitsIndex, &b_Tracks_mMtdPidTraitsIndex);
   fChain->SetBranchAddress("EmcTrigger", &EmcTrigger_, &b_EmcTrigger_);
   fChain->SetBranchAddress("EmcTrigger.fUniqueID", EmcTrigger_fUniqueID, &b_EmcTrigger_fUniqueID);
   fChain->SetBranchAddress("EmcTrigger.fBits", EmcTrigger_fBits, &b_EmcTrigger_fBits);
   fChain->SetBranchAddress("EmcTrigger.mFlag", EmcTrigger_mFlag, &b_EmcTrigger_mFlag);
   fChain->SetBranchAddress("EmcTrigger.mId", EmcTrigger_mId, &b_EmcTrigger_mId);
   fChain->SetBranchAddress("EmcTrigger.mAdc", EmcTrigger_mAdc, &b_EmcTrigger_mAdc);
   fChain->SetBranchAddress("MtdTrigger", &MtdTrigger_, &b_MtdTrigger_);
   fChain->SetBranchAddress("MtdTrigger.fUniqueID", MtdTrigger_fUniqueID, &b_MtdTrigger_fUniqueID);
   fChain->SetBranchAddress("MtdTrigger.fBits", MtdTrigger_fBits, &b_MtdTrigger_fBits);
   fChain->SetBranchAddress("MtdTrigger.mVpdTacSum", MtdTrigger_mVpdTacSum, &b_MtdTrigger_mVpdTacSum);
   fChain->SetBranchAddress("MtdTrigger.mQTtacSum[4][8]", MtdTrigger_mQTtacSum, &b_MtdTrigger_mQTtacSum);
   fChain->SetBranchAddress("MtdTrigger.mMT101Tac[4][2]", MtdTrigger_mMT101Tac, &b_MtdTrigger_mMT101Tac);
   fChain->SetBranchAddress("MtdTrigger.mMT101Id[4][2]", MtdTrigger_mMT101Id, &b_MtdTrigger_mMT101Id);
   fChain->SetBranchAddress("MtdTrigger.mTF201TriggerBit", MtdTrigger_mTF201TriggerBit, &b_MtdTrigger_mTF201TriggerBit);
   fChain->SetBranchAddress("MtdTrigger.mShouldHaveRejectEvent", MtdTrigger_mShouldHaveRejectEvent, &b_MtdTrigger_mShouldHaveRejectEvent);
   fChain->SetBranchAddress("BTOWHit", &BTOWHit_, &b_BTOWHit_);
   fChain->SetBranchAddress("BTOWHit.fUniqueID", &BTOWHit_fUniqueID, &b_BTOWHit_fUniqueID);
   fChain->SetBranchAddress("BTOWHit.fBits", &BTOWHit_fBits, &b_BTOWHit_fBits);
   fChain->SetBranchAddress("BTOWHit.mId", &BTOWHit_mId, &b_BTOWHit_mId);
   fChain->SetBranchAddress("BTOWHit.mAdc", &BTOWHit_mAdc, &b_BTOWHit_mAdc);
   fChain->SetBranchAddress("BTOWHit.mE", &BTOWHit_mE, &b_BTOWHit_mE);
   fChain->SetBranchAddress("BTofHit", &BTofHit_, &b_BTofHit_);
   fChain->SetBranchAddress("BTofHit.fUniqueID", &BTofHit_fUniqueID, &b_BTofHit_fUniqueID);
   fChain->SetBranchAddress("BTofHit.fBits", &BTofHit_fBits, &b_BTofHit_fBits);
   fChain->SetBranchAddress("BTofHit.mId", &BTofHit_mId, &b_BTofHit_mId);
   fChain->SetBranchAddress("MtdHit", &MtdHit_, &b_MtdHit_);
   fChain->SetBranchAddress("MtdHit.fUniqueID", MtdHit_fUniqueID, &b_MtdHit_fUniqueID);
   fChain->SetBranchAddress("MtdHit.fBits", MtdHit_fBits, &b_MtdHit_fBits);
   fChain->SetBranchAddress("MtdHit.mgChannel", MtdHit_mgChannel, &b_MtdHit_mgChannel);
   fChain->SetBranchAddress("MtdHit.mTriggerFlag", MtdHit_mTriggerFlag, &b_MtdHit_mTriggerFlag);
   fChain->SetBranchAddress("MtdHit.mLeadingEdgeTime.first", MtdHit_mLeadingEdgeTime_first, &b_MtdHit_mLeadingEdgeTime_first);
   fChain->SetBranchAddress("MtdHit.mLeadingEdgeTime.second", MtdHit_mLeadingEdgeTime_second, &b_MtdHit_mLeadingEdgeTime_second);
   fChain->SetBranchAddress("MtdHit.mTrailingEdgeTime.first", MtdHit_mTrailingEdgeTime_first, &b_MtdHit_mTrailingEdgeTime_first);
   fChain->SetBranchAddress("MtdHit.mTrailingEdgeTime.second", MtdHit_mTrailingEdgeTime_second, &b_MtdHit_mTrailingEdgeTime_second);
   fChain->SetBranchAddress("EmcPidTraits", &EmcPidTraits_, &b_EmcPidTraits_);
   fChain->SetBranchAddress("EmcPidTraits.fUniqueID", EmcPidTraits_fUniqueID, &b_EmcPidTraits_fUniqueID);
   fChain->SetBranchAddress("EmcPidTraits.fBits", EmcPidTraits_fBits, &b_EmcPidTraits_fBits);
   fChain->SetBranchAddress("EmcPidTraits.mTrackIndex", EmcPidTraits_mTrackIndex, &b_EmcPidTraits_mTrackIndex);
   fChain->SetBranchAddress("EmcPidTraits.mBEMCId", EmcPidTraits_mBEMCId, &b_EmcPidTraits_mBEMCId);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWADC0", EmcPidTraits_mBTOWADC0, &b_EmcPidTraits_mBTOWADC0);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWE0", EmcPidTraits_mBTOWE0, &b_EmcPidTraits_mBTOWE0);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWE", EmcPidTraits_mBTOWE, &b_EmcPidTraits_mBTOWE);
   fChain->SetBranchAddress("EmcPidTraits.mBEMCDistZ", EmcPidTraits_mBEMCDistZ, &b_EmcPidTraits_mBEMCDistZ);
   fChain->SetBranchAddress("EmcPidTraits.mBEMCDistPhi", EmcPidTraits_mBEMCDistPhi, &b_EmcPidTraits_mBEMCDistPhi);
   fChain->SetBranchAddress("EmcPidTraits.mBSMDNEta", EmcPidTraits_mBSMDNEta, &b_EmcPidTraits_mBSMDNEta);
   fChain->SetBranchAddress("EmcPidTraits.mBSMDNPhi", EmcPidTraits_mBSMDNPhi, &b_EmcPidTraits_mBSMDNPhi);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWId", EmcPidTraits_mBTOWId, &b_EmcPidTraits_mBTOWId);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWId23", EmcPidTraits_mBTOWId23, &b_EmcPidTraits_mBTOWId23);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWE1", EmcPidTraits_mBTOWE1, &b_EmcPidTraits_mBTOWE1);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWE2", EmcPidTraits_mBTOWE2, &b_EmcPidTraits_mBTOWE2);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWE3", EmcPidTraits_mBTOWE3, &b_EmcPidTraits_mBTOWE3);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWDistEta", EmcPidTraits_mBTOWDistEta, &b_EmcPidTraits_mBTOWDistEta);
   fChain->SetBranchAddress("EmcPidTraits.mBTOWDistPhi", EmcPidTraits_mBTOWDistPhi, &b_EmcPidTraits_mBTOWDistPhi);
   fChain->SetBranchAddress("BTofPidTraits", &BTofPidTraits_, &b_BTofPidTraits_);
   fChain->SetBranchAddress("BTofPidTraits.fUniqueID", BTofPidTraits_fUniqueID, &b_BTofPidTraits_fUniqueID);
   fChain->SetBranchAddress("BTofPidTraits.fBits", BTofPidTraits_fBits, &b_BTofPidTraits_fBits);
   fChain->SetBranchAddress("BTofPidTraits.mTrackIndex", BTofPidTraits_mTrackIndex, &b_BTofPidTraits_mTrackIndex);
   fChain->SetBranchAddress("BTofPidTraits.mBTofCellId", BTofPidTraits_mBTofCellId, &b_BTofPidTraits_mBTofCellId);
   fChain->SetBranchAddress("BTofPidTraits.mBTofMatchFlag", BTofPidTraits_mBTofMatchFlag, &b_BTofPidTraits_mBTofMatchFlag);
   fChain->SetBranchAddress("BTofPidTraits.mBTof", BTofPidTraits_mBTof, &b_BTofPidTraits_mBTof);
   fChain->SetBranchAddress("BTofPidTraits.mBTofBeta", BTofPidTraits_mBTofBeta, &b_BTofPidTraits_mBTofBeta);
   fChain->SetBranchAddress("BTofPidTraits.mBTofYLocal", BTofPidTraits_mBTofYLocal, &b_BTofPidTraits_mBTofYLocal);
   fChain->SetBranchAddress("BTofPidTraits.mBTofZLocal", BTofPidTraits_mBTofZLocal, &b_BTofPidTraits_mBTofZLocal);
   fChain->SetBranchAddress("BTofPidTraits.mBTofHitPosX", BTofPidTraits_mBTofHitPosX, &b_BTofPidTraits_mBTofHitPosX);
   fChain->SetBranchAddress("BTofPidTraits.mBTofHitPosY", BTofPidTraits_mBTofHitPosY, &b_BTofPidTraits_mBTofHitPosY);
   fChain->SetBranchAddress("BTofPidTraits.mBTofHitPosZ", BTofPidTraits_mBTofHitPosZ, &b_BTofPidTraits_mBTofHitPosZ);
   fChain->SetBranchAddress("MtdPidTraits", &MtdPidTraits_, &b_MtdPidTraits_);
   fChain->SetBranchAddress("MtdPidTraits.fUniqueID", MtdPidTraits_fUniqueID, &b_MtdPidTraits_fUniqueID);
   fChain->SetBranchAddress("MtdPidTraits.fBits", MtdPidTraits_fBits, &b_MtdPidTraits_fBits);
   fChain->SetBranchAddress("MtdPidTraits.mMtdHitChan", MtdPidTraits_mMtdHitChan, &b_MtdPidTraits_mMtdHitChan);
   fChain->SetBranchAddress("MtdPidTraits.mTrackIndex", MtdPidTraits_mTrackIndex, &b_MtdPidTraits_mTrackIndex);
   fChain->SetBranchAddress("MtdPidTraits.mMatchFlag", MtdPidTraits_mMatchFlag, &b_MtdPidTraits_mMatchFlag);
   fChain->SetBranchAddress("MtdPidTraits.mDeltaY", MtdPidTraits_mDeltaY, &b_MtdPidTraits_mDeltaY);
   fChain->SetBranchAddress("MtdPidTraits.mDeltaZ", MtdPidTraits_mDeltaZ, &b_MtdPidTraits_mDeltaZ);
   fChain->SetBranchAddress("MtdPidTraits.mDeltaTimeOfFlight", MtdPidTraits_mDeltaTimeOfFlight, &b_MtdPidTraits_mDeltaTimeOfFlight);
   fChain->SetBranchAddress("MtdPidTraits.mBeta", MtdPidTraits_mBeta, &b_MtdPidTraits_mBeta);
   fChain->SetBranchAddress("V0Ks", &V0Ks_, &b_V0Ks_);
   fChain->SetBranchAddress("V0Ks.mIndex2Track[2]", &V0Ks_mIndex2Track, &b_V0Ks_mIndex2Track);
   fChain->SetBranchAddress("V0Ks.mV0Pos.mX1", &V0Ks_mV0Pos_mX1, &b_V0Ks_mV0Pos_mX1);
   fChain->SetBranchAddress("V0Ks.mV0Pos.mX2", &V0Ks_mV0Pos_mX2, &b_V0Ks_mV0Pos_mX2);
   fChain->SetBranchAddress("V0Ks.mV0Pos.mX3", &V0Ks_mV0Pos_mX3, &b_V0Ks_mV0Pos_mX3);
   fChain->SetBranchAddress("V0Ks.mDcaDaughters", &V0Ks_mDcaDaughters, &b_V0Ks_mDcaDaughters);
   fChain->SetBranchAddress("V0Ks.mDca2Vtx", &V0Ks_mDca2Vtx, &b_V0Ks_mDca2Vtx);
   fChain->SetBranchAddress("V0Ks.mM", &V0Ks_mM, &b_V0Ks_mM);
   fChain->SetBranchAddress("V0L", &V0L_, &b_V0L_);
   fChain->SetBranchAddress("V0L.mIndex2Track[2]", &V0L_mIndex2Track, &b_V0L_mIndex2Track);
   fChain->SetBranchAddress("V0L.mV0Pos.mX1", &V0L_mV0Pos_mX1, &b_V0L_mV0Pos_mX1);
   fChain->SetBranchAddress("V0L.mV0Pos.mX2", &V0L_mV0Pos_mX2, &b_V0L_mV0Pos_mX2);
   fChain->SetBranchAddress("V0L.mV0Pos.mX3", &V0L_mV0Pos_mX3, &b_V0L_mV0Pos_mX3);
   fChain->SetBranchAddress("V0L.mDcaDaughters", &V0L_mDcaDaughters, &b_V0L_mDcaDaughters);
   fChain->SetBranchAddress("V0L.mDca2Vtx", &V0L_mDca2Vtx, &b_V0L_mDca2Vtx);
   fChain->SetBranchAddress("V0L.mM", &V0L_mM, &b_V0L_mM);
   fChain->SetBranchAddress("V0Lbar", &V0Lbar_, &b_V0Lbar_);
   fChain->SetBranchAddress("V0Lbar.mIndex2Track[2]", &V0Lbar_mIndex2Track, &b_V0Lbar_mIndex2Track);
   fChain->SetBranchAddress("V0Lbar.mV0Pos.mX1", &V0Lbar_mV0Pos_mX1, &b_V0Lbar_mV0Pos_mX1);
   fChain->SetBranchAddress("V0Lbar.mV0Pos.mX2", &V0Lbar_mV0Pos_mX2, &b_V0Lbar_mV0Pos_mX2);
   fChain->SetBranchAddress("V0Lbar.mV0Pos.mX3", &V0Lbar_mV0Pos_mX3, &b_V0Lbar_mV0Pos_mX3);
   fChain->SetBranchAddress("V0Lbar.mDcaDaughters", &V0Lbar_mDcaDaughters, &b_V0Lbar_mDcaDaughters);
   fChain->SetBranchAddress("V0Lbar.mDca2Vtx", &V0Lbar_mDca2Vtx, &b_V0Lbar_mDca2Vtx);
   fChain->SetBranchAddress("V0Lbar.mM", &V0Lbar_mM, &b_V0Lbar_mM);
   Notify();
}

Bool_t PicoDst::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PicoDst::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PicoDst::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PicoDst_cxx
