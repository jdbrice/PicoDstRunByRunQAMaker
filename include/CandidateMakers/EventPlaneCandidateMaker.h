#ifndef EVENT_PLANE_CANDIDATE_MAKER_H
#define EVENT_PLANE_CANDIDATE_MAKER_H

#include "CandidateMaker.h"
#include "CandidateTreeMaker.h"

class EventPlaneCandidateMaker : public CandidateMaker, public CandidateTreeMaker
{
public:
	virtual const char* classname() const { return "EventPlaneCandidateMaker"; }
	EventPlaneCandidateMaker() {}
	~EventPlaneCandidateMaker() {}


	virtual void initialize(){
		CandidateMaker::initialize();

		// add the EventPlane Branch
		createTree( true );
	}


protected:
	virtual void analyzeEvent(){
		CandidateMaker::analyzeEvent();
		mTree->Fill();
	}
	
};


#endif