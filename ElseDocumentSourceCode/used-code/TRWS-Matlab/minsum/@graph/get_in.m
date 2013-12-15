function in = get_in(G,v)
	%in = G.in{v};
	in = find(G.in(v,:));
end