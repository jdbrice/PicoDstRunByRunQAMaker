#ifndef CANDIDATE_TRACK_ARRAY_READER_H
#define CANDIDATE_TRACK_ARRAY_READER_H

class CandidateTrackArrayReader : public IObject
{
public:
	virtual const char* classname() const { return "CandidateTrackArrayReader"; }
	CandidateTrackArrayReader() {}
	CandidateTrackArrayReader( TChain * _tree, string _bn = "Tracks" ) {
		create( _tree, _bn );
	}
	~CandidateTrackArrayReader() {}

	CandidateTrack* const getTrack( int iTrack = 0 ){ return (CandidateTrack*)tracks->At( iTrack ); }

	void create( TChain * _tree, string _bn = "Event"){
		if ( nullptr == _tree ){
			ERROR( classname(), "Invalid TChain" );
			return;
		}
		b_tracks = _tree->GetBranch( _bn.c_str() );
		if ( !b_tracks ){
			ERROR( classname(), _bn << " DNE" );
			return;
		}

		tracks = new TClonesArray( "CandidateTrack" );
		_tree->SetBranchAddress( _bn.c_str(), &tracks );
		b_tracks->SetAutoDelete( kFALSE );

		INFO( classname(), "Set Branch Address for " << _bn );
	}
protected:


	TBranch * b_tracks;
	TClonesArray * tracks = nullptr;

};

#endif