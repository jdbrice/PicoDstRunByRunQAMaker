#ifndef TRIGGER_FILTER_H
#define TRIGGER_FILTER_H

#include "IPicoDst.h"

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
	
};

#endif