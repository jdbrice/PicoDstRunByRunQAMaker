import numpy as np

class DimuonBinMaker :

	def makeBins( self, **kwargs ) :
		# n_w_bins, w_width, n_phi_bins, phi_width, n_jpsi_bins, jpsi_width, lmr_width, imr_width, hmr_width ) :
		w_center = .782
		phi_center = 1.019
		jpsi_center = 3.096

		w_lmr = kwargs[ "w_lmr" ]
		w_imr = kwargs[ "w_imr" ]
		w_hmr = kwargs[ "w_hmr" ]
		n_w = kwargs[ "n_w" ]
		w_width = kwargs[ "w_width" ]
		n_phi = kwargs[ "n_phi" ]
		phi_width = kwargs[ "phi_width" ]
		n_jpsi = kwargs[ "n_jpsi" ]
		jpsi_width = kwargs[ "jpsi_width" ]

		binEdges = []
		w_left = w_center - ( n_w / 2.0 ) * w_width
		w_right = w_center + ( n_w / 2.0 ) * w_width
		phi_left = phi_center - ( n_phi / 2.0 ) * phi_width
		phi_right = phi_center + ( n_phi / 2.0 ) * phi_width
		jpsi_left = jpsi_center - ( n_jpsi / 2.0 ) * jpsi_width
		jpsi_right = jpsi_center + ( n_jpsi / 2.0 ) * jpsi_width


		for edge in np.arange( 0, w_left, w_lmr ) :
			binEdges.append( edge )
		for edge in np.linspace( w_left, w_right, n_w + 1 ) :
			binEdges.append( edge )
		for edge in np.arange( w_right + w_lmr, phi_left, w_lmr ) :
			binEdges.append( edge )
		for edge in np.linspace( phi_left, phi_right, n_phi + 1 ) :
			binEdges.append( edge ) 
		for edge in np.arange( phi_right + w_imr, jpsi_left, w_imr ) :
			binEdges.append( edge ) 
		for edge in np.linspace( jpsi_left, jpsi_right, n_jpsi + 1 ) :
			binEdges.append( edge ) 
		for edge in np.arange( jpsi_right + w_hmr, 12, w_hmr ) :
			binEdges.append( edge ) 

		return binEdges
			



