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

		for ( string hn : { "deltaPhi", "m_vs_deltaPhi", "dBL_vs_deltaPhi", "pPhi", "bl1_vs_bl2", "tp1_vs_tp2", "dEta_vs_dPhi", "m_vs_m", "m_vs_deltaBL", "m_vs_deltaEta", "m_vs_deltaES" } ){
			for ( string prefix : { "uls_", "ls_", "lsp_", "lsn_", "piuls_" } ){
				book->clone( hn, prefix + hn );
			}
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

	void fillCutHistos( string prefix, CandidatePair * pair ){
		book->fill( prefix + "_lr", pair->d1_mPid );

		if ( abs(pair->mChargeSum) == 2 ){
			book->fill( prefix + "_ls_lr", pair->d1_mPid );

			if (pair->mChargeSum == 2) {
				book->fill( prefix + "_lsp_lr", pair->d1_mPid );
	
			} else {
				book->fill( prefix + "_lsn_lr", pair->d1_mPid );
	
			}
		} else {
			book->fill( prefix + "_uls_lr", pair->d1_mPid );

		}
	}

	void analyzePair( CandidatePair * pair ){
		TLorentzVector lv, pilv1, pilv2, pilv;
		lv.SetPtEtaPhiM( pair->mMomentum_mPt, pair->mMomentum_mEta, pair->mMomentum_mPhi, pair->mMass );
		pilv1.SetPtEtaPhiM( pair->d1_mMomentum_mPt, pair->d1_mMomentum_mEta, pair->d1_mMomentum_mPhi, 0.139 );
		pilv2.SetPtEtaPhiM( pair->d2_mMomentum_mPt, pair->d2_mMomentum_mEta, pair->d2_mMomentum_mPhi, 0.139 );
		pilv = pilv1 + pilv2;


		double mass = lv.M();
		double pt = lv.Pt();
		
		book->fill( "event_cuts", 0.5 );
	

		int massBin = massBins.findBin( mass );
		int ptBin = ptBins.findBin( mass );	
		if ( massBin < 0 ) return;

		book->fill( "event_cuts", 1.5 );

		double bw = massBins.binWidth( massBin );
		double weight = 1.0;
		// double weight = 1.0 / bw;
		double ptbw = ptBins.binWidth( ptBin );
		// weight = 1.0 / ptbw;

		int bl1 = pair->d1bl();
		int bl2 = pair->d2bl();

		int es1 = pair->d1es();
		int es2 = pair->d2es();

		int dbl = abs(bl1 - bl2); // symmetry around full circle, arbitray which is 1 and which is 2
		if ( dbl > 15 ) dbl = 30 - dbl; 	// symmetry around half circle, ie larges opening angle is pi
		int des = abs( es1 - es2 );
		

		if ( useROI && !roi.inInclusiveRange( mass ) ) return;

		fillCutHistos( "all", pair );

		if ( pair->mLeadingPt < pairCuts["leadingPt"]->min )return;
		book->fill( "event_cuts", 2.5 );
		if ( !pairCuts["y"]->inInclusiveRange( lv.Rapidity() ) ) return;
		book->fill( "event_cuts", 4.5 );



		
		if (  usePidLR && ( !lrCut.inInclusiveRange( pair->d1_mPid ) || !lrCut.inInclusiveRange( pair->d2_mPid ) ) ) 
			return;
		fillCutHistos( "pass", pair );
		book->fill( "event_cuts", 5.5 );

		string prefix = "";
		string prefix2 = "";
		if ( abs(pair->mChargeSum) == 2 ){
			prefix = "ls_";
			h_like_sign->Fill( mass );
			h_like_sign_vs_pt->Fill( mass, pt );

			book->fill( "like_sign_vs_dbl", dbl, mass );
			book->fill( "like_sign_vs_bl", bl1, mass );
			book->fill( "like_sign_vs_bl", bl2, mass );
			book->fill( "like_sign_vs_dbl_des_" + ts( des ), dbl, mass );
			book->fill( "like_sign_vs_des", des, mass );

			book->fill( "like_sign_dbl_vs_des", dbl, des );

			if ( makeBin16Histos ){
				book->fill( "bin" + ts( centBin ) + "_like_sign", mass );
				book->fill( "bin" + ts( centBin ) + "_like_sign_pT", mass, pt );
			}
			

			if ( 2 == pair->mChargeSum  ){
				prefix2 = "lsp_";
				book->fill( "like_sign_Pos", mass );
				book->fill( "like_sign_Pos_pT", mass, pt );

				book->fill( "like_sign_pos_dbl_vs_des", dbl, des );

				if ( makeBin16Histos ){
					book->fill( "bin" + ts( centBin ) + "_like_sign_Pos", mass );
					book->fill( "bin" + ts( centBin ) + "_like_sign_Pos_pT", mass, pt );
				}

			} else if ( -2 == pair->mChargeSum  ){
				prefix2 = "lsn_";
				book->fill( "like_sign_Neg", mass );
				book->fill( "like_sign_Neg_pT", mass, pt );

				book->fill( "like_sign_neg_dbl_vs_des", dbl, des );

				if ( makeBin16Histos ){
					book->fill( "bin" + ts( centBin ) + "_like_sign_Neg", mass );
					book->fill( "bin" + ts( centBin ) + "_like_sign_Neg_pT", mass, pt );
				}
			}
		} else {
			prefix="uls_";
			book->fill( "unlike_sign_y", lv.Rapidity() );
			book->fill( "unlike_sign_eta", lv.Eta() );
			h_unlike_sign->Fill( mass );
			h_unlike_sign_vs_pt->Fill( mass, pt );
			
			book->fill( "unlike_sign_vs_bl", bl1, mass );
			book->fill( "unlike_sign_vs_bl", bl2, mass );


			book->fill( "unlike_sign_vs_dbl", dbl, mass );
			book->fill( "unlike_sign_vs_dbl_des_" + ts( des ), dbl, mass );
			book->fill( "unlike_sign_vs_des", des, mass );

			book->fill( "unlike_sign_dbl_vs_des", dbl, des );

			if ( makeBin16Histos ){
				book->fill( "bin" + ts( centBin ) + "_unlike_sign", mass );
				book->fill( "bin" + ts( centBin ) + "_unlike_sign_pT", mass, pt );
			}
		}

		double dPhi = pair->d1_mMomentum_mPhi - pair->d2_mMomentum_mPhi;
		if ( rnd3.Rndm() > 0.5 )
			dPhi = pair->d2_mMomentum_mPhi - pair->d1_mMomentum_mPhi;
		double dEta = pair->d1_mMomentum_mEta - pair->d2_mMomentum_mEta;
		if ( rnd3.Rndm() > 0.5 )
			dEta = pair->d2_mMomentum_mEta - pair->d1_mMomentum_mEta;;
		for ( string p : { prefix, prefix2 } ){
			if ( "" == p  ) continue;
			book->fill( p + "deltaPhi", dPhi );
			book->fill( p + "m_vs_deltaPhi", dPhi, mass );
			book->fill( p + "m_vs_deltaEta", dEta, mass );
			book->fill( p + "m_vs_deltaBL", dbl, mass );
			book->fill( p + "m_vs_deltaES", des, mass );
			book->fill( p + "dEta_vs_dPhi", dPhi, dEta );
			book->fill( p + "dBL_vs_deltaPhi", dPhi, dbl );
			book->fill( p + "pPhi", lv.Phi() );
		}

		if ( "uls_" == prefix ){
			book->fill( "piuls_m_vs_m", lv.M(), pilv.M()  );
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



		// make the pT slices
		HistoBins bPtProjections( config, "dimuonBins.pTProjections" );
		vector< pair<double, double> > ranges = bPtProjections.subranges();
		
		book->cd();
		// make the 1D dN/dM plots for pT bins 
		vector<string> variants = { "like_sign", "unlike_sign", "like_sign_Pos", "like_sign_Neg" };
		for ( auto prefix : variants ){
			string TName = prefix + "_pT_{min}_to_{max}";
			
			if ( book->exists( TName, "" ) ){
				// ge the 2D
				TH2D * h2 = (TH2D*)book->get2D( prefix + "_pT", "" );
				if ( nullptr == h2  ){ ERROR( classname(), "Cannot get " << prefix + "_pT" ); continue; }

				book->cd( "pT_slices" );

				for (auto r : ranges ){
					// INFO( classname(), "pT subrange : " << r.first << " -> " << r.second );

					XmlString xstr;
					xstr.add( "min", dtes(r.first) );
					xstr.add( "max", dtes(r.second) );
					string hName = xstr.format( TName );
					
					int b1 = h2->GetYaxis( )->FindBin( r.first );
					int b2 = h2->GetYaxis( )->FindBin( r.second );

					TH1D * h1 = h2->ProjectionX( hName.c_str(), b1, b2 );
					book->add( hName, h1 );

					if ( "unlike_sign" != prefix ){
						h1->SetLineColor( kRed );
					}

				}

			}
		}
		book->cd();

		book->cd( "computed" );
		string ssig = config.getXString( nodePath + ".Compute:signal", "gm_signal" );
		// make the S+B etc.
		TH1D * h = (TH1D*)book->get( "signal_bg" );
		TH1D * hSig = (TH1D*)book->get( ssig, "" );
		TH1D * hBg = (TH1D*)book->get( "like_sign", "" );

		h->Reset();
		h->Add( hSig );
		h->Add( hBg );

		h = (TH1D*)book->get( "signal_over_bg" );
		h->Add( hSig );
		h->Divide( hBg );

		h = (TH1D*)book->get( "sqrt_signal_bg" );
		h->Add( hSig );
		h->Add( hBg );
		for ( int i = 1; i <= h->GetNbinsX(); i++ ){
			double bc = h->GetBinContent( i );
			double be = h->GetBinError( i );
			h->SetBinContent( i, sqrt( bc ) );
			h->SetBinError( i, sqrt(be) );
		}

		h = (TH1D*)book->get( "sqrt_signal_2bg" );
		h->Add( hSig );
		h->Add( hBg, 2.0 );
		for ( int i = 1; i <= h->GetNbinsX(); i++ ){
			double bc = h->GetBinContent( i );
			double be = h->GetBinError( i );
			h->SetBinContent( i, sqrt( bc ) );
			h->SetBinError( i, sqrt(be) );
		}

		h = (TH1D*) book->get( "signal_over_sqrt_signal_bg" );
		h->Add( hSig );
		h->Divide( book->get( "sqrt_signal_bg" ) );

		h = (TH1D*) book->get( "signal_over_sqrt_signal_2bg" );
		h->Add( hSig );
		h->Divide( book->get( "sqrt_signal_2bg" ) );


		//  Making Mixed event part
		TH1D * hBpm = (TH1D*)book->get( "unlike_sign", "" );
		TH1D * hBpp = (TH1D*)book->get( "like_sign_Pos", "" );
		TH1D * hBmm = (TH1D*)book->get( "like_sign_Neg", "" );
		TH1D * hBppmm = (TH1D*)book->get( "like_sign", "" );
		book->cd( "mixedEvent" );
		h = (TH1D*) book->get( "am_acorr" );
		h->Add( hBpm );	//B+-
		h->Divide( hBppmm );	// (B++)+(B--)

		// make the geometric mean 
		TH1D * hGm = (TH1D*) book->get( "gmBg" );
		makeGeometricMean( hGm, hBpp, hBmm );

		h = (TH1D*) book->get( "acorr" );
		h->Add( hBpm ); // uls
		h->Divide( hGm );

		TH2D * h2Bpm = (TH2D*)book->get( "unlike_sign_pT", "" );
		TH2D * h2Bpp = (TH2D*)book->get( "like_sign_Pos_pT", "" );
		TH2D * h2Bmm = (TH2D*)book->get( "like_sign_Neg_pT", "" );
		TH2D * h2Bppmm = (TH2D*)book->get( "like_sign_pT", "" );


		h = (TH1D*) book->get( "acorr_pT_vs_m" );
		TH2D * h2Gm = (TH2D*) book->get( "gmBg_pT_vs_m" );
		makeGeometricMean( h2Gm, h2Bpp, h2Bmm );
		
		h->Add( h2Bpm ); // uls
		h->Divide( h2Gm );

		TH2D* h2Am = (TH2D*) book->get( "am_acorr_pT_vs_m" );
		h2Am->Add( h2Bpm ); // uls
		h2Am->Divide( h2Bppmm );





	}

	virtual void makeGeometricMean( TH1*gm, TH1* lsp, TH1* lsn ){
		if ( nullptr == gm || nullptr == lsp || nullptr == lsn ) return;

		int nBins = lsn->GetNbinsX();
		for ( int iBin = 1; iBin <= nBins; iBin++ ){
			
			double Npp = lsp->GetBinContent( iBin );
			double Nmm = lsn->GetBinContent( iBin );

			if ( 0 == Npp || 0 == Nmm ){
				gm->SetBinContent( iBin, 0 );
				gm->SetBinError( iBin, 0 );
				continue;
			}

			double Epp = lsp->GetBinError( iBin ) / Npp;
			double Emm = lsn->GetBinError( iBin ) / Nmm;

			double N = sqrt( Npp * Nmm );
			// Q = x^n  
			// ->
			// dQ/Q = n * dx/x
			double E = (Epp+Emm) * 0.5 * N;
			DEBUGC( "B++ = " << Npp << " +/- " << Epp );
			DEBUGC( "B-- = " << Nmm << " +/- " << Emm );

			DEBUGC( "gm = " << N << " +/- " << E );
			gm->SetBinContent( iBin, N );
			gm->SetBinError( iBin, E );
		}
	}

	virtual void makeGeometricMean( TH2*gm, TH2* lsp, TH2* lsn ){
		if ( nullptr == gm || nullptr == lsp || nullptr == lsn ) return;
		INFOC( "2D Geometric Mean" );

		int nBinsX = lsn->GetNbinsX()  ;
		int nBinsY = lsn->GetNbinsY()  ;

		
		for ( int iBinX = 1; iBinX <= nBinsX; iBinX++ ){
			for ( int iBinY = 1; iBinY <= nBinsY; iBinY++ ){
			
				int iBin = lsp->GetBin( iBinX, iBinY ) ;

				double Npp = lsp->GetBinContent( iBin );
				double Nmm = lsn->GetBinContent( iBin );

				if ( 0 == Npp || 0 == Nmm ){
					gm->SetBinContent( iBin, 0 );
					gm->SetBinError( iBin, 0 );
					continue;
				}

				double Epp = lsp->GetBinError( iBin ) / Npp;
				double Emm = lsn->GetBinError( iBin ) / Nmm;

				double N = sqrt( Npp * Nmm );
				// Q = x^n  
				// ->
				// dQ/Q = n * dx/x
				double E = (Epp+Emm) * 0.5 * N;
				DEBUGC( "B++ = " << Npp << " +/- " << Epp );
				DEBUGC( "B-- = " << Nmm << " +/- " << Emm );

				DEBUGC( "gm = " << N << " +/- " << E );
				gm->SetBinContent( iBin, N );
				gm->SetBinError( iBin, E );
			}
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
