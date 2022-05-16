//--------------------------  class GraphM.h  ---------------------------------
// Mohammad Zahid CSS343
// 5/10/2022
// 2/15/2022
//--------------------------------------------------------------------------------------------------------------------
// Purpose -This  project  is  to  implement  Dijkstra's  shortest  path  algorithm.  Your  code  should  be  able  to 
// read  a  data  file  consisting  of  many  lines  (an  example  file  called  data31.txt  will  be  given, 
// explained below) and will be able to find the lowest cost paths (findShortestPath function) and 
// display  the  cost  and  path  from  every  node  to  every  other  node  (displayAll  function).    Another 
// display routine (display function) will output one path in detail. 
//---------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.  
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