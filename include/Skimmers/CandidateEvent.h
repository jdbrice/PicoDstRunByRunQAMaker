#ifndef CANDIDATE_EVENT_H
#define CANDIDATE_EVENT_H

#include "TObject.h"

class CandidateEvent : public TObject
{
public:
	CandidateEvent() {}
	~CandidateEvent() {}

	Int_t runId;	//Run ID
	Int_t eventId;	//Event Id
	UShort_t bin16;	// centrality bin 16
	
	ClassDef( CandidateEvent, 1 )
};


#endif