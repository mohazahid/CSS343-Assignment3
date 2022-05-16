//--------------------------  class GraphM.cpp  ---------------------------------
//  
//---------------------------------------------------------------------------
#include "graphm.h"
#include <iomanip>
#include "limits.h"
using namespace std;
// --------------------- Default Constructor -----------------------------------------
// Constructs an empty table and initializes all values
// --------------------------------------------------------------
GraphM::GraphM() : data{}, size(0), T{}
{
    size = 0;
    for(int i = 0; i < MAXNODES; i++) {
        for(int j = 0; j < MAXNODES; j++) {
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
            C[i][j] = INT_MAX;
        }
    }
}
// --------------------- Default Constructor -----------------------------------------
// Destructor
// --------------------------------------------------------------
GraphM::~GraphM()
{
    makeEmpty();
}
// --------------------- buildGraph() -----------------------------------------
// Builds up graph node information and adjacency matrix of edges
// between each node reading from a file
// --------------------------------------------------------------
void GraphM::buildGraph(ifstream &infile)
{
    makeEmpty();
    int from, to, distance;
    infile >> size;
    if(size > 0) {
        string str;
        getline(infile, str);
        for(int i = 1; i <= size; i++) {
            data[i].setData(infile);
        }
        while(infile >> from >> to >> distance) {
            if(from == 0) {
                break;
            }
            insertEdge(from, to, distance);
        }
    }
}
// --------------------- findShortestPath() -----------------------------------------
// Finds the shortest path between every node to every other node
// in the graph using Dijkstra's algorithm
// --------------------------------------------------------------
void GraphM::findShortestPath()
{
 for(int source = 1; source <= size; source++) {
        T[source][source].dist = 0;
        for(int i = 1; i <=size; i++) {
            int v = -1;
            int minDist = INT_MAX;
            for(int j = 1; j <= size; j++) {
                if(T[source][j].dist <minDist && !T[source][j].visited) {
                    minDist = T[source][j].dist;
                    v = j;
                }
            }
            if(v == -1) {
                break;
            }
            T[source][v].visited = true;
            for(int w = 1; w <= size; w++) {
                if(C[v][w] < INT_MAX && !T[source][w].visited) {
                    if(T[source][v].dist + C[v][w] < T[source][w].dist) {
                        T[source][w].dist = T[source][v].dist + C[v][w];
                        T[source][w].path = v;
                    }
                }
            }
        }
    }
    for(int i = 1; i <= size; i++) {
        for(int j = 1; j <= size; j++) {
            T[i][j].visited = false;
        }
    }
}

// --------------------- insertEdge() -----------------------------------------
// Inserts an edge into a graph between 2 given nodes
// --------------------------------------------------------------
void GraphM::insertEdge(int from, int to, int dist)
{
    if(from > 0 && from <=size && to > 0 && to <= size) {
        C[from][to] = dist;
    }
}

// --------------------- removeEdge() -----------------------------------------
// Removes an edge between 2 given nodes
// --------------------------------------------------------------
void GraphM::removeEdge(int from, int to)
{
    if(from > 0 && from <= size && to > 0 && to <=size) {
        C[from][to] = INT_MAX;
    }
}

// --------------------- displayAll() -----------------------------------------
// Uses couts to demonstrate that the alogorithm works properly
// Uses helper function findPath()
// --------------------------------------------------------------

void GraphM::displayAll()
{
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node" << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;
    for(int i = 1; i <= size; i++) {
        cout << data[i] << endl;
        for(int j = 1; j <= size; j++) {
            if(i != j) {
                cout << setw(27) << i << setw(10) << j;
                if(T[i][j].dist < INT_MAX) {
                    cout << setw(12) << T[i][j].dist;
                } else {
                    cout << setw(12) << "----";
                }
                cout << setw(10);
                findP(i,j);
                cout << endl;
            }
        }
    }
    cout << endl;
}

// --------------------- display() -----------------------------------------
// Uses couts to display the shortest distance with path info between the
// fromNode to the toNode
// Uses helper function findPath()
// Uses helper function findData()
// --------------------------------------------------------------
void GraphM::display(int from, int to)
{
    if(from < 1 || from > size || to < 1 || to > size) {
        return;
    }
    cout << setw(7) << from << setw(7) << to;
    if(T[from][to].dist < INT_MAX) {
        cout << setw(12) << T[from][to].dist;
    } else {
        cout << setw(15) << "----";
    }
    cout << setw(15);
    findP(from, to);
    cout << endl;
    findD(from, to);
    cout << endl;
}

void GraphM::findD(int from, int to)
{
    int v = T[from][to].path;
    if(v != 0) {
        findD(from, v);
        cout << data[to] << endl;
    } else if (from == to) {
        cout << data[to] << endl;
    }
    cout << endl;
}

void GraphM::findP(int from, int to)
{
    int v = T[from][to].path;
    if(v != 0) {
        findP(from, v);
        cout << to << " ";
    } else if (from == to) {
        cout << to << " ";
    }
}

void GraphM::makeEmpty()
{
    size = 0;
    for(int i = 0; i < MAXNODES; i++) {
        for(int j = 0; j < MAXNODES; j++) {
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
            C[i][j] = INT_MAX;
        }
    }
}