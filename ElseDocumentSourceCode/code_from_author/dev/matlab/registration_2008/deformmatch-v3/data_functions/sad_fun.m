function q = sad_fun(c1,c2)
%
%  This function must return the matrix q(i,j) of costs of matching the 
%  color c1(i,j,:) to the color c2(i,j,:)
%
q = sum(abs(c1-c2),3);

end