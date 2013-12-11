function [I map] = fuse_mask(I, map, mask)

if(~exist('mask','var') || isempty(mask))
	mask = ones(size(I));
end

I = I+1;
mc = zeros(1,size(map,2));
mc(end)=1;
map = [mc; map];
I(~mask) = 1;
end