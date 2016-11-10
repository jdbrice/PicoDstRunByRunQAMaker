#ifndef CANDIDATE_BTOF_PID_TRAITS_WRITER_H
#define CANDIDATE_BTOF_PID_TRAITS_WRITER_H

#include "IObject.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrack.h"
#include "TClonesArray.h"


class CandidateBTofPidTraitsWriter : public IObject
{
public:
	virtual const char* classname() const { return "CandidateBTofPidTraitsWriter"; }
	CandidateBTofPidTraitsWriter() {}
	CandidateBTofPidTraitsWriter( TTree * _tree, string _bn = "BTofPidTraits" ) {

		array = new TClonesArray( "CandidateTrackBTofPidTraits" );
		_tree->Branch( _bn.c_str(), &array, 256000, 99 );
		nEntries = 0;
	}
	~CandidateBTofPidTraitsWriter() {}
	
	void add( CandidateTrackBTofPidTraits *_pid, CandidateTrack *_track ){
		
		CandidateTrackBTofPidTraits * pid =  new ((*array)[nEntries]) CandidateTrackBTofPidTraits( );
		pid->copy( _pid );
		_track->mBTofPidTraitsIndex = nEntries;
		nEntries++;
	}

	void reset() {
		array->Clear();
		nEntries = 0;
	}

protected:
	TClonesArray * array;
	int nEntries;
};

#endif