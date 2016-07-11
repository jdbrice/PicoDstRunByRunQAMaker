#include "RunByRunReportMaker.h"

#include "TLatex.h"
#include "TLine.h"
#include "Utils.h"

void RunByRunReportMaker::make(){
	DEBUG( classname(), "" );
	HistoAnalyzer::make();


	region = new XmlRange( &config, nodePath + ".Regions" );

	for ( int i = region->min; i < region->max; i++ ){
		badRunMask.push_back( false );
	}

	badRunHistos = config.getStringVector( nodePath + ".BadRunHistos" );
	histoNames = config.getStringVector( nodePath + ".HistoNames" );

	for ( string s : badRunHistos ){
		profile( s, false );
	}
	for ( string s : histoNames ){
		profile( s, true );
	}


	for ( int i = 0; i < badRunMask.size(); i++ ){
		if ( badRunMask[i] ){
			INFO( classname(), rmf.runForIndex( i ) << " is BAD" );
		}
	}


	INFO( classname(), "15108063 index = " << rmf.indexForRun( 15108063 ));

}

void RunByRunReportMaker::profile( string name, bool draw ){
	
	double nSig = config.getDouble( nodePath + ".nSigma:default", 5.0 );
	nSig = config.getDouble( nodePath+".nSigma." + name, nSig );


	RooPlotLib rpl;
	
	TFile * f = inFile;
	TH2D * hh = (TH2D*)f->Get( name.c_str() );
	TProfile *hp = hh->ProfileX();
	

	double m = meanForPeriod( hp );
	double rms = rmsForPeriod( hp, "" );
	double y1 = minFor( hp );
	double y2 = maxFor( hp );

	if ( m - rms * nSig < y1 )
		y1 = m - rms * nSig;
	if ( m + rms * nSig > y2 )
		y2 = m + rms * nSig;
	// now pad
	double range = fabs(y2 - y1);
	y1 -= range * .1;
	y2 += range * .1;


	TLatex latex;
	latex.SetTextSize(0.055);
	latex.SetTextAlign(13);  //align at top
	

	// rpl.style( hh )
	// 	.set( "yr", y1, y2 )
	// 	.set( "draw", "colz" )
	// 	.set( "logz", 1 )
	// 	.draw();
	vector<string> regions;
	if ( config.exists( nodePath +".Regions." + name ) ){
		for ( string child : config.childrenOf( nodePath +".Regions." + name, "XmlRange" ) ){
			regions.push_back( child );
		}
	} else {
		regions.push_back( nodePath + ".Regions" );
	}

	int iR = 0;
	for ( string path : regions ){
		XmlRange * r = new XmlRange( &config, path );

		if ( !draw ){
			findBadRuns( hp, nSig, r );
			continue;
		}

		if ( draw ){
			rpl.style( hp )
				.set( "markerstyle", 6 )
				.set( "markersize", 2 )
				.set( "title", ";runIndex; <" + name + ">" )
				.set( "yr", y1, y2 )
				.set( "draw", "" )
				.set( config, nodePath + ".Style.all" )
				.set( config, nodePath + ".Style."+name )
				.draw( );

			// only draw bands if used for bad run finding
			if ( find( badRunHistos.begin(), badRunHistos.end(), name ) != badRunHistos.end() ){
				drawBands( hp, name, nSig, r );
				// latex.DrawLatexNDC(.25,.86, ("n#sigma = " + dts( nSig )).c_str() );
			}
		}

		TH1 * bad = makeBadRunPlot( hp, name );
		
		
		if ( draw ){
			rpl.style( bad )
				.set( "markerstyle", 8 )
				.set( "markersize", 1 )
				.set( "color", kRed )
				.set( "draw", "same pe" )
				.draw();
			
			// latex.DrawLatexNDC(.3,.96,config[ nodePath + ".Reporter.title" ].c_str() );
			
			gStyle->SetOptStat(0);
			reporter->savePage();
			reporter->saveImage( "img/" + name  + "_r" + ts(iR) + ".pdf" );
		}
		iR++;
	}


	
	// c->Print( (var + ".pdf").c_str() );
}

void RunByRunReportMaker::drawBands( TProfile * h, string name, double nSig, XmlRange *r){

	if ( nullptr == r )
		r = region;

	INFO( classname(), "Name = " << name );
	INFO( classname(), "Range " << r->toString() );
	
	int x1 = r->min;
	int x2 = r->max;

	RooPlotLib rpl;

	double m = meanForPeriod( h, r );
	double rms = rmsForPeriod( h, name, r ) * nSig;
	TLine * l0 = new TLine( x1, m, x2, m );
	TLine * l1 = new TLine( x1, m + rms, x2, m+rms );
	TLine * l2 = new TLine( x1, m - rms, x2, m-rms );

	rpl.style( l0 ).set( "color", kRed ).set( "lw", 2 ).set( "linestyle", kDashed );
	rpl.style( l1 ).set( "color", kRed ).set( "lw", 2 );
	rpl.style( l2 ).set( "color", kRed ).set( "lw", 2 );

	l0->Draw("same");
	l1->Draw("same");
	l2->Draw("same");

}

