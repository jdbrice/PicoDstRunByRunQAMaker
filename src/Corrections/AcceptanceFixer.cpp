#include "AcceptanceFixer.h"
#include "TF1.h"

void AcceptanceFixer::makeGeometricMean( TH1*gm, TH1* lsp, TH1* lsn ){
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

		double N = 2 * sqrt( Npp * Nmm ); // includes the factor of 2!!!
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

void AcceptanceFixer::makeGeometricMean( TH2*gm, TH2* lsp, TH2* lsn ){
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

			double N = 2 * sqrt( Npp * Nmm ); // includes factor of 2!!!
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

void AcceptanceFixer::multiplyBinByBin( TH1 * A, TH1 * B ){
	
	int nBinsX = A->GetNbinsX()  ;
	int nBinsY = A->GetNbinsY()  ;

	for ( int iBinX = 1; iBinX <= nBinsX; iBinX++ ){
		for ( int iBinY = 1; iBinY <= nBinsY; iBinY++ ){
		
			int iBin = A->GetBin( iBinX, iBinY ) ;

			double NA = A->GetBinContent( iBin );
			double EA = A->GetBinContent( iBin ) / NA;
			double NB = B->GetBinContent( iBin );
			double EB = 0;//B->GetBinContent( iBin ) / NB;

			if ( 0 >= NA ) EA = 0;
			if ( 0 >= NB ) EB = 0;

			double N = NA * NB;
			double E = sqrt( N );//(EA + EB) * N;



			A->SetBinContent( iBin,N );
			A->SetBinError( iBin,E );
		}
	}
}

void AcceptanceFixer::applyTriggerPatchCorr( TH1* _sig, TH1* _tpcorr ){
	vector<double> sig = HistoBook::contentVector( _sig );
	vector<double> sige = HistoBook::errorVector( _sig );
	vector<double> tpc = HistoBook::contentVector( _tpcorr );;

	for ( int i = 0; i < sig.size(); i++ ){
		if ( 0.0 == sig[i] || 0.0 == tpc[i] ) {
			sig[i] = 0.0;
			sige[i] = 0.0;
		} else {
			sig[i] = sig[i] * ( 1.0 / tpc[i] );
			sige[i] = sige[i] * ( 1.0 / tpc[i] );
		}
	}

	// overwrite with new contents, dont change errors
	HistoBook::writeVector( _sig, sig, sige );
}

void AcceptanceFixer::applyTriggerPatchCorr( TH2* _sig, TH2* _tpcorr ){
	vector<double> sig = HistoBook::contentVector( _sig );
	vector<double> sige = HistoBook::errorVector( _sig );
	vector<double> tpc = HistoBook::contentVector( _tpcorr );;

	for ( int i = 0; i < sig.size(); i++ ){
		if ( 0.0 == sig[i] || 0.0 == tpc[i] ) {
			sig[i] = 0.0;
			sige[i] = 0.0;
		} else {
			sig[i] = sig[i] * ( 1.0 / tpc[i] );
			sige[i] = sige[i] * ( 1.0 / tpc[i] );
		}
	}

	// overwrite with new contents, dont change errors
	HistoBook::writeVector( _sig, sig );
}

void AcceptanceFixer::makeMass1D(){

	book->cd( "mass1D" );
	HistoBins bMass, bPt;
	bMass.load( config, "dimuonBins.signalMass" );
	bPt.load( config, "dimuonBins.signalPt" );

	INFOC( "Signal Mass bins: " << bMass.toString() );
	INFOC( "Signal pT bins: " << bPt.toString() );

	// make the mixed event acorr
	TH1D * hBpm   = get<TH1D>( "uls_dNdM"   , "ME" );
	TH1D * hBpp   = get<TH1D>( "lsp_dNdM" , "ME" );
	TH1D * hBmm   = get<TH1D>( "lsn_dNdM" , "ME" );
	TH1D * hBppmm = get<TH1D>( "ls_dNdM"     , "ME" );

	hBpm          = (TH1D*)hBpm->Rebin(   bMass.nBins(), "Bpm",   bMass.bins.data() );
	hBpp          = (TH1D*)hBpp->Rebin(   bMass.nBins(), "Bpp",   bMass.bins.data() );
	hBmm          = (TH1D*)hBmm->Rebin(   bMass.nBins(), "Bmm",   bMass.bins.data() );
	hBppmm        = (TH1D*)hBppmm->Rebin( bMass.nBins(), "Bppmm", bMass.bins.data() );

	// arithmetic mean
	TH1* h = nullptr;

	INFOC( "Arithmetic mean" );
	TH1* meam = book->addClone( "meam", hBppmm );
	meam->Scale( 0.5 );

	INFOC( "Arithmetic mean Acceptance Correction" );
	TH1 * amac = book->addClone( "amac", hBpm );
	amac->Divide( meam );

	//geometric mean
	INFOC( "Geometric mean" );
	TH1 * gmac = book->addClone( "gmac", hBpm );
	TH1* megm = book->addClone( "megm", hBpm );
	megm->Reset();
	makeGeometricMean( megm, hBpp, hBmm );
	megm->Scale( 2.0 );
	INFOC( "Geometric mean Acceptance Correction" );
	gmac->Divide( megm );

	// same event arithmetic mean
	TH1 * hNpm   = get<TH1D>( "uls_dNdM" , "SE" );
	TH1 * hNpp   = get<TH1D>( "lsp_dNdM" , "SE" );
	TH1 * hNmm   = get<TH1D>( "lsn_dNdM" , "SE" );
	TH1 * hNppmm = get<TH1D>( "ls_dNdM"  , "SE" );

	hNpm          = (TH1D*)hNpm->Rebin( bMass.nBins()   , "Npm"   , bMass.bins.data() );
	hNpp          = (TH1D*)hNpp->Rebin( bMass.nBins()   , "Npp"   , bMass.bins.data() );
	hNmm          = (TH1D*)hNmm->Rebin( bMass.nBins()   , "Nmm"   , bMass.bins.data() );
	hNppmm        = (TH1D*)hNppmm->Rebin( bMass.nBins() , "Nppmm" , bMass.bins.data() );

	TH1* seam = book->addClone( "seam", hNppmm );
	seam->Scale( 0.5 );

	TH1* segm = book->addClone( "segm", hBpm );
	segm->Reset();
	makeGeometricMean( segm, hNpp, hNmm );
	segm->Scale( 2.0 );

	TH1 *bgam = book->addClone( "bgam", seam );
	multiplyBinByBin( bgam, amac );

	TH1 *bggm = book->addClone( "bggm", segm );
	// multiplyBinByBin( bggm, gmac );

	TH1 * amsig = book->addClone( "amsig", hNpm );
	amsig->Add( bgam, -1 );
	HistoBook::weightByBinWidth( amsig );

	double R = config.getDouble( "Params.R", 1.0 );
	TH1 * gmsig = book->addClone( "gmsig", hNpm );
	gmsig->Add( bggm, -1 * R );
	HistoBook::weightByBinWidth( gmsig );


	INFOC( "Trigger Correction 1D" );
	// Trigger Patch correction
	TH2D * tpcorrnum2D= get<TH2D>( "uls_tp_pT_vs_m", "Trigger" );
	TH2D * tpcorrden2D= get<TH2D>( "uls_all_pT_vs_m", "Trigger" );
	TH1 * tpcorrnum = tpcorrnum2D->ProjectionX( "tpcorrnum" );
	TH1 * tpcorrden = tpcorrden2D->ProjectionX( "tpcorrden" );


	TH1 * tpcorr = tpcorrnum->Rebin( bMass.nBins(), "tpcorr", bMass.bins.data() );
	TH1 * tpcorrdenrb = tpcorrden->Rebin( bMass.nBins(), "tpcorrdenrb", bMass.bins.data() );

	tpcorr->Divide( tpcorrdenrb );

	TH1 * tpgmsig = book->addClone( "tpgmsig", gmsig );
	TH1 * tpamsig = book->addClone( "tpamsig", amsig );

	applyTriggerPatchCorr( tpgmsig, tpcorr );
	applyTriggerPatchCorr( tpamsig, tpcorr );

	INFOC( "Merge Correction 1D" );
	// Merge Track Corrections
	TH2D * mgcorrnum2D= get<TH2D>( "uls_merge_pT_vs_m", "Trigger" );
	TH2D * mgcorrden2D= get<TH2D>( "uls_chan_pT_vs_m", "Trigger" );
	
	TH1 * mgcorrnum = mgcorrnum2D->ProjectionX( "mgcorrnum" );
	TH1 * mgcorrden = mgcorrden2D->ProjectionX( "mgcorrden" );

	INFOC( "Merge Correction Project" );
	TH1 * mgcorr = mgcorrnum->Rebin( bMass.nBins(), "mgcorr", bMass.bins.data() );
	TH1 * mgcorrdenrb = mgcorrden->Rebin( bMass.nBins(), "mgcorrdenrb", bMass.bins.data() );

	mgcorr->Divide( mgcorrdenrb );

	TH1 * mgtpgmsig = book->addClone( "mgtpgmsig", tpgmsig );
	TH1 * mgtpamsig = book->addClone( "mgtpamsig", tpamsig );

	applyTriggerPatchCorr( mgtpgmsig, mgcorr );
	applyTriggerPatchCorr( mgtpamsig, mgcorr );



}

void AcceptanceFixer::make2D(){
	book->cd( "" );
	HistoBins bMass, bPt;
	bMass.load( config, "dimuonBins.signalMass" );
	bPt.load( config, "dimuonBins.signalPt" );

	INFOC( "Signal Mass bins: " << bMass.toString() );
	INFOC( "Signal pT bins: " << bPt.toString() );

	// make the mixed event acorr
	// TH2 * hBpm   = get<TH2>( "uls_pT_vs_dNdM"   , "ME" );
	// TH2 * hBpp   = get<TH2>( "lsp_pT_vs_dNdM" , "ME" );
	// TH2 * hBmm   = get<TH2>( "lsn_pT_vs_dNdM" , "ME" );
	// TH2 * hBppmm = get<TH2>( "ls_pT_vs_dNdM"     , "ME" );

	TH2 * hBpm   = get<TH2D>( "uls_tp_pT_vs_m", "Trigger" );
	TH2 * hBpp   = get<TH2D>( "lsp_tp_pT_vs_m", "Trigger" );
	TH2 * hBmm   = get<TH2D>( "lsn_tp_pT_vs_m", "Trigger" );
	TH2 * hBppmm = get<TH2D>( "lsp_tp_pT_vs_m", "Trigger" );
	hBppmm->Add( hBmm );
	

	hBpm          = HistoBins::rebin2D( "Bpm", hBpm, bMass, bPt );
	hBpp          = HistoBins::rebin2D( "Bpp", hBpp, bMass, bPt );
	hBmm          = HistoBins::rebin2D( "Bmm", hBmm, bMass, bPt );
	hBppmm        = HistoBins::rebin2D( "Bppmm", hBppmm, bMass, bPt );
	
	INFOC( "Arithmetic mean" );
	TH2* meam = (TH2*)book->addClone( "meam", hBppmm );
	meam->Scale( 0.5 );

	INFOC( "Arithmetic mean Acceptance Correction" );
	TH2 * amac = (TH2*)book->addClone( "amac", hBpm );
	amac->Divide( meam );

	//geometric mean
	INFOC( "Geometric mean" );
	TH2 * gmac = (TH2*)book->addClone( "gmac", hBpm );
	TH2* megm  = (TH2*)book->addClone( "megm", hBpm );
	megm->Reset();
	makeGeometricMean( megm, hBpp, hBmm );
	megm->Scale( 2.0 );
	INFOC( "Geometric mean Acceptance Correction" );
	gmac->Divide( megm );



	// same event arithmetic mean
	TH2 * hNpm   = get<TH2D>( "uls_pT_vs_dNdM" , "SE" );
	TH2 * hNpp   = get<TH2D>( "lsp_pT_vs_dNdM" , "SE" );
	TH2 * hNmm   = get<TH2D>( "lsn_pT_vs_dNdM" , "SE" );
	TH2 * hNppmm = get<TH2D>( "ls_pT_vs_dNdM"  , "SE" );

	hNpm          = HistoBins::rebin2D( "Npm", hNpm, bMass, bPt );
	hNpp          = HistoBins::rebin2D( "Npp", hNpp, bMass, bPt );
	hNmm          = HistoBins::rebin2D( "Nmm", hNmm, bMass, bPt );
	hNppmm        = HistoBins::rebin2D( "Nppmm", hNppmm, bMass, bPt );

	TH2* seam = (TH2*)book->addClone( "seam", hNppmm );
	seam->Scale( 0.5 );

	TH2* segm = (TH2*)book->addClone( "segm", hBpm );
	segm->Reset();
	makeGeometricMean( segm, hNpp, hNmm );
	segm->Scale( 2.0 );

	TH2 *bgam = (TH2*)book->addClone( "bgam", seam );
	multiplyBinByBin( bgam, amac );

	TH2 *bggm = (TH2*)book->addClone( "bggm", segm );
	multiplyBinByBin( bggm, gmac );

	TH2 * amsig = (TH2*)book->addClone( "amsig", hNpm );
	amsig->Add( bgam, -1 );
	

	double R = config.getDouble( "Params.R", 1.0 );
	TH2 * gmsig = (TH2*)book->addClone( "gmsig", hNpm );
	gmsig->Add( bggm, -1 * R );
	// HistoBook::weightByBinWidth( gmsig );
	
	TH2D * tpcorrnum2D= get<TH2D>( "uls_tp_pT_vs_m", "Trigger" );
	TH2D * tpcorrden2D= get<TH2D>( "uls_all_pT_vs_m", "Trigger" );

	TH2 * tpcorr = HistoBins::rebin2D( "tpcorr", tpcorrnum2D, bMass, bPt );
	TH2 * tpcorrden = HistoBins::rebin2D( "tpcorrden", tpcorrden2D, bMass, bPt );

	tpcorr->Divide( tpcorrden );

	TH2 * tpgmsig = (TH2*)book->addClone( "tpgmsig2d", gmsig );
	TH2 * tpamsig = (TH2*)book->addClone( "tpamsig2d", amsig );

	// applyTriggerPatchCorr( tpgmsig, tpcorr );
	tpgmsig->Divide( tpcorr );
	applyTriggerPatchCorr( tpamsig, tpcorr );

	int b1 = tpgmsig->GetYaxis()->FindBin( config.getDouble( "Params.pT:min", 0.0 ) );
	int b2 = tpgmsig->GetYaxis()->FindBin( config.getDouble( "Params.pT:max", 10.0 ) );
	TH1 * tpgmsig1d = tpgmsig->ProjectionX( "tpgmsig", b1, b2 );
	TH1 * tpamsig1d = tpamsig->ProjectionX( "tpamsig", b1, b2 );

	HistoBook::weightByBinWidth( tpamsig1d );
	HistoBook::weightByBinWidth( tpgmsig1d );

	book->add( "tpgmsig", tpgmsig1d );

	// Apply Efficiency Correction!
	TH2 * effcorrsig = (TH2*)book->addClone( "effcorrsig", tpgmsig );


	TH2* effNum = HistoBins::rebin2D( "effNum", get<TH2>( "RapCut_wdNdM_pT", "Eff" ), bMass, bPt );
	TH2* effDen = HistoBins::rebin2D( "effDen", get<TH2>( "RapCut_dNdM_pT", "Eff" ), bMass, bPt );

	TH2* effCorr = (TH2*)book->addClone( "effCorr", effNum );

	effCorr->Divide( effDen );

	double meanPt = config.getDouble( "Params.meanPt", 3.6 );
	int by = effCorr->GetYaxis()->FindBin( meanPt );
	TH1 *effCorr1d = effCorr->ProjectionX( "effCorr1d", by, by );

	TH1 *effcorrsig1d = effcorrsig->ProjectionX("effcorrsig1d", effcorrsig->GetYaxis()->FindBin(config.getDouble( "Params.pT:min", 0.0 )), effcorrsig->GetYaxis()->FindBin( config.getDouble( "Params.pT:max", 10.0 ) ) );

	applyTriggerPatchCorr( effcorrsig1d, effCorr1d );

	book->add( "effcorrsig1d", effcorrsig1d );
	effcorrsig1d->Scale(1.0, "width");

}

void AcceptanceFixer::make(){

	makeMass1D();
	make2D();
	makeEmbeddingEfficiencyCurve();

	book->cd("");
	TH1 * h = book->addClone( "normsig",  book->get("effcorrsig1d" ) );

	double NMinBias = config.getDouble( nodePath + ".NMinBias" );
	INFOC( "N MinBias Effective = " << NMinBias );
	h->Scale( 1.0 / NMinBias );



	return;
}



void AcceptanceFixer::makeEmbeddingEfficiencyCurve(){
	book->cd( "EmbedCorr" );
	HistoBins bMass, bPt;
	bMass.load( config, "dimuonBins.signalMass" );
	bPt.load( config, "dimuonBins.signalPt" );

	INFOC( "Signal Mass bins: " << bMass.toString() );
	INFOC( "Signal pT bins: " << bPt.toString() );


	TH2 * hMtd   = HistoBins::rebin2D( "Mtd" , get<TH2>( "uls_mtd_pT_vs_m" , "Embed" ) , bMass , bPt );
	TH2 * hMc    = HistoBins::rebin2D( "Mc"  , get<TH2>( "uls_mc_pT_vs_m"  , "Embed" ) , bMass , bPt );

	TH1 * h1Mtd = hMtd->ProjectionX( "mtd1D" );
	TH1 * h1Mc  = hMc->ProjectionX( "mc1D" );

	TH1 * hEff = book->addClone( "eff", h1Mtd );
	hEff->Divide( h1Mc );

	TH1 * hSig = book->addClone( "corrgmsig", book->get( "tpgmsig", "" ) );
	INFOC( "hSig = " << hSig );

	TF1 * f = new TF1( "f", "pol0" );
	hEff->Fit( f );
	double cf = 1.0 / f->GetParameter(0);
	INFOC( "Embedding correction factor = " << cf );
	hSig->Scale( cf  );

	// applyTriggerPatchCorr( hSig, hEff );



}