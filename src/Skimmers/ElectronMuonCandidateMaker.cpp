#include "ElectronMuonCandidateMaker.h"
#include "CandidateFilter.h"

ElectronMuonCandidateMaker::ElectronMuonCandidateMaker(){

}

ElectronMuonCandidateMaker::~ElectronMuonCandidateMaker(){

}

void ElectronMuonCandidateMaker::initialize(){
	CandidateMaker::initialize();
	
	if ( !config.exists( nodePath + ".MuonCandidateCuts" ) ){
		ERROR( classname(), "Cannot find **required** MuonCandidateCuts" );
		chain = nullptr;
		return;
	}
	muonCuts.init( config, nodePath + ".MuonCandidateCuts" );
	INFO( classname(), "" );
	INFO( classname(), "############### Muon Cuts ###################"  );
	muonCuts.report();
	INFO( classname(), "" );

	electronCuts.init( config, nodePath + ".ElectronCandidateCuts" );
	electronCuts.setDefault( "pt", 0.1, 10000 );
	electronCuts.setDefault( "nHitsDedx", 10, 10000 );
	electronCuts.setDefault( "nHitsRatio", 0.52, 100 );
	electronCuts.setDefault( "eta", -0.8, 0.8 );
	electronCuts.setDefault( "nSigmaPion", -1.5, 1.5 );
	electronCuts.setDefault( "matchFlagEmc", 1, 100 );
	INFO( classname(), "" );
	INFO( classname(), "############### Electron Cuts ###################"  );
	electronCuts.report();
	INFO( classname(), "" );

	gErrorIgnoreLevel = kBreak;

}



void ElectronMuonCandidateMaker::analyzeEvent(){
	CandidateMaker::analyzeEvent();

	// dont keep events by default, instead require at least 2 muon cands per event
	keepEvent = false;
}


bool ElectronMuonCandidateMaker::keepTrack( int iTrack ){
	DEBUG( classname(), fmt::format( "(iTrack={0})", iTrack ) );

	isElectron = CandidateFilter::isElectron( pico, iTrack, electronCuts );
	isMuon = CandidateFilter::isMuon( pico, iTrack, muonCuts );
	
	if ( isElectron )
		nElectrons ++;
	if ( isMuon )
		nMuons ++;

	return ( isElectron || isMuon );
 	return true;
}

void ElectronMuonCandidateMaker::analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int iCandTrack ){
	aTrack->charge = pico->Tracks_mNHitsFit[iTrack] > 0 ? 1 : -1;

	aTrack->pX = pico->Tracks_mPMomentum_mX1[iTrack];
	aTrack->pY = pico->Tracks_mPMomentum_mX2[iTrack];
	aTrack->pZ = pico->Tracks_mPMomentum_mX3[iTrack];

	aTrack->species = speciesMask();
	
	// keep events with at least 2 tracks
	if ( iCandTrack >= 1 && nElectrons >= 1 && nMuons >= 1)
		keepEvent = true;
}
