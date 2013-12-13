function x_dense = dense_field(tt, sz)
%
%	x_dense = dense_field(tt, sz)
% Create dense field map from geom_transform
%
	
	a = repmat([1:sz(1)]',1,sz(2));
	b = repmat([1:sz(2)],sz(1),1);
	x = [a(:)' ; b(:)'];
	y = pt_transform(tt,x);
	u = y(1,:);
	v = y(2,:);
	x_dense = cat(3,reshape(u,sz)-a,reshape(v,sz)-b);
end