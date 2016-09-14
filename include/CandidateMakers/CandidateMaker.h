#ifndef CANDIDATE_MAKER_H
#define CANDIDATE_MAKER_H

//Project
#include "PicoDstSkimmer.h"

#include "CandidateTreeMaker.h"
#include "EventHasher.h"
#include "RunMapFactory.h"

#include "StRefMultCorr.h"
#include "CentralityMaker.h"


//ROOT
#include "TClonesArray.h"
#include "TVector3.h"
#include "TMath.h"

class CandidateMaker : public PicoDstSkimmer
{
public:
	virtual const char *classname() const { return "CandidateMaker"; }
	CandidateMaker() {}
	~CandidateMaker() {}

	virtual void initialize(){
		INFO( classname(), "" );
		PicoDstSkimmer::initialize();

		book->cd();
		createTree();

		if ( config.getBool( nodePath + ":rmc", true ) ){
			INFO( classname(), "Setting up RMC" );
			rmc = CentralityMaker::instance()->getgRefMultCorr();
		} else {
			INFO( classname(), "NOT setting up RMC" );
		}


		if ( config.exists( nodePath + ".MixedEventBins" ) ){
			INFO( classname(), "Creating Event Hash" );
			eht.load( config, nodePath + ".MixedEventBins" );
			eventHash = config.getInt( nodePath + ".EventHash", -1 );
		} else {
			WARN( classname(), "Could not find MixedEventBins" );
			eventHash = -1;
		}

		if ( "PicoDstRun15PP200" == picoDstAdapter ){
			calcEventPlane = false;
			rmf = shared_ptr<RunMapFactory>( new RunMapFactory( "Run15PP200", false ) );
		}
		else {
			WARN( classname(), "NO BAD RUN REJECTION FOR AUAU YET" );
			rmf = shared_ptr<RunMapFactory>( new RunMapFactory( ) );
		}


		useRefMultCorr = config.getBool( nodePath + ":rmc", true );

	}


protected:
	StRefMultCorr * rmc = nullptr;
	EventHasher eht;
	int eventHash;
	shared_ptr<RunMapFactory> rmf;
	bool useRefMultCorr = false;
	bool calcEventPlane = true;


	virtual void overrideConfig(){
		INFO( classname(), "" );
		int _jobIndex = config.getInt( "jobIndex", -1 );
		INFO( classname(), "jobIndex = " << _jobIndex );

		if ( -1 < jobIndex && config.exists( nodePath + ".MixedEventBins" ) && config.getBool( nodePath + ".EventHash:split" ) ){
			EventHasher evtHasher;
			evtHasher.load( config, nodePath + ".MixedEventBins" );
			
			INFO( classname(), "max Hash = " << evtHasher.maxPossibleHash() );
			int maxHash = evtHasher.maxPossibleHash();
			map<string, string> overrides;
			int newJobIndex = _jobIndex / maxHash;
			int newEventHash = _jobIndex % maxHash;
			
			overrides[ "jobIndex" ] = ts( newJobIndex );
			overrides[ nodePath + ".EventHash" ] = ts( newEventHash );
			INFO( classname(), "JobIndex = " << newJobIndex << ", EventHash = " << newEventHash );
			config.applyOverrides( overrides );
		} else {
			INFO( classname(), "Not splitting by EventHash" );
			map<string, string> overrides;
			overrides[ "jobIndex" ] = ts( _jobIndex );
			overrides[ nodePath + ".EventHash" ] = ts( -1 );
			INFO( classname(), "JobIndex = " << _jobIndex << ", EventHash = " << -1 );
			config.applyOverrides( overrides );
		}
	}

