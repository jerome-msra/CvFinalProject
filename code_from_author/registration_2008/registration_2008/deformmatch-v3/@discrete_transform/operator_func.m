function varargout = operator_func(varargin)
%
%	operator_func(f2,f1)
%	  f1,f2 - discrete_transforms -- returns the composition discrete_transform R = f2*f1
%
%	[R mask] = operator_func(t,I,interpolation,mask) -- deforms the	image I
%	  this may be somewhat confusingm, but R=t(I) means in fact that
%	  R(x) = I(t(x)), where x is 2D coordinate
%
%	  I - [m x n x k] double/logical -- image to deform
%	  interpolation - 'linear'/'bicubic' (='linear') -- interpolation method
%	  mask [m x n] logical (optional) -- image mask
%	  R -- deformed image

if nargin==2
	if (isa(varargin{2},'discrete_transform'))
		f2 = varargin{1};
		f1 = varargin{2};
		varargout{1} = compose(f2,f1);
		return;
	end
end
if nargin==2 || nargin==3 || nargin==4
	t = varargin{1};
	I = varargin{2};
	if nargin>=3
		interpolation = varargin{3};
	else
		if(islogical(I))
			interpolation = 'nearest';
		else
			interpolation = 'linear';
		end
	end
	if(isempty(interpolation))
		interpolation = 'linear';
	end
	if ~(nargout==1 || nargout==2)
		error('1-2 outputs expected');
	end
	if (islogical(I))
		R = minterp2(t.f,I,interpolation);
	else
		[R m] = minterp2(t.f,I,interpolation);
	end
	varargout{1} = R;
	if nargin==4 && ~isempty(varargin{4})
		if(isempty(m))
			m = true(msize(R,[1 2]));
		end
		mask = varargin{4};
		mm = minterp2(t.f,mask);
		m = m & mm;
	end
	if nargout==2
		varargout{2} = m;
	end
	return;
end

error('2-3 arguments expected.');

end