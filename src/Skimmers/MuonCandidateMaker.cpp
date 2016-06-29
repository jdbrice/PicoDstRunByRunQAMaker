
#include "MuonCandidateMaker.h"
#include "CandidateFilter.h"

MuonCandidateMaker::MuonCandidateMaker(){

}

MuonCandidateMaker::~MuonCandidateMaker(){

}

void MuonCandidateMaker::initialize(){
	CandidateMaker::initialize();
	
	muonCuts.init( config, nodePath + ".MuonCandidateCuts" );

	INFO( classname(), "" );
	INFO( classname(), "############### Muon Cuts ###################"  );
	muonCuts.report();
	INFO( classname(), "" );

}


void MuonCandidateMaker::analyzeEvent(){
	CandidateMaker::analyzeEvent();

	// dont keep events by default, instead require at least 2 muon cands per event
	keepEvent = false;
}


bool MuonCandidateMaker::keepTrack( int iTrack ){
	DEBUG( classname(), fmt::format( "(iTrack={0})", iTrack ) );

	isMuon = CandidateFilter::isMuon( pico, iTrack, muonCuts, book );
	return isMuon;
}

void MuonCandidateMaker::analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int iCandTrack ){
	fillCandidateTrack( aTrack, iTrack );
	
	// keep events with at least 2 tracks
	if ( iCandTrack >= 1 )
		keepEvent = true;
}
