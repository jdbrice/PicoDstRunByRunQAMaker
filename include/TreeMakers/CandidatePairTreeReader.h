#ifndef CANDIDATE_PAIR_TREE_READER_H
#define CANDIDATE_PAIR_TREE_READER_H

#include "IObject.h"
using namespace jdb;

class CandidatePairTreeReader : public IObject
{
public:
	virtual const char * classname() const { return "CandidatePairTreeReader"; }
	CandidatePairTreeReader( TChain * _chain = nullptr ) {
		create( _chain );
	}
	~CandidatePairTreeReader(){

	}

	TTree               * mTree      = nullptr;
	TClonesArray        * pairsArray = nullptr;
	CandidatePair       * pair       = nullptr;
	Long64_t              eventHash  = -1;

	string treeType;

	void create( TChain * _chain ){
		treeType= "";
		if ( _chain == nullptr ) return;
		
		TBranch * bPairs = _chain->GetBranch( "Pairs" );
		if ( bPairs ){
			string branchClassName = bPairs->GetClassName();
			if ( "TClonesArray" == branchClassName )
				treeType = "SameEvent";
			else if ( "CandidatePair" == branchClassName )
				treeType = "MixedEvent";
			else {
				WARN( classname(), "NO TreeType found!?" );
				WARN( classname(), "GetClassName : " << bPairs->GetClassName() );
			}
		}

		if ( "MixedEvent" == treeType )
			_chain->SetBranchAddress( "Pairs", &pair );
		else if ( "SameEvent" == treeType )
			_chain->SetBranchAddress( "Pairs", &pairsArray );
		
		INFO( classname(), "TreeType = " << treeType );
		_chain->SetBranchAddress( "mEventHash", &eventHash );

	}


	CandidatePair * getPair( int index = 0 ){
		
		if ( treeType == "MixedEvent" ){
			return pair;
		} else if ( pairsArray != nullptr ){
			return (CandidatePair*)pairsArray->At( index );
		}
		return nullptr;
	}

	int getNPairs() {
		if ( "MixedEvent" ==  treeType ) return 1;
		else if ( pairsArray != nullptr ) return pairsArray->GetEntries();
		return 0;
	}
	
	
};


#endif