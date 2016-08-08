#ifndef MIXED_EVENT_TREE_MAKER_H
#define MIXED_EVENT_TREE_MAKER_H

//RooBarb
#include "CandidateSkimmer.h"
#include "ICandidateTreeMaker.h"

#include "EventHasher.h"

class MixedEventTreeMaker : public CandidateSkimmer
{
public:
	virtual const char* classname() const { return "MixedEventTreeMaker"; }
	MixedEventTreeMaker(){}
	~MixedEventTreeMaker(){}

	virtual void initialize(){
		CandidateSkimmer::initialize();
		createTree();

		eventHash = config.getInt( nodePath + ".EventHash" );
		eht.load( config, nodePath + ".MixedEventBins" );

		INFO( classname(), "EventHash = " << eventHash );

		book->cd();
		long int maxHash = eht.maxPossibleHash();
		book->add( "eventHash", new TH1I( "eventHash", "", maxHash + 10, 0, maxHash + 10 ) );

	}


protected:

	// READ
	TTree                      * mTree          = nullptr;
	CandidateEvent             * wEvent         = nullptr;
	CandidateTrack             * wTracks        = nullptr;
	CandidateTrackMtdPidTraits * wMtdPidTraits  = nullptr;

	int eventHash 				= -1;
	EventHasher 				eht;

	void overrideConfig(){
		DEBUG( classname(), "" );

		map<string, string> opts;
		int jIndex = config.getInt( "jobIndex", -1 );
		if ( !config.exists( nodePath + ".EventHash" ) )
			config.set( nodePath + ".EventHash",  ts( jIndex ) );
	}

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

		// skip events that don't matche the desired hash if we are not looking at everything
		int aEventHash = eht.hash( event );
		TRACE( classname(), "current Event = " << aEventHash );
		if ( 0 <= eventHash && eventHash != aEventHash ) return;

		book->fill( "eventHash", aEventHash );

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