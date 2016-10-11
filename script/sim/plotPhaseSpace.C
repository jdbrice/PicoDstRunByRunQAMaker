


void plotPhaseSpace(){
	jdb::XmlConfig cfg( "phaseSpace.xml" );
	using namespace jdb;

	HistoBook book( "data.root", cfg );
	HistoBins phiBins( cfg, "b.phi" );

	book.makeAll( "histos" );

	TChain * c = new TChain( "genevents" );
	c->Add( "*.root" );
	int NN = c->GetEntries();

	c->SetMakeClass(1);
	Float_t px[3];
	Float_t py[3];
	Float_t pz[3];
	Int_t nPlcs;
	Int_t mParticles_;
	c->SetBranchAddress( "mParticles", &mParticles_ );
	c->SetBranchAddress( "mParticles.mPx", &px );
	c->SetBranchAddress( "mParticles.mPy", &py );
	c->SetBranchAddress( "mParticles.mPz", &pz );
	c->SetBranchAddress( "mNumParticles", &nPlcs );

	// DataSource ds( "genevents", c );

	cout << "Get Entries == " << NN << endl;
	for ( int i = 0; i < NN; i++ ){
		cout << " [" << i << "] " << endl;
		c->GetEntry(i);
		cout << "nPlcs = " << nPlcs << endl;
		cout << "P=(" << px[0] << ", " << py[0] << ", " << pz[0] << ")" << endl;
		cout << "P=(" << px[1] << ", " << py[1] << ", " << pz[1] << ")" << endl;
		cout << "P=(" << px[2] << ", " << py[2] << ", " << pz[2] << ")" << endl;

		TLorentzVector lv1, lv2, lv;
		lv1.SetXYZM( px[1], py[1], pz[1], 0.105 );
		lv2.SetXYZM( px[2], py[2], pz[2], 0.105 );

		lv = lv1 + lv2;
		cout << "Mass = " << lv.M() << endl;

		book.fill( "mass_vs_pt_all", lv.M(), lv.Pt() );

		if ( lv1.Pt() > 1.0 && lv2.Pt() > 1.0 )
			book.fill( "mass_vs_pt_cut", lv.M(), lv.Pt() );


		int phib1 = phiBins.findBin( lv1.Phi() );
		int phib2 = phiBins.findBin( lv2.Phi() );

		// cout << "phi bin " << phib1 << " % 2 = " << phib1 % 2 << endl;

		if (  lv1.Pt() < 1.0 || lv2.Pt() < 1.0 ) continue;
		if ( fabs( lv1.DeltaPhi( lv2 )) < 0.05  ) continue;


		book.fill( "d1_phi", lv.Phi() );
		book.fill( "mass_vs_pt_dphi", lv.M(), lv.Pt() );




	}
	
	

}