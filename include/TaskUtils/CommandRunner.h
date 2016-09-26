#ifndef COMMAND_RUNNER_H
#define COMMAND_RUNNER_H

#include <glob.h>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

// RooBarb
#include "TaskRunner.h"


class CommandRunner : public TaskRunner {
public:
	virtual const char* classname() const { return "CommandRunner"; }
	CommandRunner() {}
	~CommandRunner(){}

	virtual void init(XmlConfig &_config, string _nodePath ) {
		TaskRunner::init( _config, _nodePath );
		initialize();
	}
	// virtual void init(XmlConfig &_config, string _nodePath="", string _fileList = "", string _jobPostfix = "") {
	// 	TaskRunner::init( _config, _nodePath, _fileList, _jobPostfix );
	// 	initialize();
	// }

	virtual void initialize(){
		globStr = config.getXString( nodePath + ":glob" );
	}
protected:
	string globStr = "";


	// SOURCE : http://stackoverflow.com/users/249230/szx via http://stackoverflow.com/questions/8401777/simple-glob-in-c-on-unix-system
	// THANK YOU
	inline std::vector<std::string> glob(const std::string& pat){
		using namespace std;
		glob_t glob_result;
		::glob(pat.c_str(),GLOB_TILDE,NULL,&glob_result);
		vector<string> ret;
		for(unsigned int i=0;i<glob_result.gl_pathc;++i){
		    ret.push_back(string(glob_result.gl_pathv[i]));
		}
		globfree(&glob_result);
		return ret;
	}


	virtual void make(){
		DEBUG( classname(), "" );

		// INFO( classname(), "glob: " << globStr );
		// vector<string> paths = glob( globStr );
		// INFO( classname(), "Found " << paths.size() << plural( paths.size(), " match", " matches" ) );

		INFO( classname(), "COMMAND : " << config.getXString( nodePath + ".command" ) );
		INFO( classname(), "executing" );

		// do it here
		system( config.getXString( nodePath + ".command" ).c_str() );

		INFO( classname(), "Completed" );

	}

};


#endif