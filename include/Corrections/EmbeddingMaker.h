#ifndef EMBEDDING_MAKER_H
#define EMBEDDING_MAKER_H

#include "TreeAnalyzer.h"
using namespace jdb;


#include "TLorentzVector.h"

#include "TriggerPatchMapper.h"
#include "CandidateFilter.h"

class EmbeddingMaker : public TreeAnalyzer
{
protected:

	// TreeData
	//---event level
	Int_t    runID;
	Int_t    tofMult;
	Float_t mBField;
	Float_t zdcRate;// * 1e-3
	Float_t bbcRate;
	Float_t tpcVx;
	Float_t tpcVy;
	Float_t tpcVz;
	Float_t vpdVz;
	//---track level
	Int_t    nMcTracks;
	Int_t    nMcMuon;
	Int_t    nMcJpsi;
	Int_t    nRcJpsi;
	//mc muon tracks
	Int_t    mcPkey[500];//MC track parent key
	Int_t    mcGeantId[500];//muon Id = 5 or 6
	Double_t mcpt[500];
	Double_t mcphi[500];
	Double_t mceta[500];
	Int_t    mccharge[500];
	Int_t    rcPkey[500];//RC track parent key
	Int_t    rcNHitsFit[500];
	Int_t    rcNHitsPoss[500];
	Int_t    rcNHitsDedx[500];
	Double_t rcDca[500];
	Double_t rcpt[500];
	Double_t rcphi[500];
	Double_t rceta[500];
	Double_t rcNSigmaPi[500];
	Int_t    rcCharge[500];
	// both rc track match with mtd without track quality cut 
	Int_t rcBackleg[500];
	Int_t rcModule[500];
	Double_t rcDz[500];
	Double_t rcDy[500];
	Double_t rcDtof[500];
	Int_t passTrkCut[500];
	Int_t passMuonCut[500];

	// List of branches
   TBranch        *b_runID;   //!
   TBranch        *b_tofMult;   //!
   TBranch        *b_mBField;   //!
   TBranch        *b_bbcRate;   //!
   TBranch        *b_zdcRate;   //!
   TBranch        *b_tpcVx;   //!
   TBranch        *b_tpcVy;   //!
   TBranch        *b_tpcVz;   //!
   TBranch        *b_vpdVz;   //!
   TBranch        *b_nMcTracks;   //!
   TBranch        *b_nMcMuon;   //!
   TBranch        *b_nMcJpsi;   //!
   TBranch        *b_nRcJpsi;   //!
   TBranch        *b_mcPkey;   //!
   TBranch        *b_mcGeantId;   //!
   TBranch        *b_mcpt;   //!
   TBranch        *b_mcphi;   //!
   TBranch        *b_mceta;   //!
   TBranch        *b_mccharge;   //!
   TBranch        *b_rcPkey;   //!
   TBranch        *b_rcNHitsFit;   //!
   TBranch        *b_rcNHitsPoss;   //!
   TBranch        *b_rcNHitsDedx;   //!
   TBranch        *b_rcDca;   //!
   TBranch        *b_rcpt;   //!
   TBranch        *b_rcphi;   //!
   TBranch        *b_rceta;   //!
   TBranch        *b_rcNSigmaPi;   //!
   TBranch        *b_rcCharge;   //!
   TBranch        *b_rcBackleg;   //!
   TBranch        *b_rcModule;   //!
   TBranch        *b_rcDz;   //!
   TBranch        *b_rcDy;   //!
   TBranch        *b_rcDtof;   //!
   TBranch        *b_passTrkCut;   //!
   TBranch        *b_passMuonCut;   //!


   CutCollection trackCuts;
   

public:
	virtual const char* classname() const { return "EmbeddingMaker"; }
	EmbeddingMaker() {}
	~EmbeddingMaker() {}

