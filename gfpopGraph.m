%%% Takes in multiple edges from gfpopEdge.m and combines them into a
%%% single structure to be implemented into gfpop.m.
%%%
%%%     Inputs:
%%%     varargin --> Takes in a variable number of edges
%%%
%%%     Outputs:
%%%     outGraph --> Output structure containing graph of all edges
%%%
%%%     Example:
%%%     exGraph = gfpopGraph(upEdge,dwEdge,upNull,dwNull);
%%%     

function [outGraph] = gfpopGraph(varargin)
    state1vec = zeros(1,length(varargin));
    state2vec = zeros(1,length(varargin));
    typevec = [];
    paramvec = zeros(1,length(varargin));
    penaltyvec = zeros(1,length(varargin));
    kvec = zeros(1,length(varargin));
    avec = zeros(1,length(varargin));
    minvec = zeros(1,length(varargin));
    maxvec = zeros(1,length(varargin));
    for i = 1:length(varargin)
        tempEdge = varargin{1,i};
        state1vec(i) = tempEdge.state1;
        state2vec(i) = tempEdge.state2;
        typevec = [typevec tempEdge.type];
        paramvec(i) = tempEdge.parameter;
        penaltyvec(i) = tempEdge.penalty;
        kvec(i) = tempEdge.k;
        avec(i) = tempEdge.a;
        minvec(i) = tempEdge.min;
        maxvec(i) = tempEdge.max;
    end
    outGraph = struct("state1",state1vec,"state2",state2vec,"type",typevec,"parameter",paramvec, ...
                      "penalty", penaltyvec,"K",kvec,"a",avec,"min",minvec,"max",maxvec);
end