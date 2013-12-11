function [TI TM] = im_transform(T,I,dest_sz)
%
%	TI = imtransform(T,I) -- applies transformation T to 
%	an image I (or to another function)
%
%	Input:	T -- geom_transform object;
%			I -- image
%			dest_sz (= size(I)) -- desired output image size
%
% 	Output:	TI -- transformed image
%

if ~exist('dest_sz','var')
	dest_sz = msize(I,[1 2]);
end

v = zeros(size(I,3),1);
v(end) = 0;
TI = imtransform(I,T.form,'bilinear','XData',[1 dest_sz(2)],'YData',[1 dest_sz(1)],'XYScale',1,'FillValues',v);

if(nargout>=2)
	m = zeros(msize(I, [1 2]));
	TM = imtransform(m,T.form,'bilinear','XData',[1 dest_sz(2)],'YData',[1 dest_sz(1)],'XYScale',1,'FillValues',1);
	TM = TM==0;
end

end