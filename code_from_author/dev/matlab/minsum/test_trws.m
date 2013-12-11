run ../mtools/mpath.m;
maddpath('alg_trws');

N = 10;
M = 10;
G = graph([N M]); K = 5;
E = energy(G,K);
E = random_instance(E,'potts- int32');

[x1 LB1 mu1] = alg_lp(E);
fprintf('LP bound: %d\n',LB1);
fprintf('LP solution: %d\n',E(x1));

[x LB] = alg_trws(E);

fprintf('TRW-S bound: %d\n',LB);
fprintf('TRW-S solution: %d\n',E(x));