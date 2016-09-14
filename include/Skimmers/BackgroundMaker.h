#ifndef BACKGROUND_MAKER_H
#define BACKGROUND_MAKER_H

#include "HistoAnalyzer.h"
#include "RooPlotLib.h"

class BackgroundMaker : public HistoAnalyzer {
public:
	virtual const char* classname() const { return "BackgroundMaker"; }
	BackgroundMaker() {}
	~BackgroundMaker() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();
	}

protected:


	virtual void make(){
		INFO( classname(), "" );

		TH1 * mixed_pos_1d = get1D( "like_sign_Pos", "mixed" );
		TH1 * mixed_neg_1d = get1D( "like_sign_Neg", "mixed" );
		TH1 * mixed_us_1d = get1D( "unlike_sign", "mixed" );
		TH1 * same_pos_1d = get1D( "like_sign_Pos", "same" );
		TH1 * same_neg_1d = get1D( "like_sign_Neg", "same" );

		book->cd();
		book->add( "geom_mean_bg",     (TH1*) mixed_pos_1d->Clone( "geom_mean_bg" ) );
		book->add( "geom_mean_acorr",  (TH1*) mixed_pos_1d->Clone( "geom_mean_acorr" ) );
		book->add( "arith_mean_bg",    (TH1*) mixed_pos_1d->Clone( "arith_mean_bg" ) );
		book->add( "arith_mean_acorr", (TH1*) mixed_pos_1d->Clone( "arith_mean_acorr" ) );
		book->add( "direct_sum_bg",    (TH1*) mixed_pos_1d->Clone( "direct_sum_bg" ) );

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
			
			double geom_acorr = 1.0;
			if ( 0 < n_mixed_pos * n_mixed_neg )
				geom_acorr = ( n_mixed_us / sqrt( n_mixed_pos * n_mixed_neg ) );
			double geom_bg = sqrt( n_same_pos * n_same_neg ) * geom_acorr;

			double arith_acorr = 1.0;
			if (  0 < n_mixed_pos + n_mixed_neg )
				arith_acorr = ( n_mixed_us / ( n_mixed_pos + n_mixed_neg ) );
			double arith_mean_bg = (n_same_pos + n_same_neg) * arith_acorr;

			book->setBin( "geom_mean_bg", iBin, geom_bg, sqrt( geom_bg ) );
			book->setBin( "geom_mean_acorr", iBin, geom_acorr, sqrt( geom_acorr ) );
			book->setBin( "arith_mean_bg", iBin, arith_mean_bg, sqrt( arith_mean_bg ) );
			book->setBin( "arith_mean_acorr", iBin, arith_acorr, sqrt( arith_acorr ) );
			book->setBin( "direct_sum_bg", iBin, n_same_pos + n_same_neg, sqrt( n_same_pos + n_same_neg ) );
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


	}
	
};

#endif	