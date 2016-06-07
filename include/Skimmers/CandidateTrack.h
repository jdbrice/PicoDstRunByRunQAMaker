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

	Int_t trackId;	//!
	Float_t daniel;
	
	
	ClassDef( CandidateTrack, 1 )
};

#endif