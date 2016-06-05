#include "RunByRunQAMaker.h"

#include "TVector3.h"
#include "StRefMultCorr.h"


void RunByRunQAMaker::initialize(){
	DEBUG( classname(), "initialize" );

	// build the run map tool
	rmf = shared_ptr<RunMapFactory>( new RunMapFactory( config.getBool( nodePath + ":noRunMap", false ) ) );
	pico = shared_ptr<PicoDst>( new PicoDst( chain ) );
	rmc = CentralityMaker::instance()->getgRefMultCorr();

	// so the histograms aren't so big
	if (config.getBool( nodePath + ":noRunMap", false ) ){
		config.set( "bins.runIndex:max", "10" );  
	} 

	book->makeAll( config, nodePath + ".histos.RunByRun" );

	makeTrackQA = config.getBool( nodePath + ":track", true );
	makeEventQA = config.getBool( nodePath + ":event", true );

	
}

void RunByRunQAMaker::overrideConfig(){
	// modify the output name to put the production in there
	string prod = config.getString( nodePath + ":production", "all" );
	string current = config.getString( nodePath + ".output.data" );
	

	vector<string> triggers = config.getStringVector( nodePath + ":triggers" );
	string trgString = "";
	if ( triggers.size() >= 1 ){ // 0 == all triggers
		for ( string trig : triggers ){
			trgString += trig + "_";
		}
	} else {
		trgString = "all_";
	}

	config.set( nodePath + ".output.data", "prod_" + prod + "_triggers_" + trgString + current );
}

bool RunByRunQAMaker::keepEvent() {
	DEBUG( classname(), "keepEvent" );

	int runId = pico->get<int>( "Event.mRunId" );

	/*********** Initialize the RefMultCorr *************/
	rmc->init( runId );
	rmc->initEvent( 
		pico->get<UShort_t>( "Event.mGRefMult" ), 
		pico->get<float>( "Event.mPrimaryVertex.mX3" ), 
		pico->get<UInt_t>( "Event.mZDCx" )  
	);

	book->get( "EventCuts" )->Fill( "All", 1 );

	string productions = config.getString( nodePath + ":production", "" );
	
	/*********** Production Cut *************/
	if ( "" != productions ){
		if ( ProductionFilter::productionFor( runId ) != productions )
			return false;
	}
	book->get( "EventCuts" )->Fill( "Prod", 1 );

	/*********** Trigger Cut *************/
	vector<string> triggers = config.getStringVector( nodePath + ":triggers" );
	bool foundTrigger = false;
	if ( triggers.size() >= 1 ){ // 0 == all triggers
		for ( string trig : triggers ){
			if ( pico->isMtdTrigger( trig ) ) {
				foundTrigger = true;
				break;
			}
		}
	}
	if ( false == foundTrigger )
		return false;
	book->get( "EventCuts" )->Fill( "Trigger", 1 );

	runIndex = rmf->indexForRun( runId );

	return true;
}

