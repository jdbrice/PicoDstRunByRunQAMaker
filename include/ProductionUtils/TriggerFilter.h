#ifndef TRIGGER_FILTER_H
#define TRIGGER_FILTER_H

#include "IPicoDst.h"
#include "CandidateEvent.h"


#include "HistoBook.h"

#include <string>
#include "vector"
#include <memory>

class TriggerFilter
{
protected:
	vector<string> triggerNames;

public:
	TriggerFilter() {};
	TriggerFilter( vector<string> _triggerNames ){
		setTriggers( _triggerNames );
	}
	void setTriggers( vector<string> _triggerNames ){
		triggerNames = _triggerNames;
	}
	~TriggerFilter(){}

	bool anyTrigger( shared_ptr<IPicoDst> pico ){
		if ( triggerNames.size() >= 1 ){ // 0 == all triggers
			for ( string trig : triggerNames ){
				if ( pico->isMtdTrigger( trig ) ) {
					return true;
				}
			}
		} else {
			return true;
		}

		return false;
	}


	bool anyTrigger( CandidateEvent *_event) {
		if ( triggerNames.size() >= 1 ){ // 0 == all triggers
			for ( string trig : triggerNames ){
				if ( _event->isMtdTrigger( trig ) ) {
					return true;
				}
			}
		} else {
			INFO( "TriggerFilter", "Return true" );
			return true;
		}

		return false;
	}

	void fillTriggerQA( const shared_ptr<IPicoDst>& pico, string hName, string sdir, const shared_ptr<HistoBook>& book ){
		book->cd( sdir );
		bool knownTrigger = false;

		if ( pico->isDiMuon() ){
			book->fill( hName, "dimuon" );
			knownTrigger = true;
		}
		if ( pico->isDiMuonHFT() ){
			book->fill( hName, "dimuonHFT" );
			knownTrigger = true;
		}
		if ( pico->isSingleMuon() ){
			book->fill( hName, "singleMu" );
			knownTrigger = true;
		}
		if ( pico->isEMuon() ){
			book->fill( hName, "emu" );
			knownTrigger = true;
		}

		if ( false == knownTrigger ){
			book->fill( hName, "unknown" );
		}

	}
	
};

#endif