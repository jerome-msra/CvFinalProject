function [resultTemplate resultTarget] = drawResultBoundary(template, target, blockList, labels, blockSize)
	% This function is used to show the deformation result
	% draw the template region and target region on template image and target image
	% Just draw the BOUNDARY 
	% Input: template - tempalte image
	% 		 target - target image
	% 		 blockList - the block information on template image
	% 		 labels - the translation information on the target image
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
	topTemplateList = zeros(0);
	bottomTemplateList = zeros(0);
	leftTemplateList = zeros(0);
	rightTemplateList = zeros(0);

	for b = 1:size(blockList,1)
		xPos = blockList(b,1);
		yPos = blockList(b,2);
		if findInBlockList(blockList, [xPos-blockSize+1 yPos]) == 0 
		% there is no block which is above current block
		% meaning that current block is the topest block in this column
			topTemplateList = [topTemplateList; b];
			if gray == 0
				resultTemplate(xPos:xPos+blockSize-1, yPos, 1) = 255; 
				resultTemplate(xPos:xPos+blockSize-1, yPos, 2) = 0;
				resultTemplate(xPos:xPos+blockSize-1, yPos, 3) = 0;
			elseif gray == 1
				resultTemplate(xPos:xPos+blockSize-1, yPos) = 255;
			end	  
		end

		if findInBlockList(blockList, [xPos+blockSize-1 yPos]) == 0
			bottomTemplateList = [bottomTemplateList; b];
			if gray == 0
				resultTemplate(xPos:xPos+blockSize-1, yPos+blockSize-1, 1) = 255;
				resultTemplate(xPos:xPos+blockSize-1, yPos+blockSize-1, 2) = 0;
				resultTemplate(xPos:xPos+blockSize-1, yPos+blockSize-1, 3) = 0;
			elseif gray == 1
				resultTemplate(xPos:xPos+blockSize-1, yPos+blockSize-1) = 255;
			end
		end

		if findInBlockList(blockList, [xPos yPos-blockSize+1]) == 0
			leftTemplateList = [leftTemplateList; b];
			if gray == 0
				resultTemplate(xPos, yPos:yPos+blockSize-1, 1) = 255;
				resultTemplate(xPos, yPos:yPos+blockSize-1, 2) = 0;
				resultTemplate(xPos, yPos:yPos+blockSize-1, 3) = 0;
			elseif gray == 1
				resultTemplate(xPos, yPos:yPos+blockSize-1) = 255;
			end
		end

		if findInBlockList(blockList, [xPos yPos+blockSize-1]) == 0
			rightTemplateList = [rightTemplateList; b];
			if gray == 0
				resultTemplate(xPos+blockSize-1, yPos:yPos+blockSize-1, 1) = 255;
				resultTemplate(xPos+blockSize-1, yPos:yPos+blockSize-1, 2) = 0;
				resultTemplate(xPos+blockSize-1, yPos:yPos+blockSize-1, 3) = 0;
			elseif gray == 1
				resultTemplate(xPos+blockSize-1, yPos:yPos+blockSize-1) = 255;
			end
		end
	end

	% For target image
	% because the block may be scaled, some boundary blocks may be moved apart
	% So we need to add some boundary lines between them
	% Since we have got the boundary blocks, we just use them in target image

	% Top boundary
	for t = 1:size(topTemplateList)
		xPos = labels(topTemplateList(t),1);
		yPos = labels(topTemplateList(t),2);
		if gray == 0
			resultTarget(xPos:xPos+blockSize-1, yPos, 1) = 255; 
			resultTarget(xPos:xPos+blockSize-1, yPos, 2) = 0;
			resultTarget(xPos:xPos+blockSize-1, yPos, 3) = 0;
		elseif gray == 1
			resultTarget(xPos:xPos+blockSize-1, yPos) = 255;
		end
	end

	for b = 1:size(bottomTemplateList)
		xPos = labels(bottomTemplateList(b),1);
		yPos = labels(bottomTemplateList(b),2);
		if gray == 0
			resultTarget(xPos:xPos+blockSize-1, yPos+blockSize-1, 1) = 255;
			resultTarget(xPos:xPos+blockSize-1, yPos+blockSize-1, 2) = 0;
			resultTarget(xPos:xPos+blockSize-1, yPos+blockSize-1, 3) = 0;
		elseif gray == 1
			resultTarget(xPos:xPos+blockSize-1, yPos+blockSize-1) = 255;
		end
	end

	for l = 1:size(leftTemplateList)
		xPos = labels(leftTemplateList(l),1);
		yPos = labels(leftTemplateList(l),2);
		if gray == 0
			resultTarget(xPos, yPos:yPos+blockSize-1, 1) = 255;
			resultTarget(xPos, yPos:yPos+blockSize-1, 2) = 0;
			resultTarget(xPos, yPos:yPos+blockSize-1, 3) = 0;
		elseif gray == 1
			resultTarget(xPos, yPos:yPos+blockSize-1) = 255;
		end
	end

	for r = 1:size(rightTemplateList)
		xPos = labels(rightTemplateList(r),1);
		yPos = labels(rightTemplateList(r),2);
		if gray == 0
			resultTarget(xPos+blockSize-1, yPos:yPos+blockSize-1, 1) = 255;
			resultTarget(xPos+blockSize-1, yPos:yPos+blockSize-1, 2) = 0;
			resultTarget(xPos+blockSize-1, yPos:yPos+blockSize-1, 3) = 0;
		elseif gray == 1
			resultTarget(xPos+blockSize-1, yPos:yPos+blockSize-1) = 255;
		end
	end
	% Show the result boundary
	subplot(1,2,1);
	imshow(resultTemplate);
	subplot(1,2,2);
	imshow(resultTarget);
end