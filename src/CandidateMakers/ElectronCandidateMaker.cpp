#include "ElectronCandidateMaker.h"
#include "CandidateFilter.h"

ElectronCandidateMaker::ElectronCandidateMaker(){

}

ElectronCandidateMaker::~ElectronCandidateMaker(){

}

void ElectronCandidateMaker::initialize(){
	CandidateMaker::initialize();
	
	if ( !config.exists( nodePath + ".ElectronCandidateCuts" ) ){
		ERROR( classname(), "Cannot find **required** ElectronCandidateCuts" );
		chain = nullptr;
		return;
	}

	electronCuts.init( config, nodePath + ".ElectronCandidateCuts" );
	electronCuts.setDefault( "pt", 0.2, 10000 );
	electronCuts.setDefault( "momentum", 0.0, 30.0 );
	electronCuts.setDefault( "nHitsDedx", 10, 10000 );
	electronCuts.setDefault( "nHitsRatio", 0.52, 100 );
	electronCuts.setDefault( "eta", -0.9, 0.9 );
	electronCuts.setDefault( "dca", 0, 3.0 );
	electronCuts.setDefault( "yLocal", -1.8, 1.8 );
	INFO( classname(), "" );
	INFO( classname(), "############### Electron Cuts ###################"  );
	electronCuts.report();
	INFO( classname(), "" );

	gErrorIgnoreLevel = kBreak;

}



void ElectronCandidateMaker::analyzeEvent(){
	CandidateMaker::analyzeEvent();

	// dont keep events by default, instead require at least 2 electrons cands per event
	keepCandidateEvent = false;
}


bool ElectronCandidateMaker::keepTrack( int iTrack ){
	DEBUG( classname(), fmt::format( "(iTrack={0})", iTrack ) );

	isElectron = CandidateFilter::isTpcTofElectron( pico, iTrack, electronCuts );
	if ( isElectron )
		nElectrons ++;

 	return isElectron;
}

void ElectronCandidateMaker::analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int iCandTrack ){
	
	fillCandidateTrack( aTrack, iTrack );
	// aTrack->charge = pico->Tracks_mNHitsFit[iTrack] > 0 ? 1 : -1;

	// aTrack->pX = pico->Tracks_mPMomentum_mX1[iTrack];
	// aTrack->pY = pico->Tracks_mPMomentum_mX2[iTrack];
	// aTrack->pZ = pico->Tracks_mPMomentum_mX3[iTrack];

	// aTrack->dEdx = pico->Tracks_mDedx[ iTrack ] / 1000.0;

	// int iBTof = pico->Tracks_mBTofPidTraitsIndex[ iTrack ];
	// if ( iBTof >= 0 )
	// 	aTrack->beta = pico->BTofPidTraits_mBTofBeta[ iBTof ] / 20000.0;
	// else 
	// 	aTrack->beta = 0;

	// aTrack->species = speciesMask();
	
	// keep events with at least 2 tracks
	if ( iCandTrack >= 1 && nElectrons >= 2 )
		keepCandidateEvent = true;
}
