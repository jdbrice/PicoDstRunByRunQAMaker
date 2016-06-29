#ifndef CANDIDATE_TRACK_H
#define CANDIDATE_TRACK_H

#include "TObject.h"

class CandidateTrack : public TObject
{
public:
	CandidateTrack(){
	}
	~CandidateTrack(){
	}

	int charge() { return mNHitsFit > 0 ? 1 : -1; }

	Float_t 	pX;					// primary track px
	Float_t 	pY;					// primary track py
	Float_t 	pZ;					// primary track pz
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
	Short_t mBTofPidTraitsIndex; // index of the BTOF pidTratis in the event
	Short_t mMtdPidTraitsIndex;  // index of the MTD  pidTratis in the event
	
	
	ClassDef( CandidateTrack, 2 )
};

#endif