#ifndef EVENT_FILTER_H
#define EVENT_FILTER_H

#include "PicoDst16aReader.h"
#include "CandidateEvent.h"
#include "CutCollection.h"

class EventFilter
{
public:
	EventFilter(){}
	~EventFilter(){}


	static void setDefaultEventCuts( CutCollection &ccol ){
		ccol.setDefault( "zVertex"             , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );
		ccol.setDefault( "zVertexDelta"        , std::numeric_limits<double>::lowest() , std::numeric_limits<double>::max() );

		ccol.setDefault( "bin16"               , 0 , 16 );

	}

	static bool keepEvent( shared_ptr<PicoDst16aReader> _pico, CandidateEvent *_event, CutCollection &ccol, const shared_ptr<HistoBook>& book = nullptr ){

		bool passAllCuts = true;
	
		bool makeQA = true;
		if ( nullptr == book  )
			makeQA = false;

		double zVertex = _pico->event()->primaryVertex().z();
		double zVpd = _pico->event()->vzVpd();
		
		// zVertexDelta
		double zDelta = zVertex - zVpd;

		// zVertex Selection
		if ( !ccol[ "zVertex" ]->inInclusiveRange( zVertex ) ){
			passAllCuts = false;
		} else if ( makeQA ) {
			// passEventCut( "zVertex", passAllCuts );
		}
		
		if ( abs(zDelta) > ccol[ "zVertexDelta" ]->max ){
			passAllCuts = false;
		} else if ( makeQA ) {
			// passEventCut( "zVertexDelta", passAllCuts );
		}

		int bin16 = _event->mBin16;
		if ( !ccol[ "bin16" ]->inInclusiveRange( bin16 ) ){
			passAllCuts = false;
		} else if ( makeQA ) {
			// passEventCut( "zVertex", passAllCuts );
		}

		return passAllCuts;
	}
	
};

#endif