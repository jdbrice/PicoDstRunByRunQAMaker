
#include "MuonCandidateMaker.h"
#include "CandidateFilter.h"

MuonCandidateMaker::MuonCandidateMaker(){

}

MuonCandidateMaker::~MuonCandidateMaker(){

}

void MuonCandidateMaker::initialize(){
	CandidateMaker::initialize();

	book->cd();
	
	muonCuts.init( config, nodePath + ".MuonCandidateCuts" );

	INFO( classname(), "" );
	INFO( classname(), "############### Muon Cuts ###################"  );
	muonCuts.report();
	INFO( classname(), "" );

	gErrorIgnoreLevel = kError;

}


void MuonCandidateMaker::analyzeEvent(){
	CandidateMaker::analyzeEvent();

	// dont keep events by default, instead require at least 2 muon cands per event
	// keepCandidateEvent = false;
	candidateTree->keepEvent( true );
}

bool MuonCandidateMaker::keepTrack( int iTrack ){
	DEBUG( classname(), fmt::format( "(iTrack={0})", iTrack ) );

	shared_ptr<HistoBook> qaBook = nullptr;
	if ( config.getBool( nodePath + ".MakeQA:track" ) )
		qaBook = book;
	isMuon = CandidateFilter::isMuon( pico, iTrack, muonCuts, qaBook );
	if ( isMuon ){
		TRACE( classname(), "Muon Found" );
	}
	return isMuon;
}

void MuonCandidateMaker::analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack ){
	candidateTree->fillCandidateTrack( aTrack, iTrack );
	
	DEBUG( classname(), "nCandTracks = " << candidateTree->numberOfTracks() );
	
	// keep events with at least 2 tracks
	if ( candidateTree->numberOfTracks() >= 2 ){
		candidateTree->keepEvent( true );
	}
}