	virtual void initialize(){
		TreeAnalyzer::initialize();

		chain->SetMakeClass(1);
		chain->SetBranchAddress("runID"       , &runID      , &b_runID);
		chain->SetBranchAddress("tofMult"     , &tofMult    , &b_tofMult);
		chain->SetBranchAddress("mBField"     , &mBField    , &b_mBField);
		chain->SetBranchAddress("bbcRate"     , &bbcRate    , &b_bbcRate);
		chain->SetBranchAddress("zdcRate"     , &zdcRate    , &b_zdcRate);
		chain->SetBranchAddress("tpcVx"       , &tpcVx      , &b_tpcVx);
		chain->SetBranchAddress("tpcVy"       , &tpcVy      , &b_tpcVy);
		chain->SetBranchAddress("tpcVz"       , &tpcVz      , &b_tpcVz);
		chain->SetBranchAddress("vpdVz"       , &vpdVz      , &b_vpdVz);
		chain->SetBranchAddress("nMcTracks"   , &nMcTracks  , &b_nMcTracks);
		chain->SetBranchAddress("nMcMuon"     , &nMcMuon    , &b_nMcMuon);
		chain->SetBranchAddress("nMcJpsi"     , &nMcJpsi    , &b_nMcJpsi);
		chain->SetBranchAddress("nRcJpsi"     , &nRcJpsi    , &b_nRcJpsi);
		chain->SetBranchAddress("mcPkey"      , mcPkey      , &b_mcPkey);
		chain->SetBranchAddress("mcGeantId"   , mcGeantId   , &b_mcGeantId);
		chain->SetBranchAddress("mcpt"        , mcpt        , &b_mcpt);
		chain->SetBranchAddress("mcphi"       , mcphi       , &b_mcphi);
		chain->SetBranchAddress("mceta"       , mceta       , &b_mceta);
		chain->SetBranchAddress("mccharge"    , mccharge    , &b_mccharge);
		chain->SetBranchAddress("rcPkey"      , rcPkey      , &b_rcPkey);
		chain->SetBranchAddress("rcNHitsFit"  , rcNHitsFit  , &b_rcNHitsFit);
		chain->SetBranchAddress("rcNHitsPoss" , rcNHitsPoss , &b_rcNHitsPoss);
		chain->SetBranchAddress("rcNHitsDedx" , rcNHitsDedx , &b_rcNHitsDedx);
		chain->SetBranchAddress("rcDca"       , rcDca       , &b_rcDca);
		chain->SetBranchAddress("rcpt"        , rcpt        , &b_rcpt);
		chain->SetBranchAddress("rcphi"       , rcphi       , &b_rcphi);
		chain->SetBranchAddress("rceta"       , rceta       , &b_rceta);
		chain->SetBranchAddress("rcNSigmaPi"  , rcNSigmaPi  , &b_rcNSigmaPi);
		chain->SetBranchAddress("rcCharge"    , rcCharge    , &b_rcCharge);
		chain->SetBranchAddress("rcBackleg"   , rcBackleg   , &b_rcBackleg);
		chain->SetBranchAddress("rcModule"    , rcModule    , &b_rcModule);
		chain->SetBranchAddress("rcDz"        , rcDz        , &b_rcDz);
		chain->SetBranchAddress("rcDy"        , rcDy        , &b_rcDy);
		chain->SetBranchAddress("rcDtof"      , rcDtof      , &b_rcDtof);
		chain->SetBranchAddress("passTrkCut"  , passTrkCut  , &b_passTrkCut);
		chain->SetBranchAddress("passMuonCut" , passMuonCut , &b_passMuonCut);

		book->cd();

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

	}


protected:

	virtual void preEventLoop(){
		DEBUG( classname(), "" );
		TreeAnalyzer::preEventLoop();

		vector<string> trackCutBinLabels = config.getStringVector( "TrackQABins.MtdMuon_binLabels" );
		CandidateFilter::initializeBinLabels( book, trackCutBinLabels, "MtdMuon" );

		book->cd();
	}


