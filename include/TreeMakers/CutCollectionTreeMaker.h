#ifndef CUT_COLLECTION_TREE_MAKER_H
#define CUT_COLLECTION_TREE_MAKER_H

#include "IObject.h"
#include "CutCollection.h"

#include <string>
#include <vector>

#include "TNtuple.h"

class CutCollectionTreeMaker : public IObject
{
public:
	virtual const char * classname() const { return "CutCollectionTreeMaker"; }
	CutCollectionTreeMaker(){}
	~CutCollectionTreeMaker(){}

	static void makeCutTree( CutCollection &ccol, string name ){
		INFO( "CutCollectionTreeMaker", "Making Cuts Ntuple named " << name );

		string vars = "";
		vector<float> data;
		string sep = "";
		for ( auto kv : ccol.ranges ){
			vars += sep + kv.first + "_min";
			sep=":";
			vars += sep + kv.first + "_max";

			data.push_back( kv.second->min );
			data.push_back( kv.second->max );
		}
		INFO( "CutCollectionTreeMaker", "NTUPLE vars = " << vars );
		INFO( "CutCollectionTreeMaker", "data : " << data.size() );

		TNtuple *ntuple = new TNtuple(name.c_str(),name.c_str(), vars.c_str() );
		ntuple->Fill( data.data() );
	}
	
};


#endif