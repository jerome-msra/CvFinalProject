function fplot(f)
% plots transform as two color-coded images
%
a = mmeshgrid(size(f));
A = f.f(:,:,1)-a(:,:,1);
B = f.f(:,:,2)-a(:,:,2);

%I = f.f-a;
%I(:,:,3) = 0;
%I = I-min(I(:));
%I = I/max(I(:));
%hold off; imagesc(I);
hold off; imagesc([A zeros(msize(f.f,1),1) B]);colormap jet; colorbar;

end