function [nI nx0] =  pad_bg_add(I,addsz,val)
%
%  [nI nx0] =  pad_bg_add(I,addsz) -- adds free space around the image
%

if length(addsz==1)
	addsz = [addsz addsz];
end

if(~exist('val','var')|| isempty(val))
	val = I(1,1,:);
end

x0 =-floor(addsz/2);
sz2 = msize(I,[1 2]);
esz  = sz2+addsz;

x1 = x0+esz-1;

nI = repmat(val,esz(1),esz(2));

sx0 = max(x0,[1 1]);
sx1 = min(sz2,x1);

tx0 = sx0-x0+1;
tx1 = sx1-x0+1;

nI(tx0(1):tx1(1),tx0(2):tx1(2),:) = I(sx0(1):sx1(1),sx0(2):sx1(2),:);
nx0 = [1 1];

end