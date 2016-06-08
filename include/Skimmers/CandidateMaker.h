#ifndef CANDIDATE_MAKER_H
#define CANDIDATE_MAKER_H

//Project
#include "PicoDstSkimmer.h"
#include "CandidateEvent.h"
#include "CandidateTrack.h"

//ROOT
#include "TClonesArray.h"
#include "TVector3.h"

class CandidateMaker : public PicoDstSkimmer
{
public:
	virtual const char *classname() const { return "CandidateMaker"; }
	CandidateMaker() {}
	~CandidateMaker() {}

	virtual void initialize(){
		INFO( classname(), "" );
		PicoDstSkimmer::initialize();

		event = new CandidateEvent();
		tracks = new TClonesArray( "CandidateTrack" );
		
		createTree();
	}


protected:
	string treeDescription = "Generic";
	TTree * mTree;
	Int_t nCandTracks;
	bool keepEvent;
	
	CandidateEvent * event;
	TClonesArray * tracks;

	void createTree(){
		mTree = new TTree("candidates", (treeDescription + " Candidates").c_str(), 99);
		mTree->Branch( "Event", &event, 256000, 99 );
		mTree->Branch( "Tracks", &tracks, 256000, 99 );
	}

	virtual void analyzeEvent(){
		// set the event level items
		event->runId 	= pico->Event_mRunId[0];
		event->eventId 	= pico->Event_mEventId[0];
		event->bin16 	= 0;

		// for instance, use to keep only events with pairs of muons
		// default to keep all accepted events
		keepEvent = true;
	}
	virtual void trackLoop(){
		nCandTracks = 0;
		tracks->Clear();

		for ( int iTrack = 0; iTrack < pico->Tracks_; iTrack++ ){

			if ( !keepTrack( iTrack ) ) continue;

			CandidateTrack * aTrack =  new ((*tracks)[nCandTracks]) CandidateTrack( );
			analyzeCandidateTrack( aTrack, iTrack, nCandTracks );
			nCandTracks ++;
		}

		if ( keepEvent )
			mTree->Fill();
	}
	virtual void analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int nCandTracks ){
		aTrack->charge = pico->Tracks_mNHitsFit[iTrack] > 0 ? 1 : -1;

		aTrack->pX = pico->Tracks_mPMomentum_mX1[iTrack];
		aTrack->pY = pico->Tracks_mPMomentum_mX2[iTrack];
		aTrack->pZ = pico->Tracks_mPMomentum_mX3[iTrack];
	}
	virtual bool keepTrack( int iTrack ){
		return true;
	}
	
};


#endif