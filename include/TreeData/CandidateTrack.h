#ifndef CANDIDATE_TRACK_H
#define CANDIDATE_TRACK_H

#include "TObject.h"
#include "TVector3.h"

class CandidateTrack : public TObject
{
public:
	CandidateTrack(){
	}
	~CandidateTrack(){
	}

	void copy( CandidateTrack * that ) {
		this->mPMomentum_mX1  = that->mPMomentum_mX1;
		this->mPMomentum_mX2  = that->mPMomentum_mX2;
		this->mPMomentum_mX3  = that->mPMomentum_mX3;
		this->mId             = that->mId;
		this->mDedx           = that->mDedx;
		this->mNHitsFit       = that->mNHitsFit;
		this->mNHitsMax       = that->mNHitsMax;
		this->mNHitsDedx      = that->mNHitsDedx;
		this->mNSigmaPion     = that->mNSigmaPion;
		this->mNSigmaKaon     = that->mNSigmaKaon;
		this->mNSigmaProton   = that->mNSigmaProton;
		this->mNSigmaElectron = that->mNSigmaElectron;
		this->mDCA            = that->mDCA;

		this->mBTofPidTraitsIndex 	= that->mBTofPidTraitsIndex;
		this->mMtdPidTraitsIndex 	= that->mMtdPidTraitsIndex;
	}

	int charge() { return mNHitsFit > 0 ? 1 : -1; }
	float nSigmaPion() { return mNSigmaPion / 100.0; }
	float nSigmaKaon() { return mNSigmaKaon / 100.0; }
	float nSigmaProton() { return mNSigmaProton / 100.0; }
	float nSigmaElectron() { return mNSigmaElectron / 100.0; }

	float gDCA() { return mDCA / 1000.0; }
	TVector3 pMomentum() { return TVector3( mPMomentum_mX1, mPMomentum_mX2, mPMomentum_mX3 ); }
	float dEdx() { return mDedx / 1000.0; }
	

	Float_t 	mPMomentum_mX1;					// primary track px
	Float_t 	mPMomentum_mX2;					// primary track py
	Float_t 	mPMomentum_mX3;					// primary track pz
	UShort_t 	mId;				// track Id
	UShort_t 	mDedx;				// dEdx*1000
	Char_t 		mNHitsFit;			// q*nHitsFit - TPC
	Char_t 		mNHitsMax;			// nHitsMax - TPC
	UChar_t 	mNHitsDedx;			// nHitsDedx - TPC
	Short_t 	mNSigmaPion;		// nsigmaPi * 100
	Short_t 	mNSigmaKaon;		// nsigmaK * 100
	Short_t 	mNSigmaProton;		// nsigmaP * 100
	Short_t 	mNSigmaElectron;	// nsigmaE * 100
	Short_t 	mDCA;				// global track gDCA
	
	// pidTraits
	Short_t 	mBTofPidTraitsIndex; // index of the BTOF pidTratis in the event
	Short_t 	mMtdPidTraitsIndex;  // index of the MTD  pidTratis in the event
	
	
	ClassDef( CandidateTrack, 2 )
};

#endif