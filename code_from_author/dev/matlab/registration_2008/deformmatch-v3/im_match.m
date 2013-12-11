function [f1 Q LB] = im_match(I1,mask1,I2,mask2,f0,options)
%%  [f1 Q LB] = im_match(I1,mask1,I2,mask2,f0,options) -- higher level
%%  image registration function
%%
%%	Input:
%%		I1,I2 -- color images
%%		mask1 -- logical of the size I1, 1 for the foreground part. Optional: may be set to []
%%		mask2 -- logical of the size I2, 1 for the foreground part. Optional: may be set to []
%%		f0 - discrete_transform of size I1-- initial deformation
%%		options -- options structure described in IM_MATCH_OPTIONS
%%	
%%	Output:
%%		f1 - discrete_transform -- resulting deformation
%%		Q - quality of the discrete optimization problem internally solved
%%		LB - lower bound on the quality of the optimal solution
%%
%%  based on the technique described in  A. Shekhovtsov, I. Kovtun, V. Hlavac: Efficient MRF Deformation Model for Image Matching
%%  Computer Vision and Image Understanding 112(2008), pp. 91-99.
%%  (C) Alexander Shekhovtsov

if(~exist('mask1','var') || isempty(mask1))
	mask1 = true(msize(I1,[1 2]));
end

if(~exist('mask2','var') || isempty(mask2))
	mask2 = true(msize(I2,[1 2]));
end

metric_func = options.metric_func;
block_size = options.block_size;
K = options.K;
eps = options.eps;
maxit = options.maxit;
display = options.display;
if((~exist('options.figure_handle','var') || isempty(options.figure_handle)) && options.display)
	figure_handle = figure(1);clf;
else
	figure_handle = options.figure_handle;
end
fix_strategy = options.fix_strategy;
dxc = floor(K/2);
deform_reg = options.deform_reg;
maxd = options.maxd;
sigma1 = 0;
sigma2 = 0;
x0 = options.x0;

dxc = floor(K/2);
%% starting deformation
if ~exist('f0','var') || isempty(f0)
	f0 = discrete_transform(msize(I1,[1 2])); %% identity
end
offset = discrete_transform(msize(I1,[1 2])+K-dxc-1,x0-dxc-1); %% needed for matching
f = f0(offset); %% offset the transform f0

%% display
if(display)
	drawnow;
	set(0,'CurrentFigure',figure_handle)
	subplot(3,3,1);
	hold off;show_im_bd(I1,mask1);title('I1');
end

%% apply initial transform
[tI2 tm2] = f(I2,[],mask2);

%% display
if(display)
	subplot(3,3,3);hold off;show_im_bd(tI2,tm2); title('offset I2');
	if(size(tI2,3)==1)
		colormap gray;
	end
	[I2_b m2_b] = f0(I2,[],mask2);
	subplot(3,3,2);hold off;show_im_bd(I2_b,m2_b); title('initially transformed I2');
end

%% quantize image signals
nc1 = min(length(unique(I1)),options.max_c1);
nc2 = min(length(unique(I2)),options.max_c2);
[I1i map1] = mrgb2ind(I1,nc1);
[I2i,map2] = mrgb2ind(tI2,nc2);
%% rgb2ind can produce fewer colors
nc1 = size(map1,1);
nc2 = size(map2,1);
C1(:,1,:) = map1;
C1 = repmat(C1,1,nc2);
C2(:,1,:) = map2;
C2 = repmat(C2,1,nc1);

%% get cost table
q = -metric_func(C1,permute(C2, [2 1 3]));
%% Add special penalties for the background
xq1 = -options.bg_func(map1,options.bg_func_params); %% penalty for c1 vs BG2
xq2 = -options.bg_func(map2,options.bg_func_params)'; %% penalty for BG1 vs c2
q = [0 xq2; xq1 q];

%% make non-positive
q = q-max(q(:));

%% display
if display
	subplot(3,3,4);	hold off;imagesc(-q);colormap jet;title('cost table');drawnow;
end

%% create special index for the background
[I1i map1] = fuse_mask(I1i,map1,mask1);
[I2i map2] = fuse_mask(I2i,map2,tm2);


%% //todo: move this to options

%xq1 = -0.2*ones(size(q,1),1); %% penalty for c1 vs BG2
%xq2 = -0.2*ones(1,size(q,2)); %% penalty for BG1 vs c2

%xq1 = q(:,1); %% penalty for c1 vs BG2 as if BG2 is colored in color 1
%xq2 = q(1,:); %% penalty for BG1 vs c2 as if BG1 is colored in color 1

%% extend image I1 so that integral number of blocks cover the usefull content
sz1 = msize(I1,[1 2]);
esz1 = max(ceil(sz1/block_size),1)*block_size;
I1i =  pad_bg(I1i,[1 1],esz1);

%% extend image I2 so that any deformation of I1i would fit
esz2 = max(esz1+K-1,msize(I2,[1 2]));
I2i =  pad_bg(I2i,[1 1],esz2);

tic;
%% Compute block matching costs, given the pixel-to-pixe cost table q
C = matching_cost_q(I1i,I2i,K, [1 1], block_size,q);
fprintf('Cost computations: %3.2fs.\n',toc);

%% convert to float format
%%C = single(int32(C*2^16))/2^16;
C = single(C);

%% Call mex to compute best matching
disp('mex started');tic;

dreg_params = [deform_reg eps maxit maxd fix_strategy 0 0];
[x LB] = deform_match_mex(C,dreg_params);
fprintf('Energy minimization: %3.2fs.\n',toc);
clear deform_match_mex;
Q = sol_cost(x,C);

x = double(x);
fAB = discrete_transform(x,block_size,size(I1));

%% composite result transform (note we use backward mappings)
f1 = f(fAB);

if display
	a = mmeshgrid(msize(f1.f,[1 2]));
	subplot(3,3,8); hold off; imagesc(f1.f(:,:,1)-a(:,:,1));title('transform 1st component');
	subplot(3,3,9); hold off; imagesc(f1.f(:,:,2)-a(:,:,2));title('transform 2nd component');
	[I2_b m2_b] = f1(I2,[],mask2);
	subplot(3,3,5); hold off;show_im_bd(I2_b,m2_b);title('result transformend I2');
end
end