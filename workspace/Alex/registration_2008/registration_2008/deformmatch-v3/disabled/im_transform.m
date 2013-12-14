function R = im_transform(I,x,block_size,dest_size)
%
% R = im_transform(I,x,block_size) transform image I by deformation field x
%
%  Input:
%		I: double[m x n x 3] - input image;
%		x: double[m x n x 2] - deformation field;
%       block_size: deformation field block_size
%
%  Output:
%		R: double[m x n x 3] - deformend image;
%
%   See also DEFORM_MATCH_RGB, DEFORM_RENDER, CORRESP_LIST
%
%   Alexander Shekhovtsov
%
if(isempty(dest_size))
	dest_size = msize(I,[1 2]);
end

[L R] = corresp_list(x,block_size);
form = cp2tform(L([2 1],:)',R([2 1],:)','piecewise linear');
R = imtransform(I,form,'bilinear','XData',[1 dest_size(2)],'YData',[1 dest_size(1)],'XYScale',1,'FillValues',squeeze(I(1,1,:)));