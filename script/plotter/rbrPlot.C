

RooPlotLib rpl;

double meanForPeriod( TProfile * h ){

	double total = 0;
	double n = 0;
	for ( int i = 1; i <= h->GetNbinsX(); i++ ){
		double bc = h->GetBinContent( i );
		if ( bc == 0  )
			continue;
		total += bc;
		n += 1;
	}

	cout << " Mean " << h->GetTitle() << " : " << ( total / n ) << " vs. " << h->GetMean( 2 ) << endl;

	return ( total / n  );
}

double rmsForPeriod( TProfile * h ){
	double m = meanForPeriod( h);
	double total = 0;
	double n = 0;
	for ( int i = 1; i <= h->GetNbinsX(); i++ ){

		double bc = h->GetBinContent( i );
		total += ( m - bc )*( m - bc );
		n += 1;
	}

	cout << " var " << h->GetTitle() << " : " << TMath::Sqrt( total / n ) << " vs. " << h->GetRMS( 2 ) << endl;

	return TMath::Sqrt( total / n  );
}

int x1 = 1;
int x2 = 2100;

void drawBands( TProfile * h, double nSig = 3.0 ){

	

	double m = meanForPeriod( h );
	double rms = rmsForPeriod( h ) * nSig;
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

TH1 * findBadRuns( TProfile * h, double nSig = 3.0 ){

	double m = meanForPeriod( h );
	double rms = rmsForPeriod( h ) * nSig;
	TH1D * hbad = new TH1D( ( (string)"bad_" + h->GetTitle()).c_str(), "bad", (x2-x1)+1, x1-1, x2 );

	for ( int i = x1; i <=x2; i++ ){
		double bc = h->GetBinContent( i );
		if ( bc > m + rms || bc < m - rms ){
			hbad->SetBinContent( i, bc );
			hbad->SetBinError( i, h->GetBinError( i ) );
		} else {
			hbad->SetBinContent( i, -99999 );
			hbad->SetBinError( i, 0 );
		}
	}

	return hbad;

}



void rbrPlot( string var, double nSig = 3.0, string fn = "rbr_event_QA.root" ){
	
	TCanvas * c = new TCanvas( "cc", "cc" );
	gStyle->SetOptStat(0);
	
	TFile * f = new TFile( fn.c_str(), "READ" );
	TH2D * hh = (TH2D*)f->Get( ("RunByRun/" + var).c_str() );
	TProfile *hp = hh->ProfileX();
	// hp->Fit( "pol0" );

	double m = meanForPeriod( hp );
	double rms = rmsForPeriod( hp ) * 5.0;
	double y1 = m - rms;
	double y2 = m + rms;

	// rpl.style( hh )
	// 	.set( "yr", y1, y2 )
	// 	.set( "draw", "colz" )
	// 	.set( "logz", 1 )
	// 	.draw();
	rpl.style( hp )
		.set( "markerstyle", 6 )
		.set( "markersize", 2 )
		.set( "title", ";runIndex;" + var )
		.set( "yr", y1, y2 )
		.set( "draw", "" )
		.draw( );
	drawBands( hp, nSig );
	TH1 * bad = findBadRuns( hp, nSig );
	rpl.style( bad )
		.set( "markerstyle", 8 )
		.set( "markersize", 1 )
		.set( "color", kRed )
		.set( "draw", "same pe" )
		.draw();
	c->Print( (var + ".pdf").c_str() );
}