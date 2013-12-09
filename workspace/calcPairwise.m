function singlePT = calcPairwise(currentTrans, neighTrans, cR)
	% This function is used to calculate the pairwise term of current block translation 
	% and its neighbour's translation
	if currentTrans == neighTrans
		singlePT = 0;
	elseif (currentTrans(1)+1 == neighTrans(1)) && (currentTrans(2) == neighTrans(2))
		singlePT = cR;
	elseif (currentTrans(1)-1 == neighTrans(1)) && (currentTrans(2) == neighTrans(2))
		singlePT = cR;
	elseif (currentTrans(1) == neighTrans(1)) && (currentTrans(2)+1 == neighTrans(2))
		singlePT = cR;
	elseif (currentTrans(1) == neighTrans(1)) && (currentTrans(2)-1 == neighTrans(2))
		singlePT = cR;
	elseif (currentTrans(1)+1 == neighTrans(1)) && (currentTrans(2)+1 == neighTrans(2))
		singlePT = cR;
	elseif (currentTrans(1)-1 == neighTrans(1)) && (currentTrans(2)-1 == neighTrans(2))
		singlePT = cR;
	elseif (currentTrans(1)-1 == neighTrans(1)) && (currentTrans(2)+1 == neighTrans(2))
		singlePT = cR;
	elseif (currentTrans(1)+1 == neighTrans(1)) && (currentTrans(2)-1 == neighTrans(2))
		singlePT = cR;
	else
		singlePT = Inf;
	end
end