function f2 = get_f2_full(E)

nV = get(E.G,'n');
nE = get(E.G,'m');
K = E.K;

f2 = zeros(K,K,nE);
for t = unique(E.f2.index.type)
	ii = E.f2.index.type==t;
	index = E.f2.index.i(ii);
	f2(:,:,ii) = E.f2.store{t}.f_cost(last_index(E.f2.store{t}.data,index));
end

end