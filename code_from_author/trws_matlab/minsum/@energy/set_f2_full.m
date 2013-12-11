function E = set_f2_full(E,f2)
%
% E = set_f2_full(E,f2) sets all pairwise potentials in the form of one 3d array
%
%	Input:
%		E - [@energy]
%		f2 - [K x K x nE] -- full 3d array of pairwise potentials
%
%
	nE = get(E.G,'m');
	K = E.K;
	E.f2.index.i = [1:nE];
	E.f2.index.type(:) = 1;
	E.f2.store{1}.data = f2;
end