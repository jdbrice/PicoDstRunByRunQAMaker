#ifndef INV_MASS_HISTO_MAKER_H
#define INV_MASS_HISTO_MAKER_H

#include "TreeAnalyzer.h"

#include "CandidatePairTreeReader.h"
#include "CandidateEventReader.h"
#include "TTreeQA.h"


#include <memory>

#include "TH1D.h"
#include "TH2D.h"

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

		dimuonBins.load( config, "dimuonBins.invMass" );

		INFO( classname(), "Invariant mass Bins : " << dimuonBins.toString() );


		// pairQA.setHistoBook( book );
		// pairQA.setConfig( config );
		// pairQA.addCategory( "ls" );
		// pairQA.addCategory( "pp" );
		// pairQA.addCategory( "nn" );
		// pairQA.addCategory( "us" );
		// pairQA.makeDefaultCategory( false );
		// initPairVariables( pairQA );
		// book->cd( "pairQA" );
		// pairQA.makeHistograms( "dimuonBins" );
		
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

	}

	// virtual void initPairVariables( TTreeQA &_qaMaker ){
	// 	_qaMaker.i( "invMass", "M_{#mu#mu}", "[GeV/c^{2}]", "", "x" );
	// 	_qaMaker.i( "pT", "p_{T}", "[GeV/c]" );
	// 	_qaMaker.i( "bin16" )
	// }

	HistoBins dimuonBins;
	TH1D * h_like_sign, *h_unlike_sign;
	TH2D * h_like_sign_vs_pt, *h_unlike_sign_vs_pt;
	CutCollection pairCuts;

	virtual bool keepEvent(){
		return true;
	}

	virtual void preEventLoop(){
		TreeAnalyzer::preEventLoop();
		INFO( classname(), "Aliasing Histograms" );

		book->cd( "" );
		h_like_sign = (TH1D*)book->get( "like_sign" );
		h_like_sign_vs_pt = (TH2D*)book->get2D( "like_sign_pT" );

		h_unlike_sign = (TH1D*)book->get( "unlike_sign" );
		h_unlike_sign_vs_pt = (TH2D*)book->get2D( "unlike_sign_pT" );

		book->get( "like_sign" )->SetLineColor( kRed );

		if ( book->exists( "binX_like_sign" ) ){
			vector<int> cBins = config.getIntVector( nodePath + ".CentralityBins" );
			for ( int iCen : cBins ){
				book->clone( "binX_like_sign"        , "bin" + ts( iCen ) + "_like_sign"        );
				book->clone( "binX_unlike_sign"      , "bin" + ts( iCen ) + "_unlike_sign"      );
				book->clone( "binX_like_sign_Pos"    , "bin" + ts( iCen ) + "_like_sign_Pos"    );
				book->clone( "binX_like_sign_Neg"    , "bin" + ts( iCen ) + "_like_sign_Neg"    );
				book->clone( "binX_like_sign_pT"     , "bin" + ts( iCen ) + "_like_sign_pT"     );
				book->clone( "binX_unlike_sign_pT"   , "bin" + ts( iCen ) + "_unlike_sign_pT"   );
				book->clone( "binX_like_sign_Pos_pT" , "bin" + ts( iCen ) + "_like_sign_Pos_pT" );
				book->clone( "binX_like_sign_Neg_pT" , "bin" + ts( iCen ) + "_like_sign_Neg_pT" );

				book->get( "bin" + ts( iCen ) + "_like_sign" )->SetLineColor( kRed );
			}

			book->get( "binX_like_sign"        ) ->SetDirectory( 0 ) ;
			book->get( "binX_unlike_sign"      ) ->SetDirectory( 0 ) ;
			book->get( "binX_like_sign_Pos"    ) ->SetDirectory( 0 ) ;
			book->get( "binX_like_sign_Neg"    ) ->SetDirectory( 0 ) ;
			book->get( "binX_like_sign_pT"     ) ->SetDirectory( 0 ) ;
			book->get( "binX_unlike_sign_pT"   ) ->SetDirectory( 0 ) ;
			book->get( "binX_like_sign_Pos_pT" ) ->SetDirectory( 0 ) ;
			book->get( "binX_like_sign_Neg_pT" ) ->SetDirectory( 0 ) ;



			makeBin16Histos = true;
		}




		INFO( classname(), "Histogram aliasing complete" );
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

	void analyzePair( CandidatePair * pair ){
		TLorentzVector lv;
		lv.SetXYZM( pair->mMomentum_mX1, pair->mMomentum_mX2, pair->mMomentum_mX3, pair->mMass );

		double mass = lv.M();
		double pt = lv.Pt();
		int iBin = dimuonBins.findBin( mass );
		if ( iBin < 0 ) return;

		double bw = dimuonBins.binWidth( iBin );
		double weight = 1.0 / bw;


		if ( pair->mLeadingPt < pairCuts["leadingPt"]->min )
			return;

		if ( abs(pair->mChargeSum) == 2 ){
			h_like_sign->Fill( mass, weight );
			h_like_sign_vs_pt->Fill( mass, pt, weight );

			if ( makeBin16Histos ){
				book->fill( "bin" + ts( centBin ) + "_like_sign", mass, weight );
				book->fill( "bin" + ts( centBin ) + "_like_sign_pT", mass, pt, weight );
			}
			

			if ( 2 == pair->mChargeSum  ){
				book->fill( "like_sign_Pos", mass, 1.0 / bw );
				book->fill( "like_sign_Pos_pT", mass, pt, 1.0/ bw );

				if ( makeBin16Histos ){
					book->fill( "bin" + ts( centBin ) + "_like_sign_Pos", mass, weight );
					book->fill( "bin" + ts( centBin ) + "_like_sign_Pos_pT", mass, pt, weight );
				}

			} else if ( -2 == pair->mChargeSum  ){
				book->fill( "like_sign_Neg", mass, 1.0 / bw );
				book->fill( "like_sign_Neg_pT", mass, pt, 1.0/ bw );

				if ( makeBin16Histos ){
					book->fill( "bin" + ts( centBin ) + "_like_sign_Neg", mass, weight );
					book->fill( "bin" + ts( centBin ) + "_like_sign_Neg_pT", mass, pt, weight );
				}
			}
		} else {
			book->fill( "unlike_sign_y", lv.Rapidity() );
			book->fill( "unlike_sign_eta", lv.Eta() );
			h_unlike_sign->Fill( mass, weight );
			h_unlike_sign_vs_pt->Fill( mass, pt, weight );

			if ( makeBin16Histos ){
				book->fill( "bin" + ts( centBin ) + "_unlike_sign", mass, weight );
				book->fill( "bin" + ts( centBin ) + "_unlike_sign_pT", mass, pt, weight );
			}
		}
	}	


	virtual void postEventLoop(){
		book->cd();
		
		makeGeometricMean();

		
		book->clone( "unlike_sign", "am_signal" );
		book->clone( "unlike_sign", "gm_signal" );
		book->clone( "unlike_sign", "p2_signal" );
		book->clone( "unlike_sign", "n2_signal" );

		book->get("am_signal")->Add( book->get( "like_sign" ), -1 );
		book->get("gm_signal")->Add( book->get( "like_sign_geom" ), -1 );
		book->get("p2_signal")->Add( book->get( "like_sign_Pos" ), -2 );
		book->get("n2_signal")->Add( book->get( "like_sign_Neg" ), -2 );

		vector<int> cBins = config.getIntVector( nodePath+".CentralityBins" );
		for ( int iCen : cBins ){
			makeGeometricMean( "bin" + ts( iCen ) + "_" );
			string prefix = "bin" + ts( iCen ) + "_";


			book->clone( prefix + "unlike_sign", prefix + "am_signal" );
			book->clone( prefix + "unlike_sign", prefix + "gm_signal" );
			book->clone( prefix + "unlike_sign", prefix + "p2_signal" );
			book->clone( prefix + "unlike_sign", prefix + "n2_signal" );

			book->get( prefix + "am_signal")->Add( book->get( prefix + "like_sign" ), -1 );
			book->get( prefix + "gm_signal")->Add( book->get( prefix + "like_sign_geom" ), -1 );
			book->get( prefix + "p2_signal")->Add( book->get( prefix + "like_sign_Pos" ), -2 );
			book->get( prefix + "n2_signal")->Add( book->get( prefix + "like_sign_Neg" ), -2 );

			// book->clone( "bin" + ts( iCen ) + "_unlike_sign", "bin" + ts( iCen ) + "_signal" );
			// TH1 * uls = book->get( "bin" + ts( iCen ) + "_signal" );
			// TH1 * ls = book->get( "bin" + ts( iCen ) + "_like_sign" );

			// uls->Add( ls, -1 );

		}

	}



	virtual void makeGeometricMean( string _prefix = "", string _suffix ="" ){

		TH1 * lsn = book->get( _prefix + "like_sign_Neg" );
		TH1 * lsp = book->get( _prefix + "like_sign_Pos" );
		book->clone( _prefix + "like_sign_Pos", _prefix + "like_sign_geom" );

		for ( int iBin = 1; iBin <= lsn->GetNbinsX(); iBin++ ){
			double bw = lsn->GetBinWidth( iBin );
			book->setBin( 
				_prefix + "like_sign_geom",
				iBin,
				2 * sqrt( lsn->GetBinContent( iBin ) ) * sqrt( lsp->GetBinContent( iBin ) ),
				lsn->GetBinError( iBin )
			 );
		}
	}

protected:
	shared_ptr<CandidatePairTreeReader> pairReader;
	shared_ptr<CandidateEventReader> eventReader;

	TTreeQA pairQA;
	bool makeBin16Histos = false;
};

#endif
