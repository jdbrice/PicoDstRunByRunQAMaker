

void test(){
	
	ifstream inData;
	inData.open("datafile.dat");

	// short vpdTubeRes;
	// unsigned char vpdTubeId;
	// unsigned char vpdTubeStatusFlag;
	// unsigned char vpdTubeTriggerFlag;

	int a=0, b=0, c=0, d=0;
	for ( int i = 0; i < MAX_DB_INDEX; i++ ){
		inData >> a >> b >> c >> d;
		cout << a <<", " << b << ", " << c << ", " << d << endl;
	}

}