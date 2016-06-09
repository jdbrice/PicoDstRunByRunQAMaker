
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
	isMuon = CandidateFilter::isMuon( pico, iTrack, muonCuts );
	return isMuon;
}

void MuonCandidateMaker::analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int iCandTrack ){
	aTrack->charge = pico->Tracks_mNHitsFit[iTrack] > 0 ? 1 : -1;

	aTrack->pX = pico->Tracks_mPMomentum_mX1[iTrack];
	aTrack->pY = pico->Tracks_mPMomentum_mX2[iTrack];
	aTrack->pZ = pico->Tracks_mPMomentum_mX3[iTrack];

	aTrack->species = speciesMask();

	for ( int i = 0; i < 15; i++ ){
		aTrack->padding[ i ] = i*i* aTrack->pX / 3.5;
	}
	
	// keep events with at least 2 tracks
	if ( iCandTrack >= 1 )
		keepEvent = true;
}
