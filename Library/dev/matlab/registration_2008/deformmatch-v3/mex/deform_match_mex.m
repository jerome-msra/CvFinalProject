%% [x LB] = deform_match_mex(C,dreg_params)
%%  Generic matching provided the data terms
%%  This is low-level function. For higher-level function see IM_MATCH
%%	
%%
%%	Implements the technique described in 
%%		 Research Report CTU--CMP--2006--08
%%		 Efficient {MRF} Deformation Model for Image Matching
%%		 A. Shekhovtsov, I. Kovtun, V. Hlavac
%%
%%	Input:
%%		C - [K1 x K2 x n1 x n2] -- cost data array. Here (K1,K2) is search window size
%%				(n1,n2) is size of data to match;
%%
%%		dreg_params = [deform_reg eps maxit maxd fix_strategy 0 0];
%%				deform_reg - double (0.0)-- constant in abs difference gegularization applied to allowd displacements
%%			  eps - double (0.01) -- convergence tolerance
%%        maxit - double (20) -- maximum number of macro iterations
%%				maxd - double (1.0) -- maximum allowed relative displacement of neighboring blocks
%%			  fix_strategy double 0 or 1 (1) -- slelects heuristic for labeling fixation: 0-single-pass, 1-gradual (better but slower)
%%				reg_model - double -- reserved to select regularization model
%%				reg_th - double -- reserved to select gerularization threshold
%%				
%%
%%	Output:
%%		x: int32[n1 x m1 x 2] - the found deformation field:
%%			x[:,:,1] - x-component, x[:,:,2] - y-component
%%
%%
%%   See also MATCHING_COST_Q, IM_MATCH
%%
%%   (c) Alexander Shekhovtsov%%