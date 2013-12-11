function dist = blockDistance(block1, block2)
	% This function returns the distance between block1 and block2
	% which is measured by the manhatan distance of the top left points
	dist = abs(block1(1) - block2(1)) + abs(block1(2) - block2(2));
end