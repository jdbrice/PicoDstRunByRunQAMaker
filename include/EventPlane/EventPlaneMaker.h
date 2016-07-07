#ifndef EVENT_PLANE_MAKER_H
#define EVENT_PLANE_MAKER_H

// RooBarb
#include "XmlPoint.h"
#include "XmlFunction.h"


#include "PicoDstSkimmer.h"
#include "EventPlaneCorr.h"

class EventPlaneMaker : public PicoDstSkimmer
{
public:
	virtual const char* classname() const { return "EventPlaneMaker"; }
	EventPlaneMaker(){}
	~EventPlaneMaker(){}

	TH1D * hPsi2, *hPsi2Centered, *hPsi2Flattened;
	TH2D * hQxQy, *hQxQyCentered;

	virtual void initialize();

protected:
	EventPlaneCorr epc;

	virtual void analyzeEvent();
	virtual void postEventLoop();

	float getQx() {
		return pico->EventPlane_mQx_eta_neg[0] + pico->EventPlane_mQx_eta_pos[0];
	}
	float getQy() {
		return pico->EventPlane_mQy_eta_neg[0] + pico->EventPlane_mQy_eta_pos[0];
	}
	int getNtrk(){
		return pico->EventPlane_mNtrk_eta_neg[0] + pico->EventPlane_mNtrk_eta_pos[0];
	}


	// gets the desired raw value from the pico
	// double getQ( string value, string var1, string var2="" );
	// int getNtrk( string mod1, string mod2="" );



};

#endif