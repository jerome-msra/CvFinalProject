function [resultTemplate resultTarget] = drawResult(template, target, blockList, labels, blockSize)
	% This function is used to show the deformation result
	% draw the template region and target region on template image and target image
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

	% Draw blocks on template image
	for b = 1:size(blockList, 1)
		xPos = blockList(b,1);
		yPos = blockList(b,2);
		if gray == 0 % rgb image
			resultTemplate(xPos, yPos:yPos+blockSize-1, 1) = 255; resultTemplate(xPos, yPos:yPos+blockSize-1, 2) = 0; resultTemplate(xPos, yPos:yPos+blockSize-1, 3) = 0;
			resultTemplate(xPos+blockSize-1, yPos:yPos+blockSize-1, 1) = 255; resultTemplate(xPos+blockSize-1, yPos:yPos+blockSize-1, 2) = 0; resultTemplate(xPos+blockSize-1, yPos:yPos+blockSize-1, 3) = 0;
			resultTemplate(xPos:xPos+blockSize-1, yPos, 1) = 255; resultTemplate(xPos:xPos+blockSize-1, yPos, 2) = 0; resultTemplate(xPos:xPos+blockSize-1, yPos, 3) = 0;
			resultTemplate(xPos:xPos+blockSize-1, yPos+blockSize-1, 1) = 255; resultTemplate(xPos:xPos+blockSize-1, yPos+blockSize-1, 2) = 0; resultTemplate(xPos:xPos+blockSize-1, yPos+blockSize-1, 3) = 0;
		else
			resultTemplate(xPos, yPos:yPos+blockSize-1) = 255;
			resultTemplate(xPos+blockSize-1, yPos:yPos+blockSize-1) = 255;
			resultTemplate(xPos:xPos+blockSize-1, yPos) = 255;
			resultTemplate(xPos:xPos+blockSize-1, yPos+blockSize-1) = 255;
		end
    end

    % 	Draw blocks on target image
	for b = 1:size(labels, 1)
		xPos = blockList(b,1) + labels(b,1);
		yPos = blockList(b,2) + labels(b,2);
		if gray == 0 % rgb image
			resultTarget(xPos, yPos:yPos+blockSize-1, 1) = 255; resultTarget(xPos, yPos:yPos+blockSize-1, 2) = 0; resultTarget(xPos, yPos:yPos+blockSize-1, 3) = 0;
			resultTarget(xPos+blockSize-1, yPos:yPos+blockSize-1, 1) = 255; resultTarget(xPos+blockSize-1, yPos:yPos+blockSize-1, 2) = 0; resultTarget(xPos+blockSize-1, yPos:yPos+blockSize-1, 3) = 0;
			resultTarget(xPos:xPos+blockSize-1, yPos, 1) = 255; resultTarget(xPos:xPos+blockSize-1, yPos, 2) = 0; resultTarget(xPos:xPos+blockSize-1, yPos, 3) = 0;
			resultTarget(xPos:xPos+blockSize-1, yPos+blockSize-1, 1) = 255; resultTarget(xPos:xPos+blockSize-1, yPos+blockSize-1, 2) = 0; resultTarget(xPos:xPos+blockSize-1, yPos+blockSize-1, 3) = 0;
		else
			resultTarget(xPos, yPos:yPos+blockSize-1) = 255;
			resultTarget(xPos+blockSize-1, yPos:yPos+blockSize-1) = 255;
			resultTarget(xPos:xPos+blockSize-1, yPos) = 255;
			resultTarget(xPos:xPos+blockSize-1, yPos+blockSize-1) = 255;
		end
	end

	% Show the result
	subplot(2,1,1);
	imshow(resultTemplate);
	subplot(2,1,2);
    save resultTarget
	imshow(resultTarget);
end