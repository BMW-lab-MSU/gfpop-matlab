%%% Takes in multiple edges from gfpopEdge.m and combines them into a
%%% single structure to be implemented into gfpop.m.
%%%
%%%     INPUTS:
%%%     [Required]
%%%     edges --> vector of edges constructed from gfpopEdge.m
%%%
%%%     [Optional]
%%%     startState --> string of the starting state for gfpop.m
%%%     endState --> string of the ending state for gfpop.m
%%%     allNullEdges --> boolean for creating a null edge for each state
%%%
%%%     OUTPUTS:
%%%     outputGraph --> Output structure containing graph of all edges
%%%
%%%     EXAMPLE:
%%%     exGraph = gfpopGraph([upEdge dwEdge],startState="up",endState="down",allNullEdges=true);
%%%     

function outputGraph = gfpopGraph(edgesIn,varargin)

    % Setting up optional inputs
    p = inputParser;

    % Checking inputs for required and optional values
    addRequired(p,'edgesIn',@isstruct);
    addParameter(p,'startState',"",@isstring);
    addParameter(p,'endState',"",@isstring);
    addParameter(p,'allNullEdges',false,@islogical);

    % Parsing inputs together
    parse(p,edgesIn,varargin{:});
    edges = p.Results.edgesIn;
    startState = p.Results.startState;
    endState = p.Results.endState;
    allNullEdges = p.Results.allNullEdges;

    % Declaring vectors
    state1vec = [];
    state2vec = [];
    typevec = [];
    paramvec = [];
    penaltyvec = [];
    kvec = [];
    avec = [];
    minvec = [];
    maxvec = [];

    % Defined edges
    for i = 1:length(edges)
        tempEdge = edges(i);
        state1vec = [state1vec tempEdge.state1];
        state2vec = [state2vec tempEdge.state2];
        typevec = [typevec tempEdge.type];
        paramvec = [paramvec tempEdge.parameter];
        penaltyvec = [penaltyvec tempEdge.penalty];
        kvec = [kvec tempEdge.k];
        avec = [avec tempEdge.a];
        minvec = [minvec tempEdge.min];
        maxvec = [maxvec tempEdge.max];
    end

    % Adding optional inputs
    if(allNullEdges)
        uniqueVectors = unique([state1vec state2vec]);
        for i = 1:length(uniqueVectors)
            state1vec = [state1vec uniqueVectors(i)];
            state2vec = [state2vec uniqueVectors(i)];
            typevec = [typevec "null"];
            paramvec = [paramvec 1];
            penaltyvec = [penaltyvec 0];
            kvec = [kvec Inf];
            avec = [avec 0];
            minvec = [minvec NaN];
            maxvec = [maxvec NaN];
        end
    end

    if(strlength(startState) ~= 0)
        state1vec = [state1vec startState];
        state2vec = [state2vec NaN];
        typevec = [typevec "start"];
        paramvec = [paramvec NaN];
        penaltyvec = [penaltyvec NaN];
        kvec = [kvec NaN];
        avec = [avec NaN];
        minvec = [minvec NaN];
        maxvec = [maxvec NaN];
    end

    if(strlength(endState) ~= 0)
        state1vec = [state1vec endState];
        state2vec = [state2vec NaN];
        typevec = [typevec "end"];
        paramvec = [paramvec NaN];
        penaltyvec = [penaltyvec NaN];
        kvec = [kvec NaN];
        avec = [avec NaN];
        minvec = [minvec NaN];
        maxvec = [maxvec NaN];
    end

    outputGraph = struct("state1",state1vec,"state2",state2vec,"type",typevec,"parameter",paramvec, ...
                   "penalty", penaltyvec,"K",kvec,"a",avec,"min",minvec,"max",maxvec);

end