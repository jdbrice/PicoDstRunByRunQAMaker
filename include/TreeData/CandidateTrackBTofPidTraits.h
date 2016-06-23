#ifndef CANDIDATE_TRACK_BTOF_PID_TRAITS_H
#define CANDIDATE_TRACK_BTOF_PID_TRAITS_H

#include "TObject.h"

class CandidateTrackBTofPidTraits : public TObject
{
public:
	CandidateTrackBTofPidTraits(){ }
	~CandidateTrackBTofPidTraits(){ }

	UShort_t mBTofBeta;			// beta * 20000
	Short_t  mTrackIndex;		// Index to the associated track in the event
	Short_t  mBTofYLocal;		// ylocal * 1000
	Short_t  mBTofZLocal;		// zlocal * 1000
	UChar_t  mBTofMatchFlag;	// 0 - no match, 1 - one-to-one, 2 - one-to-multiple
	
	ClassDef( CandidateTrackBTofPidTraits, 1 )
};

#endif