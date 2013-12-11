function t = mcompose(f2,f1)
%
% transform t = f2 * f1 -- that is t(x) = f2(f1(x))
%

%% extrapolate f2 so that f2(f1(x)) is defined for all x for which f1(x) is defined

a = mmeshgrid(size(f2.f));
df2 = f2.f-a;
df1 = f1.f-mmeshgrid(size(f1.f));
m = ceil(-min(mmin(df1,[1 2]),0));
M = ceil(max(mmax(df1,[1 2]),0));

A = repmat(df2(1,1,:),m(1),m(2));
B = repmat(df2(1,:,:),m(1),1);
C = repmat(df2(1,end,:),m(1),M(2));

D = repmat(df2(:,1,:),1,m(2));
E = repmat(df2(:,end,:),1,M(2));

F = repmat(df2(end,1,:),M(1),m(2));
G = repmat(df2(end,:,:),M(1),1);
H = repmat(df2(end,end,:),M(1),M(2));

sz = size(df2);

A1 = reshape([A  B  C],m(1),sz(2)+m(2)+M(2),2);
A2 =         [D df2 E];
A3 = reshape([F  G  H],M(1),sz(2)+m(2)+M(2),2);
edf2 = [A1; A2; A3];

%edf2 = [reshape([A  B  C],m(1),sz(2)+m(2)+M(2),2); [D df2 E]; reshape([F  G  H],M(1),sz(2)+m(2)+M(2),2)];


a = msub(mmeshgrid(size(edf2)),m,3);
ef2 = a+edf2;
		
for i=1:size(f2.f,3)
	aa = a(:,:,i);
	%% do lookup: r(x) = ef2(f1(x))
	r = interp2(a(:,:,2),a(:,:,1),ef2(:,:,i),f1.f(:,:,2),f1.f(:,:,1),'linear',nan);
	m = isnan(r);
	r(m) = aa(m);
	g(:,:,i) = r;
end
t = discrete_transform();
t.f = g;
end