function Q = matchin_cost_sad(I1,I2,K,x0,block_size)
	n = floor(msize(I1,[1 2])/block_size);
	i1 = [1:n(1)*block_size];
	i2 = [1:n(2)*block_size];
	i3 = [1:size(I1,3)];
	K = K(:)';
	x0 = x0(:)';
	Q = zeros([K n],'single');
	x1 = [0:K(1)-1];
	x2 = [0:K(2)-1];
	for k1 = 1:K(1)
		for k2 = 1:K(2)
			x = x0+[x1(k1) x2(k2)];
			g = sum(abs(I1(i1,i2,:)-I2(i1+x(1),i2+x(2),i3)),3);
			c1 = sum(reshape(g,block_size,[]),1);
			c2 = sum(reshape(c1,n(1),block_size,[]),2);
			c = squeeze(c2);
			Q(k1,k2,:,:) = -c;
		end
	end
end