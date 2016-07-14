#ifndef MIXED_EVENT_TREE_MAKER_H
#define MIXED_EVENT_TREE_MAKER_H

//RooBarb
#include "CandidateSkimmer.h"
#include "ICandidateTreeMaker.h"

class MixedEventTreeMaker : public CandidateSkimmer
{
public:
	virtual const char* classname() const { return "MixedEventTreeMaker"; }
	MixedEventTreeMaker(){}
	~MixedEventTreeMaker(){}

	virtual void initialize(){
		CandidateSkimmer::initialize();

		createTree();

	}


protected:

	// READ
	TTree                      * mTree          = nullptr;
	CandidateEvent             * wEvent         = nullptr;
	CandidateTrack             * wTracks        = nullptr;
	CandidateTrackMtdPidTraits * wMtdPidTraits  = nullptr;


	void createTree( ){

		// makes it safe to call multiple times
		if ( nullptr == wEvent )
			wEvent = new CandidateEvent();

		if ( nullptr == wTracks )
			wTracks = new CandidateTrack();
		
		if ( nullptr == wMtdPidTraits )
			wMtdPidTraits = new CandidateTrackMtdPidTraits();

		if ( nullptr == mTree )
			mTree = new TTree("FemtoDst", "MixedEvent Candidates", 99);
		
		mTree->Branch( "Event", &wEvent, 256000, 99 );
		mTree->Branch( "Tracks", &wTracks, 256000, 99 );
		mTree->Branch( "MtdPidTraits", &wMtdPidTraits, 256000, 99 );
	}


	virtual void analyzeEvent(){

		// Set the Event Data
		wEvent->copy( event );

		int nTracks = tracks->GetEntries();
		DEBUG( classname(), "# of Tracks = " << nTracks );

		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			wTracks->copy( aTrack );
			if ( aTrack->mMtdPidTraitsIndex >= 0 ){
				CandidateTrackMtdPidTraits * aMtdPidTraits = (CandidateTrackMtdPidTraits*) mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
				wMtdPidTraits->copy( aMtdPidTraits );
			}
			mTree->Fill();
		} // iTrack
	}

	virtual void postMake() {
		INFO( classname(), "Writing Tree out" );
		mTree->Write();
	} 
	

};

#endif