#ifndef CANDIDATE_TRACKS_WRITER_H
#define CANDIDATE_TRACKS_WRITER_H

#include "IObject.h"
#include "CandidateTrack.h"
#include "TClonesArray.h"


class CandidateTracksWriter : public IObject
{
public:
	virtual const char* classname() const { return "CandidateTracksWriter"; }
	CandidateTracksWriter() {}
	CandidateTracksWriter( TTree * _tree, string _bn = "Tracks" ) {

		tracks = new TClonesArray( "CandidateTrack" );
		_tree->Branch( _bn.c_str(), &tracks, 256000, 99 );
	}
	~CandidateTracksWriter() {}
	
	void add( CandidateTrack *_track ){
		int n = tracks->GetEntries();
		CandidateTrack * track =  new ((*tracks)[n]) CandidateTrack( );
		track->copy( _track );
	}

	void reset() {
		tracks->Clear();
	}

	int nEntries(){
		return tracks->GetEntries();
	}

protected:
	TClonesArray * tracks;
};

#endif