#ifndef INV_MASS_HISTO_MAKER_H
#define INV_MASS_HISTO_MAKER_H

#include "TreeAnalyzer.h"

#include "CandidatePairTreeReader.h"
#include "CandidateEventReader.h"
#include "TTreeQA.h"


#include <memory>

#include "TH1D.h"
#include "TH2D.h"
#include "TRandom3.h"

class InvMassHistoMaker : public TreeAnalyzer
{
public:
	virtual const char * classname() const { return "InvMassHistoMaker"; }
	InvMassHistoMaker() {}
	~InvMassHistoMaker() {}

	CandidateEvent * wEvent;
	int centBin;
	map<int, int> centralityMap;
	virtual void initialize(){
		TreeAnalyzer::initialize();

		pairReader = shared_ptr<CandidatePairTreeReader>( new CandidatePairTreeReader( chain ) );
		eventReader = shared_ptr<CandidateEventReader>( new CandidateEventReader( chain ) );

		book->cd("");

		massBins.load( config, "dimuonBins.mass" );
		ptBins.load( config, "dimuonBins.pT" );

		INFO( classname(), "Invariant mass Bins : " << massBins.toString() );
		INFO( classname(), "pT Bins : " << ptBins.toString() );

		
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

		centralityMap = config.getIntMap( nodePath + ".CentralityMap" );

		makeBin16Histos = false;

		rnd3.SetSeed(0);



		// look for a lrCut range
		lrCut.loadConfig( config, nodePath + ".LikelihoodPid" );
		if ( config.exists( nodePath + ".LikelihoodPid:min" ) ){
			INFOC( "=========Using LikelihoodPid=========" );
			INFOC( lrCut.toString() );
			usePidLR = true;
		} else {
			INFOC( "XXXXXXX NOT USING LikelihoodPid XXXXXXX" );
			usePidLR = false;
		}


		roi.loadConfig( config, nodePath + ".ROI" );
		if ( config.exists( nodePath + ".ROI:min" ) ){
			INFOC( "=========Using ROI=========" );
			INFOC( roi.toString() );
			useROI = true;
		} else {
			INFOC( "XXXXXXX NOT USING ROI XXXXXXX" );
			useROI = false;
		}
		

	}

	HistoBins massBins;
	HistoBins ptBins;
	TH1D * h_like_sign, *h_unlike_sign;
	TH2D * h_like_sign_vs_pt, *h_unlike_sign_vs_pt;
	CutCollection pairCuts;

	virtual bool keepEvent(){
		return true;
	}

	virtual void preEventLoop(){
		TreeAnalyzer::preEventLoop();
		INFO( classname(), "Aliasing Histograms" );

		book->cd();
		vector<string> states = { "uls", "ls", "lsp", "lsn", "l1", "l2" };
		vector<string> histos = { "dNdM", "pT_vs_dNdM", "rm_vs_dNdM", "R_vs_dNdM", "pT", "eta", "phi", "rapidity", "lr" };

		
		for ( string hn : histos ){
			for ( string s : states ){
				book->clone( hn, "pre_" + s + "_" + hn );
			}
		}

		for ( string hn : histos ){
			for ( string s : states ){
				book->clone( hn, s+"_"+hn );
			}
		}


	}

	virtual void analyzeEvent(){

		CandidateEvent* evt = eventReader->getEvent();
		int bin16=0;
		if ( evt != nullptr )
			bin16 = evt->mBin16;
		centBin = bin16;
		if ( centralityMap.count( bin16 ) > 0 )
			centBin = centralityMap[ bin16 ];

		CandidatePair * pair;
		int nPairs = pairReader->getNPairs();
		for ( int iPair = 0; iPair < nPairs; iPair++ ){
			pair = pairReader->getPair( iPair );
			if ( nullptr == pair ){
				ERROR( classname(), "nullptr pair? How is it possible" );
				continue;
			}
			analyzePair( pair );
		}
	}



