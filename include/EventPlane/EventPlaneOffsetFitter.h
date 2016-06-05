#ifndef EVENTPLANE_OFFSET_FITTER_H
#define EVENTPLANE_OFFSET_FITTER_H

// RooBarb
#include "HistoAnalyzer.h"
using namespace jdb;


// Project
#include "EventPlaneCorr.h"


class EventPlaneOffsetFitter : public HistoAnalyzer {
public:
	virtual const char * classname() const { return "EventPlaneOffsetFitter"; }
	EventPlaneOffsetFitter();
	~EventPlaneOffsetFitter();

	virtual void make();
};

#endif