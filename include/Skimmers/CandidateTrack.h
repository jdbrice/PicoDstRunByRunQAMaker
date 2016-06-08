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

 	Char_t charge;
	Float_t pX, pY, pZ;
	
	
	ClassDef( CandidateTrack, 1 )
};

#endif