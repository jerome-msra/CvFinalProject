function show_mask(mask,c)
%
%	show_mask(mask,c) -- show the boundary of the mask
%


if(~exist('c','var') || isempty(c))
c = 'r';
end

if(exist('mask','var') && ~isempty(mask))
maskbd = bwboundaries(mask);
hold on;
for i=1:length(maskbd)
	bd = maskbd{i};
	plot(bd(:,2),bd(:,1),c,'LineWidth',1);
end
hold off;

end