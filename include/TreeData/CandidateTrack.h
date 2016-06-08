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
 	Char_t charge;
 	Char_t species;		// BITMASK : 1 = Electron, 2 = Muon
	
	
	ClassDef( CandidateTrack, 2 )
};

#endif