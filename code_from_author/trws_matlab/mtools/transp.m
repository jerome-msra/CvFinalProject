function A = transpose(A)

switch ndims(A)
case 1
 A = A';
case 2
 A = A';
case 3
 for i=1:size(A,3)
 	A(:,:,i) = A(:,:,i)';
 end

end