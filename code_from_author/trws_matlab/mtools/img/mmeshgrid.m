function g = mmeshgrid(sz)
	a = repmat([1:sz(1)]',1,sz(2));
	b = repmat([1:sz(2)],sz(1),1);
	g = cat(3,a,b);
end