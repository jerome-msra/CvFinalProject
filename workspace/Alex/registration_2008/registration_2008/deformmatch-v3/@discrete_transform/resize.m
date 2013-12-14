function f1 = resize(f,nsize)

a = mmeshgrid(size(f));
f1 = discrete_transform();
f1.f = imresize(f.f-a,nsize,'bilinear');
a = mmeshgrid(size(f1));

for l=1:2
    f1.f(:,:,l) = f1.f(:,:,l)*nsize(l)/msize(f.f,l)+a(:,:,l);
end

end