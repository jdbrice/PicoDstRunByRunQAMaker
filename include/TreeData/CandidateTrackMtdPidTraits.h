#ifndef CANDIDATE_TRACK_MTD_PID_TRAITS_H
#define CANDIDATE_TRACK_MTD_PID_TRAITS_H

#include "TObject.h"

class CandidateTrackMtdPidTraits : public TObject
{
public:
	CandidateTrackMtdPidTraits(){ }
	~CandidateTrackMtdPidTraits(){ }

	Float_t   mDeltaY;					// DeltaY between matched track-hit pair
	Float_t   mDeltaZ;					// DeltaZ between matched track-hit pair
	Float_t   mDeltaTimeOfFlight;		// Difference between measured and expected time-of-flight
	Char_t    mMatchFlag;				// Matching flag indicating multiple matches
	Short_t   mMtdHitChan;            // (backleg-1) * 60 + (module-1) * 12 + cell
	
	ClassDef( CandidateTrackMtdPidTraits, 1 )
};

#endif