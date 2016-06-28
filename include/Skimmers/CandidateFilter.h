#ifndef CANDIDATE_FILTER_H
#define CANDIDATE_FILTER_H

//Project
#include "IPicoDst.h"

// ROOT
#include "TVector3.h"

//RooBarb
#include "CutCollection.h"
#include "HistoBook.h"


// STL
#include <memory>

class CandidateFilter
{
public:
	CandidateFilter();
	~CandidateFilter();
	
	static bool isMuon( shared_ptr<IPicoDst> pico, int iTrack, CutCollection &ccol, HistoBook * book = nullptr ){


		bool allCuts = true;

		bool makeQA = true;
		if ( nullptr == book  )
			makeQA = false;
		string cutsName = "MtdMuon";

		double nHitsFit = abs(pico->Tracks_mNHitsFit[ iTrack ]);
		double nHitsMax = pico->Tracks_mNHitsMax[ iTrack ];
		double nHitsDedx = pico->Tracks_mNHitsDedx[ iTrack ];
		double nHitsRatio = nHitsFit / nHitsMax;
		TVector3 momentum( pico->Tracks_mPMomentum_mX1[iTrack], pico->Tracks_mPMomentum_mX2[iTrack], pico->Tracks_mPMomentum_mX3[iTrack] );

		if ( momentum.Pt() < ccol[ "pt" ]->min ){
			allCuts = false;
		} else {
			passTrackCut( "mom", allCuts, book, cutsName );
		}
		if ( nHitsRatio < ccol[ "nHitsRatio" ]->min ){
			allCuts = false;
		} else {
			passTrackCut( "nHitsRatio", allCuts, book, cutsName );
		}
		if ( nHitsDedx < ccol[ "nHitsDedx" ]->min ){
			allCuts = false;
		} else {
			passTrackCut( "nHitsDedx", allCuts, book, cutsName );
		}
		if ( !ccol[ "eta" ]->inInclusiveRange( momentum.Eta() )  ){
			allCuts = false;
		} else {
			passTrackCut( "eta", allCuts, book, cutsName );
		}
		int iMtd = pico->Tracks_mMtdPidTraitsIndex[iTrack];
		if ( !ccol[ "matchFlagMtd" ]->inInclusiveRange( iMtd ) || !ccol[ "matchFlagMtd" ]->inInclusiveRange( pico->MtdPidTraits_mMatchFlag[ iMtd ] ) ){
			allCuts = false;
		} else {
			passTrackCut( "mtdMatch", allCuts, book, cutsName );
		}

		if ( !ccol[ "dTofMtd" ]->inInclusiveRange( pico->MtdPidTraits_mDeltaTimeOfFlight[ iMtd ] ) ){
			allCuts = false;
		} else {
			passTrackCut( "dTof", allCuts, book, cutsName );
		}

		if ( !ccol[ "dyMtd" ]->inInclusiveRange( pico->MtdPidTraits_mDeltaY[ iMtd ] ) ){
			allCuts = false;
		} else {
			passTrackCut( "dy", allCuts, book, cutsName );
		}
		if ( !ccol[ "dzMtd" ]->inInclusiveRange( pico->MtdPidTraits_mDeltaZ[ iMtd ] ) ){
			allCuts = false;
		} else {
			passTrackCut( "dz", allCuts, book, cutsName );
		}

		return true;
	}


	static bool isElectron( shared_ptr<IPicoDst> pico, int iTrack, CutCollection &ccol ){

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

	static bool isTpcTofElectron( shared_ptr<IPicoDst> pico, int iTrack, CutCollection &ccol, HistoBook * book = nullptr ){

		bool allCuts = true;

		bool makeQA = true;
		if ( nullptr == book  )
			makeQA = false;
		string cutsName = "tpcTofElectron";

		double nHitsFit = abs( pico->Tracks_mNHitsFit[ iTrack ] );
		double nHitsMax = pico->Tracks_mNHitsMax[ iTrack ];
		double nHitsDedx = pico->Tracks_mNHitsDedx[ iTrack ];
		double nHitsRatio = nHitsFit / nHitsMax;
		double dEdx = pico->Tracks_mDedx[ iTrack ] / 1000.0;
		TVector3 momentum( pico->Tracks_mPMomentum_mX1[iTrack], pico->Tracks_mPMomentum_mX2[iTrack], pico->Tracks_mPMomentum_mX3[iTrack] );

		int iBTof = pico->Tracks_mBTofPidTraitsIndex[ iTrack ];
		if ( iBTof < 0 ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "tofMatch", allCuts, book, cutsName );
		}

		double yLocal = -999;
		double invBeta = -999;
		if ( iBTof >= 0 ){
			yLocal = pico->BTofPidTraits_mBTofYLocal[ iBTof ] / 1000.0;
			invBeta = 1.0 / (pico->BTofPidTraits_mBTofBeta[ iBTof ] / 20000.0);		
		}
		
		double gDCA = 0;
		 
		if ( momentum.Pt() < ccol[ "pt" ]->min ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else {
			if ( makeQA ) passTrackCut( "pt", allCuts, book, cutsName );
		}
		if ( momentum.Mag() > ccol[ "momentum" ]->max ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "momentum", allCuts, book, cutsName );
		}
		if ( nHitsRatio < ccol[ "nHitsRatio" ]->min ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "nHitsRatio", allCuts, book, cutsName );
		}
		if ( nHitsDedx < ccol[ "nHitsDedx" ]->min ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "nHitsDedx", allCuts, book, cutsName );
		}
		if ( !ccol[ "eta" ]->inInclusiveRange( momentum.Eta() )  ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "eta", allCuts, book, cutsName );
		}
		
		if ( gDCA > ccol[ "dca" ]->max ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "dca", allCuts, book, cutsName );
		}
		
		if ( !ccol[ "yLocal" ]->inInclusiveRange( yLocal ) ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "yLocal", allCuts, book, cutsName );
		}

		if ( !ccol[ "invBeta" ]->inInclusiveRange( abs( 1 - invBeta ) ) ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "beta", allCuts, book, cutsName );
		}

		// INFO( "CandidateFilter", "yLocal == " << yLocal << endl );
		

		// nSigmaElectron Cuts
		if ( !ccol[ "dEdx" ]->inInclusiveRange( dEdx ) ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "dEdx", allCuts, book, cutsName );
		}




		return allCuts;
	}




	static void passTrackCut( string cut, bool passAllCuts, HistoBook * book, string name = "track" ){
		DEBUG( "CandidateFilter", fmt::format("(cut={0}, passAllCuts={1})", cut, bts(passAllCuts) ) );
		book->cd("trackQA");
		if ( !book->exists( name + "_single_cuts" ) ){
			book->clone( "track_single_cuts", name + "_single_cuts" );
		}
		if ( !book->exists( name + "_cuts" ) ){
			book->clone( "track_cuts", name + "_cuts" );
		}

		book->fill( name + "_single_cuts", cut, 1.0 );

		if ( passAllCuts ){
			book->fill( name + "_cuts", cut, 1.0 );
		}
		return;
	}

};

#endif