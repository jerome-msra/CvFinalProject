%% This example will segment random noisy image with Potts model segmentation 
%% into K labels

run ../mtools/mpath.m

maddpath('../minsum');
maddpath('../minsum/alg_trws');

%% Create a graph (grid graph in this example)
N = 100; M = 100; 
G = graph([N M]); % grid graph N x M nodes
K = 5; E = energy(G,K); % Energy over graph G with 5 labels

nV = get(G,'n'); % number of vertices in the graph
nE = get(G,'m'); % number of edges in the graph

E = set_f1(E,rand(K,nV)); % set univariate potentials randomly

f2_pots = repmat(-0.2*eye(K,K),[1 1 nE]); % create Potts model pairwise potentials
E = set_f2_full(E,f2_pots); % set to energy

%% call trws (see doc alg_trws)
[x LB phi M_bw] = alg_trws(E,0.001,20);
fprintf('TRW-S bound: %d\n',LB);
fprintf('TRW-S solution: %d\n',cost(E,x));
%clear functions; %% unlock dll so that it can be recompiled

% show segmented image:
figure(1); imagesc(reshape(x,N,M)); colormap jet;