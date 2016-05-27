

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

#include <string>
#include <limits>

class PicoDst {
public:
	int year() const {
		return Event_mRunId[0]/1000000 - 1 + 2000;
	}

	int day() const{
		return (Event_mRunId[0]%1000000)/1000;
	}


	bool isMtdTrigger( std::string trigger ){
		if ( "dimuon" == trigger )
			return isDiMuon();
		if ( "singlemuon" == trigger )
			return isSingleMuon();
		if ( "dimuonhft" == trigger )
			return isDiMuonHFT();
		if ( "emu" == trigger )
			return isEMuon();
		return false;
	}


	// Is this a dimuon trigger
	bool isDiMuon() const {
		if(year()==2014){ 
			for(Int_t i=0; i<8; i++) {
				if(Event_mTriggerWordMtd[0] & (1<<i)) return true;
			}
		} else if(year()==2013) { 
			for(Int_t i=0; i<2; i++) {
				if(Event_mTriggerWordMtd[0] & (1<<i)) return true;
			}
		}
		return false;
	}

	bool isDiMuonHFT() const { 
		if(year()==2014){ 
			for(Int_t i=5; i<8; i++){
				if(Event_mTriggerWordMtd[0] & (1<<i)) return true;
			}
		}
		return false;
	} 

	bool isSingleMuon() const { 
		if(year()==2014){ 
			for(Int_t i=13; i<18; i++){
				if(Event_mTriggerWordMtd[0] & (1<<i)) return true;
			}
		} else if(year()==2013) { 
			for(Int_t i=5; i<7; i++) {
				if(Event_mTriggerWordMtd[0] & (1<<i)) return true;
			}
		}
		return false;
	}

	bool isEMuon() const { 
		if(year()==2014){ 
			for(Int_t i=8; i<13; i++) {
				if(Event_mTriggerWordMtd[0] & (1<<i)) return true;
			}
		} else if(year()==2013) { 
			for(Int_t i=2; i<5; i++) {
				if(Event_mTriggerWordMtd[0] & (1<<i)) return true;
			}
		}
		return false;
	}


