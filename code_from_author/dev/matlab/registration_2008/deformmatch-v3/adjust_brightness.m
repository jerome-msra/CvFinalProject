function A = adjust_brightness(I1,mask1,I2,mask2)
if(isempty(mask1))
	mask1 = logical(ones(select(size(I1),[1 2])));
end
if(~exist('mask2','var') || isempty(mask2))
	mask2 = logical(ones(select(size(I2),[1 2])));
end

I1 = im2gray(im2double(I1));
I2 = im2gray(im2double(I2));

x = I1(mask1);
y = I2(mask2);

b1 = hist(x,20);
b2 = hist(y,20);
b1 = b1/sum(b1);
b2 = b2/sum(b2);
%figure(1);clf;plot(b1);hold on;plot(b2,'-r');

%m1 = [1:length(b1)]*b1';
%m2 = [1:length(b2)]*b2';
m1 = mean(x);
m2 = mean(y);

A = eye(3,4)*m2/m1;

end