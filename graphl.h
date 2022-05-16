//--------------------------  class GraphL.cpp  ---------------------------------
//  
//---------------------------------------------------------------------------
#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
#include <stdio.h>
using namespace std;

class GraphL
{
public:
    GraphL();
    ~GraphL();
    void buildGraph(ifstream&);
    void depthFirstSearch();
    void displayGraph();
private:
    int size;
    static int const MAXNODES = 100; 
    struct EdgeNode;
    struct GraphNode
    {
        EdgeNode* edgeHead;       
        NodeData* data;           
        bool visited;
    };
    GraphNode node_array[MAXNODES];
    struct EdgeNode
    {
        int adjGraphNode;           
        EdgeNode* nextEdge;        
    };
    void makeEmpty();
    void depthFirstSearchHelper(int v);
};


#endif //GRAPHL_H