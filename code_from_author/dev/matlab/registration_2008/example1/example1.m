%%
%% This is the simpliest example of registration
%%

%% set pathes
run ../deformmatch-v3/mpath.m
warning off all;
commandwindow;

%% load images to register
pth = 'S1-a5-f5-n10-cc1';
I1 = im2double(imread([pth '/' 'im1.png']));
I2 = im2double(imread([pth '/' 'im2-01.png']));

%% show the images
figure(2);imagesc(I1);colormap gray; title('I1');
figure(3);imagesc(I2);colormap gray; title('I2');

%% select registration parameters
ops = im_match_options(); %% default options
ops.K = [13 13]; %% search window size
ops.block_size = 6; %% block size

%% run registration, result is the deformation field
f1 = im_match(I1,[],I2,[],[],ops);

%% deform image I2
[R mask] = f1(I2);
%% and display it with mask
figure(4);show_im_bd(R,mask); title('deformed I2');
%imwrite(R,'result.bmp');

%% uncomment to visualize the deformation field
% figure(5);plot(f1);