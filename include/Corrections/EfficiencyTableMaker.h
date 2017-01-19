#ifndef EFFICIENCY_TABLE_MAKER_H
#define EFFICIENCY_TABLE_MAKER_H

#include "TreeAnalyzer.h"
using namespace jdb;


#include "TLorentzVector.h"

#include "TriggerPatchMapper.h"

class EfficiencyTableMaker : public TreeAnalyzer
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

public:
	virtual const char* classname() const { return "EfficiencyTableMaker"; }
	EfficiencyTableMaker() {}
	~EfficiencyTableMaker() {}

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

	}


protected:
	virtual void analyzeEvent(){
		// INFOC( "here" );
		for ( int i = 0; i < 500; i++ ){
			// INFOC( "mcPkey=" << mcPkey[i] );
			if ( mcPkey[i] >=0 && (5 == mcGeantId[i] || 6 == mcGeantId[i]) ){
				book->fill( "mc_eta_vs_pT", mcpt[i] * mccharge[i], mceta[i] );
				book->fill( "mc_eta_vs_phi", mcphi[i], mceta[i] );
				book->fill( "mc_phi_vs_pT", mcpt[i] * mccharge[i], mcphi[i] );

				book->fill( "module", rcModule[i] );

				if ( rcPkey[i] >= 0 ){
					book->fill( "eLoss", mcpt[i], rcpt[i] - mcpt[i] );
					book->fill( "rc_eta_vs_pT", mcpt[i] * mccharge[i], mceta[i] );
					book->fill( "rc_eta_vs_phi", rcphi[i], mceta[i] );
					book->fill( "rc_phi_vs_pT", mcpt[i] * mccharge[i], rcphi[i] );
					
					if ( rcModule[i] > 0 ){
						book->fill( "mtd_eta_vs_pT", mcpt[i] * mccharge[i], mceta[i] );
						book->fill( "mtd_eta_vs_phi", rcphi[i], mceta[i] );
						book->fill( "mtd_phi_vs_pT", mcpt[i] * mccharge[i], rcphi[i] );
					}// mtd hit
				}//rc track 

				for ( int j = i; j < 500; j++ ){
					if ( i == j ) continue;
					// INFOC( "mcPkey=" << mcPkey[i] );
					if ( mcPkey[j] >=0 && (5 == mcGeantId[j] || 6 == mcGeantId[j]) /*&& mcPkey[i] == mcPkey[j]*/ ){
						string pre="uls_";
						if ( mccharge[i] == mccharge[j] ) pre="ls_";
						TLorentzVector mclv1, mclv2, mclv;
						mclv1.SetPtEtaPhiM( mcpt[i], mceta[i], mcphi[i], 0.105 );
						mclv2.SetPtEtaPhiM( mcpt[j], mceta[j], mcphi[j], 0.105 );
						mclv = mclv1 + mclv2;
						book->fill( pre+"mc_dEta_vs_dPhi", mclv1.Eta() - mclv2.Eta(), mclv1.DeltaPhi( mclv2 ) );
						book->fill( pre+"mc_pT_vs_m", mclv.M(), mclv.Pt() );


						if ( rcPkey[j] >= 0 ){
							TLorentzVector rclv1, rclv2, rclv;
							rclv1.SetPtEtaPhiM( rcpt[i], rceta[i], rcphi[i], 0.105 );
							rclv2.SetPtEtaPhiM( rcpt[j], rceta[j], rcphi[j], 0.105 );
							rclv = rclv1 + rclv2;
							book->fill( pre+"rc_pT_vs_m", rclv.M(), rclv.Pt() );
							if ( rcModule[i] > 0 ){
								book->fill( pre+"mtd_pT_vs_m", rclv.M(), rclv.Pt() );



								if ( TriggerPatchMapper::findTriggerPatch( rcBackleg[i], rcModule[i] ) != TriggerPatchMapper::findTriggerPatch( rcBackleg[j], rcModule[j] ) ){
									book->fill( pre+"tp_pT_vs_m", rclv.M(), rclv.Pt() );
								}

							}
						}
					}
				}

			}//mc track
		}//loop tracks
	}


	virtual void postMake(){
		book->clone( "rc_eta_vs_pT", "tracking_eta_vs_pT" );
		book->clone( "mtd_eta_vs_pT", "mtdMatch_eta_vs_pT" );
		
		book->get("tracking_eta_vs_pT")->Divide( book->get( "mc_eta_vs_pT" ) );
		book->get("mtdMatch_eta_vs_pT")->Divide( book->get( "rc_eta_vs_pT" ) );
	}
	
};



#endif