#ifndef CANDIDATE_FILTER_H
#define CANDIDATE_FILTER_H

//Project
#include "PicoDst.h"

// ROOT
#include "TVector3.h"

//RooBarb
#include "CutCollection.h"


// STL
#include <memory>

class CandidateFilter
{
public:
	CandidateFilter();
	~CandidateFilter();
	
	static bool isMuon( shared_ptr<PicoDst> pico, int iTrack, CutCollection &ccol ){

		double nHitsFit = abs(pico->Tracks_mNHitsFit[ iTrack ]);
		double nHitsMax = pico->Tracks_mNHitsMax[ iTrack ];
		double nHitsDedx = pico->Tracks_mNHitsDedx[ iTrack ];
		double nHitsRatio = nHitsFit / nHitsMax;
		TVector3 momentum( pico->Tracks_mPMomentum_mX1[iTrack], pico->Tracks_mPMomentum_mX2[iTrack], pico->Tracks_mPMomentum_mX3[iTrack] );

		if ( momentum.Pt() < ccol[ "pt" ]->min ){
			return false;
		}
		if ( nHitsRatio < ccol[ "nHitsRatio" ]->min ){
			return false;
		}
		if ( nHitsDedx < ccol[ "nHitsDedx" ]->min ){
			return false;
		}
		if ( !ccol[ "eta" ]->inInclusiveRange( momentum.Eta() )  ){
			return false;
		}
		int iMtd = pico->Tracks_mMtdPidTraitsIndex[iTrack];
		if ( !ccol[ "matchFlagMtd" ]->inInclusiveRange( iMtd ) || !ccol[ "matchFlagMtd" ]->inInclusiveRange( pico->MtdPidTraits_mMatchFlag[ iMtd ] ) ){
			return false;
		}
		return true;
	}


	static bool isElectron( shared_ptr<PicoDst> pico, int iTrack, CutCollection &ccol ){

		double nHitsFit = abs(pico->Tracks_mNHitsFit[ iTrack ]);
		double nHitsMax = pico->Tracks_mNHitsMax[ iTrack ];
		double nHitsDedx = pico->Tracks_mNHitsDedx[ iTrack ];
		double nHitsRatio = nHitsFit / nHitsMax;
		TVector3 momentum( pico->Tracks_mPMomentum_mX1[iTrack], pico->Tracks_mPMomentum_mX2[iTrack], pico->Tracks_mPMomentum_mX3[iTrack] );

		if ( momentum.Pt() < ccol[ "pt" ]->min ){
			return false;
		}
		if ( nHitsRatio < ccol[ "nHitsRatio" ]->min ){
			return false;
		}
		if ( nHitsDedx < ccol[ "nHitsDedx" ]->min ){
			return false;
		}
		if ( !ccol[ "eta" ]->inInclusiveRange( momentum.Eta() )  ){
			return false;
		}
		int iEmc = pico->Tracks_mEmcPidTraitsIndex[iTrack];
		if ( !ccol[ "matchFlagEmc" ]->inInclusiveRange( iEmc ) ){
			return false;
		}

		return true;
	}

};

#endif