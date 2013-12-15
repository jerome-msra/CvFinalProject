function G = flip_direction(G)

G.E = flipud(G.E);

bout = G.out;
G.out = G.in;
G.in = bout;

end