	virtual bool keepEvent(){

		bool skeep = PicoDstSkimmer::keepEvent();
		if ( false == skeep )
			return false;
		
		/*********** Initialize the RefMultCorr *************/
		if ( useRefMultCorr ){
			rmc->init( pico->Event_mRunId[0] );
			rmc->initEvent( 
				pico->Event_mGRefMult[0], 
				pico->Event_mPrimaryVertex_mX3[0], 
				pico->Event_mZDCx[0]
			);
		}

		fillCandidateEvent();

		/*********** Initialize the RefMultCorr *************/
		if ( rmf->isRunBad( wEvent->mRunId ) ){
			INFO( classname(), wEvent->mRunId << " is BAD" );
			return false;
		}

		if ( eventHash > -1 ){
			int evtHash = eht.hash( wEvent );
			DEBUG( classname(), "Event Hash = " << evtHash );
			if ( eventHash != evtHash ){
				return false;
			}
		} else {
			DEBUG( classname(), "Event" )
		}

		return true;
	}

	virtual void analyzeEvent(){

		fillCandidateEventPlane();

		// for instance, use to keep only events with pairs of muons
		// default to keep all accepted events
		keepCandidateEvent = true;
		// and default the track level
		isMuon = false;
		isElectron = false;
	}

	virtual void fillCandidateEvent() {
		wEvent->mRunId 				= pico->Event_mRunId[0];
		wEvent->mEventId 			= pico->Event_mEventId[0];
		wEvent->mGRefMult 			= pico->Event_mGRefMult[0];
		wEvent->mTriggerWord 		= pico->Event_mTriggerWord[0];
		wEvent->mTriggerWordMtd 	= pico->Event_mTriggerWordMtd[0];
		wEvent->mPrimaryVertex_mX1 	= pico->vx();
		wEvent->mPrimaryVertex_mX2 	= pico->vy();
		wEvent->mPrimaryVertex_mX3 	= pico->vz();
		wEvent->mRunIndex			= rmf->indexForRun( pico->Event_mRunId[0] );

		if ( rmc ){
			wEvent->mBin16 			= rmc->getCentralityBin16();
			wEvent->mWeight 		= rmc->getWeight();
		} else {
			wEvent->mBin16 			= 0;
			wEvent->mWeight 		= 1.0;
		}

		// TODO: after EventPlane is settled
		if ( calcEventPlane )
			wEvent->mPsi2 		= (calcPsi2() * 10000) ;
		else 
			wEvent->mPsi2 		= 0.0;

		// StRefMultCorr
	}

	virtual float calcPsi2(){

		double nTracks = pico->ntrk();
		TRACE( classname(), "mNtrk = " << nTracks );
		if ( nTracks == 0 ) return -99;

		double qx = pico->qx();
		double qy = pico->qy();

		if (qx == 0) return -99;
		if (qy == 0) return -99;

		qx = qx / nTracks;
		qy = qy / nTracks;

		TRACE( classname(), "Qx = " << qx << ", Qy = " << qy );
		double psi = TMath::ATan2( qy, qx ); // raw
		// recenter
		qx = epc.center_qx( qx );
		qy = epc.center_qy( qy );
		psi = TMath::ATan2( qy, qx );
		// TODO: apply flattening

		return psi;

	}

