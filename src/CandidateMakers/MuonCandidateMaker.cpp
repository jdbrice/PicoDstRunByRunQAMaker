
#include "MuonCandidateMaker.h"
#include "CandidateFilter.h"

MuonCandidateMaker::MuonCandidateMaker(){

}

MuonCandidateMaker::~MuonCandidateMaker(){

}

void MuonCandidateMaker::initialize(){
	CandidateMaker::initialize();

	book->cd();
	// add the EventPlane Branch
	createTree( 
				false, // EventPlane branch
				true,  // Tracks
				false, // bTof
				true   // MTD
				 );
	
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
	keepCandidateEvent = false;
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

void MuonCandidateMaker::analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int iCandTrack ){
	TRACE( classname(), "" );
	fillCandidateTrack( aTrack, iTrack );
	
	// keep events with at least 2 tracks
	if ( iCandTrack >= 1 )
		keepCandidateEvent = true;
}
