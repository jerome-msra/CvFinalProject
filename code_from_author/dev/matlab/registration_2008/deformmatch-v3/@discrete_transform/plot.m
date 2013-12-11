function plot(T,mask,steps)
%
%	Plots the vector field using quiver
%	T - discrete_transform
%	mask - [m x n] logical (=[]) -- plot only field inside the mask
% steps - double (=50) -- how dense is the plot
%
%

if(~exist('mask','var') || isempty(mask))
	mask = true(msize(T.f,[1 2]));
end

if(~exist('steps','var') || isempty(steps))
	steps = 20;
end

f = T.f;

sz = msize(f, [1 2]);

step = max(floor(sz/steps), [1 1]);
a = mmeshgrid(sz);
i1 = [1:2*step(1):ceil(sz(1)/(2*step(1)))*step(1)*2 sz(1)];
i2 = [1:2*step(2):ceil(sz(2)/(2*step(2)))*step(2)*2 sz(2)];
mesh_plotk(f(i1,i2,2),f(i1,i2,1)); hold on;

f = f - a;
%V = sqrt(sum(f.^2,3));
for l=1:2
	z = f(:,:,l);
	z(~mask) = 0;
	f(:,:,l) = z;
end
i1 = 1:step(1):msize(a,1);
i2 = 1:step(2):msize(a,2);
%contour(a(:,:,2),a(:,:,1),V); hold on;
quiver(a(i1,i2,2),a(i1,i2,1),f(i1,i2,2),f(i1,i2,1),0,'r','LineWidth',1);

%h = gcf;
%scrsz = get(0,'ScreenSize');
%
%set(h,'Position',[100 200 900 675]);
%h=gca;
%set(h,'Position',[0 0 1 1]);
hold off, axis image;
axis ij;

%plot([0 1], [0 1]);