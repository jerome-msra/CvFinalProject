% Takes an image and applies Gaussian noise.
% Each pixel in the output is selected at random from a Gaussian distribution
% with a mean of the corresponding pixel value in the input image, and the
% given covariance.

function dst = blur_image(src, covar)
warning off

src = imread('original.jpg');
figure, imshow(src);
src = double(src);
covar = 100;

dst = round( normrnd(src, sqrt(covar) .* ones(size(src))) );

dst(find(dst < 0)) = 0;
dst(find(dst > 255)) = 255;

figure, imshow(uint8(dst));


