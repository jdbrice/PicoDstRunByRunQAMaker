#ifndef TRIGGER_FILTER_H
#define TRIGGER_FILTER_H

#include "IPicoDst.h"
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

	void fillTriggerQA( const shared_ptr<IPicoDst>& pico, string hName, string sdir, const shared_ptr<HistoBook>& book ){
		book->cd( sdir );
		if ( pico->isDiMuon() ){
			book->fill( hName, "dimuon" );
		}
		if ( pico->isDiMuonHFT() ){
			book->fill( hName, "dimuonHFT" );
		}
		if ( pico->isSingleMuon() ){
			book->fill( hName, "singleMu" );
		}
		if ( pico->isEMuon() ){
			book->fill( hName, "emu" );
		}

	}
	
};

#endif