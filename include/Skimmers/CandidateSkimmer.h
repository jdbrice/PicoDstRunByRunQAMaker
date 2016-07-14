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

		chain->SetBranchAddress( "Event", &event );

		DEBUG( classname(), "Checking for EventPlane Branch" );
		if ( chain->GetBranch( "EventPlane" ) ){
			chain->SetBranchAddress( "EventPlane", &eventPlane );
			DEBUG( classname(), "Got EventPlane Branch" );
		}

		DEBUG( classname(), "Checking for Track Branch" );
		if ( chain->GetBranch( "Tracks" ) ){
			chain->SetBranchAddress( "Tracks", &tracks );
			tracks = new TClonesArray( "CandidateTrack" );
			chain->GetBranch( "Tracks" )->SetAutoDelete( kFALSE );	
			DEBUG( classname(), "Got Tracks Branch" );
		}
		
		DEBUG( classname(), "Checking for BTofPidTraits Branch" );
		if ( chain->GetBranch( "BTofPidTraits" ) ){
			btofPidTraits = new TClonesArray( "CandidateTrackBTofPidTraits" );
			chain->GetBranch( "BTofPidTraits" )->SetAutoDelete( kFALSE );
			chain->SetBranchAddress( "BTofPidTraits", &btofPidTraits );
			DEBUG( classname(), "Got BTofPidTraits Branch" );
		} 
		
		DEBUG( classname(), "Checking for MtdPidTraits Branch" );
		if (chain->GetBranch( "MtdPidTraits" ) ) {
			mtdPidTraits = new TClonesArray( "CandidateTrackMtdPidTraits" );
			chain->GetBranch( "MtdPidTraits" )->SetAutoDelete( kFALSE );
			chain->SetBranchAddress( "MtdPidTraits", &mtdPidTraits );
			DEBUG( classname(), "Got MtdPidTraits Branch" );
		}
	}


protected:

	CandidateEvent      * event         = nullptr;
	CandidateEventPlane * eventPlane    = nullptr;
	TClonesArray        * tracks        = nullptr;
	TClonesArray        * btofPidTraits = nullptr;
	TClonesArray        * mtdPidTraits  = nullptr;


	virtual void analyzeEvent(){
		DEBUG( classname(), "" );
	}

	
};

#endif