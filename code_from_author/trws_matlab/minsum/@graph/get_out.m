function out = get_out(G,v)
	%out = G.out{v};
	out = find(G.out(v,:));
end