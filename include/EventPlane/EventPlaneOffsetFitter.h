#ifndef EVENTPLANE_OFFSET_FITTER_H
#define EVENTPLANE_OFFSET_FITTER_H

// RooBarb
#include "HistoAnalyzer.h"
#include "XmlString.h"
using namespace jdb;


// Project
#include "EventPlaneCorr.h"



class EventPlaneOffsetFitter : public HistoAnalyzer {
public:
	virtual const char * classname() const { return "EventPlaneOffsetFitter"; }
	EventPlaneOffsetFitter() {}
	~EventPlaneOffsetFitter() {}

	virtual void make() {
		DEBUG( classname(), "" );

		if ( nullptr == inFile || !inFile->IsOpen() ){
			ERROR( classname(), "Invalid inFile, aborting" );
			return;
		}

		TH2D *hQxQy = (TH2D*)inFile->Get( "QxQy" ); 
		book->cd();
		TH1D* qy = (TH1D*)hQxQy->ProjectionY( "qy" );
		TH1D* qx = (TH1D*)hQxQy->ProjectionX( "qx" );

		double nSig_qx = config.getDouble( nodePath + ".fitQxQy:nSig_qx", 3.0 );
		double nSig_qy = config.getDouble( nodePath + ".fitQxQy:nSig_qy", 3.0 );

		TF1 fgaus( "fgaus", "gaus" );
		qx->Fit( &fgaus, "R", "", qx->GetMean() - nSig_qx * qx->GetStdDev(), qx->GetMean() + nSig_qx * qx->GetStdDev() );
		double m_qx = fgaus.GetParameter(1);
		qy->Fit( &fgaus, "R", "", qy->GetMean() - nSig_qy * qy->GetStdDev(), qy->GetMean() + nSig_qy * qy->GetStdDev() );
		double m_qy = fgaus.GetParameter(1);

		INFO( classname(), "x = " << m_qx );
		INFO( classname(), "y = " << m_qy );
		
		epc.setMeans( m_qx, m_qy );
		// export the parameters
		string outfn = XmlString( config ).format( config[ nodePath + ".output.File:url" ] );
		INFO( classname(), "Writing correction parameters to: " << outfn );
		ofstream outfile( outfn.c_str() );
		outfile << epc.toXml();
		outfile.close();
	}

protected:
	EventPlaneCorr epc;
};

#endif