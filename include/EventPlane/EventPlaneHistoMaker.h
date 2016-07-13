#ifndef EVENT_PLANE_HISTO_MAKER_H
#define EVENT_PLANE_HISTO_MAKER_H

// RooBarb
#include "XmlPoint.h"
#include "XmlFunction.h"


#include "CandidateSkimmer.h"
#include "EventPlaneCorr.h"

class EventPlaneHistoMaker : public CandidateSkimmer
{
public:
	virtual const char* classname() const { return "EventPlaneHistoMaker"; }
	EventPlaneHistoMaker(){}
	~EventPlaneHistoMaker(){}

	TH1D * hPsi2, *hPsi2Centered, *hPsi2Flattened;
	TH2D * hQxQy, *hQxQyCentered;

	virtual void initialize();

protected:

	EventPlaneCorr epc;

	virtual void analyzeEvent();
	virtual void postEventLoop();

};

#endif