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
    int getW() { return weight; }
};

class Graph
{
    int V;
    vector<Edge> *adj;

public:
    Graph(int V);
    ~Graph();

    // Basic Operations
    void addEdge(int u, int v, int weight);
    vector<Edge> getAdjacent(int v);
    int **buildAdjMatrix();
    int **buildPIMatrix();
    void printGraph();

    // Algorithms
    Graph getTranspose();
    vector<int> topologicalSort();
    void dijkstra(int s, int *d, int *pi);
    bool bellmanFord(int s, int *d, int *pi);
    void orderedRelax(int s, vector<int> order);
    void extendShortestPaths(int **D, int **PI);
    void shortestPaths();
    void floydWarshall();
    void johnson();
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

void Graph::addEdge(int u, int v, int weight)
{
    Edge edge(v, weight);
    adj[u].push_back(edge);
}

vector<Edge> Graph::getAdjacent(int v)
{
    return adj[v];
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
    for (int i = 0; i < V; i++)
    {
        for (vector<Edge>::iterator itr = adj[i].begin(); itr != adj[i].end(); ++itr)
        {
            M[i][itr->getV()] = itr->getW();
        }
    }

    return M;
}

int **Graph::buildPIMatrix()
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

void Graph::printGraph()
{
    printMatrix(this->buildAdjMatrix(), V - 1, V - 1);
}

Graph Graph::getTranspose()
{
    Graph gt(V);

    for (int i = 0; i < V; i++)
    {
        for (vector<Edge>::iterator itr = adj[i].begin(); itr != adj[i].end(); ++itr)
        {
            gt.addEdge(itr->getV(), i, itr->getW());
        }
    }

    return gt;
}

vector<int> Graph::topologicalSort()
{
    vector<int> in_degree(V, 0);

    for (int u = 0; u < V; u++)
    {
        for (vector<Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            in_degree[itr->getV()]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    int cnt = 0;

    vector<int> top_order;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        for (int v = 0; v < V; v++)
        {
            if (--in_degree[v] == 0)
                q.push(v);
        }
        cnt++;
    }

    return top_order;
}
