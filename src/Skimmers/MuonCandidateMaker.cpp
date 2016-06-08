#include "MuonCandidateMaker.h"


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

	double nHitsFit = abs(pico->Tracks_mNHitsFit[ iTrack ]);
	double nHitsMax = pico->Tracks_mNHitsMax[ iTrack ];
	double nHitsDedx = pico->Tracks_mNHitsDedx[ iTrack ];
	double nHitsRatio = nHitsFit / nHitsMax;
	TVector3 momentum( pico->Tracks_mPMomentum_mX1[iTrack], pico->Tracks_mPMomentum_mX2[iTrack], pico->Tracks_mPMomentum_mX3[iTrack] );

	if ( momentum.Pt() < muonCuts[ "pt" ]->min ){
		return false;
	}
	if ( nHitsRatio < muonCuts[ "nHitsRatio" ]->min ){
		return false;
	}
	if ( nHitsDedx < muonCuts[ "nHitsDedx" ]->min ){
		return false;
	}
	if ( !muonCuts[ "eta" ]->inInclusiveRange( momentum.Eta() )  ){
		return false;
	}
	if ( !muonCuts[ "matchFlagMtd" ]->inInclusiveRange( pico->Tracks_mMtdPidTraitsIndex[iTrack] ) ){
		return false;
	}
	return true;
}

void MuonCandidateMaker::analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int iCandTrack ){
	aTrack->charge = pico->Tracks_mNHitsFit[iTrack] > 0 ? 1 : -1;

	aTrack->pX = pico->Tracks_mPMomentum_mX1[iTrack];
	aTrack->pY = pico->Tracks_mPMomentum_mX2[iTrack];
	aTrack->pZ = pico->Tracks_mPMomentum_mX3[iTrack];
	
	// keep events with at least 2 tracks
	if ( iCandTrack >= 1 )
		keepEvent = true;
}
