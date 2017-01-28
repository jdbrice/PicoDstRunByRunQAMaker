#ifndef SAME_EVENT_PAIR_MAKER_H
#define SAME_EVENT_PAIR_MAKER_H

//RooBarb
#include "TreeAnalyzer.h"
#include "CutCollection.h"

//ROOT
#include "TLorentzVector.h"

// Project
#include "CandidateSkimmer.h"
#include "CandidateFilter.h"
#include "EventHasher.h"
#include "RunMapFactory.h"
#include "ISameEventPairTreeMaker.h"
#include "PairFilter.h"
#include "CutCollectionTreeMaker.h"
#include "TriggerPatchMapper.h"

#include <stdint.h>


#include "PidLR.h"


class SameEventPairMaker : public CandidateSkimmer
{
public:
	virtual const char * classname() const { return "SameEventPairMaker"; }
	SameEventPairMaker(){}
	~SameEventPairMaker(){}


	int nTriggerPatch;

	virtual void initialize(){
		CandidateSkimmer::initialize();

		m1 = config.getDouble( nodePath + ".Particles:mass1", 0.0511 );
		m2 = config.getDouble( nodePath + ".Particles:mass2", 0.0511 );

		INFO( classname(), "mass1 = " << m1 );
		INFO( classname(), "mass2 = " << m2 );

		CandidateFilter::setDefaultMuonCuts( trackCuts );
		if ( config.exists( nodePath + ".MuonCandidateCuts" ) ){
			trackCuts.init( config, nodePath + ".MuonCandidateCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Muon Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		} else {
			WARN( classname(), "No Muon Cuts Found, using defaults" );
			INFO( classname(), "" );
			INFO( classname(), "############### Muon Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		}

		PairFilter::setDefaultPairCuts( pairCuts );
		if ( config.exists( nodePath + ".SameEventPairCuts" ) ){
			pairCuts.init( config, nodePath + ".SameEventPairCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Pair Cuts ###################"  );
			pairCuts.report();
			INFO( classname(), "" );
		} else {
			WARN( classname(), "No Pair Cuts Found, using defaults" );
			INFO( classname(), "" );
			INFO( classname(), "############### Pair Cuts ###################"  );
			pairCuts.report();
			INFO( classname(), "" );
		}

		eventHash = config.getInt( nodePath + ".EventHash", -1 );
		eht.load( config, nodePath + ".MixedEventBins" );

		INFO( classname(), "EventHash = " << eventHash );

		rmf = shared_ptr<RunMapFactory>( new RunMapFactory( "Run15PP200", false ) );
		INFO( classname(), "BAD == " << rmf->isRunBad( 16055005 ) );

		book->cd("PDFs");
		// createSameEventPairTree( "Same Event Muon Pairs" );
		vector<string> lrfs = config.childrenOf( nodePath + ".LikelihoodPid", "XmlFunction" );
		INFOC( "Found " << lrfs.size() << plural( lrfs.size(), " PDF", " PDFs" ) );
		for ( string p : lrfs ){
			pidLR.addPDF( config, p );
		}

		tofPid = config.getBool( nodePath + ".MuonCandidateCuts:tofPid", false );
		string pfSigmaDeltaZ = config.q( nodePath + ".MtdParams.XmlFunction{name==SigmaMtdDeltaZ}" );
		string pfSigmaDeltaY = config.q( nodePath + ".MtdParams.XmlFunction{name==SigmaMtdDeltaY}" );
		string pfSigmaDeltaTOF = config.q( nodePath + ".MtdParams.XmlFunction{name==SigmaMtdDeltaTOF}" );
		if ( config.exists( pfSigmaDeltaZ ) ){
			INFOC( "=================== SIGMA DELTA Z ENABLED ========================" );
			fSigmaDeltaZ.set( config, pfSigmaDeltaZ );
		}
		if ( config.exists( pfSigmaDeltaY ) ){
			INFOC( "=================== SIGMA DELTA Y ENABLED ========================" );
			fSigmaDeltaY.set( config, pfSigmaDeltaY );
		}
		if ( config.exists( pfSigmaDeltaTOF ) ){
			INFOC( "=================== SIGMA DELTA TOF ENABLED ========================" );
			fSigmaDeltaTOF.set( config, pfSigmaDeltaTOF );
		}


		book->cd();

	}


protected:

	double m1, m2;
	CutCollection trackCuts;
	CutCollection pairCuts;
	EventHasher eht;
	int eventHash = -1;
	int currentEventHash = -1;
	shared_ptr<RunMapFactory> rmf;
	TriggerPatchMapper tpm;
	int nFTP = 0;
	uint32_t mtdTriggerMask = 0;

	PidLR pidLR;

	bool tofPid = false;
	XmlFunction fSigmaDeltaZ, fSigmaDeltaY, fSigmaDeltaTOF;

	bool keepTrack( CandidateTrack *aTrack ){
		DEBUG( classname(), "("<< aTrack << ")" );
		
		if ( aTrack->mMtdPidTraitsIndex < 0) return false;


		bool goodTrack = CandidateFilter::isGoodTrack( aTrack, trackCuts, makeTrackCutQA ? book : nullptr, "MtdMuon" );

		if (false == goodTrack) return false;

		TF1 * f1SigmaDeltaZ   = fSigmaDeltaZ.getTF1().get();
		TF1 * f1SigmaDeltaY   = fSigmaDeltaY.getTF1().get();
		TF1 * f1SigmaDeltaTOF = fSigmaDeltaTOF.getTF1().get();
		CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
		bool mtdMuon = CandidateFilter::isMtdMuon(  aTrack, 
													mtdPid, 
													trackCuts, 
													makeTrackCutQA ? book : nullptr,
													"",
													f1SigmaDeltaZ,
													f1SigmaDeltaY,
													f1SigmaDeltaTOF );

		if ( false == mtdMuon ) return false;


		if ( tofPid && aTrack->mBTofPidTraitsIndex >= 0 ){
			CandidateTrackBTofPidTraits *btofPid = (CandidateTrackBTofPidTraits *)btofPidTraits->At( aTrack->mBTofPidTraitsIndex );
			bool tofMuon = CandidateFilter::isTofMuon(  aTrack,
														btofPid,
														trackCuts,
														makeTrackCutQA ? book : nullptr );

			if ( false == tofMuon ) return false;
		}	// TOF PID

		return true;
	}

	virtual bool keepEvent(){
		bool passAll = CandidateSkimmer::keepEvent();

		// if ( rmf->isRunBad( event->mRunId ) ){
		// 	ERROR( classname(), "Should not be bad runs here!" );
		// 	passAll = false;
		// }
		nTriggerPatch = 0;
		map<int, bool> tps;
		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			CandidateTrackMtdPidTraits * d1MtdPid = (CandidateTrackMtdPidTraits*)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
			int tp = TriggerPatchMapper::findTriggerPatch( d1MtdPid->mMtdHitChan );
			if ( 0 == tps.count( tp ) ) nTriggerPatch++;
			tps[ tp ] = true;
		}

		// if ( nTriggerPatch != 2 ) return false;

		return passAll;

	}

	virtual void analyzeEvent(){
		// INFO( classname(), "" );
		if ( event->mBin16 < 0 || event->mBin16 > 50 )
			return;

		// wEventHash comes from ISameEventPairTreeMaker
		currentEventHash = eht.hash( event );
		// wBin16     = event->mBin16;

		// TRACE( classname(), "current Event = " << currentEventHash );
		if ( 0 <= eventHash && eventHash != currentEventHash ) return;

		// set the # of fired Trigger Patches to 0
		nFTP = 0;
		mtdTriggerMask = 0;

		
		

		// Pre loop hook
		prePairLoop();

		int nTracks = tracks->GetEntries();
		int nPairs = 0;
		int pre_nPos = 0;
		int nPos = 0;
		int pre_nNeg = 0;
		int nNeg = 0;
		int nLS = 0;
		int nLSPos = 0, nLSNeg=0;
		int nULS = 0;

		
		book->cd( "pairQA" );
		if ( book->exists( "pre_nPairs" ) )
			book->get( "pre_nPairs", "pairQA" )->Fill( nTracks * ( nTracks - 1 ) / 2.0 );

		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			if ( -1 == aTrack->charge() ) pre_nNeg ++;
			if ( 1 == aTrack->charge() ) pre_nPos ++;
			if ( !keepTrack( aTrack ) ) continue;
			if ( -1 == aTrack->charge() ) nNeg ++;
			if ( 1 == aTrack->charge() ) nPos ++;

			DEBUG( classname(), "Inner track loop" );
			for ( int jTrack = iTrack; jTrack < nTracks; jTrack++ ){
				if ( iTrack == jTrack ) continue;
				CandidateTrack* bTrack = (CandidateTrack*)tracks->At( jTrack );
				if ( !keepTrack( bTrack ) ) continue;

				TLorentzVector lv1, lv2, lv;
				lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
				lv2.SetXYZM( bTrack->mPMomentum_mX1, bTrack->mPMomentum_mX2, bTrack->mPMomentum_mX3, m2 );

				lv = lv1 + lv2;

				if ( aTrack->charge() == bTrack->charge() ) {
					nLS++;
					if ( aTrack->charge() == 1 ) nLSPos++;
					if ( aTrack->charge() == -1 ) nLSNeg++;
				}
				if ( aTrack->charge() != bTrack->charge() ) nULS++;


				CandidateTrackMtdPidTraits * d1MtdPid = (CandidateTrackMtdPidTraits*)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
				CandidateTrackMtdPidTraits * d2MtdPid = (CandidateTrackMtdPidTraits*)mtdPidTraits->At( bTrack->mMtdPidTraitsIndex );
				int tpA = TriggerPatchMapper::findTriggerPatch( d1MtdPid->mMtdHitChan );
				int tpB = TriggerPatchMapper::findTriggerPatch( d2MtdPid->mMtdHitChan );

				analyzePair( aTrack, bTrack );
				
				nPairs++;

			}
		}

		book->get( "nPairs", "pairQA" )->Fill( nPairs );
		book->get( "nCharge", "pairQA" )->Fill( nPos, nNeg );
		
		if ( nPos > 1 || nNeg > 1 || (nPos == 1 && nNeg == 1) )
			book->get( "nCharge_gt1", "pairQA" )->Fill( nPos, nNeg );
		book->get( "pre_nCharge", "pairQA" )->Fill( pre_nPos, pre_nNeg );
		if ( nPos > 1 || nNeg > 1 || (nPos == 1 && nNeg == 1) )
			book->get( "pre_nCharge_gt1", "pairQA" )->Fill( pre_nPos, pre_nNeg );

		book->get( "nLS", "pairQA" )->Fill( nLS );
		book->get( "nLSPos", "pairQA" )->Fill( nLSPos );
		book->get( "nLSNeg", "pairQA" )->Fill( nLSNeg );
		book->get( "nULS", "pairQA" )->Fill( nULS );

		// post loop hook
		postPairLoop( nPairs );
		// if ( nPairs > 0 ){
		// 	book->get( "nPairs", "pairQA" )->Fill( nPairs );
		// 	mSameEventTree->Fill();
		// }
	} // analyzeEvent


	// virtual void preMake(){

	// 	book->cd();
	// 	CutCollectionTreeMaker::makeCutTree( trackCuts, "trackCuts" );
	// 	CutCollectionTreeMaker::makeCutTree( pairCuts, "pairCuts" );

	// }

	// virtual void postMake(){
	// 	CandidateSkimmer::postMake();
	// }

	virtual void analyzePair( CandidateTrack * _aTrack, CandidateTrack * _bTrack ){
		
	}

	virtual void postPairLoop( int _nPairs ){
		DEBUG( classname(), "" );
		if ( book->exists( "nPairs" ) )
			book->get( "nPairs", "pairQA" )->Fill( _nPairs );
	}

	virtual void prePairLoop(){
		DEBUG( classname(), "" );
	}

	virtual void overrideConfig(){

		if (config.getInt( "jobIndex" ) == -1 ){
			string nfn = config.getString( nodePath + ".output.TFile:url" );
			XmlString xstr;
			xstr.add( "jobIndex", "all" );
			nfn = xstr.format( nfn );
			config.set( nodePath + ".output.TFile:url", nfn );
		}
	}


	// virtual void fillCandidatePair( CandidateTrack * aTrack, CandidateTrack * bTrack ){

	// 	CandidatePair * aPair = new ((*wPairs)[nCandPairs]) CandidatePair( );
		
	// 	TLorentzVector lv1, lv2, lv;
	// 	lv1.SetXYZM( aTrack->mPMomentum_mX1, aTrack->mPMomentum_mX2, aTrack->mPMomentum_mX3, m1 );
	// 	lv2.SetXYZM( bTrack->mPMomentum_mX1, bTrack->mPMomentum_mX2, bTrack->mPMomentum_mX3, m2 );

	// 	lv = lv1 + lv2;

	// 	aPair->set( lv.Px(), lv.Py(), lv.Pz(), lv.M(), aTrack->charge() + bTrack->charge() );
	// 	nCandPairs++;
	// }

	
};

#endif