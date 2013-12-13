function T = compose(U,V,W)
%
%		T = compose(U,V,W=[]) -- composite transform T = U*V (T = U*V*W)
%

if(~exist('W','var') || isempty(W))
	T = geom_transform(maketform('composite',U.form,V.form));
else
	T = geom_transform(maketform('composite',U.form,V.form,W.form));
end

end