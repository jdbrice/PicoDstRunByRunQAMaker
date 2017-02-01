#ifndef MUON_CANDIDATE_QA_H
#define MUON_CANDIDATE_QA_H

#include "CandidateSkimmer.h"
#include "CutCollection.h"

#include "TTreeQA.h"

#include "PidLR.h"

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
			qaCuts.init( config, nodePath + ".TrackCuts" );

			// qaCuts.setDefault( "rigidity", -1000, 1000 );

			INFO( classname(), "" );
			INFO( classname(), "############### Track Cuts ###################"  );
			qaCuts.report();
			INFO( classname(), "" );
		}

		/**************************** Track QA *******************************/
		if ( config.getBool( nodePath + ".Make:track" ,true ) ){
			trackQA.setHistoBook( book );
			trackQA.setConfig( config );

			initTrackVariables( trackQA );

			book->cd( "trackQA" );
			trackQA.makeHistograms( "TrackQABins" );
		}

		/**************************** Event QA *******************************/
		if ( config.getBool( nodePath + ".Make:event" ,true ) ){
			eventQA.setHistoBook( book );
			eventQA.setConfig( config );

			initEventVariables( eventQA );

			book->cd( "eventQA" );
			eventQA.makeHistograms( "EventQABins" );
		}



		book->cd("PDFs");
		// createSameEventPairTree( "Same Event Muon Pairs" );
		vector<string> lrfs = config.childrenOf( nodePath + ".LikelihoodPid", "XmlFunction" );
		INFOC( "Found " << lrfs.size() << plural( lrfs.size(), " PDF", " PDFs" ) );
		for ( string p : lrfs ){
			pidLR.addPDF( config, p );
		}

		minLR = config.getDouble( nodePath + ".LikelihoodPid:min", -2 );
		maxLR = config.getDouble( nodePath + ".LikelihoodPid:max", 2 );


		// ====================== TRACK CUTS =========================
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
		// ====================== TRACK CUTS =========================


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
		_qaMaker.i( "dca"         , "gDCA"         , "[cm]" );

		_qaMaker.i( "nHitsFit"    , "nHitsFit"     , ""           , "nHits"   );
		_qaMaker.i( "nHitsDedx"   , "nHitsDedx"    , ""           , "nHits"   );
		_qaMaker.i( "nHitsMax"    , "nHitsMax"     , ""           , "nHits"   );
		_qaMaker.i( "nHitsRatio"  , "nHitsRatio" );

		_qaMaker.i( "runIndex", "", "", "", "x" );
	}

	static void initEventVariables( TTreeQA &_qaMaker ){
		// _qaMaker.i( "vertexX", "v_{x}", "[cm]" );
		// _qaMaker.i( "vertexY", "v_{y}", "[cm]" );
		// _qaMaker.i( "vertexZ", "v_{z}", "[cm]" );

		// _qaMaker.i( "weight", "Event Weight" );
		_qaMaker.i( "gRefMult" );
		// _qaMaker.i( "bin16", "Centrality Bin" );

		_qaMaker.i( "nPos", "N_{+}", "", "nMuons" );
		_qaMaker.i( "nNeg", "N_{+}", "", "nMuons" );
		_qaMaker.i( "nPosTracks", "N_{+} Trk", "", "nMuons" );
		_qaMaker.i( "nNegTracks", "N_{+} Trk", "", "nMuons" );
		_qaMaker.i( "nPosMuons", "N_{+} LOOSE", "", "nMuons" );
		_qaMaker.i( "nNegMuons", "N_{+} LOOSE", "", "nMuons" );
		// _qaMaker.i( "runIndex", "", "", "", "x" );
	}


	virtual bool keepEvent(){
		return true;
	}

	virtual bool keepTrack( CandidateTrack *_track ){
		if ( _track->mMtdPidTraitsIndex < 0) return false;
		bool goodTrack = CandidateFilter::isGoodTrack( _track, trackCuts, nullptr, "MtdMuon" );
		if (false == goodTrack) return false;
		return true;
	}

	virtual bool keepMtdTrack( CandidateTrack *_track ){
		CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( _track->mMtdPidTraitsIndex );
		bool mtdMuon = CandidateFilter::isMtdMuon(  _track, mtdPid, trackCuts );
		if ( false == mtdMuon ) return false;
		return true;
	}


	virtual void analyzeEvent(){


		
		



		int nPos = 0, nNeg = 0;
		int nPosTracks = 0, nNegTracks = 0;
		int nPosMuons = 0, nNegMuons = 0;
		int nPosMuonsPass = 0, nNegMuonsPass = 0;
		int nTracks = tracks->GetEntries();
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
			CandidateTrack* aTrack = (CandidateTrack*)tracks->At( iTrack );
			CandidateTrackMtdPidTraits *mtdPid = (CandidateTrackMtdPidTraits *)mtdPidTraits->At( aTrack->mMtdPidTraitsIndex );
			


			if ( aTrack->charge() > 0 )
				nPos++;
			if ( aTrack->charge() < 0 )
				nNeg++;


			if ( false == keepTrack( aTrack ) ) continue;
			if ( false == keepMtdTrack( aTrack ) ) continue;

			if ( aTrack->charge() > 0 )
				nPosTracks++;
			if ( aTrack->charge() < 0 )
				nNegTracks++;

			float lr = pidLR.eval( aTrack, mtdPid );
			if ( pidLR.nPdfs() > 0 && (lr < minLR || lr > maxLR ) ) continue;

			if ( aTrack->charge() > 0 )
				nPosMuons++;
			if ( aTrack->charge() < 0 )
				nNegMuons++;


			TVector3 mom = aTrack->pMomentum();
			float rdg        = mom.Pt() * aTrack->charge();

			if ( false == qaCuts[ "rigidity" ]->inInclusiveRange( rdg ) ) continue;
			// if ( false == trackCuts[ "mtdCell" ]->inInclusiveRange( mtdPid->mMtdHitChan % 12 ) ) continue;

			if ( dataset == "Run15PP" ){
				// INFO( classname(), "Run Index = " << event->mRunIndex );
				trackQA.s( "runIndex", event->mRunIndex );
			}

			if ( config.getBool( nodePath + ".Make:track" ,true ) ){
				book->cd( "trackQA" );
				fillCandidateTrackQA( trackQA, aTrack, mtdPid );
			}

		} // iTrack loop

		if ( config.getBool( nodePath + ".Make:event" ,true ) ){

			book->cd( "eventQA" );
			eventQA.s( "nPos", nPos );
			eventQA.s( "nNeg", nNeg );

			eventQA.s( "nPosTracks", nPosTracks );
			eventQA.s( "nNegTracks", nNegTracks );

			eventQA.s( "nPosMuons", nPosMuons );
			eventQA.s( "nNegMuons", nNegMuons );
			// eventQA.s( "runIndex", event->mRunIndex );
			fillCandidateEventQA( eventQA, event );
		}

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
		_qaMaker.s( "mtdCell"     , _mtdPid->cell() );
		_qaMaker.s( "mtdDeltaY"   , _mtdPid->mDeltaY );
		_qaMaker.s( "mtdDeltaZ"   , _mtdPid->mDeltaZ );
		_qaMaker.s( "mtdDeltaTOF" , _mtdPid->mDeltaTimeOfFlight );
		_qaMaker.s( "nSigmaPion"  , nSigmaPion );

		_qaMaker.s( "pMomentum"   , mom.Mag() * _track->charge() );
		_qaMaker.s( "pMomentumX"  , mom.Px() );
		_qaMaker.s( "pMomentumY"  , mom.Py() );
		_qaMaker.s( "pMomentumZ"  , mom.Pz() );

		_qaMaker.s( "dca"         , _track->gDCA() );

		_qaMaker.s( "nHitsFit"    , (int)_track->mNHitsFit );
		_qaMaker.s( "nHitsDedx"   , (int)_track->mNHitsDedx * _track->charge() );
		_qaMaker.s( "nHitsMax"    , (int)_track->mNHitsMax * _track->charge() );
		_qaMaker.s( "nHitsRatio"  ,  fabs( _track->mNHitsFit ) / fabs( _track->mNHitsMax ) );


		_qaMaker.fill( _cat );
	}

	static void fillCandidateEventQA( TTreeQA &_qaMaker, CandidateEvent* _event ){
		// _qaMaker.s( "vertexX"  , _event->mPrimaryVertex_mX1 );
		// _qaMaker.s( "vertexY"  , _event->mPrimaryVertex_mX2 );
		// _qaMaker.s( "vertexZ"  , _event->mPrimaryVertex_mX3 );

		// _qaMaker.s( "weight"   , _event->mWeight            );
		// _qaMaker.s( "gRefMult" , _event->mGRefMult          );
		// _qaMaker.s( "bin16"    , (int)_event->mBin16        );

		_qaMaker.fill();
	}


protected:
	CutCollection qaCuts;

	TTreeQA trackQA;
	TTreeQA eventQA;
	PidLR pidLR;
	float minLR, maxLR;
	CutCollection trackCuts;
	
};


#endif