	virtual void fillCandidateEventPlane(){

		wEventPlane->mQx_eta_pos           = pico->EventPlane_mQx_eta_pos[0];
		wEventPlane->mQy_eta_pos           = pico->EventPlane_mQy_eta_pos[0];
		wEventPlane->mQx_eta_neg           = pico->EventPlane_mQx_eta_neg[0];
		wEventPlane->mQy_eta_neg           = pico->EventPlane_mQy_eta_neg[0];
		wEventPlane->mNtrk_eta_pos         = pico->EventPlane_mNtrk_eta_pos[0];
		wEventPlane->mNtrk_eta_neg         = pico->EventPlane_mNtrk_eta_neg[0];
		wEventPlane->mWeight_eta_pos       = pico->EventPlane_mWeight_eta_pos[0];
		wEventPlane->mWeight_eta_neg       = pico->EventPlane_mWeight_eta_neg[0];
		wEventPlane->mQx_chg_pos           = pico->EventPlane_mQx_chg_pos[0];
		wEventPlane->mQy_chg_pos           = pico->EventPlane_mQy_chg_pos[0];
		wEventPlane->mQx_chg_neg           = pico->EventPlane_mQx_chg_neg[0];
		wEventPlane->mQy_chg_neg           = pico->EventPlane_mQy_chg_neg[0];
		wEventPlane->mNtrk_chg_pos_eta_pos = pico->EventPlane_mNtrk_chg_pos_eta_pos[0];
		wEventPlane->mNtrk_chg_pos_eta_neg = pico->EventPlane_mNtrk_chg_pos_eta_neg[0];
		wEventPlane->mNtrk_chg_neg_eta_pos = pico->EventPlane_mNtrk_chg_neg_eta_pos[0];
		wEventPlane->mNtrk_chg_neg_eta_neg = pico->EventPlane_mNtrk_chg_neg_eta_neg[0];
		wEventPlane->mWeight_chg_pos       = pico->EventPlane_mWeight_chg_pos[0];
		wEventPlane->mWeight_chg_neg       = pico->EventPlane_mWeight_chg_neg[0];
		wEventPlane->mQx_ran_1             = pico->EventPlane_mQx_ran_1[0];
		wEventPlane->mQy_ran_1             = pico->EventPlane_mQy_ran_1[0];
		wEventPlane->mQx_ran_2             = pico->EventPlane_mQx_ran_2[0];
		wEventPlane->mQy_ran_2             = pico->EventPlane_mQy_ran_2[0];
		wEventPlane->mNtrk_ran_1_eta_pos   = pico->EventPlane_mNtrk_ran_1_eta_pos[0];
		wEventPlane->mNtrk_ran_1_eta_neg   = pico->EventPlane_mNtrk_ran_1_eta_neg[0];
		wEventPlane->mNtrk_ran_2_eta_pos   = pico->EventPlane_mNtrk_ran_2_eta_pos[0];
		wEventPlane->mNtrk_ran_2_eta_neg   = pico->EventPlane_mNtrk_ran_2_eta_neg[0];
		wEventPlane->mWeight_ran_1         = pico->EventPlane_mWeight_ran_1[0];
		wEventPlane->mWeight_ran_2         = pico->EventPlane_mWeight_ran_2[0];
	}

	virtual void trackLoop(){
		
		// Reset the Tracks TClonesArrays and counters

		resetTracks();
		
		book->cd("eventQA");
		book->fill( "nTracks", pico->Tracks_ );

		TRACE( classname(), "# of Tracks = " << pico->Tracks_ );
		for ( int iTrack = 0; iTrack < pico->Tracks_; iTrack++ ){

			if ( !keepTrack( iTrack ) ) continue;

			CandidateTrack * aTrack =  new ((*wTracks)[nCandTracks]) CandidateTrack( );
			analyzeCandidateTrack( aTrack, iTrack, nCandTracks );
			nCandTracks ++;
		}
		postTrackLoop();
	}

	virtual void postTrackLoop(){
		if ( keepCandidateEvent ){
			TRACE( classname(), "Filling Tree" );
			mTree->Fill();
		}
	}

