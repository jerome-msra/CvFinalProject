function d = dense_field2(x,block_size,target_sz)
%
%	d = dense_field2(x,block_size,target_sz)
% Create dense smooth field from block centers shifts
%

block_size=double(block_size);
x = double(x);
sz = [size(x,1) size(x,2)];

k = 2;% how far to extrapolate

cp1 = (mmeshgrid(sz+2*k)-1)*block_size+block_size/2-block_size*k;

%% extrapolate to the border
cp2 = x;
cp2 = pad_bd_copy(cp2,2);

a = mmeshgrid(target_sz);

for i=1:size(cp2,3)
	d(:,:,i) = interp2(cp1(:,:,2),cp1(:,:,1),cp2(:,:,i),a(:,:,2),a(:,:,1),'cubic',0);
end
d = d+a;
end