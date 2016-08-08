#ifndef EVENT_HASHER_H
#define EVENT_HASHER_H

#include "IConfig.h"
#include "IObject.h"
#include "HistoBins.h"
#include "HistoBook.h"

#include <memory>
#include "CandidateEvent.h"

class EventHasher : public IConfig, public IObject
{
public:
	virtual const char* classname() const { return "EventHasher"; }
	EventHasher(){

	}
	EventHasher( XmlConfig _config, string _nodePath ) {
		load( _config, _nodePath );
	}
	~EventHasher(){

	}

	void load( XmlConfig _config, string _nodePath ){
		config = _config;
		nodePath = _nodePath;

		vxBins = shared_ptr<HistoBins>( new HistoBins( _config, _nodePath + ".VertexX" )  );
		vyBins = shared_ptr<HistoBins>( new HistoBins( _config, _nodePath + ".VertexY" )  );
		vzBins = shared_ptr<HistoBins>( new HistoBins( _config, _nodePath + ".VertexZ" )  );
		bin16Bins = shared_ptr<HistoBins>( new HistoBins( _config, _nodePath + ".Bin16" )  );
		psiBins = shared_ptr<HistoBins>( new HistoBins( _config, _nodePath + ".Psi2" )  );

		INFO( classname(), "vxBins : " << vxBins->toString() );
		INFO( classname(), "vyBins : " << vyBins->toString() );
		INFO( classname(), "vzBins : " << vzBins->toString() );
		INFO( classname(), "bin16Bins : " << bin16Bins->toString() );
		INFO( classname(), "Psi2Bins : " << psiBins->toString() );
	}

	long int hash( CandidateEvent * event, shared_ptr<HistoBook> book = nullptr ) {

		// INFO( classname(), vzBins->toString() );
		int vxBin = vxBins->findBin( event->mPrimaryVertex_mX1 );
		int vyBin = vyBins->findBin( event->mPrimaryVertex_mX2 );
		int vzBin = vzBins->findBin( event->mPrimaryVertex_mX3 );
		int bin16Bin = bin16Bins->findBin( event->mBin16 );
		int psiBin = psiBins->findBin( event->psi() );

		DEBUG( classname(), "( " << event->mPrimaryVertex_mX1 << ", " << event->mPrimaryVertex_mX2 << ", " << event->mPrimaryVertex_mX3 << ", " << (int)event->mBin16 << ", " << event->psi() << " )" );
		DEBUG( classname(), "( " << vxBin << ", " << vyBin << ", " << vzBin << ", " << bin16Bin << ", " << psiBin << " )" );

		int vxN = vxBins->nBins();
		int vyN = vyBins->nBins();
		int vzN = vzBins->nBins();
		int bin16N = bin16Bins->nBins();
		int psiN = psiBins->nBins();

		DEBUG( classname(), "vxBin = "  	<< vxBin );
		DEBUG( classname(), "vyBin = "  	<< vyBin * vxN );
		DEBUG( classname(), "vzBin = "  	<< vzBin * (vxN * vyN) << " bc " << vxN << ", " << vyN );
		DEBUG( classname(), "bin16Bin = "  	<< bin16Bin * (vxN * vyN * vzN) );
		DEBUG( classname(), "psiBin = "  	<< psiBin * (vxN * vyN * vzN * bin16N) );

		long int i = vxBin + ( vyBin * vxN ) + ( vzBin * vxN * vyN ) + ( bin16Bin * vxN * vyN * vzN ) + ( psiBin * vxN * vyN * vzN * bin16N );

		if ( -1 == vxBin || -1 == vyBin || -1 == vzBin || -1 == bin16Bin || -1 == psiBin ) {
			WARN( classname(), "EventHash Out of Bounds: " );
			WARN( classname(), "( " << event->mPrimaryVertex_mX1 << ", " << event->mPrimaryVertex_mX2 << ", " << event->mPrimaryVertex_mX3 << ", " << (int)event->mBin16 << ", " << event->psi() << " )" );
			WARN( classname(), "( " << vxBin << ", " << vyBin << ", " << vzBin << ", " << bin16Bin << ", " << psiBin << " )" );
			return -1;
		}

		return i;
	}

	long int maxPossibleHash(){
		int vxN      = vxBins->nBins();
		int vyN      = vyBins->nBins();
		int vzN      = vzBins->nBins();
		int bin16N   = bin16Bins->nBins();
		int psiN     = psiBins->nBins();

		int vxBin    = vxN - 1;
		int vyBin    = vyN - 1;
		int vzBin    = vzN - 1;
		int bin16Bin = bin16N - 1;
		int psiBin   = psiN - 1;

		long int i = vxBin + ( vyBin * vxN ) + ( vzBin * vxN * vyN ) + ( bin16Bin * vxN * vyN * vzN ) + ( psiBin * vxN * vyN * vzN * bin16N );
		return i;
	}

protected:

	shared_ptr<HistoBins> 	vzBins, 
							vxBins, 
							vyBins,
							bin16Bins,
							psiBins;


	
};


#endif