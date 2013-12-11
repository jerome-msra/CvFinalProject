function x_dense = dense_field_fw(tt, sz)
%
%	x_dense = dense_field(tt, sz)
% Create dense field map from geom_transform forward mapping
%

	a = repmat([1:sz(1)]',1,sz(2));
	b = repmat([1:sz(2)],sz(1),1);
	[u um] = im_transform(tt,a);
	[v vm] = im_transform(tt,b);
	u = u-a;
	v = v-b;
	u(~um)=0;
	v(~vm)=0;
	x_dense = cat(3,u,v);
end