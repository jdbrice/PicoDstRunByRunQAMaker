#ifndef TRIGGER_PATCH_QA_H
#define TRIGGER_PATCH_QA_H

#include "CandidateSkimmer.h"
#include "CutCollection.h"

#include "TTreeQA.h"

#include "TriggerPatchMapper.h"

class TriggerPatchQA : public CandidateSkimmer	{
protected:
	TriggerPatchMapper tpm;
	map<int, bool> ftp;


public:
	virtual const char* classname( ) const { return "TriggerPatchQA"; }
	TriggerPatchQA() {}
	~TriggerPatchQA() {}

	string dataset = "";
	virtual void initialize(){
		CandidateSkimmer::initialize();

		dataset = config[ "DataSet" ];

		if ( config.exists( nodePath + ".TrackCuts" ) ){
			trackCuts.init( config, nodePath + ".TrackCuts" );

			// trackCuts.setDefault( "rigidity", -1000, 1000 );

			INFO( classname(), "" );
			INFO( classname(), "############### Track Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		}

		eventCuts.init( config, nodePath + ".EventCuts" );
		eventCuts.setDefault( "zVertex", -100, 100 );
		eventCuts.setDefault( "zVertexDelta", 0, 3 );
		eventCuts.setDefault( "EventPlane_nTracks", 1, 10000000 );

		INFO( classname(), "" );
		INFO( classname(), "############### Event Cuts ###################"  );
		eventCuts.report();
		INFO( classname(), "" );

		/**************************** Track QA *******************************/
		trackQA.setHistoBook( book );
		trackQA.setConfig( config );

		initTrackVariables( trackQA );

		book->cd( "trackQA" );
		trackQA.makeHistograms( "TrackQABins" );

		/**************************** Event QA *******************************/
		eventQA.setHistoBook( book );
		eventQA.setConfig( config );

		initEventVariables( eventQA );

		book->cd( "eventQA" );
		eventQA.makeHistograms( "EventQABins" );


	}


	static void initTrackVariables( TTreeQA &_qaMaker ){
		// 			name 			        title 			 units 		  bins 	axis
		_qaMaker.i( "phi"                 , "#phi"         , "[rad]"                  );
		_qaMaker.i( "phiAtMtd"            , "#phi at MTD"  , "[rad]", "phi"           );
		_qaMaker.i( "eta"                 , "#eta"                                    );
		_qaMaker.i( "rigidity"            , "p_{T}*q"      , "[GeV/c]"    , ""  , "x" );
		_qaMaker.i( "mtdHitChan"          , "MTD Channel"                             );
		_qaMaker.i( "mtdCell"             , "MTD Cell"                                );
		_qaMaker.i( "mtdTriggerPatch"     , "MTD Trigger Patch"                       );
		_qaMaker.i( "mtdBackleg"          , "MTD Back leg"    , ""        ,    "mtdTriggerPatch" );
		_qaMaker.i( "mtdTriggerFlag"      , "MTD Trigger Flag", ""        ,    "mtdTriggerPatch" );
		_qaMaker.i( "mtdModule"           , "MTD Module" );
		_qaMaker.i( "mtdEtaStrip"         , "MTD Eta Strip" );
		
	}

	static void initEventVariables( TTreeQA &_qaMaker ){
		_qaMaker.i( "vertexX", "v_{x}", "[cm]" );
		_qaMaker.i( "vertexY", "v_{y}", "[cm]" );
		_qaMaker.i( "vertexZ", "v_{z}", "[cm]" );

		_qaMaker.i( "weight", "Event Weight" );
		_qaMaker.i( "gRefMult" );
		_qaMaker.i( "bin16", "Centrality Bin" );
		_qaMaker.i( "nTriggerPatch", "Num Trigger Patches" );
		_qaMaker.i( "triggerPatchA", "Trigger Patch A", "", "triggerPatch" );
		_qaMaker.i( "triggerPatchB", "Trigger Patch B", "", "triggerPatch" );
		// _qaMaker.i( "backLegA", "MTD Backleg A",        "", "triggerPatch" );
		// _qaMaker.i( "backLegB", "MTD Backleg B",        "", "triggerPatch" );
		_qaMaker.i( "nTracks", "nTracks", "", "bin16" );
	}


	virtual bool keepEvent(){
		
		if ( !eventCuts["zVertex"]->inInclusiveRange( event->mPrimaryVertex_mX3 ) )
			return false;

		return true;
	}

	virtual bool keepTrack(CandidateTrack* _track, CandidateTrackMtdPidTraits* _mtdPid){
		if ( !trackCuts["rigidity"]->inInclusiveRange( _track->pMomentum().Pt() * _track->charge() ) )
			return false;
		return true;
	}

	virtual void analyzeEvent(){

		book->cd( "trackQA" );
		int nPos = 0, nNeg = 0;
		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );

			if ( !keepTrack( aTrack, mtdPid ) ) continue;

			fillCandidateTrackQA( trackQA, aTrack, mtdPid );

		} // iTrack loop

		book->cd( "eventQA" );
		fillCandidateEventQA( eventQA, event );
		

		// book->fill( "mup_vs_mum", nNeg, nPos );
	}



