function drawnImage = drawLines(image, point1, point2, gray)
	% This function is used to draw a straight line from point 1 to point 2
	% Input: image - the image to be drawn on
	% 		 point1 - point 1
	% 		 point2 - point 2
	% Output: drawnImage - the image which has been drawn on

	drawnImage = image;
	gap = point2-point1;
	[step index] = min(abs(gap));
	signX = 1; signY = 1;
	if gap(1) ~= 0
		signX = gap(1)/abs(gap(1));
	end
	if gap(2) ~= 0
		signY = gap(2)/abs(gap(2));
	end
	for s = 1:step
		if gray == 0
			drawnImage(point1(1)+signX*s, point1(2)+signY*s, 1) = 255;
			drawnImage(point1(1)+signX*s, point1(2)+signY*s, 2) = 0;
			drawnImage(point1(1)+signX*s, point1(2)+signY*s, 3) = 0;
		elseif gray == 1
			drawnImage(point1(1)+signX*s, point1(2)+signY*s) = 255;
		end
	end
	trans = abs(abs(gap(1))-abs(gap(2)));
	tempPointX = point1(1)+signX*step;
	tempPointY = point1(2)+signY*step;
	for t = 1:trans
		if index == 1
			if gray == 0
				drawnImage(tempPointX, tempPointY+signY*t, 1) = 255;
				drawnImage(tempPointX, tempPointY+signY*t, 2) = 0;
				drawnImage(tempPointX, tempPointY+signY*t, 3) = 0;
			elseif gray == 1
				drawnImage(tempPointX, tempPointY+signY*t) = 255;
			end
		elseif index == 2
			if gray == 0
				drawnImage(tempPointX+signX*t, tempPointY, 1) = 255;
				drawnImage(tempPointX+signX*t, tempPointY, 2) = 0;
				drawnImage(tempPointX+signX*t, tempPointY, 3) = 0;
			elseif gray == 1
				drawnImage(tempPointX+signX*t, tempPointY) = 255;
			end
		end
	end
end