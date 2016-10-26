#ifndef CANDIDATE_TRACK_HELIX_H
#define CANDIDATE_TRACK_HELIX_H

#include "TObject.h"

class CandidateTrackHelix : public TObject
{
public:
	CandidateTrackHelix(){ }
	~CandidateTrackHelix(){ }

	void copy( CandidateTrackHelix * that){
		
	}

	Float_t mPar[6];
	UInt_t mMap0;
	UInt_t mMap1;
	ClassDef( CandidateTrackHelix, 1 )
};

#endif