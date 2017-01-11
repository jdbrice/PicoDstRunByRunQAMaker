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
		this->mMomentum_mX1      = that->mMomentum_mX1;
		this->mMomentum_mX2      = that->mMomentum_mX2;
		this->mMomentum_mX3      = that->mMomentum_mX3;
		this->mMass              = that->mMass;
		this->mChargeSum         = that->mChargeSum;
		this->mLeadingPt         = that->mLeadingPt;
		this->d1_mMomentum_mX1   = that->d1_mMomentum_mX1;
		this->d1_mMomentum_mX2   = that->d1_mMomentum_mX2;
		this->d1_mMomentum_mX3   = that->d1_mMomentum_mX3;
		this->d1_mMass           = that->d1_mMass;
		this->d1_mtdBackleg      = that->d1_mtdBackleg;
		this->d1_mtdTriggerPatch = that->d1_mtdTriggerPatch;
		this->d1_mtdEtaStrip     = that->d1_mtdEtaStrip;

		this->d2_mMomentum_mX1   = that->d2_mMomentum_mX1;
		this->d2_mMomentum_mX2   = that->d2_mMomentum_mX2;
		this->d2_mMomentum_mX3   = that->d2_mMomentum_mX3;
		this->d2_mMass           = that->d2_mMass;
		this->d2_mtdBackleg      = that->d2_mtdBackleg;
		this->d2_mtdTriggerPatch = that->d2_mtdTriggerPatch;
		this->d2_mtdEtaStrip     = that->d2_mtdEtaStrip;
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


	Float_t 	d1_mMomentum_mX1;
	Float_t 	d1_mMomentum_mX2;
	Float_t 	d1_mMomentum_mX3;
	Float_t 	d1_mMass;
	Char_t  	d1_mtdBackleg;
	Char_t  	d1_mtdTriggerPatch;
	Char_t  	d1_mtdEtaStrip;

	Float_t 	d2_mMomentum_mX1;
	Float_t 	d2_mMomentum_mX2;
	Float_t 	d2_mMomentum_mX3;
	Float_t 	d2_mMass;
	Char_t  	d2_mtdBackleg;
	Char_t  	d2_mtdTriggerPatch;
	Char_t  	d2_mtdEtaStrip;


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

	ClassDef( CandidatePair, 5 )
};

#endif