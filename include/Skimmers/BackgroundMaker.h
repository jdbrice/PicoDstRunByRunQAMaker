#ifndef BACKGROUND_MAKER_H
#define BACKGROUND_MAKER_H

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

		INFO( classname(), "got " << mixed_pos_1d );

		book->cd();
		book->add( "geom_mean_bg", mixed_pos_1d->Clone( "geom_mean_bg" ) );
		book->add( "geom_mean_acorr", mixed_pos_1d->Clone( "geom_mean_acorr" ) );
		book->add( "direct_sum_bg", mixed_pos_1d->Clone( "direct_sum_bg" ) );
		book->add( "direct_sum_acorr", mixed_pos_1d->Clone( "direct_sum_acorr" ) );

		for ( int iBin = 1; iBin <= mixed_pos_1d->GetNbinsX(); iBin++ ){

			int n_mixed_pos = mixed_pos_1d->GetBinContent( iBin );
			int n_mixed_neg = mixed_neg_1d->GetBinContent( iBin );
			int n_same_pos = same_pos_1d->GetBinContent( iBin );
			int n_same_neg = same_neg_1d->GetBinContent( iBin );
			int n_mixed_us = mixed_us_1d->GetBinContent( iBin );
			

			double geom_bg = sqrt( n_same_pos * n_same_neg ) * ( n_mixed_us / sqrt( n_mixed_pos * n_mixed_neg ) );
			double direct_sum_bg = (n_same_pos + n_same_neg) * ( n_mixed_us / ( n_mixed_pos + n_mixed_neg ) );

			book->setBinContent( "geom_mean_bg", iBin, geom_bg );
			book->setBinContent( "direct_sum_bg", iBin, direct_sum_bg );

		}


	}
	
};

#endif	