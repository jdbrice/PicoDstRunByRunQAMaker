#ifndef SHARED_PICODST_SKIMMER_H
#define SHARED_PICODST_SKIMMER_H

// RooBarb
#include "SharedTreeAnalyzer.h"
#include "CutCollection.h"
#include "format.h"

// Project
#include "IPicoDst.h"
#include "TriggerFilter.h"

// STL
#include <memory>

class SharedPicoDstSkimmer : public SharedTreeAnalyzer {
public:
	virtual const char* classname() const { return "SharedPicoDstSkimmer"; }
	SharedPicoDstSkimmer(){}
	~SharedPicoDstSkimmer(){}

	virtual void initialize();

	static shared_ptr<IPicoDst> getPicoDst( ) { return pico; } 
	
protected:

	static shared_ptr<IPicoDst> pico;
	vector<string> EventBranches, TrackBranches;

	virtual void eventLoop();
	
	virtual void trackLoop();

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