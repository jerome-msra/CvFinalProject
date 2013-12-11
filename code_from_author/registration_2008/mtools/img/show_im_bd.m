function show_im_bd(I,mask,c)
%
%	show_im_bd(I,mask) -- show image and the boundary of the mask
%

if(~exist('c','var') || isempty(c))
c = 'r';
end

hold off;
if(size(I,3)==1)
	I = gray2rgb(I);
end

I = I-min(I(:));
I = I/max(I(:));
imagesc(I);

if(exist('mask','var') && ~isempty(mask))
	show_mask(mask,c);
end

hold off;

end