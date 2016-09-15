#ifndef FOREST_MAKER_H
#define FOREST_MAKER_H

#include "IObject.h"
#include "Logger.h"


class ForestMaker : public IObject
{
public:
	virtual const char* classname() const { return "ForestMaker"; }
	ForestMaker() {}
	~ForestMaker() {}
	
	/* Creates a forest index from first to last
	 * 
	 */
	create( int _first, int _last ){
		first = _first;
		last = _last;

		for ( int i = first; i < last; i++ ){
			INFO( classname(), "Creating Tree Indexed @ " << i );
			forest[ i ] = shared_ptr<CandidateTreeMaker>( new CandidateTreeMaker(  ) );
			config.set( nodePath + ".EventHash", ts(i) );
			forest[ i ]->createFile( config.getXString( nodePath + ".EventHash:url" ) );
			forest[ i ]->setPicoDst( pico );
			forest[ iTree ]->createTree( );
		}

	}

protected:

	map< int, shared_ptr<CandidateTreeMaker> > forest;
	shared_ptr<CandidateTreeMaker> currentTree;
	int nOpenFiles = 0;
	int maxOpenFiles = 155;

	int first, last;


};


#endif