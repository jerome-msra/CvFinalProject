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
		resultTemplate = drawBlock(resultTemplate, blockList(b,:), gray, blockSize);
    end

    % 	Draw blocks on target image
	for b = 1:size(labels, 1)
		xPos = blockList(b,1) + labels(b,1);
		yPos = blockList(b,2) + labels(b,2);
		resultTarget = drawBlock(resultTarget, [xPos yPos], gray, blockSize);
	end

	% Show the result
	subplot(2,1,1);
	imshow(resultTemplate);
	subplot(2,1,2);
	imshow(resultTarget);
end