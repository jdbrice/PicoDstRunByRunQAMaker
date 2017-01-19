#ifndef PICODST_SKIMMER_H
#define PICODST_SKIMMER_H

// RooBarb
#include "TreeAnalyzer.h"
#include "CutCollection.h"
#include "Extra/format.h"

// Project
#include "IPicoDst.h"
#include "TriggerFilter.h"
#include "EventPlaneCorr.h"
#include "RunMapFactory.h"

// STL
#include <memory>

//ROOT
#include "TNtuple.h"


class SharedPicoDstSkimmer;

class PicoDstSkimmer : public TreeAnalyzer {
public:
	friend SharedPicoDstSkimmer;
	virtual const char* classname() const { return "PicoDstSkimmer"; }
	PicoDstSkimmer(){}
	~PicoDstSkimmer(){}

	virtual void initialize();
	
protected:

	shared_ptr<IPicoDst> pico;
	vector<string> EventBranches, TrackBranches;
	TriggerFilter tf;
	CutCollection eventCuts;
	EventPlaneCorr epc;
	shared_ptr<RunMapFactory> rmf;

	string picoDstAdapter;

	TTree * eventTree     = nullptr;
	TFile * eventTreeFile = nullptr;
	// eventTree data members
	UInt_t  et_mRunNumber;
	UInt_t  et_mEventNumber;
	Float_t et_mX1;              // Primary vertex
	Float_t et_mX2;              // Primary vertex
	Float_t et_mX3;              // Primary vertex
	Float_t et_mVpdVz;           // Z Vertex from VPD
	UInt_t  et_mNTracks;         // Number of pico Tracks
	UInt_t  et_mNTracksEvtPlane; // Number of Event Plane Tracks
	Bool_t  et_mPassCuts;        // did this pass the cuts?

	virtual void eventLoop();
	virtual bool keepEvent();
	virtual void analyzeEvent();
	
	virtual void trackLoop();
	virtual void analyzeTrack( int iTrack );

	void passEventCut( string cut, bool passAllCuts ){
		DEBUG( classname(), fmt::format("(cut={0}, passAllCuts={1})", cut, bts(passAllCuts) ) );
		book->cd("eventQA");

		book->fill( "event_single_cuts", cut, 1.0 );

		if ( passAllCuts ){
			book->fill( "event_cuts", cut, 1.0 );
		}
		return;
	}

	void passTrackCut( string cut, bool passAllCuts ){
		DEBUG( classname(), fmt::format("(cut={0}, passAllCuts={1})", cut, bts(passAllCuts) ) );
		book->cd("trackQA");

		book->fill( "track_single_cuts", cut, 1.0 );

		if ( passAllCuts ){
			book->fill( "track_cuts", cut, 1.0 );
		}
		return;
	}

	Long64_t readBranchList( vector<string> &list, Long64_t &iEvent ){
		// no protection
		Long64_t read = 0;
		for (string s : list ){
			TRACE( classname(), "Reading Branch : " << s );
			read += chain->GetBranch( s.c_str() )->GetEntry( iEvent );
		}
		return read;
	}


	virtual void postMake(){
		if ( nullptr != eventTree && nullptr != eventTreeFile ){
			eventTreeFile->cd();
			eventTree->Write();
		}
	}

};

#endif