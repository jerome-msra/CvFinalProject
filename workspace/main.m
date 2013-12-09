% CV Final Project
% Junwei Jason Zhang, Jian Jiang
% Dept. of Computer Science, SUNY-Stony Brook
% Efficient MRF Deformation Model for Non-Rigid Image Matching

% Read in Images and turn them into gray scale Images
originTemplateImage = double(imread('template.png'));		% Template Image
originTarget1 = double(imread('target1.png'));	% Target Images
originTarget2 = double(imread('target2.png'));
originTarget3 = double(imread('target3.png'));

blockSize = 4;
% Get the blocks
blockList = blockSplit(originTemplateImage, blockSize);
% Specify the number of iterations for ICM
iterations = 100;
% Get the labels through ICM optimization
labels = ICM(blockList, originTemplateImage, originTarget1, iteratioins, blockSize);
