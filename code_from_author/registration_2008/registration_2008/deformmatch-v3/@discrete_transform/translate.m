function f1 = translate(f, t0)
% f1 = translate(f, t0) -- transform f plus additional displacement t0 
% 
%
f1 = f;
f1.f = madd(f1.f,t0,3);
end