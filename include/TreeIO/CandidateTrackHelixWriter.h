#ifndef CANDIDATE_TRACK_HELIX_WRITER_H
#define CANDIDATE_TRACK_HELIX_WRITER_H

#include "IObject.h"
#include "CandidateTrackHelix.h"
#include "CandidateTrack.h"
#include "TClonesArray.h"


class CandidateTrackHelixWriter : public IObject
{
public:
	virtual const char* classname() const { return "CandidateTrackHelixWriter"; }
	CandidateTrackHelixWriter() {}
	CandidateTrackHelixWriter( TTree * _tree, string _bn = "TrackHelix" ) {

		array = new TClonesArray( "CandidateTrackHelix" );
		_tree->Branch( _bn.c_str(), &array, 256000, 99 );
		nEntries = 0;
	}
	~CandidateTrackHelixWriter() {}
	
	void add( CandidateTrackHelix *_helix, CandidateTrack *_track ){
		
		CandidateTrackHelix * pid =  new ((*array)[nEntries]) CandidateTrackHelix( );
		pid->copy( _helix );
		_track->mHelixIndex = nEntries;
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