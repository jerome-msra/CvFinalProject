function q = ssd_fun(c1,c2)
%
%  This function must return the matrix q(i,j) of costs of matching the 
%  color c1(i,j,:) to the color c2(i,j,:)
%

q = sum((c1-c2).^2,3);

end