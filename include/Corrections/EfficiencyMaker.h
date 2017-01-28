#ifndef EFFICIENCY_MAKER_H
#define EFFICIENCY_MAKER_H

#include "HistoAnalyzer.h"
using namespace jdb;



class EfficiencyMaker : public HistoAnalyzer
{
public:
	virtual const char* classname() const { return "EfficiencyMaker"; }
	EfficiencyMaker() {}
	~EfficiencyMaker() {}

	virtual void initialize(){

	}

	virtual void make(){

		// 5 = mu+
		// 6 = mu-

		// Get Embedding tables
		// Rebin
		// Divide

		book->cd();
		HistoBins bPt, bEta, bPhi;
		bPt.load( config, "bins.pT" );
		bEta.load( config, "bins.eta" );
		bPhi.load( config, "bins.phi" );

		TH3* hMc5 = get<TH3>( "mc_5_PtEtaPhi" );
		TH3* hRc5 = get<TH3>( "rc_5_PtEtaPhi" );
		TH3* hMtd5 = get<TH3>( "mtd_5_PtEtaPhi" );

		// pT vs. eta = xy
		TH2 * hMc5_PtEta  = HistoBins::rebin2D( "mc5_PtEta"  , (TH2*)hMc5->Project3D( "xy" )  , bEta , bPt );
		TH2 * hRc5_PtEta  = HistoBins::rebin2D( "rc5_PtEta"  , (TH2*)hRc5->Project3D( "xy" )  , bEta , bPt );
		TH2 * hMtd5_PtEta = HistoBins::rebin2D( "mtd5_PtEta" , (TH2*)hMtd5->Project3D( "xy" ) , bEta , bPt );


		TH2 * eff5_PtEta = (TH2*)book->addClone( "eff_5_PtEta", hMtd5_PtEta );
		eff5_PtEta->Divide( hMc5_PtEta );




		TH3* hMc6 = get<TH3>( "mc_6_PtEtaPhi" );
		TH3* hRc6 = get<TH3>( "rc_6_PtEtaPhi" );
		TH3* hMtd6 = get<TH3>( "mtd_6_PtEtaPhi" );

		// pT vs. eta = xy
		TH2 * hMc6_PtEta  = HistoBins::rebin2D( "mc6_PtEta"  , (TH2*)hMc6->Project3D( "xy" )  , bEta , bPt );
		TH2 * hRc6_PtEta  = HistoBins::rebin2D( "rc6_PtEta"  , (TH2*)hRc6->Project3D( "xy" )  , bEta , bPt );
		TH2 * hMtd6_PtEta = HistoBins::rebin2D( "mtd6_PtEta" , (TH2*)hMtd6->Project3D( "xy" ) , bEta , bPt );


		TH2 * eff6_PtEta = (TH2*)book->addClone( "eff_6_PtEta", hMtd6_PtEta );
		eff6_PtEta->Divide( hMc6_PtEta );


	}
protected:
	
};


#endif