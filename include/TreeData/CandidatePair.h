#ifndef CANDIDATE_PAIR_H
#define CANDIDATE_PAIR_H

#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#include "CandidateTrack.h"
#include "CandidateTrackMtdPidTraits.h"

class CandidatePair : public TObject
{
public:
	CandidatePair(){
		reset();
	}
	~CandidatePair(){
	}

	void copy( CandidatePair * that ) {
		this->mMomentum_mPt     = that->mMomentum_mPt;
		this->mMomentum_mEta    = that->mMomentum_mEta;
		this->mMomentum_mPhi    = that->mMomentum_mPhi;
		this->mMass             = that->mMass;
		this->mChargeSum        = that->mChargeSum;
		this->mLeadingPt        = that->mLeadingPt;
		this->d1_mMomentum_mPt  = that->d1_mMomentum_mPt;
		this->d1_mMomentum_mEta = that->d1_mMomentum_mEta;
		this->d1_mMomentum_mPhi = that->d1_mMomentum_mPhi;
		this->d1_mMass          = that->d1_mMass;
		this->d1_mMtdHitChan    = that->d1_mMtdHitChan;
		this->d1_mPid           = that->d1_mPid;

		this->d2_mMomentum_mPt  = that->d2_mMomentum_mPt;
		this->d2_mMomentum_mEta = that->d2_mMomentum_mEta;
		this->d2_mMomentum_mPhi = that->d2_mMomentum_mPhi;
		this->d2_mMass          = that->d2_mMass;
		this->d2_mMtdHitChan    = that->d2_mMtdHitChan;
		this->d2_mPid           = that->d2_mPid;
	}
	void set( TLorentzVector &lv, int cs ){
		mMomentum_mPt  = lv.Pt();
		mMomentum_mEta = lv.Eta();
		mMomentum_mPhi = lv.Phi();
		mMass          = lv.M();
		mChargeSum     = cs;
	}

	void reset(  ){
		this->mMomentum_mPt     = 0.0;
		this->mMomentum_mEta    = 0.0;
		this->mMomentum_mPhi    = 0.0;
		this->mMass             = 0.0;
		this->mChargeSum        = 0.0;
		this->mLeadingPt        = 0.0;
		this->d1_mMomentum_mPt  = 0.0;
		this->d1_mMomentum_mEta = 0.0;
		this->d1_mMomentum_mPhi = 0.0;
		this->d1_mMass          = 0.0;
		this->d1_mMtdHitChan    = 0.0;
		this->d1_mPid           = 0.0;
		this->d2_mMomentum_mPt  = 0.0;
		this->d2_mMomentum_mEta = 0.0;
		this->d2_mMomentum_mPhi = 0.0;
		this->d2_mMass          = 0.0;
		this->d2_mMtdHitChan    = 0.0;
		this->d2_mPid           = 0.0;
	}

	void setDaughters( 	TLorentzVector &lv1, int hc1, double lr1, 
						TLorentzVector &lv2, int hc2, double lr2 ){
		d1_mMomentum_mPt    = lv1.Pt();
		d1_mMomentum_mEta   = lv1.Eta();
		d1_mMomentum_mPhi   = lv1.Phi();
		d1_mMass            = lv1.M();
		d1_mMtdHitChan      = hc1;
		d1_mPid             = lr1;


		d2_mMomentum_mPt    = lv2.Pt();
		d2_mMomentum_mEta   = lv2.Eta();
		d2_mMomentum_mPhi   = lv2.Phi();
		d2_mMass            = lv2.M();
		d2_mMtdHitChan      = hc2;
		d2_mPid             = lr2;

		mLeadingPt = lv1.Pt();
		if ( lv2.Pt() > lv1.Pt() )
			mLeadingPt = lv2.Pt();
	}

	TVector3 momentum() { return TVector3( mMomentum_mPt, mMomentum_mEta, mMomentum_mPhi ); }
	int d1bl();
	int d2bl();
	int d1es();
	int d2es();
	int d1tp();
	int d2tp();


	Float_t 	mMomentum_mPt;					// pair Pt
	Float_t 	mMomentum_mEta;					// pair Eta
	Float_t 	mMomentum_mPhi;					// pair Phi
	Float_t 	mMass;							// global track gDCA
	Char_t 		mChargeSum;						// charge of daughter1 + charge of daughter2
	Float_t 	mLeadingPt;						// the pt of the leading daughter


	Float_t 	d1_mMomentum_mPt;
	Float_t 	d1_mMomentum_mEta;
	Float_t 	d1_mMomentum_mPhi;
	Float_t 	d1_mMass;
	Short_t 	d1_mMtdHitChan;
	Float_t 	d1_mPid;

	Float_t 	d2_mMomentum_mPt;
	Float_t 	d2_mMomentum_mEta;
	Float_t 	d2_mMomentum_mPhi;
	Float_t 	d2_mMass;
	Short_t 	d2_mMtdHitChan;
	Float_t 	d2_mPid;

	ClassDef( CandidatePair, 7 )
};

#endif