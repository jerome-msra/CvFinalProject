function ff = scale_transform(f,nsize)

a = mmeshgrid(msize(f,[1 2]));
ff = imresize(f-a,nsize,'bilinear');
a = mmeshgrid(msize(ff,[1 2]));

for l=1:2
    ff(:,:,l) = ff(:,:,l)*nsize(l)/msize(f,l)+a(:,:,l);
end

end