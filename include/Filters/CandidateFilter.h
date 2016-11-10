#ifndef CANDIDATE_FILTER_H
#define CANDIDATE_FILTER_H

//Project
#include "IPicoDst.h"
#include "CandidateTrack.h"
#include "CandidateTrackMtdPidTraits.h"


// ROOT
#include "TVector3.h"

//RooBarb
#include "CutCollection.h"
#include "HistoBook.h"
#include "Extra/format.h"


// STL
#include <memory>
#include <limits>

class CandidateFilter
{
public:
	CandidateFilter() {}
	~CandidateFilter() {}
	
	static void setDefaultMuonCuts( CutCollection &ccol ){
		ccol.setDefault( "pt"             , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "nSigmaPion"     , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "nHitsRatio"     , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "nHitsFit"       , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "nHitsDedx"      , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "eta"            , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "gDCA"           , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );

		ccol.setDefault( "mtdTriggerFlag" , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "matchFlagMtd"   , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "dTofMtd"        , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "dyMtd"          , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "dyMtdPos"       , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "dyMtdNeg"       , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "dzMtd"          , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "drMtd"          , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "mtdCell"        , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
	}

	static void setDefaultElectronCuts( CutCollection &ccol ){
		ccol.setDefault( "pt"             , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "momentum"       , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "nSigmaPion"     , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "nHitsRatio"     , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "nHitsFit"       , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "nHitsDedx"      , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "eta"            , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "gDCA"           , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );

		ccol.setDefault( "matchFlag"      , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "invBeta"        , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "yLocal"         , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "zLocal"         , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );

	}

	static void initializeBinLabels( const shared_ptr<HistoBook>& _book, vector<string> _labels, string _prefix ){
		if ( nullptr == _book ){
			ERROR( "CandidateFilter", "Cannot initialize bin labels, null HistoBook" );
		}


		TH1 * hsc = _book->get( _prefix + "_single_cuts", "trackQA" );
		TH1 * hc = _book->get( _prefix + "_cuts", "trackQA" );

		if ( nullptr == hsc || nullptr == hc ){
			ERROR( "CandidateFilter", "Cannot initialize bin labels, null histogram" );
		}

		for ( int i = 0; i < _labels.size(); i++ ){
			hsc->GetXaxis()->SetBinLabel( i+1, _labels[i].c_str() );
			hc->GetXaxis()->SetBinLabel( i+1, _labels[i].c_str() );
			TRACE( "CandidateFilter", "Setting " << _prefix + "_single_cuts[ " << i+1 << " ] = " << _labels[i] );
			TRACE( "CandidateFilter", "Setting " << _prefix + "_cuts[ " << i+1 << " ] = " << _labels[i] );
		}
	}

	static bool isMuon( CandidateTrack *_aTrack, CandidateTrackMtdPidTraits * _mtdPidTraits, CutCollection &ccol, const shared_ptr<HistoBook>& book = nullptr ){
		

		if ( nullptr == _aTrack || nullptr == _mtdPidTraits ){
			ERROR( "CandidateFilter", "Null Track" );
			return false;
		}

		preTrackCuts( _aTrack, _mtdPidTraits, book );

		bool allCuts = true;

		bool makeQA = true;
		if ( nullptr == book  )
			makeQA = false;
		string cutsName = "MtdMuon";

		double nHitsFit = abs( _aTrack->mNHitsFit);
		double nHitsMax = _aTrack->mNHitsMax;
		double nHitsDedx = _aTrack->mNHitsDedx;
		double nHitsRatio = nHitsFit / nHitsMax;
		double nSigmaPion = _aTrack->mNSigmaPion / 100.0;
		TVector3 momentum = _aTrack->pMomentum();

		double deltaR = sqrt( _mtdPidTraits->mDeltaY*_mtdPidTraits->mDeltaY + _mtdPidTraits->mDeltaZ*_mtdPidTraits->mDeltaZ );

		if ( makeQA ){
			book->cd("trackQA");
			passTrackCut( "All", allCuts, book, cutsName );
		}

		if ( momentum.Pt() < ccol[ "pt" ]->min ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "Mom", allCuts, book, cutsName );
		}

		if ( !ccol[ "nSigmaPion" ]->inInclusiveRange( nSigmaPion ) ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "nSigPi", allCuts, book, cutsName );
		}

