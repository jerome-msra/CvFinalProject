function index = findInBlockList(blockList, blockPos)
	% This function is used to find the index of blockPos in blockList
	% returns the index of block position if exists
	% or returns 0 if not exists
	for b = 1:size(blockList, 1)
		if blockList(b,:) == blockPos
			index = b;
		end
	end
	index = 0;
end