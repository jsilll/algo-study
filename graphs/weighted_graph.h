#include <iostream>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

#include "../array_utils.h"

class Edge
{
    int u;
    int v;
    int weight;

public:
    Edge(int _u, int _v, int _w)
    {
        u = _u;
        v = _v;
        weight = _w;
    }
    int getU() { return u; }
    int getV() { return v; }
    int getW() { return weight; }
};

class W_Graph
{
    int V;
    int E;
    vector<Edge> *adj;

public:
    W_Graph(int V);
    ~W_Graph();

    // Basic Operations
    void addEdge(int u, int v, int weight);
    void addEdgeDouble(int u, int v, int weight);
    vector<Edge> getAdjacent(int v);
    int **buildAdjMatrix();
    int **buildPIMatrix();
    void printGraph();

    // General Purpose Algorithms
    W_Graph getTranspose();
    int *topologicalSort();

    // Searches
    void bfs(int s, int t, vector<int> *d, vector<int> *pi);

    // SSSP
    bool bellmanFord(int s, int *d, int *pi);
    void orderedRelax(int s, vector<int> order);
    void dijkstra(int s, int *d, int *pi);

    // APSP
    void floydWarshall();
    void extendShortestPaths(int **D, int **PI);
    void shortestPaths();
    void johnson();

    // MST
    void kruskal();
    void prim(int s, int *d, int *pi);
};

W_Graph::W_Graph(int V)
{
    this->V = V;
    this->E = 0;
    adj = new vector<Edge>[V];
}

W_Graph::~W_Graph()
{
    delete[] adj;
}

void W_Graph::addEdge(int u, int v, int weight)
{
    adj[u].push_back(Edge(u, v, weight));
    E++;
}

void W_Graph::addEdgeDouble(int u, int v, int weight)
{
    adj[u].push_back(Edge(u, v, weight));
    adj[v].push_back(Edge(v, u, weight));
    E++;
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
            M[i][itr->getV()] = itr->getW();
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

W_Graph W_Graph::getTranspose()
{
    W_Graph gt(V);

    for (int i = 0; i < V; i++)
    {
        for (vector<Edge>::iterator itr = adj[i].begin(); itr != adj[i].end(); ++itr)
        {
            gt.addEdge(itr->getV(), i, itr->getW());
        }
    }

    return gt;
}

int *W_Graph::topologicalSort()
{
    int current_time = 0;
    vector<int> times(V, -1);
    vector<int> pi(V, -1);
    this->dfs(s, &pi, &times, &current_time);

    int *order = new int[V];
    for (int u = 0; u < V; u++)
    {
        order[V - times[u]] = u;
    }
    return order;
}

// modified version of bfs that finishes when destination (t) is reached
void W_Graph::bfs(int s, int t, vector<int> *d, vector<int> *pi)
{
    vector<bool> visited(V, false); // -1 white 0 grey 1 black
    queue<int> q;                   // priority queue

    visited[s] = true;
    (*d)[s] = 0;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (vector<Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            int v = itr->getV();
            if (visited[v] == false)
            {
                visited[v] = true;
                q.push(v);
                (*d)[v] = (*d)[u] + 1;
                (*pi)[v] = u;

                if (v == t)
                {
                    return;
                }
            }
        }
    }
}