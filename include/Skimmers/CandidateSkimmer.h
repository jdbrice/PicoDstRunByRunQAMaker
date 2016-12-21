#ifndef CANDIDATE_SKIMMER_H
#define CANDIDATE_SKIMMER_H

//RooBarb
#include "TreeAnalyzer.h"

// Project
#include "CandidateEvent.h"
#include "CandidateEventPlane.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"
#include "TriggerFilter.h"
#include "CandidateFilter.h"

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
	

		// chain->SetBranchStatus( "BTofPidTraits*", 0 );
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

		vector<string> triggers = config.getStringVector( nodePath + ":triggers" );
		tf.setTriggers( triggers );
		INFO( classname(), "Triggers: " << vts( triggers ) );

	}


protected:

	CandidateEvent      * event         = nullptr;
	CandidateEventPlane * eventPlane    = nullptr;
	TClonesArray        * tracks        = nullptr;
	TClonesArray        * btofPidTraits = nullptr;
	TClonesArray        * mtdPidTraits  = nullptr;

	bool makeTrackCutQA = false;
	bool makeEventCutQA = false;

	TriggerFilter tf;

	virtual bool keepEvent(){

		bool passAll = true;

		if ( tf.anyTrigger( event ) ){

		} else {
			passAll = false;
		}
		// INFO( classname(), "keep = " << event->mTriggerWordMtd );
		return passAll;
	}

	virtual void analyzeEvent(){
		DEBUG( classname(), "" );

		INFO( classname(), "Event vz = " << event->mPrimaryVertex_mX3 );
	}


	virtual void postMake(){

		// export the frozen config for good reference
		if ( config.exists( nodePath + ".output.XmlFile:url" ) ){
			config.toXmlFile( config.getXString( nodePath + ".output.XmlFile:url" ) );
		}
	}

	virtual void preEventLoop(){
		DEBUG( classname(), "" );
		TreeAnalyzer::preEventLoop();

		vector<string> trackCutBinLabels = config.getStringVector( "TrackQABins.MtdMuon_binLabels" );
		CandidateFilter::initializeBinLabels( book, trackCutBinLabels, "MtdMuon" );
	}

	
};

#endif