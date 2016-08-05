#ifndef MIXED_CANDIDATE_SKIMMER_H
#define MIXED_CANDIDATE_SKIMMER_H

//RooBarb
#include "TreeAnalyzer.h"
#include "CandidateEvent.h"
#include "CandidateEventPlane.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"

//ROOT
#include "TClonesArray.h"

class MixedCandidateSkimmer : public TreeAnalyzer
{
public:
	MixedCandidateSkimmer(){}
	~MixedCandidateSkimmer(){}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		DEBUG( classname(), "Setting Branch Status" );
	
		chain->SetBranchAddress( "Event", &event );

		DEBUG( classname(), "Checking for EventPlane Branch" );
		if ( chain->GetBranch( "EventPlane" ) ){
			chain->SetBranchAddress( "EventPlane", &eventPlane );
			DEBUG( classname(), "Got EventPlane Branch" );
		}

		DEBUG( classname(), "Checking for Track Branch" );
		if ( chain->GetBranch( "Tracks" ) ){
			// tracks = new TClonesArray( "CandidateTrack" );
			chain->SetBranchAddress( "Tracks", &tracks );
			// chain->GetBranch( "Tracks" )->SetAutoDelete( kFALSE );	
			DEBUG( classname(), "Got Tracks Branch" );
		}
		
		DEBUG( classname(), "Checking for BTofPidTraits Branch" );
		if ( chain->GetBranch( "BTofPidTraits" ) ){
			// btofPidTraits = new TClonesArray( "CandidateTrackBTofPidTraits" );
			// chain->GetBranch( "BTofPidTraits" )->SetAutoDelete( kFALSE );
			chain->SetBranchAddress( "BTofPidTraits", &btofPidTraits );
			DEBUG( classname(), "Got BTofPidTraits Branch" );
		} 
		
		DEBUG( classname(), "Checking for MtdPidTraits Branch" );
		if (chain->GetBranch( "MtdPidTraits" ) ) {
			// mtdPidTraits = new TClonesArray( "CandidateTrackMtdPidTraits" );
			// chain->GetBranch( "MtdPidTraits" )->SetAutoDelete( kFALSE );
			chain->SetBranchAddress( "MtdPidTraits", &mtdPidTraits );
			DEBUG( classname(), "Got MtdPidTraits Branch" );
		}
	}


protected:

	CandidateEvent              * event         = nullptr;
	CandidateEventPlane         * eventPlane    = nullptr;
	CandidateTrack              * tracks        = nullptr;
	CandidateTrackBTofPidTraits * btofPidTraits = nullptr;
	CandidateTrackMtdPidTraits  * mtdPidTraits  = nullptr;


	virtual void analyzeEvent(){
		DEBUG( classname(), "" );

		INFO( classname(), "Event vz = " << event->mPrimaryVertex_mX3 );
	}

	
};

#endif