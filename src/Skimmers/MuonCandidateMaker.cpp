#include "MuonCandidateMaker.h"


MuonCandidateMaker::MuonCandidateMaker(){

}

MuonCandidateMaker::~MuonCandidateMaker(){

}

void MuonCandidateMaker::initialize(){
	PicoDstSkimmer::initialize();
	
	INFO( classname(), "" );
	event = new CandidateEvent();
	tracks = new TClonesArray( "CandidateTrack" );
	
	createTree();

	muonCuts.init( config, nodePath + ".MuonCandidateCuts" );

	INFO( classname(), "" );
	INFO( classname(), "############### Muon Cuts ###################"  );
	muonCuts.report();
	INFO( classname(), "" );

}


bool MuonCandidateMaker::keepTrack( int iTrack ){

	double nHitsFit = abs(pico->Tracks_mNHitsFit[ iTrack ]);
	double nHitsMax = pico->Tracks_mNHitsMax[ iTrack ];
	double nHitsDedx = pico->Tracks_mNHitsDedx[ iTrack ];
	double nHitsRatio = nHitsFit / nHitsMax;
	TVector3 momentum( pico->Tracks_mPMomentum_mX1[iTrack], pico->Tracks_mPMomentum_mX2[iTrack], pico->Tracks_mPMomentum_mX3[iTrack] );

	if ( momentum.Pt() < muonCuts[ "pt" ]->min ){
		return false;
	}
	if ( nHitsRatio < muonCuts[ "nHitsRatio" ]->min ){
		// INFO( classname(), "nHitsRatio = " << nHitsRatio );
		return false;
	}
	if ( nHitsDedx < muonCuts[ "nHitsDedx" ]->min ){
		// INFO( classname(), "nHitsDedx = " << nHitsDedx );
		return false;
	}
	if ( !muonCuts[ "eta" ]->inInclusiveRange( momentum.Eta() )  ){
		// INFO( classname(), "eta = " << momentum.Eta() );
		return false;
	}
	if ( !muonCuts[ "matchFlagMtd" ]->inInclusiveRange( pico->Tracks_mMtdPidTraitsIndex[iTrack] ) ){
		return false;
	}




	// INFO( classname(), "pass ALL" );

	return true;
}