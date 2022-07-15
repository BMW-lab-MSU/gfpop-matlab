%%% Takes in edge values to create an edge to be put into gfpopGraph.m
%%%
%%%     INPUTS:
%%%     [Required]
%%%       - These inputs are not specified in the function call.
%%%     state1 --> string of first state for the edge
%%%     state2 --> string of second state for the edge
%%%     edge type --> string of the edge type for the edge
%%%         edge types: null <- u(t) == u(t+1)
%%%                     std <- u(t) != u(t+1)
%%%                     up <- u(t) + gap < u(t+1)
%%%                     down <- u(t) > u(t+1) + gap
%%%                     abs <- |u(t+1)-u(t)| > gap
%%%     [Optional]
%%%      - These inputs must be specified in the function call
%%%     decay --> nonnegative to give strength to decay into edge
%%%     gap --> nonnegative to constrain size of gap in state change
%%%     penalty --> nonnegative double of the penalty for the edge.
%%%     K --> positive double of the robust biweight gaussian loss
%%%     a --> positive double of the slope for the huber robust loss
%%%     min --> nonnegative double of the minimum gap for the edge
%%%     max --> nonnegative double of the maximum gap for the edge
%%%
%%%     OPTIONAL INPUT DEFAULTS:
%%%     decay = 0
%%%     gap = 0;
%%%     penalty = 0
%%%     K = Inf
%%%     a = 0
%%%     min = NaN
%%%     max = NaN
%%%
%%%     OUTPUTS:
%%%     edge --> Structure organized for implementation to gfpopGraph.m
%%%
%%%     EXAMPLES:
%%%     edge1 = gfpopEdge("air","ground","std")
%%%     edge2 = gfpopEdge("up","down","down",penalty=50,gap=10)
%%%     edge3 = gfpopEdge("inc_to_bee","bee","up","penalty=.1)
%%%

function edge = gfpopEdge(state1,state2,edgeType,varargin)
    
    % Default Values for Optional Inputs
    p = inputParser;
    nonNeg = @(x) assert(isnumeric(x) && (x>=0),"Value must be nonnegative");
    validTypes = ["null","std","up","down","abs"];
    checkEdge = @(x) any(matches(validTypes,x));

    % Checking inputs for required and optional values
    addRequired(p,'state1',@isstring);
    addRequired(p,'state2',@isstring);
    addRequired(p,'edgeType',checkEdge);
    addParameter(p,'decay',1,nonNeg);
    addParameter(p,'gap',0,nonNeg);
    addParameter(p,'penalty',0,nonNeg);
    addParameter(p,'k',Inf,nonNeg);
    addParameter(p,'a',0,nonNeg);
    addParameter(p,'min',NaN,nonNeg);
    addParameter(p,'max',NaN,nonNeg);

    % Parsing inputs together
    parse(p,state1,state2,edgeType,varargin{:});

    % Checking edge to choose decay or gap
    if(p.Results.edgeType == "null")
        parameter = p.Results.decay;
    else
        parameter = p.Results.gap;
    end

    % Constructing edge struct
    edge = struct("state1",p.Results.state1,"state2",p.Results.state2,"type",p.Results.edgeType,"parameter",parameter, ...
                  "penalty",p.Results.penalty,"k",p.Results.k,"a",p.Results.a,"min",p.Results.min,"max",p.Results.max);

end