	void fillCandidateTrackQA( TTreeQA &_qaMaker, CandidateTrack* _track, CandidateTrackMtdPidTraits* _mtdPid, string _cat = "" ){

		TVector3 mom = _track->pMomentum();

		TriggerPatchMapper tpm;
		float rdg        = mom.Pt() * _track->charge();
		float dEdx       = _track->mDedx/1000.0;
		float nSigmaPion = _track->mNSigmaPion / 100.0;
		int tp           = tpm.triggerPatch( _mtdPid->mMtdHitChan );

		double R = mom.Pt() / ( 0.3 * 0.5 );
		double phiAtMtd = mom.Phi() + TMath::ASin( 1.5 / ( 2 * R ) ) * _track->charge();


		_qaMaker.s( "phi"         , mom.Phi() );
		_qaMaker.s( "phiAtMtd"    , phiAtMtd );
		_qaMaker.s( "eta"         , mom.Eta() );
		_qaMaker.s( "rigidity"    , rdg );
		_qaMaker.s( "mtdHitChan"  , _mtdPid->mMtdHitChan );
		_qaMaker.s( "mtdCell"     , _mtdPid->cell() );
		_qaMaker.s( "mtdTriggerPatch", tp );
		_qaMaker.s( "mtdTriggerFlag", _mtdPid->mTriggerFlag );
		_qaMaker.s( "mtdBackleg", TriggerPatchMapper::backleg( _mtdPid->mMtdHitChan ) );
		_qaMaker.s( "mtdModule", TriggerPatchMapper::module( _mtdPid->mMtdHitChan ) + TriggerPatchMapper::backleg( _mtdPid->mMtdHitChan ) * 5 );
		_qaMaker.s( "mtdEtaStrip", TriggerPatchMapper::etaStrip( _mtdPid->mMtdHitChan ) );

		if ( _mtdPid->mTriggerFlag >= 1 )
			ftp[ tp ] = true;


		_qaMaker.fill( _cat );
	}

	void fillCandidateEventQA( TTreeQA &_qaMaker, CandidateEvent* _event ){

		int nTriggerPatch = 0;
		int tpA = -1;
		int tpB = -1; 
		for ( auto kv : ftp ){
			nTriggerPatch++;
			if ( -1 == tpA ) tpA = kv.first;
			else if ( -1 == tpB ) tpB = kv.first;
		}
		if ( nTriggerPatch != 2 ){
			tpA = -1;
			tpB = -1;
		}

		ftp.clear();
		_qaMaker.s( "vertexX"  , _event->mPrimaryVertex_mX1 );
		_qaMaker.s( "vertexY"  , _event->mPrimaryVertex_mX2 );
		_qaMaker.s( "vertexZ"  , _event->mPrimaryVertex_mX3 );

		_qaMaker.s( "weight"   , _event->mWeight            );
		_qaMaker.s( "gRefMult" , _event->mGRefMult          );
		_qaMaker.s( "bin16"    , (int)_event->mBin16        );
		_qaMaker.s( "nTriggerPatch", nTriggerPatch );
		_qaMaker.s( "triggerPatchA", tpA );
		_qaMaker.s( "triggerPatchB", tpB );
		_qaMaker.s( "nTracks", tracks->GetEntries() );

		_qaMaker.fill();
	}


protected:
	CutCollection trackCuts;
	CutCollection eventCuts;

	TTreeQA trackQA;
	TTreeQA eventQA;
	
};


#endif