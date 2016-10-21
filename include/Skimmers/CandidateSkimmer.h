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
	
		chain->SetBranchAddress( "Event", &event );

		DEBUG( classname(), "Checking for EventPlane Branch" );
		if ( chain->GetBranch( "EventPlane*" ) ){
			chain->SetBranchAddress( "EventPlane", &eventPlane );
			DEBUG( classname(), "Got EventPlane Branch" );
		}

		DEBUG( classname(), "Checking for Track Branch" );
		if ( chain->GetBranch( "Tracks" ) ){
			tracks = new TClonesArray( "CandidateTrack" );
			chain->SetBranchAddress( "Tracks", &tracks );
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


		makeEventCutQA = config.getBool( nodePath + ".MakeQA:event", false );
		makeTrackCutQA = config.getBool( nodePath + ".MakeQA:track", false );
		DEBUG( classname(), "Making Event Cut QA : " << bts( makeEventCutQA ) );
		DEBUG( classname(), "Making Track Cut QA : " << bts( makeTrackCutQA ) );


	}


protected:

	CandidateEvent      * event         = nullptr;
	CandidateEventPlane * eventPlane    = nullptr;
	TClonesArray        * tracks        = nullptr;
	TClonesArray        * btofPidTraits = nullptr;
	TClonesArray        * mtdPidTraits  = nullptr;

	bool makeTrackCutQA = false;
	bool makeEventCutQA = false;


	virtual void analyzeEvent(){
		DEBUG( classname(), "" );

		INFO( classname(), "Event vz = " << event->mPrimaryVertex_mX3 );
	}


	virtual void postMake(){
		config.toXmlFile( "freeze_config.xml" );
	}

	
};

#endif