function [L R x] = corresp_list(x,block_size,mask1,mask2)
%
%   corres_list(x,block_size,[mask1],[mask2])  make list of corresponding points
%
%   Input:
%       x - deformation field
%       block_size -- block_size for deformation field
%		mask1,mask2 -- optional masks, logical
%
%   Output:
%       L - 2 x n array with coordinates of points in the first image
%       R - 2 x n array with coordinates of deformed points by field x
%
block_size=double(block_size);

if(~exist('mask1','var') || isempty(mask1))
    mask1 = true(size(x,1),size(x,2));
else
	mask1 = prescale(1/block_size,mask1);
end

if(~exist('mask2','var') || isempty(mask2))
    mask2 = true(size(x,1),size(x,2));
else
	mask2 = prescale(1/block_size,mask2);
end

x = double(x);
shift = 2;
x = pad_bd_copy(x,shift); %% to avoid bugs on boundaries in picewice linear imtransform
mask1 = pad_bd_copy(mask1,shift);
mask2 = pad_bd_copy(mask2,shift);

%x(:,end+1,:) = x(:,end,:);
%x(end+1,:,:) = x(end,:,:);


sz = [size(x,1) size(x,2)];
i = [1:sz(1)];
j = [1:sz(2)];

%x0 = (diag(i-shift-1))*ones(sz)*block_size; %+block_size/2;
%y0 = ones(sz)*(diag(j-shift-1))*block_size; %+block_size/2;
ii0 = repmat((i'-shift-1)*block_size+block_size/2,1,sz(2));
jj0 = repmat(( j-shift-1)*block_size+block_size/2,sz(1),1);

dii = x(:,:,1);
djj = x(:,:,2);

ii1 = ii0+dii;
jj1 = jj0+djj;

L = [ ii0(:)'; jj0(:)'];
R = [ ii1(:)'; jj1(:)'];

select=true(1,length(L));
%{
for i=1:size(L,2)
	select(i) = mask1(int32(L(1,i)/block_size+shift),int32(L(2,i)/block_size+shift));
% 	p = [int32(R(1,i)/block_size+shift) int32(R(2,i)/block_size+shift)];
% 	if(any(p<1) || any(p>size(mask2)))
% 		select(i) = false;
% 	else
% 		select(i) = select(i) & logical(mask2(p(1),p(2))>0);
% 	end
end
%}
%imshow(reshape(select,sz(1),[]));
%error('bla');
L = L(:,select);
R = R(:,select);
end