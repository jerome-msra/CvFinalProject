function fi = inverse(f,target_sz)
% fi = inverse(f) -- returns the inverse transform
%   f - discrete_transform
%	target_sz [2 x 1] integer (=size(f))-- desired size
%
%	//todo: handle undefined values by mask or extrapolate
if(~exist('target_sz','var') || isempty(target_sz))
	target_sz = size(f);
end
fi = discrete_transform();
fi.f = minverse(f.f,true(target_sz));
end