#ifndef MUON_CANDIDATE_MAKER_H
#define MUON_CANDIDATE_MAKER_H

// project
#include "PicoDstSkimmer.h"
#include "CandidateEvent.h"
#include "CandidateTrack.h"

#include "TClonesArray.h"

class MuonCandidateMaker : public PicoDstSkimmer
{
public:
	virtual const char *classname() const { return "MuonCandidateMaker"; }
	MuonCandidateMaker();
	~MuonCandidateMaker();

	virtual void initialize();

protected:
	
	TTree * mTree;

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
		
	}

	virtual void trackLoop(){
		// INFO( classname(), "");
		
		tracks->Clear();
		
		
		for ( int iTrack = 0; iTrack < pico->Tracks_; iTrack++ ){
			CandidateTrack * aTrack =  new ((*tracks)[iTrack]) CandidateTrack( );
			aTrack->daniel = pico->Tracks_mDedx[iTrack];
		}

		mTree->Fill();
		
	}


};


#endif