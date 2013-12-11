function Q = matching_cost_q(I1,I2,K,x0,block_size,q)
%%
%%	Q = matching_cost_q(I1,I2,K,x0,block_size,q) -- computes
%%	block-block comparison sums, based on color-color comparison function q
%%
%%		Input:
%%			I1 - image1
%%			I2 - image2
%%			 K - [2 x 1] search window
%%			x0 - [2 x 1] initial position of I1 in I2
%%	block_size - size of block moving solidly
%%			 q - [L1 x L2] color-color comaprison function
%%
%%	   Output:
%%			 Q - [K(1) x K(2) x n(1) x n(2)], where n =
%%				size(I1)/block_size, cost data array;

%% check I2 is sufficiently large
esz = size(I1)+K-1;
x1 = x0+esz-1;
if(any(x0<1) || any(x1>size(I2)))
	error('search range is out of the I2 domain');
end

%% The Algorithm (uncomment to verify that mex is working correctly):
%{
n = floor(msize(I1,[1 2])/block_size);
i1 = [1:n(1)*block_size];
i2 = [1:n(2)*block_size];
K = K(:)';
x0 = x0(:)';
Q = zeros([K n],'single');
x1 = [0:K(1)-1];
x2 = [0:K(2)-1];
for k1 = 1:K(1)
    for k2 = 1:K(2)
        x = x0+[x1(k1) x2(k2)]-1;
		ii = sub2ind(size(q),I1(i1,i2),I2(i1+x(1),i2+x(2)));
		g =  q(ii);
        c1 = sum(reshape(g,block_size,[]),1);
        c2 = sum(reshape(c1,n(1),block_size,[]),2);
        c = squeeze(c2);
        Q(k1,k2,:,:) = c;
    end
end
return
%}

%% convert types, make indices 0-based and call mex implementation
Q = matching_cost_q_mex(int32(I1-1),int32(I2-1),int32(K),int32(x0-1),int32(block_size),single(q));
end