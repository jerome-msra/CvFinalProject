function [X mask] = deform_render(x,s,I1,I2,style)
%
%   [X mask] = deform_render(x,s,I1,I2,style) applies a deformation to
%   images I1 and I2 and combines them
%
%   Input:
%       x - deformation field
%       s - factor in [0,1] to get intermediate deformations
%       I1,I2 - images
%       style - string: 'style_type [outline]', where style_type is one of:
%           + - result is linearly interpolated from I1 and I2
%           rb - result is red-blue image where I1 is in red chanel and I2 is in
%               blue chanel
%           overlay - I1 overimposed on I2
%           1 -- deformed I1 only
%
%   Output:
%       X - combined image
%       mask - mask extracted from I1 //DEPRICATED
%
%   See also DEFORM_MATCH_RGB, IM_TRANSFORM
%
%   Alexander Shekhovtsov

global block_size;
x = double(x);

if(block_size==1 || ~isempty(strfind(style, 'nofill')))
	R = fw_map(I1,s*x,msize(I2,[1 2]));
else
	R = im_transform(I1,s*x,int32(block_size),msize(I2,[1 2]));
end

mask = sum(R.^2,3)>0.01;

if(0 && exist('I2','var') && ~isempty(I2))
	R = R(1:size(I2,1),1:size(I2,2),:);	
	R1 = back_map(I2,(1-s)*x);

	if ~isempty(strfind(style,'blend'))
		X = s*R1+(1-s)*R;
	elseif ~isempty(strfind(style,'+'))
		X = (I2+R)/2;
	elseif ~isempty(strfind(style,'rb'))
		X(:,:,1) = rgb2gray(R);
		X(:,:,3) = rgb2gray(I2);
	elseif ~isempty(strfind(style,'overlay'))
		for j=1:size(I2,3)
			t = I2(:,:,j);
			ff = R(:,:,j);
			t(mask) = ff(mask);
			X(:,:,j) = t;
        end
    elseif ~isempty(strfind(style,'1'))
        for j=1:size(I2,3)
            X(:,:,j) = R(:,:,j);
        end
	else
		error('unknown style');
	end
	%X = (1-s)*R1+s*R; %reverse
	%X = (R1+R)/2;
	%X = R1;
else
	X = R;
end

if ~isempty(strfind(style,'outline'))
	%Mc = logical(imfill(mask,'holes'));
	SE = strel('square',2);
	Mc = logical(imdilate(mask,SE));
	Mc = logical(imfill(Mc,'holes'));
	Mc = logical(imerode(Mc,SE));
	SE = strel('square',3);
	M1 = logical(imdilate(Mc,SE));
	c = [1 1 0];
	for j=1:size(X,3)
		t = X(:,:,j);
		t(M1 & ~Mc) = c(j);
		X(:,:,j) = t;
	end
end
end