#ifndef PID_EFFICIENCY_MAKER_H
#define PID_EFFICIENCY_MAKER_H

#include "HistoAnalyzer.h"
#include "XmlFunction.h"
using namespace jdb;

#include <fstream>
#include <map>


#include "TF1.h"
#include "TMath.h"


#include "CandidateFilter.h"

class PidEfficiencyMaker : public HistoAnalyzer
{

protected:

	XmlFunction fSigmaDeltaZ, fSigmaDeltaY, fSigmaDeltaTOF;
	CutCollection trackCuts;

public:
	virtual const char* classname() const { return "PidEfficiencyMaker"; }
	PidEfficiencyMaker() {}
	~PidEfficiencyMaker() {}

	virtual void initialize(){
		CandidateFilter::setDefaultMuonCuts( trackCuts );
		if ( config.exists( nodePath + ".MuonCandidateCuts" ) ){
			trackCuts.init( config, nodePath + ".MuonCandidateCuts" );

			INFO( classname(), "" );
			INFO( classname(), "############### Muon Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		} else {
			WARN( classname(), "No Muon Cuts Found, using defaults" );
			INFO( classname(), "" );
			INFO( classname(), "############### Muon Cuts ###################"  );
			trackCuts.report();
			INFO( classname(), "" );
		}


		string pfSigmaDeltaZ = config.q( nodePath + ".MtdParams.XmlFunction{name==SigmaMtdDeltaZ}" );
		string pfSigmaDeltaY = config.q( nodePath + ".MtdParams.XmlFunction{name==SigmaMtdDeltaY}" );
		string pfSigmaDeltaTOF = config.q( nodePath + ".MtdParams.XmlFunction{name==SigmaMtdDeltaTOF}" );
		if ( config.exists( pfSigmaDeltaZ ) ){
			INFOC( "=================== SIGMA DELTA Z ENABLED ========================" );
			fSigmaDeltaZ.set( config, pfSigmaDeltaZ );
			INFOC( "p0=" << fSigmaDeltaZ.getTF1().get()->GetParameter(0) << ",p1=" << fSigmaDeltaZ.getTF1().get()->GetParameter(1) << ",p2=" << fSigmaDeltaZ.getTF1().get()->GetParameter(2) );
		}
		if ( config.exists( pfSigmaDeltaY ) ){
			INFOC( "=================== SIGMA DELTA Y ENABLED ========================" );
			fSigmaDeltaY.set( config, pfSigmaDeltaY );
			INFOC( "p0=" << fSigmaDeltaY.getTF1().get()->GetParameter(0) << ",p1=" << fSigmaDeltaY.getTF1().get()->GetParameter(1) << ",p2=" << fSigmaDeltaY.getTF1().get()->GetParameter(2) );
		}
		if ( config.exists( pfSigmaDeltaTOF ) ){
			INFOC( "=================== SIGMA DELTA TOF ENABLED ========================" );
			fSigmaDeltaTOF.set( config, pfSigmaDeltaTOF );
			INFOC( "p0=" << fSigmaDeltaTOF.getTF1().get()->GetParameter(0) << ",p1=" << fSigmaDeltaTOF.getTF1().get()->GetParameter(1) << ",p2=" << fSigmaDeltaTOF.getTF1().get()->GetParameter(2) );
		}



	}


	TH1 * pTSlice( string name, TH2* _hr, int _iBin ){
		TAxis *x = _hr->GetXaxis();
		double ptMid = x->GetBinCenter( _iBin );
		int iBinNeg = x->FindBin( -ptMid );

		TH1 * hPos = _hr->ProjectionY( (name + "_hPos_" + ts(_iBin)).c_str(), _iBin, _iBin );
		TH1 * hNeg = _hr->ProjectionY( (name + "_hNeg_" + ts(_iBin)).c_str(), iBinNeg, iBinNeg );

		hPos->Add(hNeg);

		// also remove negative bins from subtraction
		for ( int i = 1; i <= hPos->GetNbinsX(); i++ ){
			if ( hPos->GetBinContent( i ) < 0.0 )
				hPos->SetBinContent( i, 0.0 );
		}

		hPos->SetTitle( ("pT = " + dts(ptMid)).c_str() );

		return (TH1*)hPos->Clone( (name + "_All_" + ts( _iBin )).c_str() );
	}


	void fillEfficiency( TH1 * _hEff, int _iBin, TH1* _slice, double _low, double _hi ){

		TAxis *x     = _slice->GetXaxis();
		double pass  = _slice->Integral( x->FindBin( _low ), x->FindBin(_hi) );
		double total = _slice->Integral();

		double eff = 1.00;
		if ( total > 0.0 ) eff = pass / total;

		_hEff->SetBinContent( _iBin, eff );

	}


	virtual void make(){

		HistoBins bpt, bmtd, bTOF;
		bpt.load( config, "bins.pt" );
		bmtd.load( config, "bins.mtdDz" );
		bTOF.load( config, "bins.dTOF" );
		HistoBins bNSigPi;
		bNSigPi.load( config, "bins.nSigPi" );
		

		
		
		TH2 * uls_roi_dz = HistoBins::rebin2D( "signalDeltaZ", get<TH2>( "trackQA/Unlike_Sign_ROI_mtdDeltaZ_vs_rigidity" ), bpt, bmtd );



		book->cd();
		TH2 * hDeltaZ   = HistoBins::rebin2D( "signal_DeltaZ",   get<TH2>( "signal_dz", "data" ),     bpt , bmtd );
		TH2 * hDeltaY   = HistoBins::rebin2D( "signal_DeltaY",   get<TH2>( "signal_dy", "data" ),     bpt , bmtd );
		TH2 * hDeltaTOF = HistoBins::rebin2D( "signal_DeltaTOF", get<TH2>( "signal_dtof", "data" ),   bpt , bTOF );
		TH2 * hnSigmaPi = HistoBins::rebin2D( "signal_nSigmaPi", get<TH2>( "signal_nSigPi", "data" ), bpt , bNSigPi);

		int b0 = hDeltaZ->GetXaxis()->FindBin(1.01);
		int b1 = hDeltaZ->GetXaxis()->FindBin( 9.0 );

		

		TH1 * hEffDeltaZ = hDeltaZ->ProjectionX( "effDeltaZ", 1, 1 );
		hEffDeltaZ->Reset();



		TH1 * hEffDeltaY = hDeltaY->ProjectionX( "effDeltaY", 1, 1 );
		hEffDeltaY->Reset();

		TH1 * hEffDeltaTOF = hDeltaTOF->ProjectionX( "effDeltaTOF", 1, 1 );
		hEffDeltaTOF->Reset();

		TH1 * hEffnSigmaPi = hnSigmaPi->ProjectionX( "effnSigmaPi", 1, 1 );
		hEffnSigmaPi->Reset();

		
		for ( int iB = b0 ; iB <= b1; iB++ ){
			INFOC( "Slicing bin " << iB );

			TH1 * hDeltaZSlice = pTSlice( "deltaZ", hDeltaZ, iB );
			TH1 * hDeltaYSlice = pTSlice( "deltaY", hDeltaY, iB );
			TH1 * hDeltaTOFSlice = pTSlice( "deltaTOF", hDeltaTOF, iB );
			TH1 * hnSigmaPiSlice = pTSlice( "nSigmaPi", hnSigmaPi, iB );

			double pTmid = hDeltaY->GetXaxis()->GetBinCenter( iB );

			double DeltaZSigma = 1.0;
			if ( nullptr != fSigmaDeltaZ.getTF1().get() ) DeltaZSigma = fSigmaDeltaZ.getTF1().get()->Eval( pTmid );
			if ( DeltaZSigma < 1.0 ) DeltaZSigma = 1.0;
			double DeltaZ1 = trackCuts[ "mtdDeltaZ" ]->min * DeltaZSigma;
			double DeltaZ2 = trackCuts[ "mtdDeltaZ" ]->max * DeltaZSigma;
			INFOC( "\tDeltaZSigma( " << pTmid <<" ) = " << DeltaZSigma );
			INFOC( "\tDeltaZ( " << DeltaZ1 << " --> " << DeltaZ2 << " )" );

			double DeltaYSigma = 1.0;
			if ( nullptr != fSigmaDeltaY.getTF1().get() ) DeltaYSigma = fSigmaDeltaY.getTF1().get()->Eval( pTmid );
			if ( DeltaYSigma < 1.0 ) DeltaYSigma = 1.0;
			double DeltaY1 = trackCuts[ "mtdDeltaY" ]->min * DeltaYSigma;
			double DeltaY2 = trackCuts[ "mtdDeltaY" ]->max * DeltaYSigma;
			INFOC( "\tDeltaYSigma( " << pTmid <<" ) = " << DeltaYSigma );
			INFOC( "\tDeltaY( " << DeltaY1 << " --> " << DeltaY2 << " )" );

			double DeltaTOFSigma = 1.0;
			if ( nullptr != fSigmaDeltaTOF.getTF1().get() ) DeltaTOFSigma = fSigmaDeltaTOF.getTF1().get()->Eval( pTmid );
			if ( DeltaTOFSigma < 0.001 ) DeltaTOFSigma = 0.001;
			double DeltaTOF1 = trackCuts[ "mtdDeltaTOF" ]->min * DeltaTOFSigma;
			double DeltaTOF2 = trackCuts[ "mtdDeltaTOF" ]->max * DeltaTOFSigma;
			INFOC( "\tDeltaTOFSigma( " << pTmid <<" ) = " << DeltaTOFSigma );
			INFOC( "\tDeltaTOF( " << DeltaTOF1 << " --> " << DeltaTOF2 << " )" );

			double nSigmaPion1 = trackCuts["nSigmaPion"]->min;
			double nSigmaPion2 = trackCuts["nSigmaPion"]->max;

			fillEfficiency( hEffDeltaZ, iB, hDeltaZSlice, DeltaZ1, DeltaZ2 );
			fillEfficiency( hEffDeltaY, iB, hDeltaYSlice, DeltaY1, DeltaY2 );
			fillEfficiency( hEffDeltaTOF, iB, hDeltaTOFSlice, DeltaTOF1, DeltaTOF2 );
			fillEfficiency( hEffnSigmaPi, iB, hnSigmaPiSlice, nSigmaPion1, nSigmaPion2 );
		}

		TH1 * hEffTotal = (TH1*)hEffDeltaZ->Clone( "effTotal" );
		hEffTotal->Multiply( hEffDeltaY );
		hEffTotal->Multiply( hEffDeltaTOF );
		hEffTotal->Multiply( hEffnSigmaPi );


	}


};


#endif