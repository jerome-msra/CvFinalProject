function labels = ICM(blockList, template, target, iterations, blockSize,option)
	% This function gives the labels of MRF using ICM optimization
	% Input: blockList - the list of blocks
	% 		 template - the template image
	% 		 target - the target image
	% 		 iterations - the number of ICM iterations
	if size(template, 3) == 3
		[width height c] = size(template);
	else
		[width height] = size(template);
    end
    

	% blockNumber - the number of blocks
	blockNumber = size(blockList, 1);
	% Set parameters
	deltaI = 1;
	cR = 0.001;
	labelRange = 30;

	labels = zeros(blockNumber, 2);

	for i = 1:iterations
		for b = 1:blockNumber
			fprintf('Block Number %d\n',b);
			position = blockList(b,:);
			minEnergy = Inf;
			minLabel = [0 0];
			% Find the index in blockList of the neighbour blocks of current block
			% and it's a vector
			neighboursIndex = findNeighbours(blockList, position, blockSize);
			for xTrans = -labelRange:labelRange
				for yTrans = -labelRange:labelRange
					singleEnergy = 0;
					dataTerm = 0;
					blockDistance = 0;
					if (position(1)+xTrans > 0 && position(1)+xTrans+blockSize-1 < width) && (position(2)+yTrans > 0 && position(2)+yTrans+blockSize-1 < height)
						targetPos = [position(1)+xTrans position(2)+yTrans];
						blockDistance = color_dis_block(template, target, position, targetPos, blockSize, option);
					end
					% Calculate the data term for the energy under current configuration
					dataTerm = blockDistance;
					% Calculate the pairwise term
					pairwiseTerm = 0;

					for n = 1:size(neighboursIndex)
						neighTrans = labels(neighboursIndex(n),:);
						singlePairwiseTerm = calcPairwise([xTrans yTrans], neighTrans, cR);
						pairwiseTerm = pairwiseTerm + singlePairwiseTerm;
					end
					singleEnergy = dataTerm + pairwiseTerm;
					if singleEnergy < minEnergy
						minEnergy = singleEnergy;
						minLabel = [xTrans yTrans];
					end
				end
			end
			labels(b,:) = minLabel;
		end
	end
end