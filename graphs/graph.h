#ifndef GRAPG_H
#define GRAPG_H

#include <iostream>
#include <vector>

using namespace std;

class Graph
{
    int V;
    int E;
    vector<int> *adj;

public:
    Graph(int V);
    ~Graph();

    // Basic Operations
    void addEdge(int v, int u);
    int getV();
    int getE();
    vector<int> getAdjacent(int v);
    void printGraph();

    // Algorithms
    vector<int> topologicalSort();
    Graph getTranspose();
    void DFS(int v, vector<int> *pi, vector<int> *times, int *current_time);
    vector<int> orderedDFS(vector<int> order);
    vector<int> getDFSClosingOrder();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<int>[V];
}

Graph::~Graph()
{
    delete[] adj;
}

void Graph::addEdge(int v, int u)
{
    adj[v].push_back(u);
    E++;
}

int Graph::getV()
{
    return V;
}

int Graph::getE()
{
    return E;
}

vector<int> Graph::getAdjacent(int v)
{
    return this->adj[v];
}

void Graph::printGraph()
{
    for (int v = 0; v < V; v++)
    {
        cout << v << " => ";
        for (vector<int>::iterator j = adj[v].begin(); j != adj[v].end(); ++j)
        {
            cout << *j << ", ";
        }
        cout << endl;
    }
}

#endif