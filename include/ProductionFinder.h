#ifndef PRODUCTION_FINDER_H
#define PRODUCTION_FINDER_H

#include <vector>
#include <map>
#include <string>

using namespace std;

class ProductionFinder
{
public:
	ProductionFinder();
	~ProductionFinder();

	static void buildMap(){
		for ( int rn : ProductionFinder::runs_production_2014 ){
			production_map[ rn ] = "AuAu_200_production_2014";
		}
		for ( int rn : ProductionFinder::runs_production_low_2014 ){
			production_map[ rn ] = "AuAu_200_production_low_2014";
		}
		for ( int rn : ProductionFinder::runs_production_mid_2014 ){
			production_map[ rn ] = "AuAu_200_production_mid_2014";
		}
		for ( int rn : ProductionFinder::runs_production_high_2014 ){
			production_map[ rn ] = "AuAu_200_production_high_2014";
		}
	}


	static bool isAuAu200Production2014( int rn ){
		if ( production_map.size() <= 0 )
			buildMap();
		return ( "AuAu_200_production_2014" == production_map[ rn ] );
	}
	static bool isAuAu200Production2014Low( int rn ){
		if ( production_map.size() <= 0 )
			buildMap();
		return ( "AuAu_200_production_low_2014" == production_map[ rn ] );
	}
	static bool isAuAu200Production2014Mid( int rn ){
		if ( production_map.size() <= 0 )
			buildMap();
		return ( "AuAu_200_production_mid_2014" == production_map[ rn ] );
	}
	static bool isAuAu200Production2014High( int rn ){
		if ( production_map.size() <= 0 )
			buildMap();
		return ( "AuAu_200_production_high_2014" == production_map[ rn ] );
	}

	static string productionFor( int rn ){

		if ( production_map.size() <= 0 )
			buildMap();
		return production_map[ rn ];
	}



protected:
	static const vector<int> runs_production_2014;
	static const vector<int> runs_production_low_2014;
	static const vector<int> runs_production_mid_2014;
	static const vector<int> runs_production_high_2014;

	static map<int, std::string> production_map;
	
};


#endif