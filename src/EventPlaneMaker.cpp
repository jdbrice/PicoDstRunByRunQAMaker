#include "EventPlaneMaker.h"
#include "TMath.h"

void EventPlaneMaker::analyzeEvent(){
	DEBUG( classname(), "" );

	double nTracks = getNtrk( v1, v2 );
	TRACE( classname(), "mNtrk = " << nTracks );
	if ( nTracks == 0 ) return;

	double qx = getQ( "mQx", v1, v2 ) ;
	double qy = getQ( "mQy", v1, v2 ) ;

	if (qx == 0) return;
	if (qy == 0) return;

	qx = qx / nTracks;
	qy = qy / nTracks;


	double Qx = ( epc.center_qx( qx ) ) * nTracks;
	double Qy = ( epc.center_qy( qy ) ) * nTracks;
	double psi = TMath::ATan2( Qy, Qx );


	if ( 0 == iEventLoop ){
		hQxQy->Fill( qx, qy );
		hPsi2->Fill( psi );	
	} else if ( 1 == iEventLoop ){
		hQxQyCentered->Fill( epc.center_qx( qx ), epc.center_qy( qy ) );
		hPsi2Centered->Fill( psi );	
	}
	

}
 

void EventPlaneMaker::postEventLoop(){

	if ( 0 == iEventLoop ){
		fitQxQy();
	} else if ( 1 == iEventLoop ){
		fitPsi();
	}

}

void EventPlaneMaker::fitQxQy(){
	DEBUG( classname(), "" );
	TH1D* qy = (TH1D*)hQxQy->ProjectionY( "qy" );
	TH1D* qx = (TH1D*)hQxQy->ProjectionX( "qx" );

	double nSig_qx = config.getDouble( nodePath + ".fitQxQy:nSig_qx", 3.0 );
	double nSig_qy = config.getDouble( nodePath + ".fitQxQy:nSig_qy", 3.0 );
	
	TF1 fgaus( "fgaus", "gaus" );
	qx->Fit( &fgaus, "R", "", qx->GetMean() - nSig_qx * qx->GetStdDev(), qx->GetMean() + nSig_qx * qx->GetStdDev() );
	double m_qx = fgaus.GetParameter(1);
	qy->Fit( &fgaus, "R", "", qy->GetMean() - nSig_qy * qy->GetStdDev(), qy->GetMean() + nSig_qy * qy->GetStdDev() );
	double m_qy = fgaus.GetParameter(1);

	epc.setMeans( m_qx, m_qy );
}


void EventPlaneMaker::fitPsi(){
	DEBUG( classname(), "");

	double psi = 1;
	double Sin2 = TMath::Sin(2*psi);
    double Cos2 = TMath::Cos(2*psi);
    double Sin4 = TMath::Sin(4*psi);
    double Cos4 = TMath::Cos(4*psi);

	// string function = "psi + 0.5*(2*[0]*[5]-2*[1]*[6]-[3]*[7]-[4]*[8])";

	// TF1 * f = new TF1( "test", function.c_str() );


}