		if ( nHitsRatio < ccol[ "nHitsRatio" ]->min ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "nHitsRatio", allCuts, book, cutsName );
		}
		if ( nHitsDedx < ccol[ "nHitsDedx" ]->min ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "nHitsDedx", allCuts, book, cutsName );
		}
		if ( nHitsFit < ccol[ "nHitsFit" ]->min ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "nHitsFit", allCuts, book, cutsName );
		}
		if ( !ccol[ "eta" ]->inInclusiveRange( momentum.Eta() )  ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "eta", allCuts, book, cutsName );
		}

		if ( !ccol[ "gDCA" ]->inInclusiveRange( _aTrack->gDCA() ) ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "gDCA", allCuts, book, cutsName );
		}

		if ( !ccol[ "matchFlagMtd" ]->inInclusiveRange( _mtdPidTraits->mMatchFlag ) ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "mtdMatchFlag", allCuts, book, cutsName );
		}

		if ( !ccol[ "mtdTriggerFlag" ]->inInclusiveRange( _mtdPidTraits->mTriggerFlag ) ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "mtdTriggerFlag", allCuts, book, cutsName );
		}

		if ( !ccol[ "mtdCell" ]->inInclusiveRange( _mtdPidTraits->mMtdHitChan % 12 ) ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ){
			passTrackCut( "mtdCell", allCuts, book, cutsName );
		}

		if ( !ccol[ "dTofMtd" ]->inInclusiveRange( _mtdPidTraits->mDeltaTimeOfFlight ) ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "mtdDeltaTof", allCuts, book, cutsName );
		}

		if ( !ccol[ "dyMtd" ]->inInclusiveRange( _mtdPidTraits->mDeltaY ) ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "mtdDeltaY", allCuts, book, cutsName );
		}

		if ( _aTrack->charge() > 0 ){
			if ( !ccol[ "dyMtdPos" ]->inInclusiveRange( _mtdPidTraits->mDeltaY ) ){
				allCuts = false;
				if ( !makeQA ) return false;
			} else if ( makeQA ) {
				passTrackCut( "mtdDeltaYCharge", allCuts, book, cutsName );
			}
		} else if ( _aTrack->charge() < 0  ){
			if ( !ccol[ "dyMtdNeg" ]->inInclusiveRange( _mtdPidTraits->mDeltaY ) ){
				allCuts = false;
				if ( !makeQA ) return false;
			} else if ( makeQA ) {
				passTrackCut( "mtdDeltaYCharge", allCuts, book, cutsName );
			}
		}
		

		if ( !ccol[ "dzMtd" ]->inInclusiveRange( _mtdPidTraits->mDeltaZ ) ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "mtdDeltaZ", allCuts, book, cutsName );
		}
		if ( !ccol[ "drMtd" ]->inInclusiveRange( deltaR ) ){
			allCuts = false;
			if ( !makeQA ) return false;
		} else if ( makeQA ) {
			passTrackCut( "mtdDeltaR", allCuts, book, cutsName );
		}

		return allCuts;
	}

	static bool isMuon( shared_ptr<IPicoDst> pico, int iTrack, CutCollection &ccol, const shared_ptr<HistoBook>& book = nullptr ){


		bool allCuts = true;

		bool makeQA = true;
		if ( nullptr == book  )
			makeQA = false;
		string cutsName = "MtdMuon";

		double nHitsFit = abs(pico->Tracks_mNHitsFit[ iTrack ]);
		double nHitsMax = pico->Tracks_mNHitsMax[ iTrack ];
		double nHitsDedx = pico->Tracks_mNHitsDedx[ iTrack ];
		double nHitsRatio = nHitsFit / nHitsMax;
		double nSigmaPion = pico->Tracks_mNSigmaPion[iTrack] / 100.0;
		TVector3 momentum = pico->pMomentum( iTrack );//( pico->Tracks_mPMomentum_mX1[iTrack], pico->Tracks_mPMomentum_mX2[iTrack], pico->Tracks_mPMomentum_mX3[iTrack] );
		int iMtd = pico->Tracks_mMtdPidTraitsIndex[iTrack];
		double deltaR = 3000;
		
		if ( iMtd >= 0 )
			deltaR = sqrt( pow(pico->MtdPidTraits_mDeltaY[ iMtd ], 2) + pow(pico->MtdPidTraits_mDeltaZ[ iMtd ], 2) );

		if ( makeQA ){
			book->cd("trackQA");
			passTrackCut( "All", allCuts, book, cutsName );
		}

		if ( momentum.Pt() < ccol[ "pt" ]->min ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "Mom", allCuts, book, cutsName );
		}

		if ( !ccol[ "nSigmaPion" ]->inInclusiveRange( nSigmaPion ) ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "nSigPi", allCuts, book, cutsName );
		}

		if ( nHitsRatio < ccol[ "nHitsRatio" ]->min ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "nHitsRatio", allCuts, book, cutsName );
		}
		if ( nHitsDedx < ccol[ "nHitsDedx" ]->min ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "nHitsDedx", allCuts, book, cutsName );
		}
		if ( nHitsFit < ccol[ "nHitsFit" ]->min ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "nHitsFit", allCuts, book, cutsName );
		}
		if ( !ccol[ "eta" ]->inInclusiveRange( momentum.Eta() )  ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "eta", allCuts, book, cutsName );
		}

		if ( !ccol[ "gDCA" ]->inInclusiveRange( pico->gDCA( iTrack ) ) ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "gDCA", allCuts, book, cutsName );
		}

		if ( !ccol[ "matchFlagMtd" ]->inInclusiveRange( iMtd+1 ) || !ccol[ "matchFlagMtd" ]->inInclusiveRange( pico->MtdPidTraits_mMatchFlag[ iMtd ] ) ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "mtdMatch", allCuts, book, cutsName );
		}

		if ( !ccol[ "dTofMtd" ]->inInclusiveRange( pico->MtdPidTraits_mDeltaTimeOfFlight[ iMtd ] ) ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "dTof", allCuts, book, cutsName );
		}

		if ( !ccol[ "dyMtd" ]->inInclusiveRange( pico->MtdPidTraits_mDeltaY[ iMtd ] ) ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "dy", allCuts, book, cutsName );
		}
		if ( !ccol[ "dzMtd" ]->inInclusiveRange( pico->MtdPidTraits_mDeltaZ[ iMtd ] ) ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "dz", allCuts, book, cutsName );
		}
		if ( !ccol[ "drMtd" ]->inInclusiveRange( deltaR ) ){
			allCuts = false;
		} else if ( makeQA ) {
			passTrackCut( "dr", allCuts, book, cutsName );
		}

		return allCuts;
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

	static bool isTpcTofElectron( shared_ptr<IPicoDst> pico, int iTrack, CutCollection &ccol, const shared_ptr<HistoBook>& book = nullptr ){

		bool allCuts = true;

		bool makeQA = true;
		if ( nullptr == book  )
			makeQA = false;
		string cutsName = "TpcTofElectron";

		double nHitsFit = abs( pico->Tracks_mNHitsFit[ iTrack ] );
		double nHitsMax = pico->Tracks_mNHitsMax[ iTrack ];
		double nHitsDedx = pico->Tracks_mNHitsDedx[ iTrack ];
		double nHitsRatio = nHitsFit / nHitsMax;
		double dEdx = pico->Tracks_mDedx[ iTrack ] / 1000.0;
		TVector3 momentum( pico->Tracks_mPMomentum_mX1[iTrack], pico->Tracks_mPMomentum_mX2[iTrack], pico->Tracks_mPMomentum_mX3[iTrack] );

		if ( makeQA ) { 
			passTrackCut( "all", allCuts, book, cutsName );
		}

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
		
		double gDCA = 0;pico->gDCA( iTrack );
		 
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

	static bool isTpcTofElectron( CandidateTrack *_track, CandidateTrackBTofPidTraits *_pid, CutCollection &ccol, const shared_ptr<HistoBook>& book = nullptr ){

		bool allCuts = true;

		bool makeQA = true;
		if ( nullptr == book  )
			makeQA = false;
		string cutsName = "TpcTofElectron";

		double nHitsFit = abs( _track->mNHitsFit );
		double nHitsMax = _track->mNHitsMax;
		double nHitsDedx = _track->mNHitsDedx;
		double nHitsRatio = nHitsFit / nHitsMax;
		double dEdx = _track->dEdx();
		TVector3 momentum( _track->mPMomentum_mX1, _track->mPMomentum_mX2, _track->mPMomentum_mX3 );

		if ( makeQA ) { 
			passTrackCut( "all", allCuts, book, cutsName );
		}

		if ( !_pid || !ccol[ "matchFlag" ]->inInclusiveRange( _pid->mBTofMatchFlag ) ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "tofMatch", allCuts, book, cutsName );
		}

		double yLocal = -999;
		double zLocal = -999;
		double invBeta = -999;

		if ( _pid ){
			yLocal = _pid->yLocal();
			zLocal = _pid->zLocal();
			invBeta = 1.0 / _pid->beta();		
		}
		
		double gDCA = 0;//pico->gDCA( iTrack );
		 
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
		
		if ( gDCA > ccol[ "gDCA" ]->max ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "gDCA", allCuts, book, cutsName );
		}
		
		if ( !ccol[ "yLocal" ]->inInclusiveRange( yLocal ) ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "yLocal", allCuts, book, cutsName );
		}

		if ( !ccol[ "zLocal" ]->inInclusiveRange( zLocal ) ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "zLocal", allCuts, book, cutsName );
		}

		if ( !ccol[ "invBeta" ]->inInclusiveRange( abs( 1 - invBeta ) ) ){
			allCuts = false;
			if ( false == makeQA ) return false;
		} else if ( makeQA ) { 
			passTrackCut( "beta", allCuts, book, cutsName );
		}

		// INFO( "CandidateFilter", "yLocal == " << yLocal << endl );
		

		// nSigmaElectron Cuts
		// if ( !ccol[ "dEdx" ]->inInclusiveRange( dEdx ) ){
		// 	allCuts = false;
		// 	if ( false == makeQA ) return false;
		// } else if ( makeQA ) { 
		// 	passTrackCut( "dEdx", allCuts, book, cutsName );
		// }




		return allCuts;
	}




	static void passTrackCut( string cut, bool passAllCuts, const shared_ptr<HistoBook>& book, string name = "track" ){
		DEBUG( "CandidateFilter", fmt::format("(cut={0}, passAllCuts={1})", cut, bts(passAllCuts) ) );
		
		book->cd("trackQA");
		book->fill( name + "_single_cuts", cut, 1 );

		if ( passAllCuts ){
			book->fill( name + "_cuts", cut, 1 );
		}
		return;
	}

	static void preTrackCuts( CandidateTrack *_aTrack, CandidateTrackMtdPidTraits * _mtdPidTraits, const shared_ptr<HistoBook>& book ){
		if ( nullptr == book )
			return;
		// book->cd("trackQA");
		// book->fill( "dTofMtd", _mtdPidTraits->mDeltaTimeOfFlight );
		// book->fill( "deltaYMtd", _mtdPidTraits->mDeltaY );
		// book->fill( "deltaZMtd", _mtdPidTraits->mDeltaZ );
	}

};

#endif