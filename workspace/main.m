% CV Final Project
% Junwei Jason Zhang, Jian Jiang
% Dept. of Computer Science, SUNY-Stony Brook
% Efficient MRF Deformation Model for Non-Rigid Image Matching
function main(option)
	% if option == 1, use grayscale images
	% if option == 2, use rgb images

	% Read in Images and turn them into gray scale Images
	originTemplateImage = double(imread('../template.png'));		% Template Image
	originTarget1 = double(imread('../target1.png'));	% Target Images
	originTarget2 = double(imread('../target2.png'));
	originTarget3 = double(imread('../target3.png'));

	grayTemplateImage = rgb2gray(originTemplateImage);
	grayTarget1 = rgb2gray(originTarget1);
	grayTarget2 = rgb2gray(originTarget2);
	grayTarget3 = rgb2gray(originTarget3);

	blockSize = 4;
	% Get the blocks
	if option == 2
		blockList = blockSplit(originTemplateImage, blockSize);
	elseif option == 1
		blockList = blockSplit(grayTemplateImage, blockSize);
	end
	% Specify the number of iterations for ICM
	iterations = 1;
	% Get the labels through ICM optimization
	if option == 2
		labels = ICM(blockList, originTemplateImage, originTarget1, iterations, blockSize);
	elseif option == 1
		labels = ICM(blockList, grayTemplateImage, grayTarget1, iterations, blockSize);
	end
end
