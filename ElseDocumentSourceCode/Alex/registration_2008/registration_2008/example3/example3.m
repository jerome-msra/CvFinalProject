%
%  Advanced example with mask and two-stage processing: estimate homography transform 
%  at coarse scale and refine at full scale. Goal is to register the tissue
%  ignoring the instruments -- they are segmented roughly by a simple segmentation method.
%  This example was for Tanja Shilling, I would like to thank her for the idea of the task and the images.
%
%

run ../deformmatch-v3/mpath.m
warning off all;
commandwindow;

%
I1 = im2double(imread('images/img001.jpg'));
I2 = im2double(imread('images/img020.jpg'));
%
mask1 = im2double(imread('images/mask-img001.bmp'));
mask1 = (sum(mask1.^2,3)<0.25);
mask1 = imresize(mask1,select(size(I1),[1 2]),'nearest');
%
mask2 = im2double(imread('images/mask-img020.bmp'));
mask2 = (sum(mask2.^2,3)<0.25);
mask2 = imresize(mask2,select(size(I2),[1 2]),'nearest');

I1 = pad_bg_add(I1,20);
I2 = pad_bg_add(I2,20);
mask1 = pad_bg_add(mask1,20,false);
mask2 = pad_bg_add(mask2,20,false);

figure(1);show_im_bd(I1,~mask1,'y');
figure(2);show_im_bd(I2,~mask2,'y');

%% assign a fixed penalty for matching to the background
bg_penalty = 0.05;

[t A] = im_match_multi(I1,mask1,I2,mask2,bg_penalty);

tI2 = t(color_transform(I2,A));
tmask2 = t(mask2);

figure(3);show_im_bd(tI2,tmask2,'y');