void RunByRunQAMaker::analyzeEvent(){
	DEBUG( classname(), "event" );


	// book->cd( "RunByRun" );

	if ( makeEventQA ){
		/**************** Event.* *******************************/
		book->fill( "mPrimaryVertex_mX1", runIndex, pico->get<float>( "Event.mPrimaryVertex.mX1" ) );
		book->fill( "mPrimaryVertex_mX2", runIndex, pico->get<float>( "Event.mPrimaryVertex.mX2" ) );
		book->fill( "mPrimaryVertex_mX3", runIndex, pico->get<float>( "Event.mPrimaryVertex.mX3" ) );
		book->fill( "mRanking", runIndex, pico->get<float>( "Event.mRanking" ) );
		book->fill( "mRefMult", runIndex, pico->get<UShort_t>( "Event.mRefMultPos" ) + pico->get<UShort_t>( "Event.mRefMultNeg" )  );
		book->fill( "mRefMultCorr", runIndex, rmc->getRefMultCorr() );
		book->fill( "mBin9", runIndex, rmc->getCentralityBin9() );
		book->fill( "mBin16", runIndex, rmc->getCentralityBin16() );
		book->fill( "mRefMultPos", runIndex, pico->get<UShort_t>( "Event.mRefMultPos" )   );
		book->fill( "mRefMultNeg", runIndex, pico->get<UShort_t>( "Event.mRefMultNeg" )   );
		book->fill( "mGRefMult", runIndex, pico->get<UShort_t>( "Event.mGRefMult" )  );
		book->fill( "mNBTOFMatch", runIndex, pico->get<UShort_t>( "Event.mNBTOFMatch" )  );
		book->fill( "mNBEMCMatch", runIndex, pico->get<UShort_t>( "Event.mNBEMCMatch" )  );
		book->fill( "mNumberOfGlobalTracks", runIndex, pico->get<UShort_t>( "Event.mNumberOfGlobalTracks" )  );
		book->fill( "delta_mVzVpd_mPrimaryVertex_mX3",
					runIndex,
					(pico->get<short>( "Event.mVzVpd" )/100.0) - pico->get<float>("Event.mPrimaryVertex.mX3") );
		book->fill( "mVzVpd", runIndex, pico->get<short>( "Event.mVzVpd" )/100.0 );

		book->fill( "mBBCx", runIndex, pico->get<UInt_t>( "Event.mBBCx" )  );
		book->fill( "mZDCx", runIndex, pico->get<UInt_t>( "Event.mZDCx" )  );
		book->fill( "mBackgroundRate", runIndex, pico->get<Float_t>( "Event.mBackgroundRate" )  );
		book->fill( "mbTofTrayMultiplicity", runIndex, pico->get<UShort_t>( "Event.mbTofTrayMultiplicity" )  );
		
		/**************** EventPlane.* *******************************/
		book->fill( "mQx_eta_pos", runIndex, pico->get<float>( "EventPlane.mQx_eta_pos" ) );
		book->fill( "mQx_eta_neg", runIndex, pico->get<float>( "EventPlane.mQx_eta_neg" ) );
		book->fill( "mQy_eta_pos", runIndex, pico->get<float>( "EventPlane.mQy_eta_pos" ) );
		book->fill( "mQy_eta_neg", runIndex, pico->get<float>( "EventPlane.mQy_eta_neg" ) );

		book->fill( "mQx_chg_pos", runIndex, pico->get<float>( "EventPlane.mQx_chg_pos" ) );
		book->fill( "mQx_chg_neg", runIndex, pico->get<float>( "EventPlane.mQx_chg_neg" ) );
		book->fill( "mQy_chg_pos", runIndex, pico->get<float>( "EventPlane.mQy_chg_pos" ) );
		book->fill( "mQy_chg_neg", runIndex, pico->get<float>( "EventPlane.mQy_chg_neg" ) );

		book->fill( "mNtrk_eta_pos", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_eta_pos" ) );
		book->fill( "mNtrk_eta_neg", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_eta_neg" ) );
		book->fill( "mNtrk_chg_pos_eta_pos", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_chg_pos_eta_pos" ) );
		book->fill( "mNtrk_chg_pos_eta_neg", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_chg_pos_eta_neg" ) );
		book->fill( "mNtrk_chg_neg_eta_pos", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_chg_neg_eta_pos" ) );
		book->fill( "mNtrk_chg_neg_eta_neg", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_chg_neg_eta_neg" ) );

		book->fill( "mNtrk_ran_1_eta_pos", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_ran_1_eta_pos" ) );
		book->fill( "mNtrk_ran_1_eta_neg", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_ran_1_eta_neg" ) );
		book->fill( "mNtrk_ran_2_eta_pos", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_ran_2_eta_pos" ) );
		book->fill( "mNtrk_ran_2_eta_neg", runIndex, pico->get<Short_t>( "EventPlane.mNtrk_ran_2_eta_neg" ) );


		book->fill( "mWeight_eta_pos", runIndex, pico->get<float>( "EventPlane.mWeight_eta_pos" ) );
		book->fill( "mWeight_eta_neg", runIndex, pico->get<float>( "EventPlane.mWeight_eta_neg" ) );
		book->fill( "mWeight_chg_pos", runIndex, pico->get<float>( "EventPlane.mWeight_chg_pos" ) );
		book->fill( "mWeight_chg_neg", runIndex, pico->get<float>( "EventPlane.mWeight_chg_neg" ) );
		book->fill( "mWeight_ran_1", runIndex, pico->get<float>( "EventPlane.mWeight_ran_1" ) );
		book->fill( "mWeight_ran_2", runIndex, pico->get<float>( "EventPlane.mWeight_ran_2" ) );
	}

	int nMtdMatched = 0;
	int nBTofMatched = 0;
	int nEmcMatched = 0;
	bool requireMtdMatch = config.getBool( nodePath + ".TrackCuts.MtdMatch", false );
	bool requireBTofMatch = config.getBool( nodePath + ".TrackCuts.BTofMatch", false );
	bool requireEmcMatch = config.getBool( nodePath + ".TrackCuts.EmcMatch", false );
	if ( makeTrackQA ){
		/**************** Tracks *******************************/
		int nTracks = pico->get<Int_t>( "Tracks_" );
		
		for ( int iTrack = 0; iTrack < nTracks; iTrack++ ) {
		
			TVector3 p( pico->get<float>( "Tracks.mPMomentum.mX1", iTrack ), pico->get<float>( "Tracks.mPMomentum.mX2", iTrack ), pico->get<float>( "Tracks.mPMomentum.mX3", iTrack ) );
			
			if ( p.Mag() <= 0.001 ) continue;

			int iBTof = pico->get<Short_t>( "Tracks.mBTofPidTraitsIndex", iTrack );
			int iMtd = pico->get<Short_t>( "Tracks.mMtdPidTraitsIndex", iTrack );
			int iEmc = pico->get<Short_t>( "Tracks.mEmcPidTraitsIndex", iTrack );

			if ( requireEmcMatch && iEmc < 0 ) continue;
			if ( requireMtdMatch && iMtd < 0 ) continue;
			if ( requireBTofMatch && iBTof < 0 ) continue;

			book->fill( "Tracks_mChi2", runIndex, pico->get<UShort_t>( "Tracks.mChi2", iTrack ) );
			book->fill( "Tracks_mPMomentum", runIndex, p.Mag() );
			book->fill( "Tracks_mPtMomentum", runIndex, p.Pt() );
			book->fill( "Tracks_mEta", runIndex, p.Eta() );
			book->fill( "Tracks_mPhi", runIndex, p.Phi() );
			book->fill( "Tracks_mDedx", runIndex, pico->get<UShort_t>( "Tracks.mDedx", iTrack ) / 1000.0 );
			book->fill( "Tracks_mNHitsFit", runIndex, fabs( pico->get<Char_t>( "Tracks.mNHitsFit", iTrack ) ) );
			book->fill( "Tracks_mNHitsMax", runIndex, pico->get<Char_t>( "Tracks.mNHitsMax", iTrack ) );
			book->fill( "Tracks_mNHitsDedx", runIndex, pico->get<UChar_t>( "Tracks.mNHitsDedx", iTrack ) );

			
			if ( iBTof >= 0 ){
				book->fill( "BTofPidTraits_mBTofYLocal", runIndex, pico->get<Short_t>( "BTofPidTraits.mBTofYLocal", iBTof ) / 1000.0 );
				book->fill( "BTofPidTraits_mBTofZLocal", runIndex, pico->get<Short_t>( "BTofPidTraits.mBTofZLocal", iBTof ) / 1000.0 );
				book->fill( "BTofPidTraits_mBTofMatchFlag", runIndex, pico->get<UChar_t>( "BTofPidTraits.mBTofMatchFlag", iBTof ) );	
				book->fill( "BTofPidTraits_mBTof", runIndex, pico->get<UShort_t>( "BTofPidTraits.mBTof", iBTof ) / 1000.0 );
				book->fill( "BTofPidTraits_mBTofBeta", runIndex, pico->get<UShort_t>( "BTofPidTraits.mBTofBeta", iBTof ) / 20000.0 );
				nBTofMatched++;
			}
			if ( iMtd >= 0 ) {
				book->fill( "MtdPidTraits_mDeltaZ", runIndex, pico->get<float>( "MtdPidTraits.mDeltaZ", iMtd ) );	
				book->fill( "MtdPidTraits_mDeltaY", runIndex, pico->get<float>( "MtdPidTraits.mDeltaY", iMtd ) );	
				book->fill( "MtdPidTraits_mMtdHitChan", runIndex, pico->get<Short_t>( "MtdPidTraits.mMtdHitChan", iMtd ) );
				book->fill( "MtdPidTraits_mMatchFlag", runIndex, pico->get<Char_t>( "MtdPidTraits.mMatchFlag", iMtd ) );	
				book->fill( "MtdPidTraits_mDeltaTimeOfFlight", runIndex, pico->get<float>( "MtdPidTraits.mDeltaTimeOfFlight", iMtd ) );
				book->fill( "MtdPidTraits_mBeta", runIndex, pico->get<float>( "MtdPidTraits.mBeta", iMtd ) );	
				nMtdMatched++;
			}
			if ( iEmc >= 0 ){
				book->fill( "EmcPidTraits_mBEMCId", runIndex, pico->get<Short_t>("EmcPidTraits.mBEMCId", iEmc ) );
				book->fill( "EmcPidTraits_mBTOWADC0", runIndex, pico->get<Short_t>("EmcPidTraits.mBTOWADC0", iEmc ) );
				book->fill( "EmcPidTraits_mBTOWE0", runIndex, pico->get<Short_t>("EmcPidTraits.mBTOWE0", iEmc ) / 1000.0 );
				book->fill( "EmcPidTraits_mBTOWE", runIndex, pico->get<Short_t>("EmcPidTraits.mBTOWE", iEmc ) / 1000.0 );
				book->fill( "EmcPidTraits_mBEMCDistZ", runIndex, pico->get<Short_t>("EmcPidTraits.mBEMCDistZ", iEmc ) / 100.0 );
				book->fill( "EmcPidTraits_mBEMCDistPhi", runIndex, pico->get<Short_t>("EmcPidTraits.mBEMCDistPhi", iEmc ) / 10000.0 );
				book->fill( "EmcPidTraits_mBSMDNEta", runIndex, pico->get<UChar_t>("EmcPidTraits.mBSMDNEta", iEmc ) );
				book->fill( "EmcPidTraits_mBSMDNPhi", runIndex, pico->get<UChar_t>("EmcPidTraits.mBSMDNPhi", iEmc ) );
				book->fill( "EmcPidTraits_mBTOWId", runIndex, pico->get<Short_t>("EmcPidTraits.mBTOWId", iEmc ) );
				book->fill( "EmcPidTraits_mBTOWId23", runIndex, pico->get<Char_t>("EmcPidTraits.mBTOWId23", iEmc ) );
				book->fill( "EmcPidTraits_mBTOWE1", runIndex, pico->get<Short_t>("EmcPidTraits.mBTOWE1", iEmc ) / 1000.0 );
				book->fill( "EmcPidTraits_mBTOWE2", runIndex, pico->get<Short_t>("EmcPidTraits.mBTOWE2", iEmc ) / 1000.0 );
				book->fill( "EmcPidTraits_mBTOWE3", runIndex, pico->get<Short_t>("EmcPidTraits.mBTOWE3", iEmc ) / 1000.0 );
				book->fill( "EmcPidTraits_mBTOWDistEta", runIndex, pico->get<Short_t>("EmcPidTraits.mBTOWDistEta", iEmc ) / 10000.0 );
				book->fill( "EmcPidTraits_mBTOWDistPhi", runIndex, pico->get<Short_t>("EmcPidTraits.mBTOWDistPhi", iEmc ) / 10000.0 );
				nEmcMatched++;
			}


		} // loop on tracks	
	}

	book->fill( "mNMtdMatched", runIndex, nMtdMatched  );

}