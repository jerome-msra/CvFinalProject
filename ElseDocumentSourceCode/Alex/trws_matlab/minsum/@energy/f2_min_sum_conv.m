function y = f2_min_sum_conv(E,st,x)
	t = E.f2.index.type(st);
	i = E.f2.index.i(st);
	y = E.f2.store{t}.f_min_sum_conv(last_index(E.f2.store{t}.data,i),x);
end