%%% Takes in edge values to create an edge to be put into gfpopGraph.m
%%%
%%%     INPUTS:
%%%     state1 ---> string of first state for the edge
%%%     state2 ---> string of second state for the edge
%%%     edge type ---> string of the edge type for the edge
%%%         edge types: null <- u(t) == u(t+1)
%%%                     std <- u(t) != u(t+1)
%%%                     up <- u(t) + gap < u(t+1)
%%%                     down <- u(t) > u(t+1) + gap
%%%                     abs <- |u(t+1)-u(t)| > gap
%%%     parameter ---> double of the parameters for the edge
%%%     penalty ---> nonnegative double of the penalty for the edge
%%%     K ---> positive double of the robust biweight gaussian loss
%%%     a ---> positive double of the slope for the huber robust loss
%%%     min ---> nonnegative double of the minimum gap for the edge
%%%     max ---> nonnegative double of the maximum gap for the edge
%%%
%%%     OUTPUTS:
%%%     edge ---> Structure organized for implementation to gfpopGraph.m
%%%
%%%     EXAMPLE:
%%%     edge1 = gfpopEdge(0,0,"null",1,0,Inf,0,NaN,NaN);
%%%

function edge = gfpopEdge(state1,state2,edgeType,parameter,penalty,k,a,min,max)
    edge = struct("state1",state1,"state2",state2,"type",edgeType,"parameter",parameter, ...
                  "penalty",penalty,"k",k,"a",a,"min",min,"max",max);
end