#ifndef RUN_MAP_FACTORY_H
#define RUN_MAP_FACTORY_H

#include <vector>
#include <map>
#include <string>

using namespace std;

class RunMapFactory
{
public:
	RunMapFactory( bool _dynamic = false ){
		dynamic = _dynamic;

		if ( false == dynamic ){
			int runIndex = 0;

			for ( int iRun : run_14_auau_200_picodst_runs ){
				runIndices[ iRun ] = runIndex;
				indexRuns[ runIndex ] = iRun;
				runIndex++;
			}	
		} else {
			nextRunIndex = -1; // so that it starts at 0
		}
		
	}
	~RunMapFactory(){}

	inline int indexForRun( int rn ){
		if ( dynamic ){
			if ( runIndices.count( rn ) >= 1 )  // already set, then return it
				return runIndices[ rn ];
			else { // push this one onto the map
				nextRunIndex++; // makes it start at 0
				runIndices[ rn ] = nextRunIndex;
				return nextRunIndex;
			}
		}
		return runIndices[ rn ];
	}

	inline int runForIndex( int index ){
		return indexRuns[ index ];
	}

protected:
	map< int, int > runIndices;
	map< int, int > indexRuns;
	static const vector<int> run_14_auau_200_picodst_runs;
	

	bool dynamic;
	int nextRunIndex;

};

#endif