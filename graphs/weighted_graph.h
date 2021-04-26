#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
using namespace std;

#include "../array_utils.h"

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

class W_Graph
{
    int V;
    vector<Edge> *adj;

public:
    W_Graph(int V);
    ~W_Graph();

    // Basic Operations
    void addEdge(int u, int v, int weight);
    vector<Edge> getAdjacent(int v);
    int **buildAdjMatrix();
    int **buildPIMatrix();
    void printGraph();

    // Algorithms
    W_Graph getTranspose();
    vector<int> topologicalSort();
    void dijkstra(int s, int *d, int *pi);
    bool bellmanFord(int s, int *d, int *pi);
    void orderedRelax(int s, vector<int> order);
    void extendShortestPaths(int **D, int **PI);
    void shortestPaths();
    void floydWarshall();
    void johnson();
};

W_Graph::W_Graph(int V)
{
    this->V = V;
    adj = new vector<Edge>[V];
}

W_Graph::~W_Graph()
{
    delete[] adj;
}

void W_Graph::addEdge(int u, int v, int weight)
{
    Edge edge(v, weight);
    adj[u].push_back(edge);
}

vector<Edge> W_Graph::getAdjacent(int v)
{
    return adj[v];
}

int **W_Graph::buildAdjMatrix()
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
    for (int i = 0; i < V; i++)
    {
        for (vector<Edge>::iterator itr = adj[i].begin(); itr != adj[i].end(); ++itr)
        {
            M[i][itr->getV()] = itr->getWeight();
        }
    }

    return M;
}

int **W_Graph::buildPIMatrix()
{
    int **PI = new int *[V];
    for (int u = 0; u < V; u++)
    {
        PI[u] = new int[V];
        for (int j = 0; j < V; j++)
        {
            PI[u][j] = -1;
        }
    }

    return PI;
}

void W_Graph::printGraph()
{
    printMatrix(this->buildAdjMatrix(), V - 1, V - 1);
}