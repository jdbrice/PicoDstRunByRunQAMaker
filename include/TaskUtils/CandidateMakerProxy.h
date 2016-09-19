#ifndef CANDIDATE_MAKER_PROXY_H
#define CANDIDATE_MAKER_PROXY_H

#include "CommandRunner.h"
#include "EventHasher.h"

class CandidateMakerProxy : public CommandRunner
{
public:
	virtual const char* classname() const { return "CandidateMakerProxy"; }
	CandidateMakerProxy() {}
	~CandidateMakerProxy() {}

protected:
	EventHasher eht;

	virtual void overrideConfig(){
		INFO( classname(), "" );

		eht.load( config, nodePath + ".MixedEventBins" );
		int mh = eht.maxPossibleHash();
		INFO( classname(), "maxHash = " << mh );
		int _jobIndex = config.getInt( "jobIndex", -1 );
		int nJobs = config.getInt( nodePath + ":nJobs", 1 );
		int splitBy = config.getInt( nodePath + ":splitBy", 10 );

		INFO( classname(), "raw jobIndex = " << _jobIndex );
		INFO( classname(), "nJobs=" << nJobs  << " (to cover dataset once)");
		INFO( classname(), "splitBy=" << splitBy << "( max number of event Hashes to cover - ie open files! )");

		int jobIndex = _jobIndex % nJobs;
		int ehIndex = _jobIndex / nJobs;
		int minEventHash = ehIndex * splitBy;
		int maxEventHash = (ehIndex + 1) * splitBy;


		INFO( classname(), "jobIndex=" << jobIndex );
		INFO( classname(), "ehIndex=" << ehIndex );
		INFO( classname(), "minEventHash=" << minEventHash );
		INFO( classname(), "maxEventHash=" << maxEventHash );

		string proxiedNodePath = config[ nodePath + ".ProxiedMaker:nodePath" ];
		string proxiedConfig   = config[ nodePath + ".ProxiedMaker:config" ];

		string command = config.getString( "CWD:exe" ) + "app";
		command += " " + config[ "CWD:cfg" ] + proxiedConfig;
		command += " --jobIndex=" + ts( jobIndex );
		command += " --" + proxiedNodePath + ".EventHash:min=" + ts( minEventHash );
		command += " --" + proxiedNodePath + ".EventHash:max=" + ts( maxEventHash );
		INFO( classname(), "command = " << command );
		config.set( nodePath + ".command", command );

	}
	
};

#endif