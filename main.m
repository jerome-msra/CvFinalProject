% CV Final Project
% Junwei Jason Zhang, Jian Jiang
% Dept. of Computer Science, SUNY-Stony Brook
% Efficient MRF Deformation Model for Non-Rigid Image Matching

% Read in Images and turn them into gray scale Images
originTemplateImage = double(imread('template.png'));		% Template Image
originTarget1 = double(imread('target1.png'));	% Target Images
originTarget2 = double(imread('target2.png'));
originTarget3 = double(imread('target3.png'));

% Turn them into gray scale Images
templateImage = rgb2gray(originTemplateImage);
target1 = rgb2gray(originTarget1);
target2 = rgb2gray(originTarget2);
target3 = rgb2gray(originTarget3);

