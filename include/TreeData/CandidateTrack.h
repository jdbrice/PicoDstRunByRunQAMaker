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

	Float_t pX, pY, pZ;
 	Float_t dEdx, beta;
 	Char_t charge;
 	Char_t species;		// charge * BITMASK : 1 = Electron, 2 = Muon 
	
	
	ClassDef( CandidateTrack, 2 )
};

#endif