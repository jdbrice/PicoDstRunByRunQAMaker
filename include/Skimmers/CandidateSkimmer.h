#ifndef CANDIDATE_SKIMMER_H
#define CANDIDATE_SKIMMER_H

//RooBarb
#include "TreeAnalyzer.h"
#include "CandidateEvent.h"
#include "CandidateEventPlane.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"

//ROOT
#include "TClonesArray.h"

class CandidateSkimmer : public TreeAnalyzer
{
public:
	CandidateSkimmer(){}
	~CandidateSkimmer(){}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		DEBUG( classname(), "Setting Branch Status" );
		chain->SetBranchStatus( "*", 1 );

		DEBUG( classname(), "Creating TClonesArrays" );
		
		
		

		DEBUG( classname(), "Setting Autodelete" );
		if ( chain->GetBranch( "Tracks" ) ){
			chain->SetBranchAddress( "Tracks", &tracks );
			tracks = new TClonesArray( "CandidateTrack" );
			chain->GetBranch( "Tracks" )->SetAutoDelete( kFALSE );	
		}
		
		if ( chain->GetBranch( "BTofPidTraits" ) ){
			btofPidTraits = new TClonesArray( "CandidateTrackBTofPidTraits" );
			chain->GetBranch( "BTofPidTraits" )->SetAutoDelete( kFALSE );
			chain->SetBranchAddress( "BTofPidTraits", &btofPidTraits );
		} 
		
		if (chain->GetBranch( "MtdPidTraits" ) ) {
			mtdPidTraits = new TClonesArray( "CandidateTrackMtdPidTraits" );
			chain->GetBranch( "MtdPidTraits" )->SetAutoDelete( kFALSE );
			chain->SetBranchAddress( "MtdPidTraits", &mtdPidTraits );
		}
		
		
		
		DEBUG( classname(), "Setting Branch Address" );
		
		
		
		chain->SetBranchAddress( "Event", &event );
		chain->SetBranchAddress( "EventPlane", &eventPlane );
	}


protected:

	CandidateEvent      * event         = nullptr;
	CandidateEventPlane * eventPlane    = nullptr;
	TClonesArray        * tracks        = nullptr;
	TClonesArray        * btofPidTraits = nullptr;
	TClonesArray        * mtdPidTraits  = nullptr;


	virtual void analyzeEvent(){
		// INFO( classname(), "daniel" );
		
		// INFO( classname(), tracks->GetEntries() );
		// INFO( classname(), event->mEventId );
		// if ( tracks->GetEntries() >= 20 ){
		// 	CandidateTrack* track = (CandidateTrack*)tracks->At( 19 );
		// 	// cout << track->beta << endl;
		// }

	}

	
};

#endif