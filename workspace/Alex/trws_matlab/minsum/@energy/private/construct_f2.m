function E = construct_f2(E)
nV = get(E.G,'n');
nE = get(E.G,'m');
K = E.K;

E.f2 = [];
E.f2.index = [];
E.f2.index.i = ones(1,nE);
E.f2.index.type = ones(1,nE);

E.f2.store = {};
E.f2.store{1} = [];
E.f2.store{1}.type = 'full';
E.f2.store{1}.f_cost = @f2_full_cost;
%E.f2.store{1}.f_min_sum_conv = @(D,x)min(D+repmat(x',size(D,2),1),[],2);
E.f2.store{1}.f_min_sum_conv = @f2_full_min_sum_conv;
%E.f2.store{1}.f_tmin_sum_conv = @(D,x)min(D+repmat(x,1,size(D,2)),[],1)';
E.f2.store{1}.f_tmin_sum_conv = @f2_full_tmin_sum_conv;

E.f2.store{2} = [];
E.f2.store{2}.type = 'potts';
%E.f2.store{2}.f_cost = @(dd)reshape(full(spdiags(dd,size(dd,1)*[0:size(dd,2)-1],size(dd,1),size(dd,1)*size(dd,2))),size(dd,1),size(dd,1),[]);
E.f2.store{2}.f_cost = @f2_potts_cost;
E.f2.store{2}.f_min_sum_conv = @f2_potts_min_sum_conv;
E.f2.store{2}.f_tmin_sum_conv = @f2_potts_min_sum_conv;
%E.f2.store{2}.f_min_sum_conv =  @(d,x)min(min(x),x+d);
%E.f2.store{2}.f_tmin_sum_conv = @(x,d)min(min(x),x+d);

E.f2.store{1}.data = zeros(K,K,1);
E.f2.store{2}.data = zeros(K,1);
end


function D = f2_full_cost(D)
end
function y = f2_full_min_sum_conv(D,x)
y = min(D+repmat(x',size(D,1),1),[],2);
end
function y = f2_full_tmin_sum_conv(D,x)
y = min(D+repmat(x,1,size(D,2)),[],1)';
end
function f2 = f2_potts_cost(dd)
f2 = reshape(full(spdiags(dd,size(dd,1)*[0:size(dd,2)-1],size(dd,1),size(dd,1)*size(dd,2))),size(dd,1),size(dd,1),[]);
end
function y = f2_potts_min_sum_conv(d,x)
y = min(min(x),x+d);
end
