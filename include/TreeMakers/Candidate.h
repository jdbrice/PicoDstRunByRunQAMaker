#ifndef CANDIDATE_H
#define CANDIDATE_H

// RooBarb
#include "IObject.h"
#include "Logger.h"
using namespace jdb;

// STL
#include <string>

// Project
#include "CandidateEvent.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"
// #include "CandidateTrackEmcPidTraits.h"
#include "IPicoDst.h"

#include <memory>

class Candidate : public IObject
{
public:
	virtual const char* classname() const { return "Candidate"; }
	Candidate() {}
	~Candidate() {}

	void set( 	CandidateEvent * _event, 
				CandidateTrack * _track, 
				CandidateTrackMtdPidTraits * _mtdPidTraits ){
		event = shared_ptr<CandidateEvent>( new CandidateEvent() );
		event->copy( _event );

		track = shared_ptr<CandidateTrack>( new CandidateTrack() );
		track->copy( _track );

		// btofPidTraits = shared_ptr<CandidateTrackBTofPidTraits>( new CandidateTrackBTofPidTraits() );
		// btofPidTraits->copy( _btofPidTraits );

		mtdPidTraits = shared_ptr<CandidateTrackMtdPidTraits>( new CandidateTrackMtdPidTraits() );
		mtdPidTraits->copy( _mtdPidTraits );

	}

	string toString(){
		string str = "";
		// str = " Event : " + event + ", Track : " + track + "";
		return str;
	}

	shared_ptr<CandidateEvent> event = nullptr;
	shared_ptr<CandidateTrack> track = nullptr;
	shared_ptr<CandidateTrackBTofPidTraits> btofPidTraits = nullptr;
	shared_ptr<CandidateTrackMtdPidTraits> mtdPidTraits = nullptr;
	// CandidateTrackEmcPidTraits * emcPidTraits;

	
	bool operator==( const Candidate &r ){
		bool same = this->event->mEventId == r.event->mEventId;
		same &= this->track->mId == r.track->mId;
		return same;
	}


};

#endif