double RunByRunReportMaker::minFor( TProfile * h ){

	double m = 1000000;
	for ( int i = 1; i <= h->GetNbinsX(); i++ ){
		double bc = h->GetBinContent( i );
		if ( 0 == h->GetBinEntries( i ) ) continue;
		if (bc < m )
			m = bc;
	}
	return m - 0.25 * abs( m );
}

double RunByRunReportMaker::maxFor( TProfile * h ){

	double m = -10000;
	for ( int i = 1; i <= h->GetNbinsX(); i++ ){
		double bc = h->GetBinContent( i );
		if ( 0 == h->GetBinEntries( i ) ) continue;
		if (bc > m )
			m = bc;
	}
	return m + abs(m) * .25;
}

double RunByRunReportMaker::meanForPeriod( TProfile * h, XmlRange *r ){
	if ( nullptr == r )
		r = region;

	double total = 0;
	double n = 0;
	for ( int i = r->min; i <= r->max; i++ ){
		if ( i <= 0 || i > h->GetNbinsX() ) continue;
		
		double bc = h->GetBinContent( i );
		
		if ( bc == 0 || 0 == h->GetBinEntries( i ) )
			continue;
		total += bc;
		n += 1;
	}

	cout << " Mean " << h->GetTitle() << " : " << ( total / n ) << " vs. " << h->GetMean( 2 ) << endl;

	return ( total / n  );
}

double RunByRunReportMaker::rmsForPeriod( TProfile * h, string name, XmlRange *r ){
	book->cd();

	INFO( classname(), "Name = " << name );

	gStyle->SetOptStat(1111);

	if ( nullptr == r )
		r = region;

	string rname = ts(r->min) + "_" + ts(r->max);

	
	TH1D * hrms = nullptr;
	if ( ""!= name )
		hrms = new TH1D( ( name +"_rms_" + rname ).c_str(), "hrms", 500, minFor( h ), maxFor( h ) );
	
	double m = meanForPeriod( h, r );
	double total = 0;
	double n = 0;
	for ( int i = r->min; i <= r->max; i++ ){
		if ( i <= 0 || i > h->GetNbinsX() ) continue;

		if ( badRunMask[i] == true ) continue;
		double bc = h->GetBinContent( i );
		if ( h->GetBinEntries( i ) == 0 ) continue;
		
		if ( nullptr != hrms )
			hrms->Fill( bc );
		total += ( m - bc )*( m - bc );
		n += 1;
	}

	cout << " var " << h->GetTitle() << " : " << TMath::Sqrt( total / n ) << " vs. " << h->GetRMS( 2 ) << endl;

	return TMath::Sqrt( total / n  );
}


void RunByRunReportMaker::findBadRuns( TProfile * h, double nSig, XmlRange *r  ){

	if ( nullptr == r )
		r = region;

	int x1 = r->min;
	int x2 = r->max;


	double m = meanForPeriod( h, r );
	double rms = rmsForPeriod( h, "", r ) * nSig;

	for ( int i = x1; i <=x2; i++ ){
		if ( h->GetBinEntries(i) <= 0 ) continue;
		double bc = h->GetBinContent( i );
		if ( bc > m + rms || bc < m - rms ){
			WARN( classname(), i << " MARKED AS BAD " );
			badRunMask[i] = true;
		} 
	}
}

TH1 * RunByRunReportMaker::makeBadRunPlot( TProfile * h, string name, XmlRange *r ){

	if ( nullptr == r )
		r = region;

	int x1 = r->min;
	int x2 = r->max;
	INFO( classname(), "Range " << r->toString() );
	string rname = ts(r->min) + "_" + ts(r->max);

	TH1D * hbad = new TH1D( ( (string)"bad_" + name +"_" + rname ).c_str(), "bad", (x2-x1)+1, x1-1, x2 );

	for ( int i = x1; i <=x2; i++ ){
		double bc = h->GetBinContent( i );
		if ( badRunMask[i] ){
			hbad->SetBinContent( i, bc );
			hbad->SetBinError( i, h->GetBinError( i ) );
		} else {
			hbad->SetBinContent( i, -99999 );
			hbad->SetBinError( i, 0 );
		}
	}

	return hbad;

}