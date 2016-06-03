#ifndef PICODST_SKIMMER_H
#define PICODST_SKIMMER_H

// RooBarb
#include "TreeAnalyzer.h"

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
	}
	
protected:

	shared_ptr<PicoDst> pico;
	vector<string> EventBranches, TrackBranches;
	TriggerFilter tf;

	virtual void eventLoop();
	virtual bool keepEvent();
	virtual void analyzeEvent();
	
	virtual void trackLoop();
	virtual void analyzeTrack( int iTrack );

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