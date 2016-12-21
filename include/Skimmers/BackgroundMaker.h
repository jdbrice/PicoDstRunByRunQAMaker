#ifndef BACKGROUND_MAKER_H
#define BACKGROUND_MAKER_H

#include "HistoAnalyzer.h"
#include "RooPlotLib.h"
#include "Extra/format.h"

class BackgroundMaker : public HistoAnalyzer {
public:
	virtual const char* classname() const { return "BackgroundMaker"; }
	BackgroundMaker() {}
	~BackgroundMaker() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();
	}

protected:

	virtual void make() {
		make1d();
		

		TH1D * hSignal = nullptr;
		double pTWidth = 1.5;
		for ( int i = 0; i < 5; i+=pTWidth ){
			TH1 * h = make1d( i, i + pTWidth );
			if ( nullptr == hSignal ){
				hSignal = (TH1D*) h->Clone( "signal" );
			} else {
				hSignal->Add( h );
			}
		}

	}


	TH1* make1d( double min, double max ){
		TH2D * mixed_pos_2d = (TH2D*)get2D( "like_sign_Pos_pT", "mixed" );
		TH2D * mixed_neg_2d = (TH2D*)get2D( "like_sign_Neg_pT", "mixed" );
		TH2D * mixed_us_2d = (TH2D*)get2D( "unlike_sign_pT", "mixed" );

		TH2D * same_pos_2d = (TH2D*)get2D( "like_sign_Pos_pT", "same" );
		TH2D * same_neg_2d = (TH2D*)get2D( "like_sign_Neg_pT", "same" );

		if ( nullptr == mixed_pos_2d ) { ERROR( classname(), "NULL histo in mixed" ); return nullptr; }
		if ( nullptr == mixed_neg_2d ) { ERROR( classname(), "NULL histo in mixed" ); return nullptr; }
		if ( nullptr == mixed_us_2d ) { ERROR( classname(), "NULL histo in mixed" ); return nullptr; }
		if ( nullptr == same_pos_2d ) { ERROR( classname(), "NULL histo in same" ); return nullptr; }
		if ( nullptr == same_pos_2d ) { ERROR( classname(), "NULL histo in same" ); return nullptr; }

		book->cd( "2D" );
		TAxis * y =mixed_pos_2d->GetYaxis();

		int bin1 = y->FindBin( min );
		int bin2 = y->FindBin( max );
		string tName = "{0}_1d_pT_{1}_to_{2}";

		TH1D * mixed_pos_1d = mixed_pos_2d->ProjectionX( fmt::format( tName, "mixed_pos", min, max ).c_str(), bin1, bin2 );
		TH1D * mixed_neg_1d = mixed_neg_2d->ProjectionX( fmt::format( tName, "mixed_neg", min, max ).c_str(), bin1, bin2 );
		TH1D * mixed_us_1d = mixed_us_2d->ProjectionX( fmt::format( tName, "mixed_us", min, max ).c_str(), bin1, bin2 );
		TH1D * same_pos_1d = same_pos_2d->ProjectionX( fmt::format( tName, "same_pos", min, max ).c_str(), bin1, bin2 );
		TH1D * same_neg_1d = same_neg_2d->ProjectionX( fmt::format( tName, "same_neg", min, max ).c_str(), bin1, bin2 );

		string n_geom_mean_bg = fmt::format("geom_mean_bg_pT_{0}_to_{1}",     min, max );
		book->addClone( n_geom_mean_bg, mixed_pos_1d );

		string n_geom_mean_acorr = fmt::format("geom_mean_acorr_pT_{0}_to_{1}",  min, max );
		book->addClone( n_geom_mean_acorr, mixed_pos_1d );

		string n_arith_mean_bg = fmt::format("arith_mean_bg_pT_{0}_to_{1}",    min, max );
		book->addClone( n_arith_mean_bg, mixed_pos_1d );

		string n_arith_mean_acorr = fmt::format("arith_mean_acorr_pT_{0}_to_{1}", min, max );
		book->addClone( n_arith_mean_acorr, mixed_pos_1d );
		
		string n_direct_sum_bg = fmt::format("direct_sum_bg_pT_{0}_to_{1}", min, max);
		book->addClone( n_direct_sum_bg, mixed_pos_1d );

		string n_mixed_event_us_over_ls = fmt::format("mixed_event_us_over_ls_pT_{0}_to_{1}", min, max);
		book->addClone( n_mixed_event_us_over_ls, mixed_pos_1d );

		// book->add( "raw_signal", (TH1D*) get1D( "unlike_sign", "same" )->Clone( "raw_signal" ) );
		string n_signal_minus_geom_mean_bg = fmt::format( "signal_minus_geom_mean_bg_pT_{0}_to_{1}", min, max);
		book->addClone( n_signal_minus_geom_mean_bg, get2D( "unlike_sign_pT", "same" )->ProjectionX( "px", bin1, bin2 ) );

		string n_raw_signal = fmt::format( "raw_signal_pT_{0}_to_{1}", min, max);
		book->addClone( n_raw_signal, get2D( "unlike_sign_pT", "same" )->ProjectionX( "px", bin1, bin2 ) );

		RooPlotLib rpl;
		rpl.link( book );

		// set the titles and colors for easy drawing
		rpl.style( n_geom_mean_bg )
			.set( "title", "Geometric Mean BG; M_{#mu#mu} [GeV/c^{2}]; dN/dM" )
			.set( "color", kRed );
		rpl.style( n_arith_mean_bg )
			.set( "title", "Arithmetic Mean BG; M_{#mu#mu} [GeV/c^{2}]; dN/dM" )
			.set( "color", kBlue );
		rpl.style( n_direct_sum_bg )
			.set( "title", "Direct Sum BG; M_{#mu#mu} [GeV/c^{2}]; dN/dM" )
			.set( "color", kGreen );

		for ( int iBin = 1; iBin <= mixed_pos_1d->GetNbinsX(); iBin++ ){

			double n_mixed_pos = mixed_pos_1d->GetBinContent( iBin );
			double n_mixed_neg = mixed_neg_1d->GetBinContent( iBin );
			double n_same_pos  = same_pos_1d->GetBinContent( iBin );
			double n_same_neg  = same_neg_1d->GetBinContent( iBin );
			double n_mixed_us  = mixed_us_1d->GetBinContent( iBin );

			TRACE( classname(), "iBin = " << iBin );
			TRACE( classname(), "n_mixed_pos = " << n_mixed_pos );
			TRACE( classname(), "n_mixed_neg = " << n_mixed_neg );
			TRACE( classname(), "n_same_pos = " << n_same_pos );
			TRACE( classname(), "n_same_neg = " << n_same_neg );
			TRACE( classname(), "n_mixed_us = " << n_mixed_us );
			
			double geom_acorr = 1.0;
			if ( 0 < n_mixed_pos * n_mixed_neg )
				geom_acorr = ( n_mixed_us / sqrt( n_mixed_pos * n_mixed_neg ) );
			double geom_bg = sqrt( n_same_pos * n_same_neg ) * geom_acorr;

			double arith_acorr = 1.0;
			if (  0 < n_mixed_pos + n_mixed_neg )
				arith_acorr = ( n_mixed_us / ( n_mixed_pos + n_mixed_neg ) );
			double arith_mean_bg = (n_same_pos + n_same_neg) * arith_acorr;

			book->setBin( n_geom_mean_bg, iBin, geom_bg, sqrt( geom_bg ) );
			book->setBin( n_geom_mean_acorr, iBin, geom_acorr, sqrt( geom_acorr ) );
			book->setBin( n_arith_mean_bg, iBin, arith_mean_bg, sqrt( arith_mean_bg ) );
			book->setBin( n_arith_mean_acorr, iBin, arith_acorr, sqrt( arith_acorr ) );
			book->setBin( n_direct_sum_bg, iBin, n_same_pos + n_same_neg, sqrt( n_same_pos + n_same_neg ) );

			book->setBin( n_mixed_event_us_over_ls, iBin, n_mixed_us / ( n_mixed_pos + n_mixed_neg ), 1e-10 );
		}

		book->get( n_signal_minus_geom_mean_bg )->Add( book->get( n_geom_mean_bg ), -1 );

		HistoBook::weightByBinWidth( book->get( n_signal_minus_geom_mean_bg ) );
		return (TH1*)book->get( n_signal_minus_geom_mean_bg );

	}


	virtual void make1d(){
		INFO( classname(), "" );

		TH1D * mixed_pos_1d = (TH1D*)get1D( "like_sign_Pos", "mixed" );
		TH1D * mixed_neg_1d = (TH1D*)get1D( "like_sign_Neg", "mixed" );
		TH1D * mixed_us_1d = (TH1D*)get1D( "unlike_sign", "mixed" );

		TH1D * same_pos_1d = (TH1D*)get1D( "like_sign_Pos", "same" );
		TH1D * same_neg_1d = (TH1D*)get1D( "like_sign_Neg", "same" );

		if ( nullptr == mixed_pos_1d ) { ERROR( classname(), "NULL histo in mixed" ); return; }
		if ( nullptr == mixed_neg_1d ) { ERROR( classname(), "NULL histo in mixed" ); return; }
		if ( nullptr == mixed_us_1d ) { ERROR( classname(), "NULL histo in mixed" ); return; }
		if ( nullptr == same_pos_1d ) { ERROR( classname(), "NULL histo in same" ); return; }
		if ( nullptr == same_pos_1d ) { ERROR( classname(), "NULL histo in same" ); return; }

		int rbX = config.getInt( nodePath + ".Bg1d:rebinX", 1 );
		mixed_pos_1d->RebinX( rbX );
		mixed_neg_1d->RebinX( rbX );
		mixed_us_1d->RebinX( rbX );
		same_pos_1d->RebinX( rbX );
		same_neg_1d->RebinX( rbX );


		book->cd();
		book->add( "geom_mean_bg",     (TH1D*) mixed_pos_1d->Clone( "geom_mean_bg" ) );
		book->add( "geom_mean_acorr",  (TH1D*) mixed_pos_1d->Clone( "geom_mean_acorr" ) );
		book->add( "arith_mean_bg",    (TH1D*) mixed_pos_1d->Clone( "arith_mean_bg" ) );
		book->add( "arith_mean_acorr", (TH1D*) mixed_pos_1d->Clone( "arith_mean_acorr" ) );
		book->add( "direct_sum_bg",    (TH1D*) mixed_pos_1d->Clone( "direct_sum_bg" ) );

		book->add( "mixed_event_us_over_ls",    (TH1D*) mixed_pos_1d->Clone( "mixed_event_us_over_ls" ) );

		book->add( "raw_signal", (TH1D*) get1D( "unlike_sign", "same" )->Clone( "raw_signal" ) );
		book->add( "signal_minus_geom_mean", (TH1D*) get1D( "unlike_sign", "same" )->Clone( "signal_minus_geom_mean" ) );

		book->get( "raw_signal" )->RebinX( rbX );
		book->get( "signal_minus_geom_mean" )->RebinX( rbX );

		RooPlotLib rpl;
		rpl.link( book );

		// set the titles and colors for easy drawing
		rpl.style( "geom_mean_bg" )
			.set( "title", "Geometric Mean BG; M_{#mu#mu} [GeV/c^{2}]; dN/dM" )
			.set( "color", kRed );
		rpl.style( "arith_mean_bg" )
			.set( "title", "Arithmetic Mean BG; M_{#mu#mu} [GeV/c^{2}]; dN/dM" )
			.set( "color", kBlue );
		rpl.style( "direct_sum_bg" )
			.set( "title", "Direct Sum BG; M_{#mu#mu} [GeV/c^{2}]; dN/dM" )
			.set( "color", kGreen );

		for ( int iBin = 1; iBin <= mixed_pos_1d->GetNbinsX(); iBin++ ){

			double n_mixed_pos = mixed_pos_1d->GetBinContent( iBin );
			double n_mixed_neg = mixed_neg_1d->GetBinContent( iBin );
			double n_same_pos  = same_pos_1d->GetBinContent( iBin );
			double n_same_neg  = same_neg_1d->GetBinContent( iBin );
			double n_mixed_us  = mixed_us_1d->GetBinContent( iBin );

			TRACE( classname(), "iBin = " << iBin );
			TRACE( classname(), "n_mixed_pos = " << n_mixed_pos );
			TRACE( classname(), "n_mixed_neg = " << n_mixed_neg );
			TRACE( classname(), "n_same_pos = " << n_same_pos );
			TRACE( classname(), "n_same_neg = " << n_same_neg );
			TRACE( classname(), "n_mixed_us = " << n_mixed_us );
			
			double geom_acorr = 1.0;
			if ( 0 < n_mixed_pos * n_mixed_neg )
				geom_acorr = ( n_mixed_us / sqrt( n_mixed_pos * n_mixed_neg ) );
			double geom_bg = sqrt( n_same_pos * n_same_neg ) * geom_acorr;

			TRACE( classname(), "geom_sum = " << geom_bg  );

			double arith_acorr = 1.0;
			if (  0 < n_mixed_pos + n_mixed_neg )
				arith_acorr = ( n_mixed_us / ( n_mixed_pos + n_mixed_neg ) );
			double arith_mean_bg = (n_same_pos + n_same_neg) * arith_acorr;

			book->setBin( "geom_mean_bg", iBin, geom_bg, sqrt( geom_bg ) );
			book->setBin( "geom_mean_acorr", iBin, geom_acorr, sqrt( geom_acorr ) );
			book->setBin( "arith_mean_bg", iBin, arith_mean_bg, sqrt( arith_mean_bg ) );
			book->setBin( "arith_mean_acorr", iBin, arith_acorr, sqrt( arith_acorr ) );
			book->setBin( "direct_sum_bg", iBin, n_same_pos + n_same_neg, sqrt( n_same_pos + n_same_neg ) );

			book->setBin( "mixed_event_us_over_ls", iBin, n_mixed_us / ( n_mixed_pos + n_mixed_neg ), 1e-10 );
		}


		book->clone( "geom_mean_bg", "geom_over_arith_bg" );
		book->clone( "geom_mean_bg", "geom_over_sum_bg" );
		book->clone( "arith_mean_bg", "arith_over_sum_bg" );

		rpl.style( "geom_over_arith_bg" ).set( "title", ";M_{#mu#mu} [GeV/c^{2}];Geometric / Arithmetic" );
		rpl.style( "geom_over_sum_bg" ).set( "title", ";M_{#mu#mu} [GeV/c^{2}];Geometric / Sum" );
		rpl.style( "arith_over_sum_bg" ).set( "title", ";M_{#mu#mu} [GeV/c^{2}];Arithmetic / Sum" );

		book->get( "geom_over_arith_bg" )->Divide( book->get( "arith_mean_bg" ) );
		book->get( "geom_over_sum_bg" )->Divide( book->get( "direct_sum_bg" ) );
		book->get( "arith_over_sum_bg" )->Divide( book->get( "direct_sum_bg" ) );

		book->get( "signal_minus_geom_mean" )->Add( book->get( "geom_mean_bg" ), -1 );

		book->addClone( "signal_over_geom_mean", book->get( "signal_minus_geom_mean" ) );
		book->get( "signal_over_geom_mean" )->Divide( book->get( "geom_mean_bg" ) );


	}
	
};

#endif	