#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>

#include "weighted_graph.h"

using namespace std;

class F_Edge
{
private:
    int v;
    int c;
    int f;

public:
    F_Edge(int _v, int _c, int _f = 0)
    {
        v = _v;
        c = _c;
        f = _f;
    }

    int getV() { return v; }
    int getCapacity() { return c; }
    int getFlow() { return this->f; }
    int getResidualCapacity()
    {
        return c - f;
    }

    void setFlow(int _f)
    {
        f = _f;
    }
};

class F_Graph
{
private:
    int V;
    vector<F_Edge> *adj;

public:
    F_Graph(int V);
    ~F_Graph();

    // Basic Operations
    void addEdge(int u, int v, int capacity);
    vector<F_Edge> getAdjacent(int v);
    void printGraph();

    // Algorithms
    F_Graph getTranspose();
    vector<int> topologicalSort();
    W_Graph buildResidualNetwork();
    int edmondsKarp(int s, int t);
};

F_Graph::F_Graph(int V)
{
    this->V = V;
    adj = new vector<F_Edge>[V];
}

F_Graph::~F_Graph()
{
    delete[] adj;
}

void F_Graph::addEdge(int u, int v, int capacity)
{
    adj[u].push_back(F_Edge(v, capacity));
}

vector<F_Edge> F_Graph::getAdjacent(int v)
{
    return adj[v];
}

void F_Graph::printGraph()
{
    cout << "(v, c, f)" << endl;
    for (int u = 0; u < V; u++)
    {
        cout << u << " : ";
        for (vector<F_Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            cout << "(" << itr->getV() << ", " << itr->getFlow() << "/" << itr->getCapacity() << "), ";
        }
        cout << endl;
    }
}