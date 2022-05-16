//--------------------------  class GraphL.cpp  ---------------------------------
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
#include "graphl.h"
//#include "string.h"
#include "limits.h"
#include <iomanip>

// --------------------- GraphL() -----------------------------------------
// Default constructor
// --------------------------------------------------------------
GraphL::GraphL()
{
    size = 0;
    for(int i = 0; i < MAXNODES; i++) {
        node_array[i].edgeHead = NULL;
        node_array[i].data = NULL;
        node_array[i].visited = false;
    }
}
// --------------------- ~GraphL() -----------------------------------------
// Destructor
// --------------------------------------------------------------
GraphL::~GraphL()
{
    makeEmpty();
}
// --------------------- makeEmpty() -----------------------------------------
// Helper function for Destructor
// --------------------------------------------------------------
void GraphL::makeEmpty()
{
    for(int i = 1; i <= size; i++) {
        node_array[i].visited = false;
        delete node_array[i].data;
        node_array[i].data = NULL;
        if(node_array[i].edgeHead != NULL) {
            EdgeNode* target = node_array[i].edgeHead;
            while(target != NULL) {
                node_array[i].edgeHead = node_array[i].edgeHead -> nextEdge;
                delete target;
                target = NULL;
                target = node_array[i].edgeHead;
            }
        }
    }
}

// --------------------- buildGraph() -----------------------------------------
// Builds up graph node information and adjacency list of edges between each
// --------------------------------------------------------------
void GraphL::buildGraph(ifstream& inFile)
{
    int from, to;
    inFile >> size;
    if(size > 0) {
        string str;
        getline(inFile, str);
        for(int i = 1; i <= size; i++) {
            node_array[i].data = new NodeData();
            node_array[i].data -> setData(inFile);
        }
        while(inFile >> from >> to) {
            if(from == 0) {
                break;
            }
            EdgeNode* node = new EdgeNode;
            node -> adjGraphNode = to;
            if(node_array[from].edgeHead == NULL) {
                node_array[from].edgeHead = node;
                node_array[from].edgeHead -> nextEdge = NULL;
            } else {
                node -> nextEdge = node_array[from].edgeHead;
                node_array[from].edgeHead = node;
            }
        }
    }
}
// --------------------- depthFirstSearch() -----------------------------------------
// Makes a depth-first search and displays each node in depth-first order
// --------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering: ";
    for(int i = 1; i <= size; i++) {
        if(!node_array[i].visited) {
            depthFirstSearchHelper(i);
        }
    }
    cout << "\n" << endl;
}

// --------------------- depthFirstSearchHelper() -----------------------------------------
// Helper function for depthFirstSearch()
// --------------------------------------------------------------
void GraphL::depthFirstSearchHelper(int v)
{
    cout << "  " << v;
    node_array[v].visited = true;
    EdgeNode* current = node_array[v].edgeHead;
    while(current != NULL) {
        if(!node_array[current -> adjGraphNode].visited) {
            depthFirstSearchHelper(current -> adjGraphNode);
        }
        current = current -> nextEdge;
    }
}

// --------------------- displayGraph() -----------------------------------------
// Displays each node information and edge in the graph
// --------------------------------------------------------------
void GraphL::displayGraph()
{
    cout << "Graph: " << endl;
    for(int i = 1; i <= size; i++) {
        cout << "Node" << i << "\t\t " << *node_array[i].data << endl;
        cout << endl;
        EdgeNode* current = node_array[i].edgeHead;
        while(current != NULL) {
            cout << "  " << "edge  " << i << "  " << current -> adjGraphNode << endl;
            current = current -> nextEdge;
        }
    }
    cout << endl;
}