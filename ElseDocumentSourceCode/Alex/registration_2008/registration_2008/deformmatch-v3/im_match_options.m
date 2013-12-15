function ops = im_match_options(varargin)
% There are parameters for im_match. To change some of the default options here use syntax 'param',value 
%
%  parameters and their default values:
%
%  metric_func = @ssd_fun -- user defined pixel-to-pixel cost function
%  K = [15 15] -- search window size
%  block_size = 10 -- block size
%  max_c1 = 200 -- maximum number of entries for quantization of I1
%  max_c2 = 200 -- maximum number of entries for quantization of I2
%  x0 = [1 1] -- search relative position
%  eps = 1e-2 -- convergence tolerance
%  maxit = 20 -- maximum number of iterations
%  fix_strategy = 1 -- which fix strategy to use 0/1
%  dxc = floor(K/2) -- search center point (resedved)
%  display = false -- visualize processing stage
%  figure_handle = [] -- handle to figure where visualization will be display
%  deform_reg -- deformation regularization parameter (no effect, reserved)
%  maxd (=1) -- deformation maximum allower relative displacement (no effect, reserved)
%  bg_func (=@bg_penalty_fun) -- user defined pixel-to-background cost function
%  bg_func_params (=0.2) -- set if your function accepts more params

ops = [];
ops. metric_func = @ssd_fun;
ops.K = [15 15];
ops.block_size = 10;
ops.max_c1 = 200;
ops.max_c2 = 200;
ops.x0 = [1 1];
ops.eps = 1e-2;
ops.maxit = 20;
ops.fix_strategy = 1;
ops.display = false;
ops.figure_handle = [];
ops.deform_reg = 0;
ops.maxd = 1;
ops.bg_policy = 1;
ops.bg_func = @bg_penalty_func;
ops.bg_func_params = 0.2;

for i=1:2:length(varargin)
	ops = setfield(ops, varargin{i},varargin{i+1});
end

end