	virtual void analyzeEvent(){
		
		shared_ptr<CandidateTrack> tA, tB;
		shared_ptr<CandidateTrackMtdPidTraits> pidA, pidB;

		tA = shared_ptr<CandidateTrack>( new CandidateTrack() );
		tB = shared_ptr<CandidateTrack>( new CandidateTrack() );

		pidA = shared_ptr<CandidateTrackMtdPidTraits>( new CandidateTrackMtdPidTraits() );
		pidB = shared_ptr<CandidateTrackMtdPidTraits>( new CandidateTrackMtdPidTraits() );

		for ( int i = 0; i < 500; i++ ){
			// INFOC( "mcPkey=" << mcPkey[i] );
			if ( mcPkey[i] >=0 && (5 == mcGeantId[i] || 6 == mcGeantId[i]) ){
				book->fill( "mc_eta_vs_pT", mcpt[i] * mccharge[i], mceta[i] );
				book->fill( "mc_eta_vs_phi", mcphi[i], mceta[i] );
				book->fill( "mc_phi_vs_pT", mcpt[i] * mccharge[i], mcphi[i] );

				book->fill( "mc_" + ts( mcGeantId[i] ) + "_PtEtaPhi", mcpt[i], mceta[i], mcphi[i] );

				book->fill( "module", rcModule[i] );

				for ( int j = i; j < 500; j++ ){
					if ( i == j ) continue;
					
					if ( mcPkey[j] >=0 && (5 == mcGeantId[j] || 6 == mcGeantId[j]) ){
						string pre="uls_";
						if ( mccharge[i] == mccharge[j] ) pre="ls_";
						if ( mcPkey[i] == mcPkey[j] ) pre="jpsi_";

						TLorentzVector mclv1, mclv2, mclv;
						mclv1.SetPtEtaPhiM( mcpt[i], mceta[i], mcphi[i], 0.105 );
						mclv2.SetPtEtaPhiM( mcpt[j], mceta[j], mcphi[j], 0.105 );
						mclv = mclv1 + mclv2;

						if ( "jpsi_" == pre && mclv1.Pt() > 1.3 && mclv2.Pt() > 1.3 && ( mclv1.Pt() > 1.5 || mclv2.Pt() > 1.5 ) ){
							book->fill( "N_mc_jpsi_pT", mclv.Pt() );
						}

						// if ( abs(mclv.Rapidity()) > 0.5 && "jpsi_" == pre ) continue;
						book->fill( pre+"mc_dEta_vs_dPhi", mclv1.Eta() - mclv2.Eta(), mclv1.DeltaPhi( mclv2 ) );
						book->fill( pre+"mc_pT_vs_m", mclv.M(), mclv.Pt() );
					}
				}



				// RECO LEVEL

				if ( rcPkey[i] >= 0 ){
					track( i, tA, pidA );
					if ( !CandidateFilter::isMuon( tA.get(), pidA.get(), trackCuts, nullptr, "pt" ) ) continue;

					book->fill( "eLoss", mcpt[i], rcpt[i] - mcpt[i] );
					book->fill( "rc_eta_vs_pT", mcpt[i] * mccharge[i], mceta[i] );
					book->fill( "rc_eta_vs_phi", rcphi[i], mceta[i] );
					book->fill( "rc_phi_vs_pT", mcpt[i] * mccharge[i], rcphi[i] );

					book->fill( "rc_" + ts( mcGeantId[i] ) + "_PtEtaPhi", mcpt[i], mceta[i], mcphi[i] );
					
					if ( rcModule[i] > 0 ){
						book->fill( "mtd_eta_vs_pT", mcpt[i] * mccharge[i], mceta[i] );
						book->fill( "mtd_eta_vs_phi", rcphi[i], mceta[i] );
						book->fill( "mtd_phi_vs_pT", mcpt[i] * mccharge[i], rcphi[i] );

						book->fill( "mtd_" + ts( mcGeantId[i] ) + "_PtEtaPhi", rcpt[i], rceta[i], rcphi[i] );
					}// mtd hit
				


					for ( int j = i; j < 500; j++ ){
						if ( i == j ) continue;
						// INFOC( "mcPkey=" << mcPkey[i] );
						if ( mcPkey[j] >=0 && (5 == mcGeantId[j] || 6 == mcGeantId[j]) ){
							string pre="uls_";
							if ( mccharge[i] == mccharge[j] ) pre="ls_";
							if ( mcPkey[i] == mcPkey[j] ) pre = "jpsi_";

							if ( rcPkey[j] >= 0 ){
								track( i, tB, pidB );
								if ( !CandidateFilter::isMuon( tB.get(), pidB.get(), trackCuts ) ) continue;

								TLorentzVector rclv1, rclv2, rclv;
								rclv1.SetPtEtaPhiM( rcpt[i], rceta[i], rcphi[i], 0.105 );
								rclv2.SetPtEtaPhiM( rcpt[j], rceta[j], rcphi[j], 0.105 );
								rclv = rclv1 + rclv2;

								if ( "jpsi_" == pre && rclv1.Pt() > 1.3 && rclv2.Pt() > 1.3 && ( rclv1.Pt() > 1.5 || rclv2.Pt() > 1.5 ) ){
									book->fill( "N_rc_jpsi_pT", rclv.Pt() );
								}

								book->fill( pre+"rc_dEta_vs_dPhi", rclv1.Eta() - rclv2.Eta(), rclv1.DeltaPhi( rclv2 ) );
								book->fill( pre+"rc_pT_vs_m", rclv.M(), rclv.Pt() );
								if ( rcModule[i] > 0 && rcModule[j] > 0 ){

									if ( "jpsi_" == pre && rclv1.Pt() > 1.3 && rclv2.Pt() > 1.3 && ( rclv1.Pt() > 1.5 || rclv2.Pt() > 1.5 ) ){
										book->fill( "N_mtd_jpsi_pT", rclv.Pt() );
									}

									book->fill( pre+"mtd_dEta_vs_dPhi", rclv1.Eta() - rclv2.Eta(), rclv1.DeltaPhi( rclv2 ) );
									book->fill( pre+"mtd_pT_vs_m", rclv.M(), rclv.Pt() );

									if ( fabs( rclv1.Eta() - rclv2.Eta() ) > 0.05 || fabs( rclv1.DeltaPhi( rclv2 ) ) > 1.0 ){
										book->fill( pre+"dc_pT_vs_m", rclv.M(), rclv.Pt() );
									}

									if (  rclv.M() < 0.3 ){
										book->fill( pre+"lmr_dEta_vs_dPhi", rclv1.Eta() - rclv2.Eta(), rclv1.DeltaPhi( rclv2 ) );
									}

									if ( TriggerPatchMapper::findTriggerPatch( rcBackleg[i], rcModule[i] ) != TriggerPatchMapper::findTriggerPatch( rcBackleg[j], rcModule[j] ) ){
										book->fill( pre+"tp_dEta_vs_dPhi", rclv1.Eta() - rclv2.Eta(), rclv1.DeltaPhi( rclv2 ) );
										book->fill( pre+"tp_pT_vs_m", rclv.M(), rclv.Pt() );


										if ( TriggerPatchMapper::findTriggerPatch( rcBackleg[i], rcModule[i] ) == -1 || TriggerPatchMapper::findTriggerPatch( rcBackleg[j], rcModule[j] ) == -1){
										INFOC( "bl1 = " << rcBackleg[i] << ", mod1 = " << rcModule[i] << ", TP1 == " << TriggerPatchMapper::findTriggerPatch( rcBackleg[i], rcModule[i] ) );
										INFOC( "bl1 = " << rcBackleg[j] << ", mod1 = " << rcModule[j] << ", TP1 == " << TriggerPatchMapper::findTriggerPatch( rcBackleg[j], rcModule[j] ) );}

										// if (  rclv.M() < 0.3 ){
										// 	INFOC( "=========LOW MASS PAIR===========" );
										// 	print( i );
										// 	print( j );
										// }

									} // j tp
								} // j mtd track
							} // j rc track 
						} // j mc track 
					} // inner loop j
				}//rc track 
			}//mc track
		}//loop tracks
	}

