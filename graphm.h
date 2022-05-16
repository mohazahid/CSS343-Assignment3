//--------------------------  class GraphM.h  ---------------------------------
//  
//---------------------------------------------------------------------------
#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <stdio.h>

using namespace std;
class GraphM
{
public:
    GraphM();
    ~GraphM(); 
    void buildGraph(ifstream &);
    void findShortestPath();
    void insertEdge(int from, int to, int dist);
    void removeEdge(int from, int to);
    void display(int from, int to);
    void displayAll();
private:
    static int const MAXNODES = 101;
    struct TableType
    {
        bool visited; // whether node has been visited
        int dist;     // shortest distance from source known so far
        int path;     // previous node in path of min dist
    };
    NodeData data[MAXNODES];         
    int C[MAXNODES][MAXNODES];       
    int size;                        
    TableType T[MAXNODES][MAXNODES]; 
    void makeEmpty();   
    void findD(int from, int to); // description
    void findP(int from, int to); //path
};
#endif // GRAPHM.H