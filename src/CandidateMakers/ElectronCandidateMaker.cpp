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
	electronCuts.setDefault( "dEdx", -10000000, 10000000 );
	electronCuts.setDefault( "invBeta", -1000000, 10000000 );
	INFO( classname(), "" );
	INFO( classname(), "############### Electron Cuts ###################"  );
	electronCuts.report();
	INFO( classname(), "" );

	gErrorIgnoreLevel = kBreak;

}



void ElectronCandidateMaker::analyzeEvent(){
	CandidateMaker::analyzeEvent();

	// dont keep events by default, instead require at least 2 electrons cands per event
	// keepCandidateEvent = false;
	nElectrons = 0;
}


bool ElectronCandidateMaker::keepTrack( int iTrack ){
	DEBUG( classname(), fmt::format( "(iTrack={0})", iTrack ) );



	shared_ptr<HistoBook> qaBook = nullptr;
	if ( config.getBool( nodePath + ".MakeQA:track" ) )
		qaBook = book;

	isElectron = CandidateFilter::isTpcTofElectron( pico, iTrack, electronCuts, qaBook );
	if ( isElectron )
		nElectrons ++;

 	return isElectron;
}

void ElectronCandidateMaker::analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack ){
	
	candidateTree->fillCandidateTrack( aTrack, iTrack );
	if ( candidateTree->numberOfTracks() >= 2 ){
		candidateTree->keepEvent( true );
	}
}
