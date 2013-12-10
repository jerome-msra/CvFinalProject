function resultImage = drawBlock(image, block, gray, blockSize)
	% This function is used to draw single block
	% returns the image drawn
	resultImage = image;
	xPos = block(1);
	yPos = block(2);
	if gray == 0 % rgb image
		resultImage(xPos, yPos:yPos+blockSize-1, 1) = 255; resultImage(xPos, yPos:yPos+blockSize-1, 2) = 0; resultImage(xPos, yPos:yPos+blockSize-1, 3) = 0;
		resultImage(xPos+blockSize-1, yPos:yPos+blockSize-1, 1) = 255; resultImage(xPos+blockSize-1, yPos:yPos+blockSize-1, 2) = 0; resultImage(xPos+blockSize-1, yPos:yPos+blockSize-1, 3) = 0;
		resultImage(xPos:xPos+blockSize-1, yPos, 1) = 255; resultImage(xPos:xPos+blockSize-1, yPos, 2) = 0; resultImage(xPos:xPos+blockSize-1, yPos, 3) = 0;
		resultImage(xPos:xPos+blockSize-1, yPos+blockSize-1, 1) = 255; resultImage(xPos:xPos+blockSize-1, yPos+blockSize-1, 2) = 0; resultImage(xPos:xPos+blockSize-1, yPos+blockSize-1, 3) = 0;
	else
		resultImage(xPos, yPos:yPos+blockSize-1) = 255;
		resultImage(xPos+blockSize-1, yPos:yPos+blockSize-1) = 255;
		resultImage(xPos:xPos+blockSize-1, yPos) = 255;
		resultImage(xPos:xPos+blockSize-1, yPos+blockSize-1) = 255;
	end
end