function [f1 A] = im_match_multi(I1,mask1,I2,mask2,bg_penalty)
%
%	[t A] = im_match_multi(I1,mask1,I2,mask2,bg_penalty) -- image fitting with 2 scales 
%  processing and with color model compensation.
%  !Create your own favourite multi-scale processing scheme, dont rely on this one!
%
%	Input:	I1,I2 -  images to be registred
%			mask1,mask2 - masks of meaningfull pixels, if empty full images are takein into
%			account
%     bg_penalty - penalty for matching the color to the BG (outside of image domain or the element 0 in the mask)
%
%	Output: t -- found transformation, of the class discrete_transform
%			A -- found linear color mapping, a 3 x 4 matrix
%
%	See also IM_MATCH, DISCRETE_TRANSFORM/DISCRETE_TRANSFORM, COLOR_TRANSFORM
%		
%	Alexander Shekhovtsov


%% equalize brightness/contrast using histograms
A0 = adjust_brightness(I1,mask1,I2,mask2);
I1 = color_transform(I1,A0);

k = max(max(I1(:)),max(I2(:)));
I1 = I1/k;
I2 = I2/k;

f0 = discrete_transform(msize(I1,[1 2]));

if(max(size(I1))>500)%% low resolution fitting step if large
	fprintf('Performing coarse resolution preprocessing:\n');
	scale = 500/max(size(I1));
	f1 = scale_step(scale,I1,mask1,I2,mask2,[15 15],8,false,f0,bg_penalty);
	%% f1  - is composed transform now
	f1 = f1.smooth(10);%% blur it a lot to dump bad local fits
	%% //todo: maybe better to fit homography for some applications here
end

scale = 1;
if(max(size(I1))<240) %% if image is small do scale 1 and enlarge x 2
	if(min(size(I1,1),size(I1,2))>100)
		%% //todo: test how this case works
		f1 = scale_step(1,I1,mask1,I2,mask2,[31 31],8,false,f0,bg_penalty);
		f1 = f1.smooth(5);
	end
	scale = 2;
	fprintf('Small image: scale x 2.\n');
end

% figure(1);show_im_bd(I1,mask1);
% figure(2);show_im_bd(I2,mask2);
% figure(3);show_im_bd(tI1,tmask1);
% pause;

block_size = max(scale*ceil(max(size(I1)/60)),4);
[f1 A] = scale_step(scale,I1,mask1,I2,mask2,[31 31],block_size,true,f1,bg_penalty);
A = [A(:,1:3)*A0(:,1:3) A(:,4)*k];
%figure(1);show_im_bd(I1*k,mask1);
%figure(2);show_im_bd(I2*k,mask2);
%figure(3);show_im_bd(T*k);
end