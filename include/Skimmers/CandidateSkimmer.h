#ifndef CANDIDATE_SKIMMER_H
#define CANDIDATE_SKIMMER_H

//RooBarb
#include "TreeAnalyzer.h"

//ROOT
#include "TClonesArray.h"

class CandidateSkimmer : public TreeAnalyzer
{
public:
	CandidateSkimmer(){}
	~CandidateSkimmer(){}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		tracks = new TClonesArray( "CandidateTrack" );
		chain->GetBranch( "Tracks" )->SetAutoDelete( kFALSE );
		
		chain->SetBranchStatus( "Tracks*", 1 );
		chain->SetBranchAddress( "Tracks", &tracks );
		chain->SetBranchAddress( "Event", &event );


	}


protected:

	CandidateEvent *event;
	CandidateEventPlane *eventPlane;
	TClonesArray *tracks;
	TClonesArray *btofPidTraits;
	TClonesArray *mtdPidTraits;


	virtual void analyzeEvent(){
		INFO( classname(), "daniel" );
		
		INFO( classname(), tracks->GetEntries() );
		INFO( classname(), event->mEventId );
		if ( tracks->GetEntries() >= 20 ){
			CandidateTrack* track = (CandidateTrack*)tracks->At( 19 );
			// cout << track->beta << endl;
		}

	}

	
};

#endif