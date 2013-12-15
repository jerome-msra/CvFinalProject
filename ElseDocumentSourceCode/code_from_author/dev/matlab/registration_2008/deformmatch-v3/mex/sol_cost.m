function c = sol_cost(x,C)

K = msize(C,[1 2]);
n = msize(C,[3 4]);

i1 = diag([1:n(1)])*ones(n);
j1 = ones(n)*diag([1:n(2)]);

x = double(x)+1;

c = sum(sum(C(sub2ind(size(C),x(:,:,1),x(:,:,2),i1,j1))));

end