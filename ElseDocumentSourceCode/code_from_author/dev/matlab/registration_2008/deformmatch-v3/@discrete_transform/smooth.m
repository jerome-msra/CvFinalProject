function f1 = smooth(f,sigma1)
% f1 = smooth(f,sigma1) -- apply gaussian smoothing filter with variance
% sigma (px)
%
%
fAB = f.f;
a = mmeshgrid(msize(fAB, [1 2]));
fAB = fAB-a;
%fAB = msub(fAB,dxc,3);
fAB = conv2_gauss(fAB,sigma1);
fAB = fAB+a;
%fAB = madd(fAB,dxc,3);
f1 = f;
f1.f = fAB;
end