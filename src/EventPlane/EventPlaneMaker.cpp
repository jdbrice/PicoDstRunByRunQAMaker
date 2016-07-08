#include "EventPlaneMaker.h"
#include "TMath.h"


void EventPlaneMaker::initialize(){
	PicoDstSkimmer::initialize();

	hPsi2 = new TH1D("Psi2","",640,-3.2,3.2);
	hQxQy = new TH2D("QxQy","",1000,-1,1,1000,-1,1);
	hPsi2Centered = new TH1D("Psi2Centered","",640,-3.2,3.2);
	hQxQyCentered = new TH2D("QxQyCentered","",1000,-1,1,1000,-1,1);

	hPsi2Flattened = new TH1D("Psi2Flattened","",640,-3.2,3.2);

	// // load in the parameters
	// epc.load( config, nodePath + ".EventPlaneCorr" );

	// config.toXmlFile( "configOut.xml" );
	
}

void EventPlaneMaker::analyzeEvent(){
	DEBUG( classname(), "" );

	double nTracks = pico->ntrk();
	TRACE( classname(), "mNtrk = " << nTracks );
	if ( nTracks == 0 ) return;

	double qx = pico->qx();
	double qy = pico->qy();

	if (qx == 0) return;
	if (qy == 0) return;

	qx = qx / nTracks;
	qy = qy / nTracks;

	double psi = TMath::ATan2( qy, qx );

	hQxQy->Fill( qx, qy );
	hPsi2->Fill( psi );	

	// apply centering
	qx = epc.center_qx( qx );
	qy = epc.center_qy( qy );
	psi = TMath::ATan2( qy, qx );

	// plot the centered version
	hQxQyCentered->Fill( epc.center_qx( qx ), epc.center_qy( qy ) );
	hPsi2Centered->Fill( psi );

	// now flatten if given a flattening function
	double psi_weight = epc.flatten( psi );
	hPsi2Flattened->Fill( psi, psi_weight );
}
 

void EventPlaneMaker::postEventLoop(){

	// if ( 0 == iEventLoop ){
	// 	fitQxQy();
	// } else if ( 1 == iEventLoop ){
	// 	fitPsi();
	// }

}

// void EventPlaneMaker::fitQxQy(){
// 	DEBUG( classname(), "" );
// 	TH1D* qy = (TH1D*)hQxQy->ProjectionY( "qy" );
// 	TH1D* qx = (TH1D*)hQxQy->ProjectionX( "qx" );

// 	double nSig_qx = config.getDouble( nodePath + ".fitQxQy:nSig_qx", 3.0 );
// 	double nSig_qy = config.getDouble( nodePath + ".fitQxQy:nSig_qy", 3.0 );
	
// 	TF1 fgaus( "fgaus", "gaus" );
// 	qx->Fit( &fgaus, "R", "", qx->GetMean() - nSig_qx * qx->GetStdDev(), qx->GetMean() + nSig_qx * qx->GetStdDev() );
// 	double m_qx = fgaus.GetParameter(1);
// 	qy->Fit( &fgaus, "R", "", qy->GetMean() - nSig_qy * qy->GetStdDev(), qy->GetMean() + nSig_qy * qy->GetStdDev() );
// 	double m_qy = fgaus.GetParameter(1);

// 	epc.setMeans( m_qx, m_qy );
// }


// void EventPlaneMaker::fitPsi(){
// 	DEBUG( classname(), "");

// 	// double psi = 1;
// 	// double Sin2 = TMath::Sin(2*psi);
//  //    double Cos2 = TMath::Cos(2*psi);
//  //    double Sin4 = TMath::Sin(4*psi);
//  //    double Cos4 = TMath::Cos(4*psi);

// 	// string function = "psi + 0.5*(2*[0]*[5]-2*[1]*[6]-[3]*[7]-[4]*[8])";

// 	// TF1 * f = new TF1( "test", function.c_str() );


// }