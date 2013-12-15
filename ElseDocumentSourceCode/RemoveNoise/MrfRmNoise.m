%MRF remove noise
%create the salt & pepper noise
Img =  imread('target1.png');		% Template Image
%figure, imshow(Img);
Img = rgb2gray(Img);
%figure, imshow(Img);
NoiseImg = imnoise(Img,'salt & pepper',0.02);
figure, imshow(NoiseImg);

Img = double(Img);
NoiseImg = double(NoiseImg);

%create the MRF machine
