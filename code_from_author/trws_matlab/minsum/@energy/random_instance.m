function E = random_instance(E,type)
nV = get(E.G,'n');
nE = get(E.G,'m');
K = E.K;

if(~exist('type','var'))
	type = [];
end

E = construct_f2(E);

if strfind(type,'potts')
	sign = -1;
	if strfind(type,'+')
		sign = +1;
	end
	E.f1 = rand(K,nV);
	E.f2.index.i = [1:nE];
	E.f2.index.type(:) = 2;
	E.f2.store{2}.data = 0.5*rand(K,nE)*sign;
else
	E.f1 = rand(K,nV);
	E.f2.index.i = [1:nE];
	E.f2.index.type(:) = 1;
	E.f2.store{1}.data = rand(K,K,nE);	
end

if strfind(type,'int32')
	E.f1 = floor(100*E.f1);
	for i=1:length(E.f2.store)
		E.f2.store{i}.data = floor(100*E.f2.store{i}.data);
	end
end

end