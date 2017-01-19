#ifndef MTD_GEOMETRY_WEIGHT_MAP_MAKER_H
#define MTD_GEOMETRY_WEIGHT_MAP_MAKER_H

#include "HistoAnalyzer.h"
#include "RooPlotLib.h"
using namespace jdb;




class MtdGeometryWeightMapMaker : public HistoAnalyzer
{
public:
	MtdGeometryWeightMapMaker() {}
	~MtdGeometryWeightMapMaker() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();
	}

	TH1D * getComponent( int dbl, int des, string prefix = "unlike_sign" ){

		TH2D * mom = get<TH2D>( prefix + "_vs_dbl_des_" + ts( des ) );
		if ( nullptr == mom ){
			ERRORC( "null histo! dbl=" << dbl << ", des=" << des << ", prefix=" << quote(prefix) );
			return nullptr;
		}
		string name = prefix + "_dbl_" + ts(dbl) + "_des_" + ts( des );
		TH1D * h = mom->ProjectionY( name.c_str(), dbl+1, dbl+1 );

		// scale it by it's weight factor
		string sprefix = "uls";
		if ( "like_sign" == prefix ) sprefix = "ls";
		if ( "like_sign_pos" == prefix ) sprefix = "ls_pos";
		if ( "like_sign_neg" == prefix ) sprefix = "ls_neg";

		sprefix="ls";
		double weight = book->get( sprefix + "_weights" )->GetBinContent( dbl+1, des+1 );
		// weight = 1.0;
		h->Scale( weight );

		return h;
	}

	virtual void make(){

		RooPlotLib rpl;

		rpl.link( book );
		
		TH2D* se_uls = get<TH2D>( "unlike_sign_dbl_vs_des", "same_event" );
		TH2D* me_uls = get<TH2D>( "unlike_sign_dbl_vs_des", "mixed_event" );

		TH2D* se_ls = get<TH2D>( "like_sign_dbl_vs_des", "same_event" );
		TH2D* me_ls = get<TH2D>( "like_sign_dbl_vs_des", "mixed_event" );

		TH2D* se_ls_pos = get<TH2D>( "like_sign_pos_dbl_vs_des", "same_event" );
		TH2D* me_ls_pos = get<TH2D>( "like_sign_pos_dbl_vs_des", "mixed_event" );

		TH2D* se_ls_neg = get<TH2D>( "like_sign_neg_dbl_vs_des", "same_event" );
		TH2D* me_ls_neg = get<TH2D>( "like_sign_neg_dbl_vs_des", "mixed_event" );
		if ( nullptr == se_uls || nullptr == me_uls || nullptr == se_ls_pos || nullptr == me_ls_pos || nullptr == se_ls_neg || nullptr == me_ls_neg  || nullptr == se_ls || nullptr == me_ls ){
			ERRORC( "NULL histograms" );
			return;
		}
		se_uls->Scale( 1.0 / se_uls->Integral() );
		me_uls->Scale( 1.0 / me_uls->Integral() );

		se_ls_pos->Scale( 1.0 / se_ls_pos->Integral() );
		me_ls_pos->Scale( 1.0 / me_ls_pos->Integral() );

		se_ls_neg->Scale( 1.0 / se_ls_neg->Integral() );
		me_ls_neg->Scale( 1.0 / me_ls_neg->Integral() );

		se_ls->Scale( 1.0 / se_ls->Integral() );
		me_ls->Scale( 1.0 / me_ls->Integral() );

		book->cd();
		book->addClone( "se_uls", se_uls );
		book->addClone( "me_uls", me_uls );
		book->addClone( "uls_weights", se_uls );
		book->get( "uls_weights" )->Divide( me_uls );

		book->addClone( "se_ls", se_ls );
		book->addClone( "me_ls", me_ls );
		book->addClone( "ls_weights", se_ls );
		book->get( "ls_weights" )->Divide( me_ls );

		book->addClone( "se_ls_pos", se_ls_pos );
		book->addClone( "me_ls_pos", me_ls_pos );
		book->addClone( "ls_pos_weights", se_ls_pos );
		book->get( "ls_pos_weights" )->Divide( me_ls_pos );

		book->addClone( "se_ls_neg", se_ls_neg );
		book->addClone( "me_ls_neg", me_ls_neg );
		book->addClone( "ls_neg_weights", se_ls_neg );
		book->get( "ls_neg_weights" )->Divide( me_ls_neg );

		//  Clone the unlike sign for the new ones
		book->addClone( "corr_signal", get<TH1D>( "unlike_sign", "same_event" ) );
		book->addClone( "raw_signal", get<TH1D>( "unlike_sign", "same_event" ) );
		book->addClone( "unweighted_uls_mass", get<TH1D>( "unlike_sign", "mixed_event" ) );
		book->addClone( "unweighted_over_weighted_uls_mass", get<TH1D>( "unlike_sign", "mixed_event" ) );
		book->addClone( "uls_mass", get<TH1D>( "unlike_sign", "mixed_event" ) );
		book->get( "uls_mass" )->Reset();

		book->addClone( "raw_ls_mass", get<TH1D>( "like_sign", "same_event" ) );
		book->addClone( "acorr_ls_mass", get<TH1D>( "like_sign", "same_event" ) );
		book->addClone( "unweighted_ls_mass", get<TH1D>( "like_sign", "mixed_event" ) );
		book->addClone( "unweighted_over_weighted_ls_mass", get<TH1D>( "like_sign", "mixed_event" ) );
		book->addClone( "ls_mass", get<TH1D>( "like_sign", "mixed_event" ) );
		book->get( "ls_mass" )->Reset();

		// Clone the like sign pos
		book->addClone( "unweighted_ls_pos_mass", get<TH1D>( "like_sign_Pos", "mixed_event" ) );
		book->addClone( "unweighted_over_weighted_ls_pos_mass", get<TH1D>( "like_sign_Pos", "mixed_event" ) );
		book->addClone( "ls_pos_mass", get<TH1D>( "like_sign_Pos", "mixed_event" ) );
		book->get( "ls_pos_mass" )->Reset();

		book->addClone( "unweighted_ls_neg_mass", get<TH1D>( "like_sign_Neg", "mixed_event" ) );
		book->addClone( "unweighted_over_weighted_ls_neg_mass", get<TH1D>( "like_sign_Neg", "mixed_event" ) );
		book->addClone( "ls_neg_mass", get<TH1D>( "like_sign_Neg", "mixed_event" ) );
		book->get( "ls_neg_mass" )->Reset();


		for ( int dbl = 0; dbl < 16; dbl++ ){
			for ( int des = 0; des < 5; des++ ){

				TH1D * ulsComp = getComponent( dbl, des, "unlike_sign" );
				if ( nullptr != ulsComp )
					book->get("uls_mass")->Add( ulsComp );

				TH1D * lsComp = getComponent( dbl, des, "like_sign" );
				if ( nullptr != lsComp )
					book->get("ls_mass")->Add( lsComp );

				// TH1D * lspComp = getComponent( dbl, des, "like_sign_pos" );
				// book->get("ls_pos_mass")->Add( lspComp );

				// TH1D * lsnComp = getComponent( dbl, des, "like_sign_neg" );
				// book->get("ls_neg_mass")->Add( lsnComp );
			}
		}

		rpl.style( "unweighted_uls_mass" ).set( "lc", "red" ).set( "markercolor", "red" );
		book->get( "unweighted_over_weighted_uls_mass" )->Divide( book->get( "uls_mass" ) );

		rpl.style( "ls_mass" ).set( "lc", "blue" ).set( "markercolor", "blue" );
		rpl.style( "unweighted_ls_mass" ).set( "lc", "red" ).set( "markercolor", "red" );
		book->get( "unweighted_over_weighted_ls_mass" )->Divide( book->get( "ls_mass" ) );

		book->clone( "uls_mass", "acorr" );

		book->get( "acorr" )->Divide( book->get("ls_mass") );

		book->get( "acorr_ls_mass" )->Multiply( book->get( "acorr" ) );

		book->get( "corr_signal" )->Add( book->get("acorr_ls_mass"), -1 );




	}
	
};



#endif