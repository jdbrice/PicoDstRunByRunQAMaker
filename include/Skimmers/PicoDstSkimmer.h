#ifndef PICODST_SKIMMER_H
#define PICODST_SKIMMER_H

// RooBarb
#include "TreeAnalyzer.h"
#include "CutCollection.h"

// Project
#include "PicoDst.h"
#include "TriggerFilter.h"

// STL
#include <memory>

class PicoDstSkimmer : public TreeAnalyzer {
public:
	virtual const char* classname() const { return "PicoDstSkimmer"; }
	PicoDstSkimmer(){}
	~PicoDstSkimmer(){}

	virtual void initialize(){

		pico = shared_ptr<PicoDst>( new PicoDst( chain ) );

		EventBranches = config.getStringVector( nodePath + ".EventBranches" );//, (vector<string>){ "Event" } );
		TrackBranches = config.getStringVector( nodePath + ".TrackBranches" );//, (vector<string>){"Tracks", "BTofPidTraits", "EmcPidTraits", "MtdPidTraits"} ); 

		vector<string> triggers = config.getStringVector( nodePath + ":triggers" );
		tf.setTriggers( triggers );

		// eventCuts
		eventCuts.init( config, nodePath + ".EventCuts" );
		book->cd( "eventQA" );
		book->makeAll( config, nodePath + ".histograms.EventQAHistos" );

	}
	
protected:

	shared_ptr<PicoDst> pico;
	vector<string> EventBranches, TrackBranches;
	TriggerFilter tf;
	CutCollection eventCuts;

	virtual void eventLoop();
	virtual bool keepEvent();
	virtual void analyzeEvent();
	
	virtual void trackLoop();
	virtual void analyzeTrack( int iTrack );

	void passEventCut( string cut, bool passAllCuts ){
		book->cd("eventQA");

		book->fill( "event_single_cuts", cut, 1.0 );

		if ( passAllCuts ){
			book->fill( "event_cuts", cut, 1.0 );
		}
		return;
	}

	Long64_t readBranchList( vector<string> &list, Long64_t &iEvent ){
		// no protection
		Long64_t read = 0;
		for (string s : list ){
			read += chain->GetBranch( s.c_str() )->GetEntry( iEvent );
		}
		return read;
	}






};

#endif