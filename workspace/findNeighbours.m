function neighbours = findNeighbours(blockList, currentBlockPosition, blockSize)

	% This function is used to return the index (in blockList) of neighbours of current block

	blockNumber = size(blockList,1);
	neighbours = size(0);
	neighboursPositions = [currentBlockPosition(1)-blockSize currentBlockPosition(2);
							currentBlockPosition(1) currentBlockPosition(2)-blockSize;
							currentBlockPosition(1)+blockSize currentBlockPosition(2);
							currentBlockPosition(1) currentBlockPosition(2)+blockSize]; 
	for b = 1:blockNumber
		for n = 1:size(neighboursPositions,1)
			if blockList(b,:) == neighboursPositions(n,:)
				neighbours = [neighbours b]
			end
		end
	end
end