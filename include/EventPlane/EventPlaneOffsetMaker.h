#ifndef EVENT_PLANE_OFFSET_MAKER_H
#define EVENT_PLANE_OFFSET_MAKER_H

#include "EventPlaneCorr.h"

class EventPlaneOffsetMaker : public HistoAnalyzer
{
public:
	virtual const char *classname() const {return "EventPlaneOffsetMaker"; }
	EventPlaneOffsetMaker();
	~EventPlaneOffsetMaker();

	virtual void initialize(){
		HistoAnalyzer::initialize();
	}


protected:
	EventPlaneCorr epc;	

	virtual void make(){

		fitQxQy();
		cout << epc.toXml() << endl;

	}

	void EventPlaneMaker::fitQxQy(){
		DEBUG( classname(), "" );

		TH2D *hQxQy = (TH2D*)inFile->Get( "QxQy" );
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
	
};
#endif