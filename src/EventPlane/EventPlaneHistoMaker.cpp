#include "EventPlaneHistoMaker.h"
#include "TMath.h"


void EventPlaneHistoMaker::initialize(){
	CandidateSkimmer::initialize();

	if ( config.exists( nodePath + ".EventPlaneCorr" ) ){
		INFO( classname(), "" );
		INFO( classname(), "############### EventPlaneCorr ###################"  );
		epc.load( config, nodePath + ".EventPlaneCorr" );
	} else {
		WARN( classname(), "No EventPlane Corrections found" );
	}
	
}

void EventPlaneHistoMaker::analyzeEvent(){
	DEBUG( classname(), "" );

	book->cd( "eventPlaneQA" );
	double nTracks = eventPlane->mNtrk_eta_pos + eventPlane->mNtrk_eta_neg;
	TRACE( classname(), "mNtrk = " << nTracks );
	if ( nTracks == 0 ) return;

	double qx = eventPlane->mQx_eta_pos + eventPlane->mQx_eta_neg;
	double qy = eventPlane->mQy_eta_pos + eventPlane->mQy_eta_neg;


	book->fill( "nTracks", nTracks );

	if (qx == 0) return;
	if (qy == 0) return;

	qx = qx / nTracks;
	qy = qy / nTracks;

	double psi = TMath::ATan2( qy, qx ) / 2.0;

	book->cd();
	book->fill( "QxQy", qx, qy );
	book->fill( "Psi", psi );	

	// apply centering
	qx = epc.center_qx( qx );
	qy = epc.center_qy( qy );
	psi = TMath::ATan2( qy, qx ) / 2.0;

	// plot the centered version
	book->fill( "QxQyCentered", qx, qy );
	book->fill( "PsiCentered", psi );	

	// now flatten if given a flattening function
	double psi_weight = epc.flatten( psi );
	// hPsi2Flattened->Fill( psi, psi_weight );
}
 

void EventPlaneHistoMaker::postEventLoop(){

	// if ( 0 == iEventLoop ){
	// 	fitQxQy();
	// } else if ( 1 == iEventLoop ){
	// 	fitPsi();
	// }

}

// void EventPlaneHistoMaker::fitQxQy(){
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


// void EventPlaneHistoMaker::fitPsi(){
// 	DEBUG( classname(), "");

// 	// double psi = 1;
// 	// double Sin2 = TMath::Sin(2*psi);
//  //    double Cos2 = TMath::Cos(2*psi);
//  //    double Sin4 = TMath::Sin(4*psi);
//  //    double Cos4 = TMath::Cos(4*psi);

// 	// string function = "psi + 0.5*(2*[0]*[5]-2*[1]*[6]-[3]*[7]-[4]*[8])";

// 	// TF1 * f = new TF1( "test", function.c_str() );


// }