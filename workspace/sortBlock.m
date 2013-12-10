function sortedBlock = sortBlock(blockIndexPosList, direction)
	% This function is used to sort the boundary block list 
	% with respect to some column, specified by 'direction'
	if direction == 'row'
		[sortedCol pos] = sort(blockIndexPosList(:,2));
		sortedBlock = blockIndexPosList(pos,:);
	elseif direction == 'col'
		[sortedCol pos] = sort(blockIndexPosList(:,3));
		sortedBlock = blockIndexPosList(pos,:);
	end
end