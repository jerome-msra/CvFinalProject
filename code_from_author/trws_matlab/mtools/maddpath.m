function maddpath(pth)
%	mfaddpath(pth) adds path relative to the caller file location
%	and handles the relative path names correctly
%
%

%% get caller's location
stack = dbstack('-completenames');
if (length(stack)>1)
	root = stack(2).file;
else
	root = '';
end
%% root= evalin('caller','mfilename(''fullpath'');'); -- worked with older matlab version
r1 = strfind(root,'/');
r2 = strfind(root,'\');
r = max([r1 r2]);
root = root(1:r-1);
%% if called from command line -- no caller, use cd
if(isempty(root))
	root = cd;
end

%% fprintf('%s\n',root);return;

if (strcmp(pth,'.')) %% path only '.'
	pth = '';
	ff = root;
else
	ff = [root '/' pth];
end
%%

%resolve relative positions within ff

while 1
	p = strfind(ff,'..');
	if length(p)==0
		break;
	end
	p = p(1);
	r1 = strfind(ff(1:p-2),'/');
	r2 = strfind(ff(1:p-2),'\');
	r = max([r1 r2]);
	ff = [ff(1:r) ff(p+3:end)];
end

fprintf('path %s\n',ff);
addpath(ff);

end