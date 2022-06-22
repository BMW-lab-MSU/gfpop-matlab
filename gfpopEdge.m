%%% Takes in edge values to create an edge to be put into gfpopGraph.m
%%%
%%%     INPUTS:
%%%     [Required]
%%%     state1 --> string of first state for the edge
%%%     state2 --> string of second state for the edge
%%%     edge type --> string of the edge type for the edge
%%%         edge types: null <- u(t) == u(t+1)
%%%                     std <- u(t) != u(t+1)
%%%                     up <- u(t) + gap < u(t+1)
%%%                     down <- u(t) > u(t+1) + gap
%%%                     abs <- |u(t+1)-u(t)| > gap
%%%     [Optional]
%%%     parameter --> double of the parameters for the edge.
%%%     penalty --> nonnegative double of the penalty for the edge.
%%%     K --> positive double of the robust biweight gaussian loss
%%%     a --> positive double of the slope for the huber robust loss
%%%     min --> nonnegative double of the minimum gap for the edge
%%%     max --> nonnegative double of the maximum gap for the edge
%%%
%%%     OPTIONAL INPUT DEFAULTS:
%%%     parameter = 0
%%%     penalty = 0
%%%     K = Inf
%%%     a = 0
%%%     min = NaN
%%%     max = NaN
%%%
%%%     OUTPUTS:
%%%     edge --> Structure organized for implementation to gfpopGraph.m
%%%
%%%     EXAMPLE:
%%%     edge1 = gfpopEdge(0,0,"null",1,0,Inf,0,NaN,NaN);
%%%

function edge = gfpopEdge(state1,state2,edgeType,varargin)
    
    % Default Values for Optional Inputs
    p = inputParser;
    defaultparameter = 0;
    defaultpenalty = 0;
    defaultk = Inf;
    defaulta = 0;
    defaultmin = NaN;
    defaultmax = NaN;

    % Checking inputs for required and optional values
    addRequired(p,'state1',@isstring);
    addRequired(p,'state2',@isstring);
    addRequired(p,'edgeType',@isstring);
    addParameter(p,'parameter',defaultparameter,@isnumeric);
    addParameter(p,'penalty',defaultpenalty,@isnumeric);
    addParameter(p,'k',defaultk,@isnumeric);
    addParameter(p,'a',defaulta,@isnumeric);
    addParameter(p,'min',defaultmin,@isnumeric);
    addParameter(p,'max',defaultmax,@isnumeric);

    % Parsing inputs together
    parse(p,state1,state2,edgeType,varargin{:});

    % Constructing edge struct
    edge = struct("state1",p.Results.state1,"state2",p.Results.state2,"type",p.Results.edgeType,"parameter",p.Results.parameter, ...
                  "penalty",p.Results.penalty,"k",p.Results.k,"a",p.Results.a,"min",p.Results.min,"max",p.Results.max);

end