	Long64_t readEventBranches( Long64_t iEntry ){
		
		Long64_t read = 0;
		// read += b_Event_->GetEntry( iEntry );
		// read += b_Event_mRunId->GetEntry( iEntry );
		// read += b_Event_mEventId->GetEntry( iEntry );
		// read += b_Event_mBField->GetEntry( iEntry );
		// read += b_Event_mPrimaryVertex_mX1->GetEntry( iEntry );
		// read += b_Event_mPrimaryVertex_mX2->GetEntry( iEntry );
		// read += b_Event_mPrimaryVertex_mX3->GetEntry( iEntry );
		// read += b_Event_mZDCx->GetEntry( iEntry );
		// read += b_Event_mGRefMult->GetEntry( iEntry );

		return read;



		// b_Event_mTriggerWordMtd->GetEntry( iEntry );


		// b_Event_mTriggerWord->GetEntry( iEntry );
		// b_Event_mFillId->GetEntry( iEntry );
		// b_Event_mSecondVertex_mX1->GetEntry( iEntry );
		// b_Event_mSecondVertex_mX2->GetEntry( iEntry );
		// b_Event_mSecondVertex_mX3->GetEntry( iEntry );
		// b_Event_mPrimaryVertexError_mX1->GetEntry( iEntry );
		// b_Event_mPrimaryVertexError_mX2->GetEntry( iEntry );
		// b_Event_mPrimaryVertexError_mX3->GetEntry( iEntry );
		
		// b_Event_mRefMultFtpcEast->GetEntry( iEntry );
		// b_Event_mRefMultFtpcWest->GetEntry( iEntry );
		// b_Event_mRefMultNeg->GetEntry( iEntry );
		// b_Event_mRefMultPos->GetEntry( iEntry );
		// b_Event_mRefMult2NegEast->GetEntry( iEntry );
		// b_Event_mRefMult2PosEast->GetEntry( iEntry );
		// b_Event_mRefMult2NegWest->GetEntry( iEntry );
		// b_Event_mRefMult2PosWest->GetEntry( iEntry );
		// b_Event_mRefMultHalfNegEast->GetEntry( iEntry );
		// b_Event_mRefMultHalfPosEast->GetEntry( iEntry );
		// b_Event_mRefMultHalfNegWest->GetEntry( iEntry );
		// b_Event_mRefMultHalfPosWest->GetEntry( iEntry );
		
		// b_Event_mNHitsHFT->GetEntry( iEntry );
		// b_Event_mNVpdHitsEast->GetEntry( iEntry );
		// b_Event_mNVpdHitsWest->GetEntry( iEntry );
		// b_Event_mNT0->GetEntry( iEntry );
		// b_Event_mVzVpd->GetEntry( iEntry );
		
		// b_Event_mBBCx->GetEntry( iEntry );
		// b_Event_mBackgroundRate->GetEntry( iEntry );
		// b_Event_mBbcBlueBackgroundRate->GetEntry( iEntry );
		// b_Event_mBbcYellowBackgroundRate->GetEntry( iEntry );
		// b_Event_mBbcEastRate->GetEntry( iEntry );
		// b_Event_mBbcWestRate->GetEntry( iEntry );
		// b_Event_mZdcEastRate->GetEntry( iEntry );
		// b_Event_mZdcWestRate->GetEntry( iEntry );
		// b_Event_mVpd->GetEntry( iEntry );
		// b_Event_mZdcSumAdcEast->GetEntry( iEntry );
		// b_Event_mZdcSumAdcWest->GetEntry( iEntry );
		// b_Event_mZdcSmdEastHorizontal->GetEntry( iEntry );
		// b_Event_mZdcSmdEastVertical->GetEntry( iEntry );
		// b_Event_mZdcSmdWestHorizontal->GetEntry( iEntry );
		// b_Event_mZdcSmdWestVertical->GetEntry( iEntry );
		// b_Event_mSpaceCharge->GetEntry( iEntry );
		// b_Event_mbTofTrayMultiplicity->GetEntry( iEntry );
		// b_Event_mNumberOfGlobalTracks->GetEntry( iEntry );
		// b_Event_mRanking->GetEntry( iEntry );
		// b_Event_mNBEMCMatch->GetEntry( iEntry );
		// b_Event_mNBTOFMatch->GetEntry( iEntry );
		// b_Event_mBbcAdcEast->GetEntry( iEntry );
		// b_Event_mBbcAdcWest->GetEntry( iEntry );
		// b_Event_mHT_Th->GetEntry( iEntry );
		// b_Event_mJP_Th->GetEntry( iEntry );


	}




public :
	TTree          *fChain;   //!pointer to the analyzed TTree or TChain
	Int_t           fCurrent; //!current Tree number in a TChain

	// Fixed size dimensions of array or collections stored in the TTree if any.
	static const Int_t kMaxEvent = 1;
	static const Int_t kMaxEventPlane = 1;
	static const Int_t kMaxTracks = 3000;
	static const Int_t kMaxEmcTrigger = 32;
	static const Int_t kMaxMtdTrigger = 1;
	static const Int_t kMaxBTOWHit = 1;
	static const Int_t kMaxBTofHit = 1;
	static const Int_t kMaxMtdHit = 100;
	static const Int_t kMaxEmcPidTraits = 1000;
	static const Int_t kMaxBTofPidTraits = 2000;
	static const Int_t kMaxMtdPidTraits = 8;
	static const Int_t kMaxV0Ks = 1;
	static const Int_t kMaxV0L = 1;
	static const Int_t kMaxV0Lbar = 1;

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

	Float_t         V0Ks_mV0Pos_mX1[kMaxV0Ks];   //[V0Ks_]
	Float_t         V0Ks_mV0Pos_mX2[kMaxV0Ks];   //[V0Ks_]
	Float_t         V0Ks_mV0Pos_mX3[kMaxV0Ks];   //[V0Ks_]
	UShort_t        V0Ks_mDcaDaughters[kMaxV0Ks];   //[V0Ks_]
	UShort_t        V0Ks_mDca2Vtx[kMaxV0Ks];   //[V0Ks_]
	Float_t         V0Ks_mM[kMaxV0Ks];   //[V0Ks_]
	Int_t           V0L_;
	Short_t         V0L_mIndex2Track[kMaxV0L][2];   //[V0L_]

