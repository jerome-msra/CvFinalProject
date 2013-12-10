function index = findInBlockList(blockList, blockPos)
	% This function is used to find the index of blockPos in blockList
	% returns the index of block position if exists
	% or returns 0 if not exists
	index = 0;
	for b = 1:size(blockList, 1)
		if sum(blockList(b,:) == blockPos) == 2
			index = b;
		end
	end
end