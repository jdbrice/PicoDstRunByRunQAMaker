#ifndef FILE_LIST_MAKER_H
#define FILE_LIST_MAKER_H

#include <glob.h>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// RooBarb
#include "TaskRunner.h"


class FileListMaker : public TaskRunner {
public:
	virtual const char* classname() const { return "FileListMaker"; }
	FileListMaker() {}
	~FileListMaker(){}

	virtual void init(XmlConfig &_config, string _nodePath="", int _jobIndex = -1) {
		TaskRunner::init( _config, _nodePath, _jobIndex );
		initialize();
	}
	virtual void init(XmlConfig &_config, string _nodePath="", string _fileList = "", string _jobPostfix = "") {
		TaskRunner::init( _config, _nodePath, _fileList, _jobPostfix );
		initialize();
	}

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

		INFO( classname(), "glob: " << globStr );
		vector<string> paths = glob( globStr );
		INFO( classname(), "Found " << paths.size() << plural( paths.size(), " path", " paths" ) );

		string outfn = config.getXString( nodePath + ".output.File:url" );
		INFO( classname(), "OUTPUT: " << outfn );
		ofstream outf( outfn.c_str() );

		for ( string path : paths ){
			INFO( classname(), "PATH : " << path );
			outf << path << endl;
		}
		outf.close();
	}

};


#endif