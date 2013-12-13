function T = geom_transform(varargin)
%
% 	T = geom_transform(tform) -- constructor from tform.
% 	T = geom_transform(a_discrete_transform) -- constructor from discrete_transform.
% 	T = geom_transform() -- identity transform.
% 	T = geom_transform(s,type) -- scale/translation transform: type = 'scale' or 'translation'.
% 	T = geom_transform(x,block_size,type,[mask1],[mask2],fw) -- transform using displacement field x.
%																		type: 'projective', 'piecewise linear', etc.
%								fw = true -- forward transform, false -- backward transform 
%
%

T = [];
T.form = [];

switch nargin
	case 0
		T.form = maketform('affine',eye(3));
	case 1
		if(isa(varargin{1},'discrete_transform'))
			error('not implemented');
		else
			T.form = varargin{1};
		end
	case 2
		a = varargin{1};
		a = a(:);
		type = varargin{2};
		if ~isempty(strfind(type,'scale'))
		if(isa(a,'double'))
			A = eye(2)*a;
			T.form = maketform('affine', [A (eye(2)-A)*[1;1]]');
		else
			error('Unrecognized argument 1');
		end
		elseif ~isempty(strfind(type,'translation'))
			A = eye(2);
			T.form = maketform('affine', [A a([2 1])]');
		else
			error('Unrecognized argument 1');
		end
end
if(nargin>=3 && nargin<=6)
	x = varargin{1};
	block_size = varargin{2};
	type = varargin{3};
	if(nargin>=4)
		mask1 = varargin{4};
	else
		mask1 = [];
	end
	if(nargin==5)
		mask2 = varargin{5};
	else
		mask2 = [];
	end
	if(nargin==6)
		fw = varargin{6};
	else 
		fw = true;
	end
	[L R] = corresp_list(x,block_size,mask1,mask2);
	
%  	d2 = zeros(msize(x,[1 2]));
%  	d2(:,1:2:end) = 0.1;
%  	d1 = zeros(msize(x,[1 2]));
%  	d1(1:2:end,:) = 0.1;	
%  	L(1,:) = L(1,:)+d2(:)';
%  	L(2,:) = L(2,:)+d1(:)';
%  	R(1,:) = R(1,:)+d2(:)';
%  	R(2,:) = R(2,:)+d1(:)';

	%mL = min(L,[],2);
	%L = L-repmat(mL,1,size(L,2));
	if ~isempty(strfind(type,'projective'))
			n = size(L,2);
			sL = range(L(:));
			sR = range(R(:));
			mL = mean(L,2)/sL;
			mR = mean(R,2)/sR;
			
			TL = [1/sL 0 -mL(1); 0 1/sL -mL(2); 0 0 1];
			TR = [1/sR 0 -mR(1); 0 1/sR -mR(2); 0 0 1];
			L(3,:)=1;
			R(3,:)=1;
			
			l = TL*L;
			r = TR*R;
			f = cp2tform(l([2 1],:)',r([2 1],:)','projective');
			h = f.tdata.T([2 1 3],[2 1 3]);
			%h = r/l;
			H = TR^-1*h'*TL;
			H = 0.1*H+0.9*eye(3);
			T.form = maketform('projective',H([2 1 3],[2 1 3])');			
	else
		if fw
			%% fprward transform
			T.form  = cp2tform(L([2 1],:)',R([2 1],:)',type);
		else
			%% inverse transform
			T.form  = cp2tform(R([2 1],:)',L([2 1],:)',type);
		end
	end
elseif(nargin>5)
	error('Unrecognized arguments');
end
T = class(T,'geom_transform');
end