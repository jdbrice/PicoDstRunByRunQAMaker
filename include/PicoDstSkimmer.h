#ifndef PICODST_SKIMMER_H
#define PICODST_SKIMMER_H

// RooBarb
#include "TreeAnalyzer.h"
#include "PicoDst.h"

#include <memory>

class PicoDstSkimmer : public TreeAnalyzer {
public:
	PicoDstSkimmer(){}
	~PicoDstSkimmer(){}

	virtual void initialize(){

		pico = shared_ptr<PicoDst>( new PicoDst( chain ) );

		EventBranches = config.getStringVector( nodePath + ".EventBranches" );
		TrackBranches = config.getStringVector( nodePath + ".TrackBranches" );
	}
	
protected:

	shared_ptr<PicoDst> pico;
	vector<string> EventBranches, TrackBranches;

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