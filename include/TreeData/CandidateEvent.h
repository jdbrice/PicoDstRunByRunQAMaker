#ifndef CANDIDATE_EVENT_H
#define CANDIDATE_EVENT_H

#include "TObject.h"

class CandidateEvent : public TObject
{
public:
	CandidateEvent() {}
	~CandidateEvent() {}

	Int_t 		mRunId;			// Run ID
	Int_t 		mEventId;		// Event Id
	Int_t 		mPsi2;			// event plane angle
	UShort_t 	mBin16;			// centrality bin 16

	ClassDef( CandidateEvent, 1 )
};


#endif