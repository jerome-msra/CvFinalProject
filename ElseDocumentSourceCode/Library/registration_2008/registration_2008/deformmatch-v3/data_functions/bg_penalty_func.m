function q = bg_penalty_func(c1,cost)
%
%  This function must return the matrix q(i) of costs of matching the 
%  color c1(i,:) to the background
%

q = cost*ones(size(c1,1),1); % small fixed penalty independent of c1

end