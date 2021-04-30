#ifndef GRAPG_H
#define GRAPG_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

#include "../../array_utils.h"

using namespace std;

class Edge
{
    int u;
    int v;
    int w;

public:
    Edge(int _u, int _v, int _w)
    {
        u = _u;
        v = _v;
        w = _w;
    }
    int getU() { return u; }
    int getV() { return v; }
    int getW() { return w; }
};

class Graph
{
    int V;
    vector<Edge> edges;
    vector<int> *adj;

public:
    Graph(int V);
    ~Graph();

    // Basic Operations
    void addEdge(int v, int u, int w);
    int getV();
    int getE();
    vector<int> getAdjacent(int v);
    int **buildAdjMatrix();
    void printGraph();

    // Prim
    void prim(int s, int *d, int *pi);
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

void Graph::addEdge(int u, int v, int w)
{
    edges.push_back(Edge(u, v, w));
    adj[u].push_back(edges.size() - 1);
    adj[v].push_back(edges.size() - 1);
}

int Graph::getV()
{
    return V;
}

int Graph::getE()
{
    return edges.size();
}

vector<int> Graph::getAdjacent(int v)
{
    return this->adj[v];
}

int **Graph::buildAdjMatrix()
{
    int **M = new int *[V];

    // Setting up the matrix
    for (int i = 0; i < V; i++)
    {
        M[i] = new int[V];
        for (int j = 0; j < V; j++)
        {
            M[i][j] = INT_MAX;
        }
    }

    // Filling with weight values
    for (vector<Edge>::iterator itr = edges.begin(); itr != edges.end(); ++itr)
    {
        M[itr->getU()][itr->getV()] = itr->getW();
        M[itr->getV()][itr->getU()] = itr->getW();
    }

    return M;
}

void Graph::printGraph()
{
    printMatrix(this->buildAdjMatrix(), V - 1, V - 1);
}

#endif