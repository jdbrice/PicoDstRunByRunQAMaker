#ifndef PICODST16A_SKIMMER_H
#define PICODST16A_SKIMMER_H

// RooBarb
#include "TreeAnalyzer.h"
#include "CutCollection.h"
#include "Extra/format.h"

// Project
#include "PicoDst16aReader.h"
#include "CandidateTreeMaker.h"
#include "CandidateEventWriter.h"
#include "CandidateTracksWriter.h"
#include "CandidateMtdPidTraitsWriter.h"
#include "CandidateBTofPidTraitsWriter.h"
#include "CandidateTrackHelixWriter.h"

#include "CandidateFilter.h"
#include "EventFilter.h"

#include "StPicoTrack.h"

#include "StRefMultCorr.h"
#include "CentralityMaker.h"

// STL
#include <memory>


class PicoDst16aSkimmer : public TreeAnalyzer {
public:
	virtual const char* classname() const { return "PicoDst16aSkimmer"; }
	PicoDst16aSkimmer(){}
	~PicoDst16aSkimmer(){}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		pico = shared_ptr<PicoDst16aReader>( new PicoDst16aReader( chain ) );

		fEvent   = new CandidateEvent();
		fTrack   = new CandidateTrack();
		fMtdPid  = new CandidateTrackMtdPidTraits();
		fBTofPid = new CandidateTrackBTofPidTraits();
		fHelix   = new CandidateTrackHelix();

		treeFile = new TFile( config.getXString( nodePath + ".output.TTree:url" ).c_str(), "RECREATE" );
		treeFile->cd();
		tree = new TTree( "FemtoDst", "" );
		eventWriter   = shared_ptr<CandidateEventWriter>( new CandidateEventWriter( tree ) );
		tracksWriter  = shared_ptr<CandidateTracksWriter>( new CandidateTracksWriter( tree ) );
		mtdPidWriter  = shared_ptr<CandidateMtdPidTraitsWriter>( new CandidateMtdPidTraitsWriter( tree ) );
		btofPidWriter = shared_ptr<CandidateBTofPidTraitsWriter>( new CandidateBTofPidTraitsWriter( tree ) );
		helixWriter   = shared_ptr<CandidateTrackHelixWriter>( new CandidateTrackHelixWriter( tree ) );



		eventCuts.init( config, nodePath + ".EventCuts" );
		EventFilter::setDefaultEventCuts( eventCuts );
		INFO( classname(), "" );
		INFO( classname(), "############### Event Cuts ###################"  );
		eventCuts.report();
		INFO( classname(), "" );

		muonCuts.init( config, nodePath + ".MuonCandidateCuts" );
		CandidateFilter::setDefaultMuonCuts( muonCuts );
		INFO( classname(), "" );
		INFO( classname(), "############### Muon Cuts ###################"  );
		muonCuts.report();
		INFO( classname(), "" );

		electronCuts.init( config, nodePath + ".ElectronCandidateCuts" );
		CandidateFilter::setDefaultElectronCuts( electronCuts );
		INFO( classname(), "" );
		INFO( classname(), "############### Electron Cuts ###################"  );
		electronCuts.report();
		INFO( classname(), "" );


		wantElectrons = config.getBool( nodePath + ".Select:electrons", false );
		wantMuons = config.getBool( nodePath + ".Select:muons", false );

		INFO( classname(), "Want Electrons : " << bts( wantElectrons ) );
		INFO( classname(), "Want Muons : " << bts( wantMuons ) );

		rmc = CentralityMaker::instance()->getgRefMultCorr();

	}
	
protected:

	bool wantMuons     = false;
	bool wantElectrons = false;
	TFile * treeFile   = nullptr;
	TTree * tree       = nullptr;
	shared_ptr<PicoDst16aReader> pico;
	
	CutCollection eventCuts;
	CutCollection muonCuts;
	CutCollection electronCuts;

	CandidateEvent *fEvent;
	CandidateTrack *fTrack;
	CandidateTrackMtdPidTraits *fMtdPid;
	CandidateTrackBTofPidTraits *fBTofPid;
	CandidateTrackHelix *fHelix;

	StRefMultCorr * rmc = nullptr;
	
	
	virtual void postMake() {
		TreeAnalyzer::postMake();

		INFO( classname(), "Writing treeFile " << treeFile );
		treeFile->cd();
		tree->Write();
		treeFile->Close();
	}

	virtual bool keepEvent(){

		rmc->init( pico->event()->runId() );
		rmc->initEvent( 
			pico->event()->grefMult(), 
			pico->event()->primaryVertex().z(), 
			pico->event()->ZDCx()
		);

		CandidateTreeMaker::fillCandidateEvent( pico, fEvent, 
												0, 
												rmc->getCentralityBin16(), 
												rmc->getWeight(), 
												0 );



		return EventFilter::keepEvent( pico, fEvent, eventCuts );
	}
	virtual bool keepTrack( int iTrack ){

		// INFO( classname(), "PicoTrack[" << iTrack << "]" );
		
		fTrack->reset();
		fMtdPid->reset();
		fBTofPid->reset();
		fHelix->reset();

		StPicoTrack * pTrack = pico->track( iTrack );
		StPicoMtdPidTraits * pMtdPid = pico->mtdPidTraitFor( iTrack );
		StPicoBTofPidTraits * pBTofPid = pico->btofPidTraitFor( iTrack );


		CandidateTreeMaker::fillCandidateTrack( pTrack, pico->event(), fTrack );
		CandidateTreeMaker::fillCandidateMtdPidTraits( pMtdPid, fMtdPid );
		CandidateTreeMaker::fillCandidateBTofPidTraits( pBTofPid, fBTofPid );
		CandidateTreeMaker::fillCandidateTrackHelix( pTrack, fHelix );

		bool isMuon = false;

		if ( wantMuons )
			isMuon = CandidateFilter::isMuon( fTrack, fMtdPid, muonCuts );
		
		bool isElectron = false;

		if ( wantElectrons )
			isElectron = CandidateFilter::isTpcTofElectron( fTrack, fBTofPid, electronCuts );

		return (wantMuons && isMuon) || ( wantElectrons && isElectron) ;
	}

	virtual void analyzeEvent(){


		eventWriter->set( fEvent );
		DEBUG( classname(), "==========EVENT START=========" );

		tracksWriter->reset();
		btofPidWriter->reset();
		mtdPidWriter->reset();
		helixWriter->reset();

		int nTracks = pico->nTracks();
		for ( int i = 0; i < nTracks; i++ ){
			if ( keepTrack( i ) ){
				analyzeTrack( i );
			}
		}
		// DEBUG( classname(), "mRunId" << pico->event()->runId() );
		tree->Fill();

		DEBUG( classname(), "==========EVENT STOP=========" );
	}
	
	// virtual void trackLoop();
	virtual void analyzeTrack( int iTrack ){
		

		btofPidWriter->add( fBTofPid, fTrack );	
		mtdPidWriter->add( fMtdPid, fTrack );

		helixWriter->add( fHelix, fTrack );
		DEBUG( classname(), "\n" << fTrack->print() );
		DEBUG( classname(), "\n" << fMtdPid->print() );
		
		tracksWriter->add( fTrack );
		
		

	}

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


	shared_ptr<CandidateEventWriter> eventWriter;
	shared_ptr<CandidateTracksWriter> tracksWriter;
	shared_ptr<CandidateMtdPidTraitsWriter> mtdPidWriter;
	shared_ptr<CandidateBTofPidTraitsWriter> btofPidWriter;
	shared_ptr<CandidateTrackHelixWriter> helixWriter;

};

#endif