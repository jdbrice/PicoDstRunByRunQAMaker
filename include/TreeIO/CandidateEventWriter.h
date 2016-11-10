#ifndef CANDIDATE_EVENT_WRITER_H
#define CANDIDATE_EVENT_WRITER_H

#include "IObject.h"
#include "CandidateEvent.h"


class CandidateEventWriter : public IObject
{
public:
	virtual const char* classname() const { return "CandidateEventWriter"; }
	CandidateEventWriter() {}
	CandidateEventWriter( TTree * _tree, string _bn = "Event" ) {

		event = new CandidateEvent();
		_tree->Branch( _bn.c_str(), &event, 256000, 99 );
		INFO( classname(), "Setting Branch" );
	}
	~CandidateEventWriter() {}
	
	void set( CandidateEvent *_event ){
		event->copy( _event );
	}

protected:
	CandidateEvent * event;
};

#endif