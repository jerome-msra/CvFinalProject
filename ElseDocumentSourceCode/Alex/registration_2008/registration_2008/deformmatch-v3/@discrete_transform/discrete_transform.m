function T = discrete_transform(varargin)
%
% 	discrete_transform(x,block_size,target_sz) -- create from block centers displacements field.
% 	discrete_transform() -- empty object.
%	discrete_transform(sz) -- identity transform of size sz
%			sz [1 2] integer -- size
%	discrete_transform(sz, t0) -- displacemet by t0 transform of size sz
%			sz [1 2] integer -- size
%			t0 [1 2] double -- displacement
%

T.f = [];

switch(nargin)
	case 0
	case 1 %% identity transform
		sz = varargin{1};
		T.f = mmeshgrid(sz);
	case 2 %% displacement transform
		sz = varargin{1};
		t0 = varargin{2};
		T.f = mmeshgrid(sz);
		T.f = madd(mmeshgrid(sz),t0,3);
	case 3 %% dense_field transform
		x = varargin{1};
		block_size = varargin{2};
		target_sz = varargin{3};
		T.f = dense_field2(x,block_size,target_sz);
	otherwise
		error('wrong arguments');
end

T = class(T,'discrete_transform');
end