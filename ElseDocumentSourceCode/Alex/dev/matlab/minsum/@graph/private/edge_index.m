function G = edge_index(G)
	G.out = cell(length(G.V),1);
	G.in = cell(length(G.V),1);
	for i=1:get(G,'m')
		v1 = G.E(1,i);
		v2 = G.E(2,i);
		G.out{v1} = [G.out{v1} i];
		G.in{v2} = [G.in{v2} i];
	end
end