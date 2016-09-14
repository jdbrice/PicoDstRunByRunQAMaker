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
	}
	~CandidatePair(){
	}

	void copy( CandidatePair * that ) {
		this->mMomentum_mX1  = that->mMomentum_mX1;
		this->mMomentum_mX2  = that->mMomentum_mX2;
		this->mMomentum_mX3  = that->mMomentum_mX3;
		this->mMass 		 = that->mMass;
		this->mChargeProduct = that->mChargeProduct;
	}
	void set( float px, float py, float pz, float m, int cp ){
		mMomentum_mX1 = px;
		mMomentum_mX2 = py;
		mMomentum_mX3 = pz;
		mMass = m;
		mChargeProduct = cp;
	}

	TVector3 momentum() { return TVector3( mMomentum_mX1, mMomentum_mX2, mMomentum_mX3 ); }

	Float_t 	mMomentum_mX1;					// pair px
	Float_t 	mMomentum_mX2;					// pair py
	Float_t 	mMomentum_mX3;					// pair pz
	Float_t 	mMass;							// global track gDCA
	Char_t		mChargeProduct;					// charge of daughter1 * charge of daughter2
	
	CandidateTrack d1, d2;
	CandidateTrackMtdPidTraits mtd1, mtd2;


	ClassDef( CandidatePair, 2 )
};

#endif