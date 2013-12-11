function c = cost(E,x)
%
%	cost(E,x)
%

% mu1 = sparse(x(:),1:length(x),ones(length(x),1),E.K,length(x));
% G = E.G;
% EE = get(G,'E');
%
% i1 = x(EE(1,:));
% i2 = x(EE(2,:));
% i3 = 1:get(G,'m');
%
% f2x = select(E.f2,i1,i2,i3);
% %mu2 = sparse(x(:),1:length(x),ones(length(x),1),E.K,length(x));
%
% %mu2 = mu1(:,EE(1,:)).*mu1(:,EE(2,:));
%
% %c = E.f1(:)'*mu1(:) + E.f2(:)'*mu2(:);
% c = E.f1(:)'*mu1(:) + sum(f2x);

if(size(x,2)==1)
 		x = x';
end

switch size(x,2)

	case get(E.G,'n')

		[mu1 mu2] = get_mu(E.L,x);
		f2 = get_f2_full(E);
		c = E.f1(:)'*mu1(:)+f2(:)'*mu2(:);

	otherwise

		f2 = get_f2_full(E);
		c = [E.f1(:); f2(:)]'*x;

end

end