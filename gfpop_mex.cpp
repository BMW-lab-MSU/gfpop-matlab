/* main_mex.cpp 
    Main file for using gfpop in Matlab 
*/
#include <iostream>
#include <string>
#include "math.h"

#include"Omega.h"
#include"Cost.h"
#include"ExternFunctions.h"
#include"Data.h"
#include"Graph.h"
#include"Edge.h"
#include"Interval.h"
#include"Track.h"
#include"Piece.h"
#include"ListPiece.h"

#include "Cost.cpp"
#include "Data.cpp"
#include "Edge.cpp"
#include "ExternFunctions.cpp"
#include "Graph.cpp"
#include "Interval.cpp"
#include "ListPiece.cpp"
#include "Omega.cpp"
#include "Piece.cpp"
#include "Track.cpp"

#include "mex.hpp"
#include "mexAdapter.hpp"

using namespace matlab::data;
using matlab::mex::ArgumentList;

class MexFunction : public matlab::mex::Function{
    ArrayFactory factory;
    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
    std::ostringstream stream;

public:
    void operator()(ArgumentList outputs, ArgumentList inputs){
        //checkArguments(outputs, inputs);

        // Input Setup
        TypedArray<double> vectDataIn = std::move(inputs[0]);
        std::vector<double> vectData(vectDataIn.begin(),vectDataIn.end());
        stream << "data loaded\n";
        displayOnMATLAB(stream);
       
        StructArray mygraph(inputs[1]);
        Range<ForwardIterator,MATLABFieldIdentifier const> fields = mygraph.getFieldNames();
        TypedArray<double> state1In = mygraph[0][fields.begin()[0]];
        TypedArray<double> state2In = mygraph[0][fields.begin()[1]];
        TypedArray<MATLABString> edgeIn = mygraph[0][fields.begin()[2]];
        TypedArray<double> parameterIn = mygraph[0][fields.begin()[3]];
        TypedArray<double> penaltyIn = mygraph[0][fields.begin()[4]];
        TypedArray<double> KIn = mygraph[0][fields.begin()[5]];
        TypedArray<double> aIn = mygraph[0][fields.begin()[6]];
        TypedArray<double> minnIn = mygraph[0][fields.begin()[7]];
        TypedArray<double> maxxIn = mygraph[0][fields.begin()[8]];

                  ///9 variables in mygraph
    stream << "state 1\n";
    displayOnMATLAB(stream);
        std::vector<int> state1(state1In.begin(),state1In.end());
    
    stream << "state 2\n";
    displayOnMATLAB(stream);
        std::vector<int> state2(state2In.begin(),state2In.end());
    
    stream << "edge type\n";
    displayOnMATLAB(stream);
        std::vector<std::string> typeEdge(edgeIn.begin(),edgeIn.end());
    
    stream << "parameter\n";
    displayOnMATLAB(stream);
        std::vector<double> parameter(parameterIn.begin(),parameterIn.end());
    
    stream << "penalty\n";
    displayOnMATLAB(stream);
        std::vector<double> penalty(penaltyIn.begin(),penaltyIn.end());
    
    stream << "k\n";
    displayOnMATLAB(stream);
        std::vector<double> KK(KIn.begin(),KIn.end());
    
    stream << "a\n";
    displayOnMATLAB(stream);
        std::vector<double> aa(aIn.begin(),aIn.end());
          
    stream << "min\n";
    displayOnMATLAB(stream);
        std::vector<double> minn(minnIn.begin(),minnIn.end());
    
    stream << "max\n";
    displayOnMATLAB(stream);
        std::vector<double> maxx(maxxIn.begin(),maxxIn.end());
        
    stream << "graph loaded\n";
    displayOnMATLAB(stream);

        TypedArray<MATLABString> typeIn = inputs[2];
        std::string type = std::string(typeIn[0]);
    stream << "type loaded\n";
    displayOnMATLAB(stream);


        TypedArray<double> vectWeightIn = std::move(inputs[3]);
        std::vector<double> vectWeight(vectWeightIn.begin(),vectWeightIn.end());
    stream << "weights loaded\n";
    displayOnMATLAB(stream);

        int testMode = 0;

        /* Only useful for debugging
        TypedArray<bool> testModeIn = std::move(inputs[4]);
        //std::vector<bool> testMode(testModeIn.begin(),testModeIn.end());
        std::vector<bool> testMode(testModeIn[0]);
        stream << "test mode loaded\n";
        displayOnMATLAB(stream);
        */

// INPUT CHECKING ON GRAPH AND DATA
stream << "--- INPUT CHECKING --- INPUT CHECKING --- INPUT CHECKING ---";
displayOnMATLAB(stream);

int indexCheck = 0;

stream << "\nIndex : ";
displayOnMATLAB(stream);
stream << std::to_string(indexCheck);
displayOnMATLAB(stream);

stream << "\n State1: ";
displayOnMATLAB(stream);
stream << std::to_string(state1[indexCheck]);
displayOnMATLAB(stream);

stream << "\n State2: ";
displayOnMATLAB(stream);
stream << std::to_string(state2[indexCheck]);
displayOnMATLAB(stream);

stream << "\n Edge Type: ";
displayOnMATLAB(stream);
stream << (typeEdge[indexCheck]);
displayOnMATLAB(stream);

stream << "\n Parameter: ";
displayOnMATLAB(stream);
stream << std::to_string(parameter[indexCheck]);
displayOnMATLAB(stream);

stream << "\n Penalty: ";
displayOnMATLAB(stream);
stream << std::to_string(penalty[indexCheck]);
displayOnMATLAB(stream);

stream << "\n K: ";
displayOnMATLAB(stream);
stream << std::to_string(KK[indexCheck]);
displayOnMATLAB(stream);

stream << "\n a: ";
displayOnMATLAB(stream);
stream << std::to_string(aa[indexCheck]);
displayOnMATLAB(stream);

stream << "\n min: ";
displayOnMATLAB(stream);
stream << std::to_string(penalty[indexCheck]);
displayOnMATLAB(stream);

stream << "\n max: ";
displayOnMATLAB(stream);
stream << std::to_string(penalty[indexCheck]);
displayOnMATLAB(stream);

stream << "\n --- END CHECKING --- END CHECKING --- END CHECKING --- \n";
displayOnMATLAB(stream);


        
        // Code from main.cpp for gfpop
                ///////////////////////////////////////////
          /////////// DATA TRANSFORMATION ///////////
          ///////////////////////////////////////////
          double epsilon = std::pow(10.0,-12.0);
        
      stream << "checking type\n";
      displayOnMATLAB(stream);    
          if(type == "variance")
          {
            double mean = 0;
            for(int i = 0; i < vectData.size(); i++){mean = mean + vectData[i];}
            mean = mean/vectData.size();
            for(int i = 0; i < vectData.size(); i++){vectData[i] = vectData[i] - mean; if(vectData[i] == 0){vectData[i] = epsilon;}}
          }
        
          if(type == "poisson")
          {
            for(int i = 0; i < vectData.size(); i++){if(vectData[i] < 0){throw std::range_error("There are some negative data");}}
            //for(int i = 0; i < vectData.size(); i++){if(vectData[i]  > floor(vectData[i])){throw std::range_error("There are some non-integer data");}}
          }
        
          if(type == "exp")
          {
            for(int i = 0; i < vectData.size(); i++){if(vectData[i] <= 0){throw std::range_error("Data has to be all positive");}}
          }
        
          if(type == "negbin")
          {
            unsigned int windowSize = 100;
            unsigned int k = vectData.size() / windowSize;
            double mean = 0;
            double variance = 0;
            double disp = 0;
        
            for(unsigned int j = 0; j < k; j++)
            {
              mean = 0;
              variance = 0;
              for(unsigned int i = j * windowSize; i < (j + 1)*windowSize; i++){mean = mean + vectData[i];}
              mean = mean/windowSize;
              for(unsigned int i =  j * windowSize; i < (j + 1)*windowSize; i++){variance = variance + (vectData[i] - mean) * (vectData[i] - mean);}
              variance = variance/(windowSize - 1);
              disp = disp  + (mean * mean / (variance - mean));
            }
            disp = disp/k;
            for(int i = 0; i < vectData.size(); i++){vectData[i] = vectData[i]/disp; if(vectData[i] == 0){vectData[i] = epsilon/(1- epsilon);}}
          }

    stream << "type checked\n";
    displayOnMATLAB(stream);
        
          // BEGIN TRANSFERT into C++ objects  // BEGIN TRANSFERT into C++ objects  // BEGIN TRANSFERT into C++ objects
          // BEGIN TRANSFERT into C++ objects  // BEGIN TRANSFERT into C++ objects  // BEGIN TRANSFERT into C++ objects
          // DATA AND GRAPH
        
          /////////////////////////////////
          /////////// DATA COPY ///////////
          /////////////////////////////////

stream << "data copy\n";
displayOnMATLAB(stream);

          Data data = Data();
          data.copy(vectData, vectWeight, vectData.size(), vectWeight.size());
        
          //////////////////////////////////
          /////////// GRAPH COPY ///////////
          //////////////////////////////////

stream << "graph copy\n";
displayOnMATLAB(stream);
        
          Graph graph = Graph();
          Edge newedge;

stream << "graph copy loop\n";
displayOnMATLAB(stream);

          for(int i = 0 ; i < state1.size(); i++){
stream << std::to_string(i);
displayOnMATLAB(stream);
stream << "   |   ";
displayOnMATLAB(stream);
stream << std::to_string(state1[i]);
displayOnMATLAB(stream);
stream << "   |   ";
displayOnMATLAB(stream);
stream << std::to_string(state2[i]);
displayOnMATLAB(stream);
stream << "   |   ";
displayOnMATLAB(stream);
stream << (typeEdge[i]);
displayOnMATLAB(stream);
stream << "   |   ";
displayOnMATLAB(stream);
stream << std::to_string(parameter[i]);
displayOnMATLAB(stream);
stream << "   |   ";
displayOnMATLAB(stream);
stream << std::to_string(penalty[i]);
displayOnMATLAB(stream);
stream << "   |   ";
displayOnMATLAB(stream);
stream << std::to_string(KK[i]);
displayOnMATLAB(stream);
stream << "   |   ";
displayOnMATLAB(stream);
stream << std::to_string(aa[i]);
displayOnMATLAB(stream);
stream << "   |   ";
displayOnMATLAB(stream);
stream << std::to_string(minn[i]);
displayOnMATLAB(stream);
stream << "   |   ";
displayOnMATLAB(stream);
stream << std::to_string(maxx[i]);
displayOnMATLAB(stream);



stream << "\n";
displayOnMATLAB(stream);
              graph << Edge(state1[i], state2[i], typeEdge[i], fabs(parameter[i]), penalty[i], fabs(KK[i]), fabs(aa[i]), minn[i], maxx[i]);
          }

          if(testMode == 1){graph.show();} ///TESTMODE
        
          // END TRANSFERT into C++ objects  // END TRANSFERT into C++ objects  // END TRANSFERT into C++ objects
          // END TRANSFERT into C++ objects  // END TRANSFERT into C++ objects  // END TRANSFERT into C++ objects
        
          /////////////////////////////////////////////
          /////////// COST FUNCTION LOADING ///////////
          /////////////////////////////////////////////

    stream << "cost function loading\n";
    displayOnMATLAB(stream);
        
          cost_coeff = coeff_factory(type);
          cost_eval = eval_factory(type);
        
          cost_min = min_factory(type);
          cost_minInterval = minInterval_factory(type);
          cost_argmin = argmin_factory(type);
          cost_argminInterval = argminInterval_factory(type);
          cost_argminBacktrack = argminBacktrack_factory(type);
        
          cost_shift = shift_factory(type);
          cost_interShift = interShift_factory(type);
          cost_expDecay = expDecay_factory(type);
          cost_interExpDecay = interExpDecay_factory(type);
        
          cost_intervalInterRoots = intervalInterRoots_factory(type);
          cost_age = age_factory(type);
          cost_interval = interval_factory(type);


          /////////////////////////////
          /////////// OMEGA ///////////
          /////////////////////////////

stream << "Edge Check\n";
displayOnMATLAB(stream);
for(int i = 0; i < graph.nb_edges(); i++){
    Edge tmp = graph.getEdge(i);
    stream << std::to_string(i);
    displayOnMATLAB(stream);
    stream << ": ";
    displayOnMATLAB(stream);
    stream << std::to_string(tmp.getState1());
    displayOnMATLAB(stream);
    stream << "\n";
    displayOnMATLAB(stream);
}

    stream << "\nomega construction\n";
    displayOnMATLAB(stream);
        
          Omega omega(graph);



Point* tmpData = data.getVecPt();
stream << std::to_string(tmpData[0].y);
displayOnMATLAB(stream);
stream << "\n";
displayOnMATLAB(stream);
stream << std::to_string(tmpData[0].w);
displayOnMATLAB(stream);
stream << "\n";
displayOnMATLAB(stream);

        

    stream << "omega run\n";
    displayOnMATLAB(stream);
          if(testMode == 0){
              omega.gfpop(data);
          }else{
              omega.gfpopTestMode(data);
          }

          /////////////////////////////
          /////////// RETURN //////////
          /////////////////////////////

    stream << "gathering outputs\n";
    displayOnMATLAB(stream);
        
        // Gathering Output Parameters into C++ Data
        std::vector<std::vector<int>> changepoints = omega.GetChangepoints();
        std::vector<std::vector<int>> states = omega.GetStates();
        std::vector<std::vector<bool>> forced = omega.GetForced();
        std::vector<std::vector<double>> parameters = omega.GetParameters();
        std::vector<double> globalCost = omega.GetGlobalCost();

    stream << "generating output structure\n";
    displayOnMATLAB(stream);

        // Output Structure Array Setup
        StructArray res = factory.createStructArray({1,1},{"changepoints", "states", "forced", "parameters", "globalcost"});
        CellArray changepointsCell = factory.createCellArray({1,1});
        CellArray statesCell = factory.createCellArray({1,1});
        CellArray forcedCell = factory.createCellArray({1,1});
        CellArray paramCell = factory.createCellArray({1,1});
        TypedArray<double> globalCostCell = factory.createArray<double>({1,globalCost.size()}, globalCost.data(), globalCost.data()+globalCost.size());

    stream << "--- OUTPUT CHECKING --- OUTPUT CHECKING --- OUTPUT CHECKING ---\n";
    displayOnMATLAB(stream);

    stream << ("changepoints.size: ");
    displayOnMATLAB(stream);
    stream << std::to_string(changepoints.size());
    displayOnMATLAB(stream);
    stream << ("\n");
    displayOnMATLAB(stream);

    stream << ("states.size: ");
    displayOnMATLAB(stream);
    stream << std::to_string(states.size());
    displayOnMATLAB(stream);
    stream << ("\n");
    displayOnMATLAB(stream);
    
    stream << ("col  :  state\n");
    displayOnMATLAB(stream);
    for(int i = 0; i < changepoints.size(); i++){
        for(int j = 0; j < changepoints[i].size(); j++){
            stream << std::to_string(changepoints[i][j]);
            displayOnMATLAB(stream);
            stream << " --> ";
            displayOnMATLAB(stream);
            stream << std::to_string(states[i][j]);
            displayOnMATLAB(stream);
            stream << "\n";
            displayOnMATLAB(stream);
        }
    }

        stream << "--- END OUTPUT CHECKING --- END OUTPUT CHECKING --- END OUTPUT CHECKING ---\n";
    displayOnMATLAB(stream);

        // Output Structure Array Population


    stream << "assigning outputs\n";
    displayOnMATLAB(stream);    

        // Assigning outputs
        res[0]["changepoints"] = changepointsCell;
        res[0]["states"] = statesCell;
        res[0]["forced"] = forcedCell;
        res[0]["parameters"] = paramCell;
        res[0]["globalcost"] = globalCostCell;

        // Output Setup
        outputs[0] = res;
        
        //return res;
    }
    /*
    void checkArguments(ArgumentList outputs, ArgumentList inputs){
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr getEngine();
        ArrayFactory factory;
        // Check first input

        // Check output
    }
    */

    void displayOnMATLAB(std::ostringstream& stream){
        matlabPtr -> feval(u"fprintf",0,std::vector<Array>({factory.createScalar(stream.str())}));
        stream.str("");
    }
    
};