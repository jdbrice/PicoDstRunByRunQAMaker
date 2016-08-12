#ifndef PAIR_FILTER_H
#define PAIR_FILTER_H

// Project
#include "CandidateTrack.h"
#include "CandidateTrackMtdPidTraits.h"


// ROOT
#include "TVector3.h"

class PairFilter
{
public:
	PairFilter();
	~PairFilter();

	static bool keepMixedPair( 	shared_ptr<CandidateTrack> &aTrack, 
								shared_ptr<CandidateTrackMtdPidTraits> &aMtdPid,
								shared_ptr<CandidateTrack> &bTrack, 
								shared_ptr<CandidateTrackMtdPidTraits> &bMtdPid ){

		if ( aMtdPid->mMtdHitChan == bMtdPid->mMtdHitChan ) return false;

	}
	
};



#endif