	void print( int i ){
		string msg = "Track[" + ts(i) + "]";

		msg += "\n\t mcPkey=" + dts( mcPkey[i] );
		msg += "\n\t mcGeantId=" + dts( mcGeantId[i] );
		msg += "\n\t mcpt=" + dts( mcpt[i] );
		msg += "\n\t mcphi=" + dts( mcphi[i] );
		msg += "\n\t mceta=" + dts( mceta[i] );
		msg += "\n\t mccharge=" + dts( mccharge[i] );
		msg += "\n\t rcPkey=" + dts( rcPkey[i] );
		msg += "\n\t rcNHitsFit=" + dts( rcNHitsFit[i] );
		msg += "\n\t rcNHitsPoss=" + dts( rcNHitsPoss[i] );
		msg += "\n\t rcNHitsDedx=" + dts( rcNHitsDedx[i] );
		msg += "\n\t rcDca=" + dts( rcDca[i] );
		msg += "\n\t rcpt=" + dts( rcpt[i] );
		msg += "\n\t rcphi=" + dts( rcphi[i] );
		msg += "\n\t rceta=" + dts( rceta[i] );
		msg += "\n\t rcNSigmaPi=" + dts( rcNSigmaPi[i] );
		msg += "\n\t rcCharge=" + dts( rcCharge[i] );
		msg += "\n\t rcBackleg=" + dts( rcBackleg[i] );
		msg += "\n\t rcModule=" + dts( rcModule[i] );
		msg += "\n\t rcDz=" + dts( rcDz[i] );
		msg += "\n\t rcDy=" + dts( rcDy[i] );
		msg += "\n\t rcDtof=" + dts( rcDtof[i] );
		INFOC( msg );
	}

