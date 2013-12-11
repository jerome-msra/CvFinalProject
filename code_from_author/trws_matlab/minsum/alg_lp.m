function [x LB mu1 mu2 phi duals] = alg_lp(energy)
%
%	[x LB mu1 mu2 phi] = alg_lp(energy) -- LP-relaxation of energy 
%		minimization via linprog. Only small instances are feasible.
%
%	Input:
%		energy [@energy] -- pairwise gibbs energy function to minimize
%
%	Output:
%		x [1 x nV] -- best integral labeling found
%		LB [double] -- lower bound (best dual cost)
%		mu1 [K x nV] -- relaxed label indicators
%		mu2 [K x K x nE] -- relaxed pairwise label indicators
%		phi -- dual variables
%
%

L = get_poly(energy);
K = get(energy,'K');

[A_eq b_eq] = get_A(L);
theta = get_theta(energy);

%ops = optimset('LargeScale','on','Display','iter');
ops = optimset('LargeScale','on','Display','off');
[mus,fval,exitflag,output,lambda] = linprog(theta,[],[],A_eq,b_eq,zeros(length(theta),1),[],[],ops);
%[fval,mus,duals,stat] = lp_solve(-theta,A_eq,b_eq,zeros(size(A_eq,1),1),zeros(length(theta),1),[],[]);

LB = fval;
duals = lambda.eqlin;

phi = duals'*A_eq;

mu_s = get_mu1_index(L);
mu_st = get_mu2_index(L);

mu1 = reshape(mus(mu_s(:)),K,[]);
mu2 = reshape(mus(mu_st(:)),K,K,[]);
[a x] = max(mu1,[],1);

nnint = sum(sum(mu1.^2,1)<1-1e-3);
fprintf('LP: Non-integer nodes: %i\n',nnint);

%c1 = f1(:)'*mus(mu_s(:))
%c2 = f2(:)'*mus(mu_st(:))

end