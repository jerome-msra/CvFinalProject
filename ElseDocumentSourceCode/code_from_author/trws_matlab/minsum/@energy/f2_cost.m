function c = f2_cost(E,st,labeling)
	t = E.f2.index.type{st};
	i = E.f2.index.i{st};
	C = E.f2.store{t}.f_cost(E.f2.store{t}.data{i});
	c = C(labeling(1),labeling(2));
end