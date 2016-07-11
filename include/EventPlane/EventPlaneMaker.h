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
	// EventPlaneCorr epc;

	virtual void analyzeEvent();
	virtual void postEventLoop();

};

#endif