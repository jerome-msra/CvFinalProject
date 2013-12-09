function labels = ICM(blockList, template, target, iterations, blockSize)
	% This function gives the labels of MRF using ICM optimization
	% Input: blockList - the list of blocks
	% 		 template - the template image
	% 		 target - the target image
	% 		 iterations - the number of ICM iterations

	[width height c] = size(template);

	% blockNumber - the number of blocks
	blockNumber = size(blockList, 1);
	% Set parameters
	deltaI = 1;
	cR = 0.001;
	labelRange = 30;
	labels = zeros(blockNumber, 2);
	for i = 1:iterations
		for b = 1:blockNumber
			position = blockList(b);
			minEnergy = -1;
			for xTrans = -labelRange:labelRange
				for yTrans = -labelRange:labelRange
					if (position(1)+xTrans > 0 and position(1)+xTrans+blockSize-1 < width) and (position(2)+yTrans > 0 and position(2)+yTrans+blockSize-1 < height)
						targetPos = [position(1)+xTrans position(2)+yTrans];
						blockDistance = color_dis_block(template, target, position, targetPos, blockSize, 1);
					end
					% Calculate the data term under current configuration
					dataTerm = 0;
					for bn = 1:blockNumber
						if bn ~= b
							dataTerm = dataTerm + color_dis_block(template, target, position, position+labels(bn), blockSize, 1);
						else
							dataTerm = dataTerm + blockDistance
					end
					dataTerm = dataTerm / (2*deltaI)
					% Calculate the pairwise term under current configuration
					pairwiseTerm = 0;

				end
			end
		end
	end
end