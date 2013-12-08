function blockList = blockSplit(template, blockSize)
	% This function is used to split the image into blocks (just the area of interest- AOI). 
	% Input: template - a template image where areas except AOI are all black
	% 		 blockSize - the block size is blockSize*blockSize pixels
	% Output: A blockList matrix n*2,where n is the number of blocks and each row stands for the top-left
	% corner position
	% Convert the template to gray scale image
	if size(size(template)) == [1 3]
		template = rgb2gray(template);
	end

	[m n] = size(template)
	blockList = zeros(0,2);
	for i = 1:blockSize:m
		for j = 2:blockSize:n
			if template(i,j) > 0
				blockList = [ blockList; i j];
			end
		end
	end
end