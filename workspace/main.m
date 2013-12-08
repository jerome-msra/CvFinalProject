% CV Final Project
% Junwei Jason Zhang, Jian Jiang
% Dept. of Computer Science, SUNY-Stony Brook
% Efficient MRF Deformation Model for Non-Rigid Image Matching

% Read in Images and turn them into gray scale Images
originTemplateImage = double(imread('template.png'));		% Template Image
originTarget1 = double(imread('target1.png'));	% Target Images
originTarget2 = double(imread('target2.png'));
originTarget3 = double(imread('target3.png'));

blockList = blockSplit(originTemplateImage);
dis = color_dis();


