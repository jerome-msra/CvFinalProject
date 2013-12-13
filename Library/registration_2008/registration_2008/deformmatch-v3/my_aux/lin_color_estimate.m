function A = lin_color_estimate(I1,mask1,I2,mask2)
if(isempty(mask1))
    mask1 = logical(ones(select(size(I1),[1 2])));
end
if(~exist('mask2','var') || isempty(mask2))
    mask2 = logical(ones(select(size(I2),[1 2])));
end

mask = mask1 & mask2;

I1 = im2double(I1);
I2 = im2double(I2);

d = size(I1,3);

x = select(I1,mask,[1:d]);
y = select(I2,mask,[1:d]);

diff = sum((x-y).^2,2);
ind = diff<0.02;

if(nnz(ind)/nnz(mask)<0.1)
	A = eye(3,4);
	return;
end

x = x(ind,:);
y = y(ind,:);

x(:,d+1)=1;

Z = x'*x;
Y = x'*y;

A = (Z\Y)';

end