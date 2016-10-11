#ifndef MUON_CANDIDATE_QA_H
#define MUON_CANDIDATE_QA_H

#include "CandidateSkimmer.h"
#include "CutCollection.h"

#include "TTreeQA.h"

class MuonCandidateQA : public CandidateSkimmer	{
public:
	virtual const char* classname( ) const { return "MuonCandidateQA"; }
	MuonCandidateQA() {}
	~MuonCandidateQA() {}

	virtual void initialize(){
		CandidateSkimmer::initialize();

		

		if ( config.exists( nodePath + ".TrackCuts" ) ){
			trackCuts.init( config, nodePath + ".TrackCuts" );

			// trackCuts.setDefault( "rigidity", -1000, 1000 );

			INFO( classname(), "" );
			INFO( classname(), "############### Track Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		}

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
		_qaMaker.initVariable( "phi"         , "#phi"         , "[rad]"                  );
		_qaMaker.initVariable( "eta"         , "#eta"                                    );
		_qaMaker.initVariable( "rigidity"    , "p_{T}*q"      , "[GeV/c]"    , ""  , "x" );
		_qaMaker.initVariable( "mtdHitChan"  , "MTD Channel"                             );
		_qaMaker.initVariable( "mtdDeltaY"   , "MTD #DeltaY"  , "[cm]"                   );
		_qaMaker.initVariable( "mtdDeltaZ"   , "MTD #DeltaZ"  , "[cm]"                   );
		_qaMaker.initVariable( "nSigmaPion"  , "n#sigma_{#pi}"                           );
		_qaMaker.initVariable( "mtdDeltaTOF" , "#DeltaTOF"    , "[ns]"                   );
		_qaMaker.initVariable( "pMomentum"   , "P"            , "[GeV/c]"    , "P"       );
		_qaMaker.initVariable( "pMomentumX"  , "P_{x}"        , "[GeV/c]"    , "P"       );
		_qaMaker.initVariable( "pMomentumY"  , "P_{y}"        , "[GeV/c]"    , "P"       );
		_qaMaker.initVariable( "pMomentumZ"  , "P_{z}"        , "[GeV/c]"    , "P"       );

		_qaMaker.initVariable( "nHitsFit"    , "nHitsFit"     , ""           , "nHits"   );
		_qaMaker.initVariable( "nHitsDedx"   , "nHitsDedx"    , ""           , "nHits"   );
		_qaMaker.initVariable( "nHitsMax"    , "nHitsMax"     , ""           , "nHits"   );
	}

	static void initEventVariables( TTreeQA &_qaMaker ){
		_qaMaker.i( "vertexX", "v_{x}", "[cm]" );
		_qaMaker.i( "vertexY", "v_{y}", "[cm]" );
		_qaMaker.i( "vertexZ", "v_{z}", "[cm]" );

		_qaMaker.i( "weight", "Event Weight" );
		_qaMaker.i( "gRefMult" );
		_qaMaker.i( "bin16", "Centrality Bin" );
	}


	virtual bool keepEvent(){
		return true;
	}

	virtual void analyzeEvent(){


		book->cd( "eventQA" );
		fillCandidateEventQA( eventQA, event );
		book->cd( "trackQA" );

		int nPos = 0, nNeg = 0;
		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
			
			TVector3 mom = aTrack->pMomentum();
			float rdg        = mom.Pt() * aTrack->charge();

			if ( false == trackCuts[ "rigidity" ]->inInclusiveRange( rdg ) ) continue;

			fillCandidateTrackQA( trackQA, aTrack, mtdPid );
			

			if ( aTrack->charge() > 0 )
				nPos++;
			if ( aTrack->charge() < 0 )
				nNeg++;

		} // iTrack loop

		// book->fill( "mup_vs_mum", nNeg, nPos );
	}



	static void fillCandidateTrackQA( TTreeQA &_qaMaker, CandidateTrack* _track, CandidateTrackMtdPidTraits* _mtdPid ){

		TVector3 mom = _track->pMomentum();

		float rdg        = mom.Pt() * _track->charge();
		float dEdx       = _track->mDedx/1000.0;
		float nSigmaPion = _track->mNSigmaPion / 100.0;

		_qaMaker.setVariable( "phi"         , mom.Phi() );
		_qaMaker.setVariable( "eta"         , mom.Eta() );
		_qaMaker.setVariable( "rigidity"    , rdg );
		_qaMaker.setVariable( "mtdHitChan"  , _mtdPid->mMtdHitChan );
		_qaMaker.setVariable( "mtdDeltaY"   , _mtdPid->mDeltaY );
		_qaMaker.setVariable( "mtdDeltaZ"   , _mtdPid->mDeltaZ );
		_qaMaker.setVariable( "mtdDeltaTOF" , _mtdPid->mDeltaTimeOfFlight );
		_qaMaker.setVariable( "nSigmaPion"  , nSigmaPion );

		_qaMaker.setVariable( "pMomentum"   , mom.Mag() * _track->charge() );
		_qaMaker.setVariable( "pMomentumX"  , mom.Px() );
		_qaMaker.setVariable( "pMomentumY"  , mom.Py() );
		_qaMaker.setVariable( "pMomentumZ"  , mom.Pz() );

		_qaMaker.setVariable( "nHitsFit"    , (int)_track->mNHitsFit );
		_qaMaker.setVariable( "nHitsDedx"   , (int)_track->mNHitsDedx * _track->charge() );
		_qaMaker.setVariable( "nHitsMax"    , (int)_track->mNHitsMax * _track->charge() );


		_qaMaker.fill();
	}

	static void fillCandidateEventQA( TTreeQA &_qaMaker, CandidateEvent* _event ){
		_qaMaker.s( "vertexX"  , _event->mPrimaryVertex_mX1 );
		_qaMaker.s( "vertexY"  , _event->mPrimaryVertex_mX2 );
		_qaMaker.s( "vertexZ"  , _event->mPrimaryVertex_mX3 );

		_qaMaker.s( "weight"   , _event->mWeight            );
		_qaMaker.s( "gRefMult" , _event->mGRefMult          );
		_qaMaker.s( "bin16"    , (int)_event->mBin16        );

		_qaMaker.fill();
	}


protected:
	CutCollection trackCuts;

	TTreeQA trackQA;
	TTreeQA eventQA;
	
};


#endif