	virtual void fillCandidateTrack( CandidateTrack * aTrack, int iTrack ){
		

		aTrack->mId                 = pico->Tracks_mId[iTrack];
		aTrack->mPMomentum_mX1      = pico->Tracks_mPMomentum_mX1[iTrack];
		aTrack->mPMomentum_mX2      = pico->Tracks_mPMomentum_mX2[iTrack];
		aTrack->mPMomentum_mX3      = pico->Tracks_mPMomentum_mX3[iTrack];

		aTrack->mDedx               = pico->Tracks_mDedx[ iTrack ];
		aTrack->mNHitsFit           = pico->Tracks_mNHitsFit[iTrack];
		aTrack->mNHitsMax           = pico->Tracks_mNHitsMax[iTrack];
		aTrack->mNHitsDedx          = pico->Tracks_mNHitsDedx[iTrack];

		aTrack->mNSigmaPion         = pico->Tracks_mNSigmaPion[ iTrack ];
		aTrack->mNSigmaKaon         = pico->Tracks_mNSigmaKaon[ iTrack ];
		aTrack->mNSigmaProton       = pico->Tracks_mNSigmaProton[ iTrack ];
		aTrack->mNSigmaElectron     = pico->Tracks_mNSigmaElectron[ iTrack ];

		aTrack->mDCA                = pico->mGDCA( iTrack );

		// default out the PidTraits
		aTrack->mBTofPidTraitsIndex = -1;
		aTrack->mMtdPidTraitsIndex  = -1;

		fillCandidateBTofPidTraits( aTrack, iTrack );
		fillCandidateMtdPidTraits( aTrack, iTrack );
		

		// aTrack->species = speciesMask();
	}

	virtual void fillCandidateBTofPidTraits( CandidateTrack * aTrack, int iTrack ){
		// BTofPidTraits
		int iBTof = pico->Tracks_mBTofPidTraitsIndex[ iTrack ];
		if ( iBTof >= 0 && isElectron){
			aTrack->mBTofPidTraitsIndex = nBTofPidTraits;

			CandidateTrackBTofPidTraits * btpid = new ((*wBTofPidTraits)[nBTofPidTraits]) CandidateTrackBTofPidTraits( );
			btpid->mBTofBeta 		= pico->BTofPidTraits_mBTofBeta[ iBTof ];
			btpid->mBTofYLocal 		= pico->BTofPidTraits_mBTofYLocal[ iBTof ];
			btpid->mBTofZLocal 		= pico->BTofPidTraits_mBTofZLocal[ iBTof ];
			btpid->mBTofMatchFlag 	= pico->BTofPidTraits_mBTofMatchFlag[ iBTof ];

			nBTofPidTraits++;
		}
		else {
		}
	}

	virtual void fillCandidateMtdPidTraits( CandidateTrack * aTrack, int iTrack ){
		// MtdPidTraits
		int iMtd = pico->Tracks_mMtdPidTraitsIndex[ iTrack ];
		if ( iMtd >= 0 ){
			aTrack->mMtdPidTraitsIndex = nMtdPidTraits;
			CandidateTrackMtdPidTraits * mtdpid = new ((*wMtdPidTraits)[nMtdPidTraits]) CandidateTrackMtdPidTraits( );

			mtdpid->mMatchFlag 			= pico->MtdPidTraits_mMatchFlag[ iMtd ];
			mtdpid->mDeltaY 			= pico->MtdPidTraits_mDeltaY[ iMtd ];
			mtdpid->mDeltaZ 			= pico->MtdPidTraits_mDeltaZ[ iMtd ];
			mtdpid->mDeltaTimeOfFlight 	= pico->MtdPidTraits_mDeltaTimeOfFlight[ iMtd ];
			mtdpid->mMtdHitChan 		= pico->MtdPidTraits_mMtdHitChan[ iMtd ];

			nMtdPidTraits ++;
		} else {

		}
	}


	virtual void analyzeCandidateTrack( CandidateTrack * aTrack, int iTrack, int nCandTracks ){
		fillCandidateTrack( aTrack, iTrack );
	}
	virtual bool keepTrack( int iTrack ){
		return true;
	}


	virtual void postMake() {
		INFO( classname(), "Writing Tree out" );
		book->cd();
		mTree->Write();
	}

	Char_t speciesMask( ){
		Char_t mask = 0;
		if ( isElectron )
			mask |= 1;
		if ( isMuon )
			mask |= 2;
		return mask;
	}
	
};


#endif