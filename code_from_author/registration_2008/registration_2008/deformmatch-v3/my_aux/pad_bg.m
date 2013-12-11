function [nI nx0] =  pad_bg(I,x0,esz)

sz2 = msize(I,[1 2]);
x1 = x0+esz-1;

nI = ones(esz,class(I));

sx0 = max(x0,[1 1]);
sx1 = min(sz2,x1);

tx0 = sx0-x0+1;
tx1 = sx1-x0+1;

nI(tx0(1):tx1(1),tx0(2):tx1(2),:) = I(sx0(1):sx1(1),sx0(2):sx1(2),:);
nx0 = [1 1];

end