	void fillState( string _s, TLorentzVector &_lv, double _lr = -1 ){
		book->fill( _s + "_dNdM", _lv.M() );
		book->fill( _s + "_pT_vs_dNdM", _lv.M(), _lv.Pt() );

		// int rm = eventReader->getEvent()->mGRefMult;
		// float n = (rm - 1) / 2.0;
		// float R = sqrt( (n+1 ) / (n-1) );

		// book->fill( _s + "_rm_vs_dNdM", _lv.M(), rm );
		// book->fill( _s + "_R_vs_dNdM", _lv.M(), 1.0 );
		book->fill( _s + "_pT", _lv.Pt() );
		book->fill( _s + "_eta", _lv.Eta() );
		book->fill( _s + "_phi", _lv.Phi() );
		book->fill( _s + "_rapidity", _lv.Rapidity() );
		book->fill( _s + "_lr", _lr );
	}


	void analyzePair( CandidatePair *pair ){


		TLorentzVector lv, lv1, lv2;
		lv.SetPtEtaPhiM( pair->mMomentum_mPt, pair->mMomentum_mEta, pair->mMomentum_mPhi, pair->mMass );
		lv1.SetPtEtaPhiM( pair->d1_mMomentum_mPt, pair->d1_mMomentum_mEta, pair->d1_mMomentum_mPhi, pair->d1_mMass );
		lv2.SetPtEtaPhiM( pair->d2_mMomentum_mPt, pair->d2_mMomentum_mEta, pair->d2_mMomentum_mPhi, pair->d2_mMass );
		

		fillState( "pre_l1", lv1, pair->d1_mPid );
		fillState( "pre_l2", lv2, pair->d2_mPid );

		string pChg1 = "uls";
		string pChg2 = "";
		
		if ( 2 == pair->mChargeSum  ){
			pChg1 = "ls";
			pChg2 = "lsp";
		}
		if ( -2 == pair->mChargeSum  ){
			pChg1 = "ls";
			pChg2 = "lsn";
		}
		if ( 0 == pair->mChargeSum  ){
			pChg1 = "uls";
			pChg2 = "";
		}

		fillState( "pre_" + pChg1, lv );
		if ( "" != pChg2 )
			fillState( "pre_" + pChg2, lv );

		// bool passPid = false;
		// if (  usePidLR && lrCut.inInclusiveRange( pair->d1_mPid ) && lrCut.inInclusiveRange( pair->d2_mPid ) ) 
		// 	passPid = true;
		// else if ( false == usePidLR )
		// 	passPid = true;


		if ( PairFilter::keepSameEventPair( pairCuts, lv, lv1, lv2, pair->d1_mPid , pair->d2_mPid ) ){

			fillState( "l1", lv1, pair->d1_mPid);
			fillState( "l2", lv2, pair->d2_mPid);
			fillState( pChg1, lv );
			if ( "" != pChg2 )
				fillState( pChg2, lv );
		}
	}// analyzePair


protected:

	XmlRange lrCut;
	XmlRange roi;
	bool usePidLR;
	bool useROI;

	virtual void overrideConfig(){

		if (config.getInt( "jobIndex" ) == -1 ){
			string nfn = config.getString( nodePath + ".output.TFile:url" );
			XmlString xstr;
			xstr.add( "jobIndex", "all" );
			nfn = xstr.format( nfn );
			config.set( nodePath + ".output.TFile:url", nfn );
		}
	}

	virtual void postMake(){

		// export the frozen config for good reference
		if ( config.exists( nodePath + ".output.XmlFile:url" ) ){
			config.toXmlFile( config.getXString( nodePath + ".output.XmlFile:url" ) );
		}
	}


	shared_ptr<CandidatePairTreeReader> pairReader;
	shared_ptr<CandidateEventReader> eventReader;

	TTreeQA pairQA;
	bool makeBin16Histos = false;
	TRandom3 rnd3;
};

#endif
