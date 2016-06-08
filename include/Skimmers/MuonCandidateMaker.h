#ifndef MUON_CANDIDATE_MAKER_H
#define MUON_CANDIDATE_MAKER_H

// project
#include "PicoDstSkimmer.h"
#include "CandidateEvent.h"
#include "CandidateTrack.h"

//RooBarb
#include "CutCollection.h"

#include "TClonesArray.h"
#include "TVector3.h"

class MuonCandidateMaker : public PicoDstSkimmer
{
public:
	virtual const char *classname() const { return "MuonCandidateMaker"; }
	MuonCandidateMaker();
	~MuonCandidateMaker();

	virtual void initialize();

protected:
	CutCollection muonCuts;
	TTree * mTree;
	Int_t nCandTracks;

	void createTree(){
		mTree = new TTree("candidates","Muon Candidates");

		mTree->Branch( "Event", &event, 256000, 99 );
		mTree->Branch( "Tracks", &tracks, 256000, 99 );

	}
	CandidateEvent * event;
	TClonesArray * tracks;


	virtual void analyzeEvent(){

		event->runId 	= pico->Event_mRunId[0];
		event->eventId 	= pico->Event_mEventId[0];
		event->bin16 	= 0;

		nCandTracks = 0;
		
	}

	virtual void trackLoop(){
		// INFO( classname(), "");
		
		tracks->Clear();
		
		for ( int iTrack = 0; iTrack < pico->Tracks_; iTrack++ ){

			if ( !keepTrack( iTrack ) ) continue;

			CandidateTrack * aTrack =  new ((*tracks)[nCandTracks]) CandidateTrack( );
			
			aTrack->charge = pico->Tracks_mNHitsFit[iTrack] > 0 ? 1 : -1;
			aTrack->pX = pico->Tracks_mPMomentum_mX1[iTrack];
			aTrack->pY = pico->Tracks_mPMomentum_mX2[iTrack];
			aTrack->pZ = pico->Tracks_mPMomentum_mX3[iTrack];

			nCandTracks ++;
		}

		mTree->Fill();
		
	}

	bool keepTrack( int iTrack );


};


#endif