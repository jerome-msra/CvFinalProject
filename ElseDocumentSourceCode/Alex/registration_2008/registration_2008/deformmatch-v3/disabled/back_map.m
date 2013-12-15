function R = back_map(I, x, block_size, sz)

%global block_size;

%sz = floor([size(I,1) size(I,2)]/block_size)*block_size;

%i = 1:floor(sz(1)/block_size);
%j = 1:floor(sz(2)/block_size);

%mask = int32(I(i*block_size,j*block_size)>0);
%x(:,:,2) = x(:,:,2).*mask;
%figure(2);imagesc(x(:,:,2));colormap gray;axis equal;


%sz = floor([size(I,1) size(I,2)]/block_size)*block_size;
if(~exist('sz','var'))
	sz = msize(I,[1 2]);
end
sz = floor(sz/block_size)*block_size;

i = [1:sz(1)];
j = [1:sz(2)];

x0 = diag(i)*ones(sz);
y0 = ones(sz)*diag(j);

dx = x(floor((i-1)/block_size)+1,floor((j-1)/block_size)+1,1);
dy = x(floor((i-1)/block_size)+1,floor((j-1)/block_size)+1,2);

%dx = dx.*int32(I(i,j)>0);
%dy = dy.*int32(I(i,j)>0);

x1 = int32(min(max(x0+double(dx),1),size(I,1)));
y1 = int32(min(max(y0+double(dy),1),size(I,2)));

R = zeros(sz,class(I));

for k=1:size(I,3)
	R(i,j,k) = I( sub2ind(size(I),x1,y1,k*int32(ones(sz))) );
end

end