%%
%% This is an advanced example which uses custom similarity function to register
%% contour to the distance transform of edge detector image.
%% This example was for Oscar Danielsson, I would like to thank him for the idea of the task and the images.
%%

%% set path
run ../deformmatch-v3/mpath.m
commandwindow;

%% load images
pth = 'img';
I1 = im2double(imread([pth '/' 'model_stroke.bmp']));
I2_img = im2double(imread([pth '/' 'target.bmp']));

%% extract edges from I2_img
bw = edge(im2gray(I2_img),'sobel',0.08);
figure(7); imagesc(bw); colormap gray;

%% compute distance transform
D = bwdist(bw);
figure(6);imagesc(D); colormap gray;

%% target image is distance transform
I2 = D;

%% show initial aligment
figure(2);show_im_bd(I2_img,I1,'r');

%% apply additional scaling factor
scale = 0.8;
[I1s I2s] = prescale(scale,I1,I2);
%% enforce contour image to be binary
I1s = (I1s>0.2);

%% select registration parameters
ops = im_match_options();
ops.K = [15 15];
ops.block_size = 10;
ops.display = true;

%% my_fun.m returns 0 in the non-contour points and returns value of the
%% distance transform image in the contour point
ops.metric_func = @my_fun;

%% run registration
[f1 Q LB] = im_match(I1s,[],I2s,[],[],ops);

%% how far we are from the optimal solution
appratio = Q/LB

%% scale the transformation back so it applies to full-size images
f1 = f1.resize(msize(I1, [1 2]));


%% show distance map, edges and the original image registered with the contour
figure(3);show_im_bd(f1(I2),I1,'r');%% distance map
figure(8);show_im_bd(f1(bw),I1,'r');%% edges
figure(4);show_im_bd(f1(I2_img),I1,'r'); %% image

return
%% if inverse mapping is needed, do this: (slow) or swap the input images
if1 = f1.inverse();
dI1 = if1(I1);
figure(5);show_im_bd(I2_img,dI1,'r');