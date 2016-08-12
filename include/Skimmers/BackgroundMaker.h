#ifndef BACKGROUND_MAKER_H
#define BACKGROUND_MAKER_H

class BackgroundMaker : public HistoAnalyzer {
public:
	virtual const char* classname() const { return "BackgroundMaker"; }
	BackgroundMaker() {}
	~BackgroundMaker() {}

	virtual void initialize(){
		HistoAnalyzer::initialize();


	}

protected:


	virtual void make(){
		INFO( classname(), "" );

		

	}
	
};

#endif	