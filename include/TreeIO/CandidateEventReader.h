#ifndef CANDIDATE_EVENT_READER_H
#define CANDIDATE_EVENT_READER_H

#include "IObject.h"
#include "Logger.h"
using namespace jdb;

#include "CandidateEvent.h"


class CandidateEventReader : public IObject
{
public:
	virtual const char* classname() const { return "CandidateEventReader"; }
	CandidateEventReader() {}
	CandidateEventReader( TChain * _tree, string _bn = "Event" ) {
		create( _tree, _bn );
	}
	~CandidateEventReader() {}

	CandidateEvent* const getEvent(){ return event; }

	void create( TChain * _tree, string _bn = "Event"){
		if ( nullptr == _tree ){
			ERROR( classname(), "Invalid TChain" );
			return;
		}
		b_event = _tree->GetBranch( _bn.c_str() );
		if ( !b_event ){
			ERROR( classname(), _bn << " DNE" );
			return;
		}

		// INFO( classname(), "Found " << _bn << " Branch with address : " << b_event );
		_tree->SetBranchAddress( _bn.c_str(), &event );

		INFO( classname(), "Set Branch Address for " << _bn );
	}
protected:


	TBranch * b_event;
	CandidateEvent * event = nullptr;

	


};


#endif