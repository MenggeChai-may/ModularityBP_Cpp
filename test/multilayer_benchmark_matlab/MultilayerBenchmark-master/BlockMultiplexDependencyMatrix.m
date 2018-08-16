function P=BlockMultiplexDependencyMatrix(n_blocks,n_layers,p_in,p_out)
% Generate a block-multiplex dependency matrix
%
% Input: 
%   
%   n_blocks: number of equal-sized blocks of layers
%
%   n_layers: number of layers in each block
%
%   p_in: probability for a state node to copy its community assignment from
%       corresponding state nodes in the same block
%
%   p_out: [default: 0] probability for a state node to copy its community 
%       assignment from corresponding state nodes in a different block 
%
% Output:
%
%   P: Dependency matrix for use with PartitionGenerator
%
% Note that p_in+p_out<=1
%
% Version: 1.0.1
% Date: Tue  4 Jul 2017 16:38:06 BST
% Author: Lucas Jeub
% Email: ljeub@iu.edu
%
% References:
% 
%       [1] Generative benchmark models for mesoscale structure in multilayer 
%       networks, M. Bazzi, L. G. S. Jeub, A. Arenas, S. D. Howison, M. A. 
%       Porter. arXiv1:608.06196.
%
% Citation: 
%
%       If you use this code, please cite as
%       Lucas G. S. Jeub and Marya Bazzi
%       "A generative model for mesoscale structure in multilayer networks 
%       implemented in MATLAB," https://github.com/MultilayerBenchmark/MultilayerBenchmark (2016).

if nargin<4
    p_out=0;
end

if p_in+p_out>1
    error('MultilayerBenchmark:BlockMultiplexMatrix:probability',...
        'Sum of copying probabilities>1');
end

A=(ones(n_layers)-eye(n_layers))*p_in/(n_layers-1);
B=ones(n_layers)*p_out/(n_layers*(n_blocks-1));

P=kron(eye(n_blocks),A)+kron(ones(n_blocks)-eye(n_blocks),B);

end
