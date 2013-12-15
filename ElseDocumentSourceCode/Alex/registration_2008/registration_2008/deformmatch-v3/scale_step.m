function [f1 A] = scale_step(scale,I1,mask1,I2,mask2,region,block_size,fitcolor,f0,bg_penalty)
%
%		[t A] = scale_step(scale,I1,mask1,I2,mask2,region,fitcolor,f0)
%
%   t = scale_step(0.5,I1,mask1,I2,mask2,[15 15],false,[],0.05);
%
%	See also IM_MATCH_MULTI, DISCRETE_TRANSFORM/DISCRETE_TRANSFORM, COLOR_TRANSFORM

%% fit linear color model
if fitcolor
	A = lin_color_estimate(I1,mask1,I2,mask2);
else
	A = eye(size(I1,3));
	A(:,end+1)=0;
end
I1 = color_transform(I1,A);

%% check initial deformation
if ~exist('f0','var') || isempty(f0)
	f0 = discrete_transform(msize(I1,[1 2])); %% identity
end

%% rescale images and the deformation
[I1s I2s mask1s mask2s] = prescale(scale,I1,I2,mask1,mask2);
f0 = f0.resize(msize(I1s,[1 2]));

%% select registration parameters
ops = im_match_options(); %% default options
if(length(region)==1)
	region =[region region];
end
ops.K = region; %% search window size
ops.maxit = 10;
ops.block_size = block_size; %max(floor(max(size(I1s)/50)),8);
ops.bg_func_params = bg_penalty;
%% run registration, result is the deformation field

f1 = im_match(I1s,mask1s,I2s,mask2s,f0,ops);
f1 = f1.resize(msize(I1,[1 2]));
%t = geom_transform(x,block_size,'projective',mask1,mask2);
%p = geom_transform(scale,'scale');
%t = compose(inverse(p),compose(t,p));
end