	virtual void track( int i, shared_ptr<CandidateTrack> _track, shared_ptr<CandidateTrackMtdPidTraits> _mtdPid ){
		if ( nullptr == _track || nullptr == _mtdPid ) return;

		TLorentzVector lv;
		lv.SetPtEtaPhiM( rcpt[i], rceta[i], rcphi[i], 0.105 );
		_track->mPMomentum_mX1      = lv.Px();
		_track->mPMomentum_mX2      = lv.Py();
		_track->mPMomentum_mX3      = lv.Pz();
		_track->mId                 = 1;
		_track->mDedx               = 0.0;
		_track->mNHitsFit           = rcNHitsFit[i];
		_track->mNHitsMax           = rcNHitsPoss[i];
		_track->mNHitsDedx          = rcNHitsDedx[i];
		
		_track->mNSigmaKaon         = 0.0;
		_track->mNSigmaProton       = 0.0;
		_track->mNSigmaElectron     = 0.0;
		_track->mDCA                = rcDca[i] * 1000.0;
		_track->mBTofPidTraitsIndex = 1;
		_track->mMtdPidTraitsIndex  = 1;
		_track->mHelixIndex         = 1;

		// we take care of these in the PID efficiency section
		_track->mNSigmaPion         = rcNSigmaPi[i] * 100.0;
		_mtdPid->mDeltaY            = 0;
		_mtdPid->mDeltaZ            = 0;
		_mtdPid->mDeltaTimeOfFlight = 0;
		_mtdPid->mMatchFlag         = 1;
		_mtdPid->mMtdHitChan        = 1;
		_mtdPid->mTriggerFlag       = 1;
	} 


	virtual void postMake(){
		book->clone( "rc_eta_vs_pT", "tracking_eta_vs_pT" );
		book->clone( "mtd_eta_vs_pT", "mtdMatch_eta_vs_pT" );
		
		book->get("tracking_eta_vs_pT")->Divide( book->get( "mc_eta_vs_pT" ) );
		book->get("mtdMatch_eta_vs_pT")->Divide( book->get( "rc_eta_vs_pT" ) );
	}
	
};



#endif