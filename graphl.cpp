//--------------------------  class GraphL.h  ---------------------------------
//  
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
// node reading from a data file
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