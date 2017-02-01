#ifndef EVENT_XML_EXPORTER_H
#define EVENT_XML_EXPORTER_H

#include "CandidateSkimmer.h"

#include <fstream>


class EventXMLExporter : public CandidateSkimmer
{
public:
	virtual const char* classname() const { return "EventXMLExporter"; }
	EventXMLExporter() {}
	~EventXMLExporter() {}

	virtual void initialize(){
		CandidateSkimmer::initialize();

		xmlFile.open( config.getXString( nodePath + ".output.File:url" ).c_str() );
		xmlFile << XmlConfig::declarationV1;
		xmlFile << endl << "<config>" << endl;
		xmlFile << "\t<Events>" << endl;
	}


	virtual void analyzeEvent(){
		xmlFile << "\t\t<E RId=" << quote( event->mRunId ) << " EId=" << quote(event->mEventId) << " B=" << quote( event->mBin16 )  << "/>" << endl;
	}

	virtual void postMake(){
		xmlFile << "\t</Events>" << endl;
		xmlFile << endl << "</config>" << endl;
		xmlFile.close();
	}

protected:
	ofstream xmlFile;
};

#endif