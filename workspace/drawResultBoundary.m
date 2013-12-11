function [resultTemplate resultTarget] = drawResultBoundary(template, target, blockList, labels, blockSize, threshold)
	% This function is used to show the deformation result
	% draw the template region and target region on template image and target image
	% Just draw the BOUNDARY 
	% Input: template - tempalte image
	% 		 target - target image
	% 		 blockList - the block information on template image
	% 		 labels - the translation information on the target image
	% 		 threshold - used to judge the neighbour block on the boundary
	% If template and target are grayscale
	% we guarantee that they are both rgb or both gray
	if size(template, 3) == 3
		gray = 0;
	else
		gray = 1;
	end
	

	resultTemplate = template;
	resultTarget = target;

	% We maintain four lists accounting for the boundary blocks index in blockList
	% for template
	topTemplateList = zeros(0,3);
	bottomTemplateList = zeros(0,3);
	leftTemplateList = zeros(0,3);
	rightTemplateList = zeros(0,3);

	for b = 1:size(blockList,1)
		xPos = blockList(b,1);
		yPos = blockList(b,2);
		% findInBlockList(blockList, [xPos-blockSize yPos])
		if findInBlockList(blockList, [xPos-blockSize yPos]) == 0 
		% there is no block which is above current block
		% meaning that current block is the topest block in this column
			topTemplateList = [topTemplateList; [b xPos yPos]];
			resultTemplate = drawBlock(resultTemplate, blockList(b,:), gray, blockSize);	  
		end

		if findInBlockList(blockList, [xPos+blockSize yPos]) == 0
			bottomTemplateList = [bottomTemplateList; [b xPos yPos]];
			resultTemplate = drawBlock(resultTemplate, blockList(b,:), gray, blockSize);
		end

		if findInBlockList(blockList, [xPos yPos-blockSize]) == 0
			leftTemplateList = [leftTemplateList; [b xPos yPos]];
			resultTemplate = drawBlock(resultTemplate, blockList(b,:), gray, blockSize);
		end

		if findInBlockList(blockList, [xPos yPos+blockSize]) == 0
			rightTemplateList = [rightTemplateList; [b xPos yPos]];
			resultTemplate = drawBlock(resultTemplate, blockList(b,:), gray, blockSize);
		end
	end
	
	% For target image
	% because the block may be scaled, some boundary blocks may be moved apart
	% So we need to add some boundary lines between them
	% Since we have got the boundary blocks, we just use them in target image

	% We need to sort the four lists according to some column to find the neighbour block
	% in the boundary, which will be used to draw lines

	topTemplateList = sortBlock(topTemplateList, 'row');
	bottomTemplateList = sortBlock(bottomTemplateList, 'row');
	leftTemplateList = sortBlock(leftTemplateList, 'col');
	rightTemplateList = sortBlock(rightTemplateList, 'col');

	% Top boundary
	for t = 1:size(topTemplateList,1)
		xPos = topTemplateList(t,2) + labels(topTemplateList(t,1),1);
		yPos = topTemplateList(t,3) + labels(topTemplateList(t,1),2);
		resultTarget = drawBlock(resultTarget, [xPos yPos], gray, blockSize);
		if t < size(topTemplateList,1)
			pPos = topTemplateList(t+1,2) + labels(topTemplateList(t+1,1),1);
			qPos = topTemplateList(t+1,3) + labels(topTemplateList(t+1,1),2);
			if blockDistance([xPos yPos], [pPos qPos]) < threshold
				resultTarget = drawLines(resultTarget, [xPos yPos], [pPos qPos], gray);
			end
		end
	end

	% Bottom boundary
	for b = 1:size(bottomTemplateList,1)
		xPos = bottomTemplateList(b,2) + labels(bottomTemplateList(b,1),1);
		yPos = bottomTemplateList(b,3) + labels(bottomTemplateList(b,1),2);
		resultTarget = drawBlock(resultTarget, [xPos yPos], gray, blockSize);
		if b < size(bottomTemplateList,1)
			pPos = bottomTemplateList(b+1,2) + labels(bottomTemplateList(b+1,1),1);
			qPos = bottomTemplateList(b+1,3) + labels(bottomTemplateList(b+1,1),2);
			if blockDistance([xPos yPos], [pPos qPos]) < threshold
				resultTarget = drawLines(resultTarget, [xPos yPos], [pPos qPos], gray);
			end
		end
	end

	% Left boundary
	for l = 1:size(leftTemplateList,1)
		xPos = leftTemplateList(l,2) + labels(leftTemplateList(l,1),1);
		yPos = leftTemplateList(l,3) + labels(leftTemplateList(l,1),2);
		resultTarget = drawBlock(resultTarget, [xPos yPos], gray, blockSize);
		if l < size(leftTemplateList,1)
			pPos = leftTemplateList(l+1,2) + labels(leftTemplateList(l+1,1),1);
			qPos = leftTemplateList(l+1,3) + labels(leftTemplateList(l+1,1),2);
			if blockDistance([xPos yPos], [pPos qPos]) < threshold
				resultTarget = drawLines(resultTarget, [xPos yPos], [pPos qPos], gray);
			end
		end
	end

	% right boundary
	for r = 1:size(rightTemplateList,1)
		xPos = rightTemplateList(r,2) + labels(rightTemplateList(r,1),1);
		yPos = rightTemplateList(r,3) + labels(rightTemplateList(r,1),2);
		resultTarget = drawBlock(resultTarget, [xPos yPos], gray, blockSize);
		if r < size(rightTemplateList,1)
			pPos = rightTemplateList(r+1,2) + labels(rightTemplateList(r+1,1),1);
			qPos = rightTemplateList(r+1,3) + labels(rightTemplateList(r+1,1),2);
			if blockDistance([xPos yPos], [pPos qPos]) < threshold
				resultTarget = drawLines(resultTarget, [xPos yPos], [pPos qPos], gray);
			end
		end
	end

	% We also need to draw lines for target image because boundary blocks maybe moved apart
	% Show the result boundary
	subplot(1,2,1);
	imshow(resultTemplate);
	subplot(1,2,2);
	imshow(resultTarget);
end