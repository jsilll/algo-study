#ifndef GRAPG_H
#define GRAPG_H

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Edge
{
    int v;
    int weight;

public:
    Edge(int _v, int _w)
    {
        v = _v;
        weight = _w;
    }
    int getV() { return v; }
    int getWeight() { return weight; }
};

class Graph
{
    int V;
    int E;
    vector<Edge> *adj;

    // Algo helper functions
    void initializeSingleSource(int s);
    void relax(int u, int v, int w);

public:
    Graph(int V);
    ~Graph();

    // Basic Operations
    void addEdge(int v, int u, int weight);
    int getV();
    int getE();
    vector<Edge> getAdjacent(int v);
    void printGraph();

    // Algorithms
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<Edge>[V];
}

Graph::~Graph()
{
    delete[] adj;
}

void Graph::addEdge(int v, int u, int weight)
{
    adj[v].push_back(Edge(v, weight));
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

vector<Edge> Graph::getAdjacent(int v)
{
    return this->adj[v];
}

void Graph::initializeSingleSource(int s)
{
    int d[V] = {-1};
    int pi[V] = {0};
}

void Graph::relax(int u, int v, int w)
{
    int d[V] = {-1};
    int pi[V] = {0};

    if (d[v] > d[u] + adj[u])
}

void Graph::printGraph()
{
    for (int v = 0; v < V; v++)
    {
        cout << v << " => ";
        for (vector<Edge>::iterator j = adj[v].begin(); j != adj[v].end(); ++j)
        {
            cout << j->getV() << ", ";
        }
        cout << endl;
    }
}

#endif