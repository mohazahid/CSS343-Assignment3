//--------------------------  class GraphL.h  ---------------------------------
// Mohammad Zahid CSS343
// 5/10/2022
// 2/15/2022
// --------------------------------------------------------------------------------------------------------------------
// Purpose - This  project  is  to  display  the  graph  information  and  implement  depth-first  (search  always 
// starts at node #1). Similar to Part 1, in the input data (e.g., data32.txt), the first line tells the number of nodes, say n, 
// followed by a text description of each of the 1 through n nodes, one description per line (50 chars 
// max  length).    After  that,  each  line  consists  of  2  integers  (instead  of  3  integers  in  Part  1) 
// representing an edge. If there is an edge from node 1 to node 2, the data is: 1 2.  A zero for the 
// first  integer  signifies  the  end  of  the  data  for  that  one  graph.    In  the  file,  all  the  edges  for  the  1st 
// node  will  be  listed  first,  then  all  the  edges  for  the  2nd  node,  etc.  Take  them  as  they  come,  no 
// sorting.
// -------------------------------------------------------------------------------------------------------------------- 
// Notes on specifications, special algorithms, and assumptions.  
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
    static int const MAXNODES = 101; 
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