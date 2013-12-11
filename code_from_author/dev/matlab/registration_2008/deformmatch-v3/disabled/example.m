I = imread('test4.bmp');
%I = imread('IMG_0393-8.bmp');
K = 20;
m = size(I,2);
I = im2double(I);
I1 = I(:,1:floor(m/2),:);
I2 = I(:,floor(m/2)+1:end,:);
mask = sum(I1.^2,3)>0.01;
%[I1 I2 mask] = prescale(2,I1,I2,mask);
t1 = cputime;
global block_size;
block_size = 4;
nc1 = 200;
nc2 = 200;

[I1i map1] = mrgb2ind(I1,nc1);
[I2i,map2] = mrgb2ind(I2,nc2);

ro1 = colormap_sq_metric(map1);
ro2 = colormap_sq_metric(map2);
sigma1 = 0.015*sqrt(size(I1,3));
sigma2 = 0.015*sqrt(size(I2,3));
eps1 = 0.01/(length(map1)*length(map2));

pp12 = pp./repmat(sum(pp,1),size(pp,1),1);
q = log_t(pp12,eps1);
subplot(3,3,4);	hold off;imagesc(-q);colormap jet;drawnow;

[I1i map1] = fuse_mask(I1i,map1,[]);
[I2i map2] = fuse_mask(I2i,map2,tm2);
xq1 = -50*ones(size(q,1),1); %% big penalty for c1 vs BG2
%xq1 = 2*q(:,1); %% q(c1,BG2) = q(c1,1)
xq2 = zeros(1,size(q,2)); %% no penalty for BG1 vs c2
q = [0 xq2; xq1 q];

I2i =  pad_bg(I2i,[1 1],esize);

drawnow;

%% Compute matching cost, given the histogram q
C = matching_cost_q(I1i,I2i,K, [1 1], block_size,q);
fprintf('Cost computations: %3.2fs.\n',toc);

disp('mex started');
[x LB] = deform_match_mex(C,dreg_params);
clear deform_match_mex;
sol_cost(x,C);


t2 = cputime;
fprintf('Q: %g\t LB: %g\t Time: %g\n',Q,LB,t2-t1);
T1 = zeros(size(I1));
R = deform_render(x,1,I1,I2,'overlay outline nofill');
figure(1);
imagesc([I1 I2; T1 R]);
axis equal;
clear functions
return
