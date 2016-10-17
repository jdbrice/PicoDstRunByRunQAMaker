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
		// 			name 			title 			 units 		  bins 	axis
		_qaMaker.i( "phi"         , "#phi"         , "[rad]"                  );
		_qaMaker.i( "eta"         , "#eta"                                    );
		_qaMaker.i( "rigidity"    , "p_{T}*q"      , "[GeV/c]"    , ""  , "x" );
		_qaMaker.i( "mtdHitChan"  , "MTD Channel"                             );
		_qaMaker.i( "mtdCell"     , "MTD Cell"                                );
		_qaMaker.i( "mtdDeltaY"   , "MTD #DeltaY"  , "[cm]"                   );
		_qaMaker.i( "mtdDeltaZ"   , "MTD #DeltaZ"  , "[cm]"                   );
		_qaMaker.i( "nSigmaPion"  , "n#sigma_{#pi}"                           );
		_qaMaker.i( "mtdDeltaTOF" , "#DeltaTOF"    , "[ns]"                   );
		_qaMaker.i( "pMomentum"   , "P"            , "[GeV/c]"    , "P"       );
		_qaMaker.i( "pMomentumX"  , "P_{x}"        , "[GeV/c]"    , "P"       );
		_qaMaker.i( "pMomentumY"  , "P_{y}"        , "[GeV/c]"    , "P"       );
		_qaMaker.i( "pMomentumZ"  , "P_{z}"        , "[GeV/c]"    , "P"       );

		_qaMaker.i( "nHitsFit"    , "nHitsFit"     , ""           , "nHits"   );
		_qaMaker.i( "nHitsDedx"   , "nHitsDedx"    , ""           , "nHits"   );
		_qaMaker.i( "nHitsMax"    , "nHitsMax"     , ""           , "nHits"   );

		_qaMaker.i( "runIndex", "", "", "", "x" );
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
			// if ( false == trackCuts[ "mtdCell" ]->inInclusiveRange( mtdPid->mMtdHitChan % 12 ) ) continue;

			if ( dataset == "Run15PP" ){
				// INFO( classname(), "Run Index = " << event->mRunIndex );
				trackQA.s( "runIndex", event->mRunIndex );
			}

			fillCandidateTrackQA( trackQA, aTrack, mtdPid );
			

			if ( aTrack->charge() > 0 )
				nPos++;
			if ( aTrack->charge() < 0 )
				nNeg++;

		} // iTrack loop

		// book->fill( "mup_vs_mum", nNeg, nPos );
	}



	static void fillCandidateTrackQA( TTreeQA &_qaMaker, CandidateTrack* _track, CandidateTrackMtdPidTraits* _mtdPid, string _cat = "" ){

		TVector3 mom = _track->pMomentum();

		float rdg        = mom.Pt() * _track->charge();
		float dEdx       = _track->mDedx/1000.0;
		float nSigmaPion = _track->mNSigmaPion / 100.0;

		_qaMaker.s( "phi"         , mom.Phi() );
		_qaMaker.s( "eta"         , mom.Eta() );
		_qaMaker.s( "rigidity"    , rdg );
		_qaMaker.s( "mtdHitChan"  , _mtdPid->mMtdHitChan );
		_qaMaker.s( "mtdCell"     , _mtdPid->mMtdHitChan % 12 );
		_qaMaker.s( "mtdDeltaY"   , _mtdPid->mDeltaY );
		_qaMaker.s( "mtdDeltaZ"   , _mtdPid->mDeltaZ );
		_qaMaker.s( "mtdDeltaTOF" , _mtdPid->mDeltaTimeOfFlight );
		_qaMaker.s( "nSigmaPion"  , nSigmaPion );

		_qaMaker.s( "pMomentum"   , mom.Mag() * _track->charge() );
		_qaMaker.s( "pMomentumX"  , mom.Px() );
		_qaMaker.s( "pMomentumY"  , mom.Py() );
		_qaMaker.s( "pMomentumZ"  , mom.Pz() );

		_qaMaker.s( "nHitsFit"    , (int)_track->mNHitsFit );
		_qaMaker.s( "nHitsDedx"   , (int)_track->mNHitsDedx * _track->charge() );
		_qaMaker.s( "nHitsMax"    , (int)_track->mNHitsMax * _track->charge() );


		_qaMaker.fill( _cat );
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