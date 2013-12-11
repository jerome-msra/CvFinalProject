function [x LB phi M_bw] = alg_trws(energy,eps, maxiter,M_bw0)
%
%	[x LB phi M_bw] = alg_trws(energy,eps, maxiter,M_bw0=[]) -- energy 
%	minimization by TRW-S algorithm dual suboptimal to LP-relaxation
%	
%	Input:
%		energy [@energy] -- pairwise gibbs energy function
%		eps	[double] (0.001) -- precision when terminate the convergence 
%			(terminate if the inf-norm on messages and min-marginals < eps)
%		maxiter [integer] (20) -- maximum number of iterations
%		M_bw0 [K x nE] ([]) -- starting dual point (for repeated calls)
%
%	Output:
%		x [1 x nV] -- labeling
%		LB -- lower bound achieved (dual cost)
%		phi [K x nV] -- min-marginals
%		M_bw [K x nE] -- best found dual point
%
%	See also ENERGY/ENERGY, GRAPH/GRAPH, ALG_LP

if(~exist('eps','var') || isempty(eps))
	eps = 0.01;
end

if(~exist('maxiter','var') || isempty(maxiter))
	maxiter = 20;
end

if(~exist('M_bw0','var'))
	M_bw0 = [];
end

G = get(energy,'G');

V = get(G,'V');
E = get(G,'E');

f1 = get(energy,'f1');
f2 = get_f2_full(energy);

params = [eps maxiter];

[x LB phi M_bw] = alg_trws_mex(int32(V-1),int32(E-1),-f1,-f2,params,M_bw0);

LB = -LB;
phi = -phi;
x = double(x')+1;

end