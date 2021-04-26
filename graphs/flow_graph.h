#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
using namespace std;

class Edge
{
    int v;
    int c;
    int f;

public:
    Edge(int _v, int _c)
    {
        v = _v;
        c = _c;
        f = 0;
    }

    int getV() { return v; }
    int getCapacity() { return c; }
    int getFlow() { return f; }
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
    int V;
    vector<Edge> *adj;

public:
    F_Graph(int V);
    ~F_Graph();

    // Basic Operations
    void addEdge(int u, int v, int weight);
    vector<Edge> getAdjacent(int v);
    void printGraph();

    // Algorithms
    F_Graph getTranspose();
    vector<int> topologicalSort();
};

F_Graph::F_Graph(int V)
{
    this->V = V;
    adj = new vector<Edge>[V];
}

F_Graph::~F_Graph()
{
    delete[] adj;
}

void F_Graph::addEdge(int u, int v, int weight)
{
    Edge edge(v, weight);
    adj[u].push_back(edge);
}

vector<Edge> F_Graph::getAdjacent(int v)
{
    return adj[v];
}

void F_Graph::printGraph()
{
    cout << "(v, c, f)" << endl;
    for (int u = 0; u < V; u++)
    {
        cout << u << " : ";
        for (vector<Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            cout << "(" << itr->getV() << ", " << itr->getFlow() << "/" << itr->getCapacity() << "), ";
        }
        cout << endl;
    }
}