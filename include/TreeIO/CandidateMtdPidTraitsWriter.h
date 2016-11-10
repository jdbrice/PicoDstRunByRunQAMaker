#ifndef CANDIDATE_MTD_PID_TRAITS_WRITER_H
#define CANDIDATE_MTD_PID_TRAITS_WRITER_H

#include "IObject.h"
#include "CandidateTrackMtdPidTraits.h"
#include "CandidateTrack.h"
#include "TClonesArray.h"


class CandidateMtdPidTraitsWriter : public IObject
{
public:
	virtual const char* classname() const { return "CandidateMtdPidTraitsWriter"; }
	CandidateMtdPidTraitsWriter() {}
	CandidateMtdPidTraitsWriter( TTree * _tree, string _bn = "MtdPidTraits" ) {

		array = new TClonesArray( "CandidateTrackMtdPidTraits" );
		_tree->Branch( _bn.c_str(), &array, 256000, 99 );
		nEntries = 0;
	}
	~CandidateMtdPidTraitsWriter() {}
	
	void add( CandidateTrackMtdPidTraits *_pid, CandidateTrack *_track ){
		
		CandidateTrackMtdPidTraits * pid =  new ((*array)[nEntries]) CandidateTrackMtdPidTraits( );
		pid->copy( _pid );
		_track->mMtdPidTraitsIndex = nEntries;
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