#ifndef CANDIDATE_TRACK_HELIX_H
#define CANDIDATE_TRACK_HELIX_H

#include "TObject.h"

class CandidateTrackHelix : public TObject
{
public:
	CandidateTrackHelix(){
		reset();
	}
	~CandidateTrackHelix(){ }

	void copy( CandidateTrackHelix * that){
		this->mPar[0]   = that->mPar[0];
		this->mPar[1]   = that->mPar[1];
		this->mPar[2]   = that->mPar[2];
		this->mPar[3]   = that->mPar[3];
		this->mPar[4]   = that->mPar[4];
		this->mPar[5]   = that->mPar[5];

		this->mMap0     = that->mMap0;
		this->mMap1     = that->mMap1;
	}
	void reset() {
		mPar[0] = 0;
		mPar[1] = 0;
		mPar[2] = 0;
		mPar[3] = 0;
		mPar[4] = 0;
		mPar[5] = 0;

		mMap0 = 0;
		mMap1 = 0;
	}

	Float_t mPar[6];
	UInt_t mMap0;
	UInt_t mMap1;
	ClassDef( CandidateTrackHelix, 1 )
};

#endif