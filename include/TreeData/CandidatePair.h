#ifndef CANDIDATE_PAIR_H
#define CANDIDATE_PAIR_H

#include "TObject.h"
#include "TVector3.h"

#include "CandidateTrack.h"
#include "CandidateTrackMtdPidTraits.h"

class CandidatePair : public TObject
{
public:
	CandidatePair(){
		// d1 = new CandidateTrack();
		// d2 = new CandidateTrack();
		// mtd1 = new CandidateTrackMtdPidTraits();
		// mtd2 = new CandidateTrackMtdPidTraits();
	}
	~CandidatePair(){
	}

	void copy( CandidatePair * that ) {
		this->mMomentum_mX1  = that->mMomentum_mX1;
		this->mMomentum_mX2  = that->mMomentum_mX2;
		this->mMomentum_mX3  = that->mMomentum_mX3;
		this->mMass 		 = that->mMass;
		this->mChargeSum = that->mChargeSum;
	}
	void set( float px, float py, float pz, float m, int cs, float lpt ){
		mMomentum_mX1 = px;
		mMomentum_mX2 = py;
		mMomentum_mX3 = pz;
		mMass         = m;
		mChargeSum    = cs;
		mLeadingPt    = lpt;
	}

	TVector3 momentum() { return TVector3( mMomentum_mX1, mMomentum_mX2, mMomentum_mX3 ); }

	Float_t 	mMomentum_mX1;					// pair px
	Float_t 	mMomentum_mX2;					// pair py
	Float_t 	mMomentum_mX3;					// pair pz
	Float_t 	mMass;							// global track gDCA
	Char_t 		mChargeSum;						// charge of daughter1 + charge of daughter2
	Float_t 	mLeadingPt;						// the pt of the leading daughter

	// CandidateTrack* d1 = nullptr;
	// CandidateTrack* d2 = nullptr;

	// CandidateTrackMtdPidTraits *mtd1 = nullptr;
	// CandidateTrackMtdPidTraits *mtd2 = nullptr;



	// Short_t mD1Index;
	// Short_t mD2Index;

	// CandidateTrack * d1( TClonesArray * _tracks ){
	// 	if ( _tracks && _tracks->GetEntries() > mD1Index ){
	// 		return (CandidateTrack*)_tracks->At( mD1Index );
	// 	}
	// 	return nullptr;
	// }
	// CandidateTrack * d2( TClonesArray * _tracks ){
	// 	if ( _tracks && _tracks->GetEntries() > mD2Index ){
	// 		return (CandidateTrack*)_tracks->At( mD2Index );
	// 	}
	// 	return nullptr;
	// }

	ClassDef( CandidatePair, 3 )
};

#endif