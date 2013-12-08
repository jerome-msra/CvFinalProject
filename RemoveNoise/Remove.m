%
warning off
t1=clock;
src = imread('original.jpg');
figure, imshow(src);
src = double(src);
covar = 100;
dst = blur_image(src,covar);


max_diff = 200;
weight_diff = 0.02;
iterations = 10;


restore_image(dst, covar, max_diff, weight_diff, iterations);

t2= clock;

etime(t2,t1)