	Float_t         V0L_mV0Pos_mX1[kMaxV0L];   //[V0L_]
	Float_t         V0L_mV0Pos_mX2[kMaxV0L];   //[V0L_]
	Float_t         V0L_mV0Pos_mX3[kMaxV0L];   //[V0L_]
	UShort_t        V0L_mDcaDaughters[kMaxV0L];   //[V0L_]
	UShort_t        V0L_mDca2Vtx[kMaxV0L];   //[V0L_]
	Float_t         V0L_mM[kMaxV0L];   //[V0L_]
	Int_t           V0Lbar_;
	Short_t         V0Lbar_mIndex2Track[kMaxV0Lbar][2];   //[V0Lbar_]

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
	virtual Bool_t   Notify();
	virtual void     Show(Long64_t entry = -1);

	

	template <typename T>
	T get( std::string var, unsigned int i = 0, unsigned int j = 0, unsigned int k = 0 ) {


		// added aliases
		if (var == "Event.mRefMult" ) return Event_mRefMultPos[0]+Event_mRefMultNeg[0];

		if (var == "Event_" ) return Event_;
		if (var == "Event.mRunId" ) return Event_mRunId[0];
		if (var == "Event.mEventId" ) return Event_mEventId[0];
		if (var == "Event.mFillId" ) return Event_mFillId[0];
		if (var == "Event.mBField" ) return Event_mBField[0];
		if (var == "Event.mPrimaryVertex.mX1" ) return Event_mPrimaryVertex_mX1[0];
		if (var == "Event.mPrimaryVertex.mX2" ) return Event_mPrimaryVertex_mX2[0];
		if (var == "Event.mPrimaryVertex.mX3" ) return Event_mPrimaryVertex_mX3[0];
		if (var == "Event.mSecondVertex.mX1" ) return Event_mSecondVertex_mX1[0];
		if (var == "Event.mSecondVertex.mX2" ) return Event_mSecondVertex_mX2[0];
		if (var == "Event.mSecondVertex.mX3" ) return Event_mSecondVertex_mX3[0];
		if (var == "Event.mPrimaryVertexError.mX1" ) return Event_mPrimaryVertexError_mX1[0];
		if (var == "Event.mPrimaryVertexError.mX2" ) return Event_mPrimaryVertexError_mX2[0];
		if (var == "Event.mPrimaryVertexError.mX3" ) return Event_mPrimaryVertexError_mX3[0];
		if (var == "Event.mTriggerWord" ) return Event_mTriggerWord[0];
		if (var == "Event.mTriggerWordMtd" ) return Event_mTriggerWordMtd[0];
		if (var == "Event.mRefMultFtpcEast" ) return Event_mRefMultFtpcEast[0];
		if (var == "Event.mRefMultFtpcWest" ) return Event_mRefMultFtpcWest[0];
		if (var == "Event.mRefMultNeg" ) return Event_mRefMultNeg[0];
		if (var == "Event.mRefMultPos" ) return Event_mRefMultPos[0];
		if (var == "Event.mRefMult2NegEast" ) return Event_mRefMult2NegEast[0];
		if (var == "Event.mRefMult2PosEast" ) return Event_mRefMult2PosEast[0];
		if (var == "Event.mRefMult2NegWest" ) return Event_mRefMult2NegWest[0];
		if (var == "Event.mRefMult2PosWest" ) return Event_mRefMult2PosWest[0];
		if (var == "Event.mRefMultHalfNegEast" ) return Event_mRefMultHalfNegEast[0];
		if (var == "Event.mRefMultHalfPosEast" ) return Event_mRefMultHalfPosEast[0];
		if (var == "Event.mRefMultHalfNegWest" ) return Event_mRefMultHalfNegWest[0];
		if (var == "Event.mRefMultHalfPosWest" ) return Event_mRefMultHalfPosWest[0];
		if (var == "Event.mGRefMult" ) return Event_mGRefMult[0];
		if (var == "Event.mNHitsHFT" ) return Event_mNHitsHFT[0][i];
		if (var == "Event.mNVpdHitsEast" ) return Event_mNVpdHitsEast[0];
		if (var == "Event.mNVpdHitsWest" ) return Event_mNVpdHitsWest[0];
		if (var == "Event.mNT0" ) return Event_mNT0[0];
		if (var == "Event.mVzVpd" ) return Event_mVzVpd[0];
		if (var == "Event.mZDCx" ) return Event_mZDCx[0];
		if (var == "Event.mBBCx" ) return Event_mBBCx[0];
		if (var == "Event.mBackgroundRate" ) return Event_mBackgroundRate[0];
		if (var == "Event.mBbcBlueBackgroundRate" ) return Event_mBbcBlueBackgroundRate[0];
		if (var == "Event.mBbcYellowBackgroundRate" ) return Event_mBbcYellowBackgroundRate[0];
		if (var == "Event.mBbcEastRate" ) return Event_mBbcEastRate[0];
		if (var == "Event.mBbcWestRate" ) return Event_mBbcWestRate[0];
		if (var == "Event.mZdcEastRate" ) return Event_mZdcEastRate[0];
		if (var == "Event.mZdcWestRate" ) return Event_mZdcWestRate[0];
		if (var == "Event.mVpd" ) return Event_mVpd[0][i];
		if (var == "Event.mZdcSumAdcEast" ) return Event_mZdcSumAdcEast[0];
		if (var == "Event.mZdcSumAdcWest" ) return Event_mZdcSumAdcWest[0];
		if (var == "Event.mZdcSmdEastHorizontal" ) return Event_mZdcSmdEastHorizontal[0][i];
		if (var == "Event.mZdcSmdEastVertical" ) return Event_mZdcSmdEastVertical[0][i];
		if (var == "Event.mZdcSmdWestHorizontal" ) return Event_mZdcSmdWestHorizontal[0][i];
		if (var == "Event.mZdcSmdWestVertical" ) return Event_mZdcSmdWestVertical[0][i];
		if (var == "Event.mSpaceCharge" ) return Event_mSpaceCharge[0];
		if (var == "Event.mbTofTrayMultiplicity" ) return Event_mbTofTrayMultiplicity[0];
		if (var == "Event.mNumberOfGlobalTracks" ) return Event_mNumberOfGlobalTracks[0];
		if (var == "Event.mRanking" ) return Event_mRanking[0];
		if (var == "Event.mNBEMCMatch" ) return Event_mNBEMCMatch[0];
		if (var == "Event.mNBTOFMatch" ) return Event_mNBTOFMatch[0];
		if (var == "Event.mBbcAdcEast" ) return Event_mBbcAdcEast[0][i];
		if (var == "Event.mBbcAdcWest" ) return Event_mBbcAdcWest[0][i];
		if (var == "Event.mHT_Th" ) return Event_mHT_Th[0][i];
		if (var == "Event.mJP_Th" ) return Event_mJP_Th[0][i];
		if (var == "EventPlane_" ) return EventPlane_;
		if (var == "EventPlane.fUniqueID" ) return EventPlane_fUniqueID[0];
		if (var == "EventPlane.fBits" ) return EventPlane_fBits[0];
		if (var == "EventPlane.mQx_eta_pos" ) return EventPlane_mQx_eta_pos[0];
		if (var == "EventPlane.mQy_eta_pos" ) return EventPlane_mQy_eta_pos[0];
		if (var == "EventPlane.mQx_eta_neg" ) return EventPlane_mQx_eta_neg[0];
		if (var == "EventPlane.mQy_eta_neg" ) return EventPlane_mQy_eta_neg[0];
		if (var == "EventPlane.mNtrk_eta_pos" ) return EventPlane_mNtrk_eta_pos[0];
		if (var == "EventPlane.mNtrk_eta_neg" ) return EventPlane_mNtrk_eta_neg[0];
		if (var == "EventPlane.mWeight_eta_pos" ) return EventPlane_mWeight_eta_pos[0];
		if (var == "EventPlane.mWeight_eta_neg" ) return EventPlane_mWeight_eta_neg[0];
		if (var == "EventPlane.mQx_chg_pos" ) return EventPlane_mQx_chg_pos[0];
		if (var == "EventPlane.mQy_chg_pos" ) return EventPlane_mQy_chg_pos[0];
		if (var == "EventPlane.mQx_chg_neg" ) return EventPlane_mQx_chg_neg[0];
		if (var == "EventPlane.mQy_chg_neg" ) return EventPlane_mQy_chg_neg[0];
		if (var == "EventPlane.mNtrk_chg_pos_eta_pos" ) return EventPlane_mNtrk_chg_pos_eta_pos[0];
		if (var == "EventPlane.mNtrk_chg_pos_eta_neg" ) return EventPlane_mNtrk_chg_pos_eta_neg[0];
		if (var == "EventPlane.mNtrk_chg_neg_eta_pos" ) return EventPlane_mNtrk_chg_neg_eta_pos[0];
		if (var == "EventPlane.mNtrk_chg_neg_eta_neg" ) return EventPlane_mNtrk_chg_neg_eta_neg[0];
		if (var == "EventPlane.mWeight_chg_pos" ) return EventPlane_mWeight_chg_pos[0];
		if (var == "EventPlane.mWeight_chg_neg" ) return EventPlane_mWeight_chg_neg[0];
		if (var == "EventPlane.mQx_ran_1" ) return EventPlane_mQx_ran_1[0];
		if (var == "EventPlane.mQy_ran_1" ) return EventPlane_mQy_ran_1[0];
		if (var == "EventPlane.mQx_ran_2" ) return EventPlane_mQx_ran_2[0];
		if (var == "EventPlane.mQy_ran_2" ) return EventPlane_mQy_ran_2[0];
		if (var == "EventPlane.mNtrk_ran_1_eta_pos" ) return EventPlane_mNtrk_ran_1_eta_pos[0];
		if (var == "EventPlane.mNtrk_ran_1_eta_neg" ) return EventPlane_mNtrk_ran_1_eta_neg[0];
		if (var == "EventPlane.mNtrk_ran_2_eta_pos" ) return EventPlane_mNtrk_ran_2_eta_pos[0];
		if (var == "EventPlane.mNtrk_ran_2_eta_neg" ) return EventPlane_mNtrk_ran_2_eta_neg[0];
		if (var == "EventPlane.mWeight_ran_1" ) return EventPlane_mWeight_ran_1[0];
		if (var == "EventPlane.mWeight_ran_2" ) return EventPlane_mWeight_ran_2[0];
		if (var == "Tracks_" ) return Tracks_;
		if (var == "Tracks.mId" ) return Tracks_mId[i];
		if (var == "Tracks.mChi2" ) return Tracks_mChi2[i];
		if (var == "Tracks.mPMomentum.mX1" ) return Tracks_mPMomentum_mX1[i];
		if (var == "Tracks.mPMomentum.mX2" ) return Tracks_mPMomentum_mX2[i];
		if (var == "Tracks.mPMomentum.mX3" ) return Tracks_mPMomentum_mX3[i];
		if (var == "Tracks.mDedx" ) return Tracks_mDedx[i];
		if (var == "Tracks.mNHitsFit" ) return Tracks_mNHitsFit[i];
		if (var == "Tracks.mNHitsMax" ) return Tracks_mNHitsMax[i];
		if (var == "Tracks.mNHitsDedx" ) return Tracks_mNHitsDedx[i];
		if (var == "Tracks.mNSigmaPion" ) return Tracks_mNSigmaPion[i];
		if (var == "Tracks.mNSigmaKaon" ) return Tracks_mNSigmaKaon[i];
		if (var == "Tracks.mNSigmaProton" ) return Tracks_mNSigmaProton[i];
		if (var == "Tracks.mNSigmaElectron" ) return Tracks_mNSigmaElectron[i];
		if (var == "Tracks.mMap0" ) return Tracks_mMap0[i];
		if (var == "Tracks.mMap1" ) return Tracks_mMap1[i];
		if (var == "Tracks.mPar" ) return Tracks_mPar[i][j];
		if (var == "Tracks.mErrMatrix" ) return Tracks_mErrMatrix[i][j];
		if (var == "Tracks.mEmcPidTraitsIndex" ) return Tracks_mEmcPidTraitsIndex[i];
		if (var == "Tracks.mBTofPidTraitsIndex" ) return Tracks_mBTofPidTraitsIndex[i];
		if (var == "Tracks.mMtdPidTraitsIndex" ) return Tracks_mMtdPidTraitsIndex[i];
		if (var == "EmcTrigger_" ) return EmcTrigger_;
		if (var == "EmcTrigger.fUniqueID" ) return EmcTrigger_fUniqueID[i];
		if (var == "EmcTrigger.fBits" ) return EmcTrigger_fBits[i];
		if (var == "EmcTrigger.mFlag" ) return EmcTrigger_mFlag[i];
		if (var == "EmcTrigger.mId" ) return EmcTrigger_mId[i];
		if (var == "EmcTrigger.mAdc" ) return EmcTrigger_mAdc[i];
		if (var == "MtdTrigger_" ) return MtdTrigger_;
		if (var == "MtdTrigger.fUniqueID" ) return MtdTrigger_fUniqueID[i];
		if (var == "MtdTrigger.fBits" ) return MtdTrigger_fBits[i];
		if (var == "MtdTrigger.mVpdTacSum" ) return MtdTrigger_mVpdTacSum[i];
		if (var == "MtdTrigger.mQTtacSum" ) return MtdTrigger_mQTtacSum[i][j][k];
		if (var == "MtdTrigger.mMT101Tac" ) return MtdTrigger_mMT101Tac[i][j][k];
		if (var == "MtdTrigger.mMT101Id" ) return MtdTrigger_mMT101Id[i][j][k];
		if (var == "MtdTrigger.mTF201TriggerBit" ) return MtdTrigger_mTF201TriggerBit[i];
		if (var == "MtdTrigger.mShouldHaveRejectEvent" ) return MtdTrigger_mShouldHaveRejectEvent[i];
		if (var == "BTOWHit_" ) return BTOWHit_;
		if (var == "BTOWHit.fUniqueID" ) return BTOWHit_fUniqueID[i];
		if (var == "BTOWHit.fBits" ) return BTOWHit_fBits[i];
		if (var == "BTOWHit.mId" ) return BTOWHit_mId[i];
		if (var == "BTOWHit.mAdc" ) return BTOWHit_mAdc[i];
		if (var == "BTOWHit.mE" ) return BTOWHit_mE[i];
		if (var == "BTofHit_" ) return BTofHit_;
		if (var == "BTofHit.fUniqueID" ) return BTofHit_fUniqueID[i];
		if (var == "BTofHit.fBits" ) return BTofHit_fBits[i];
		if (var == "BTofHit.mId" ) return BTofHit_mId[i];
		if (var == "MtdHit_" ) return MtdHit_;
		if (var == "MtdHit.fUniqueID" ) return MtdHit_fUniqueID[i];
		if (var == "MtdHit.fBits" ) return MtdHit_fBits[i];
		if (var == "MtdHit.mgChannel" ) return MtdHit_mgChannel[i];
		if (var == "MtdHit.mTriggerFlag" ) return MtdHit_mTriggerFlag[i];
		if (var == "MtdHit.mLeadingEdgeTime_first" ) return MtdHit_mLeadingEdgeTime_first[i];
		if (var == "MtdHit.mLeadingEdgeTime_second" ) return MtdHit_mLeadingEdgeTime_second[i];
		if (var == "MtdHit.mTrailingEdgeTime_first" ) return MtdHit_mTrailingEdgeTime_first[i];
		if (var == "MtdHit.mTrailingEdgeTime_second" ) return MtdHit_mTrailingEdgeTime_second[i];
		if (var == "EmcPidTraits_" ) return EmcPidTraits_;
		if (var == "EmcPidTraits.fUniqueID" ) return EmcPidTraits_fUniqueID[i];
		if (var == "EmcPidTraits.fBits" ) return EmcPidTraits_fBits[i];
		if (var == "EmcPidTraits.mTrackIndex" ) return EmcPidTraits_mTrackIndex[i];
		if (var == "EmcPidTraits.mBEMCId" ) return EmcPidTraits_mBEMCId[i];
		if (var == "EmcPidTraits.mBTOWADC0" ) return EmcPidTraits_mBTOWADC0[i];
		if (var == "EmcPidTraits.mBTOWE0" ) return EmcPidTraits_mBTOWE0[i];
		if (var == "EmcPidTraits.mBTOWE" ) return EmcPidTraits_mBTOWE[i];
		if (var == "EmcPidTraits.mBEMCDistZ" ) return EmcPidTraits_mBEMCDistZ[i];
		if (var == "EmcPidTraits.mBEMCDistPhi" ) return EmcPidTraits_mBEMCDistPhi[i];
		if (var == "EmcPidTraits.mBSMDNEta" ) return EmcPidTraits_mBSMDNEta[i];
		if (var == "EmcPidTraits.mBSMDNPhi" ) return EmcPidTraits_mBSMDNPhi[i];
		if (var == "EmcPidTraits.mBTOWId" ) return EmcPidTraits_mBTOWId[i];
		if (var == "EmcPidTraits.mBTOWId23" ) return EmcPidTraits_mBTOWId23[i];
		if (var == "EmcPidTraits.mBTOWE1" ) return EmcPidTraits_mBTOWE1[i];
		if (var == "EmcPidTraits.mBTOWE2" ) return EmcPidTraits_mBTOWE2[i];
		if (var == "EmcPidTraits.mBTOWE3" ) return EmcPidTraits_mBTOWE3[i];
		if (var == "EmcPidTraits.mBTOWDistEta" ) return EmcPidTraits_mBTOWDistEta[i];
		if (var == "EmcPidTraits.mBTOWDistPhi" ) return EmcPidTraits_mBTOWDistPhi[i];
		if (var == "BTofPidTraits_" ) return BTofPidTraits_;
		if (var == "BTofPidTraits.fUniqueID" ) return BTofPidTraits_fUniqueID[i];
		if (var == "BTofPidTraits.fBits" ) return BTofPidTraits_fBits[i];
		if (var == "BTofPidTraits.mTrackIndex" ) return BTofPidTraits_mTrackIndex[i];
		if (var == "BTofPidTraits.mBTofCellId" ) return BTofPidTraits_mBTofCellId[i];
		if (var == "BTofPidTraits.mBTofMatchFlag" ) return BTofPidTraits_mBTofMatchFlag[i];
		if (var == "BTofPidTraits.mBTof" ) return BTofPidTraits_mBTof[i];
		if (var == "BTofPidTraits.mBTofBeta" ) return BTofPidTraits_mBTofBeta[i];
		if (var == "BTofPidTraits.mBTofYLocal" ) return BTofPidTraits_mBTofYLocal[i];
		if (var == "BTofPidTraits.mBTofZLocal" ) return BTofPidTraits_mBTofZLocal[i];
		if (var == "BTofPidTraits.mBTofHitPosX" ) return BTofPidTraits_mBTofHitPosX[i];
		if (var == "BTofPidTraits.mBTofHitPosY" ) return BTofPidTraits_mBTofHitPosY[i];
		if (var == "BTofPidTraits.mBTofHitPosZ" ) return BTofPidTraits_mBTofHitPosZ[i];
		if (var == "MtdPidTraits_" ) return MtdPidTraits_;
		if (var == "MtdPidTraits.fUniqueID" ) return MtdPidTraits_fUniqueID[i];
		if (var == "MtdPidTraits.fBits" ) return MtdPidTraits_fBits[i];
		if (var == "MtdPidTraits.mMtdHitChan" ) return MtdPidTraits_mMtdHitChan[i];
		if (var == "MtdPidTraits.mTrackIndex" ) return MtdPidTraits_mTrackIndex[i];
		if (var == "MtdPidTraits.mMatchFlag" ) return MtdPidTraits_mMatchFlag[i];
		if (var == "MtdPidTraits.mDeltaY" ) return MtdPidTraits_mDeltaY[i];
		if (var == "MtdPidTraits.mDeltaZ" ) return MtdPidTraits_mDeltaZ[i];
		if (var == "MtdPidTraits.mDeltaTimeOfFlight" ) return MtdPidTraits_mDeltaTimeOfFlight[i];
		if (var == "MtdPidTraits.mBeta" ) return MtdPidTraits_mBeta[i];
		return std::numeric_limits<T>::quiet_NaN();  
	}

	 
};

#endif


