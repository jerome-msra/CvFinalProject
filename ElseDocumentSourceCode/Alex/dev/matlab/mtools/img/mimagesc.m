function mimagesc(I)

I = I-min(I(:));
I = I/max(I(:));
imagesc(I);

end