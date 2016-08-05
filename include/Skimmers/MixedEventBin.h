#ifndef MIXED_EVENT_BIN_H
#define MIXED_EVENT_BIN_H

#include "IConfig.h"
#include "IObject.h"
#include "HistoBins.h"

#include <memory>
#include "CandidateEvent.h"

class MixedEventBin : public IConfig, public IObject
{
public:
	virtual const char* classname() const { return "MixedEventBin"; }
	MixedEventBin(){

	}
	MixedEventBin( XmlConfig _config, string _nodePath ) {
		load( _config, _nodePath );
	}
	~MixedEventBin(){

	}

	void load( XmlConfig _config, string _nodePath ){
		config = _config;
		nodePath = _nodePath;

		vxBins = shared_ptr<HistoBins>( new HistoBins( _config, _nodePath + ".VertexX" )  );
		vyBins = shared_ptr<HistoBins>( new HistoBins( _config, _nodePath + ".VertexY" )  );
		vzBins = shared_ptr<HistoBins>( new HistoBins( _config, _nodePath + ".VertexZ" )  );
	}

	int eventBin( CandidateEvent * event ) {

		// INFO( classname(), vzBins->toString() );
		int vzBin = vzBins->findBin( event->mPrimaryVertex_mX3 );

		return vzBin;
	}

protected:

	shared_ptr<HistoBins> 	vzBins, 
							vxBins, 
							vyBins;

	
};


#endif