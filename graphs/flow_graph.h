#include <iostream>
#include <climits>
#include <vector>
#include <queue>

#include "weighted_graph.h"

using namespace std;

class F_Edge
{
private:
    int u;
    int v;
    int c;
    int f;

public:
    F_Edge(int _u, int _v, int _c, int _f = 0)
    {
        u = _u;
        v = _v;
        c = _c;
        f = _f;
    }

    int getU() { return u; }
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
    int E;
    vector<F_Edge> *adj;

    // Push Relabel Algorithms
    int *e, *h;
    vector<F_Edge *> *N;
    vector<F_Edge *>::iterator *N_current;

public:
    F_Graph(int V);
    ~F_Graph();

    // Basic Operations
    void addEdge(int u, int v, int capacity);
    vector<F_Edge> getAdjacent(int v);
    void printGraph();

    // Ford-Fulkerson
    F_Graph getTranspose();
    vector<int> topologicalSort();
    W_Graph buildResidualNetwork();
    int edmondsKarp(int s, int t);

    // Push Relabel
    void push(int u, int v, F_Edge *edge);
    void relabel(int u);
    void pushRelabelInitialize(int s);
    void pushRelabel(int s, int t);
    void discharge(int u);
    void relabelToFront(int s, int t);
};

F_Graph::F_Graph(int V)
{
    this->V = V;
    this->E = 0;
    adj = new vector<F_Edge>[V];

    // Needed for push_relabel algos
    e = new int[V];
    h = new int[V];
    N = new vector<F_Edge *>[V];
    N_current = new vector<F_Edge *>::iterator[V];
}

F_Graph::~F_Graph()
{
    delete[] adj;
}

void F_Graph::addEdge(int u, int v, int capacity)
{
    adj[u].push_back(F_Edge(u, v, capacity));
    E++;
}

vector<F_Edge> F_Graph::getAdjacent(int v)
{
    return adj[v];
}

W_Graph F_Graph::buildResidualNetwork()
{
    W_Graph gf(V); // Construir a rede residual

    for (int u = 0; u < V; u++)
    {
        for (vector<F_Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            int v = itr->getV();
            int f = itr->getFlow();
            int rc = itr->getResidualCapacity();
            if (rc)
            {
                gf.addEdge(u, v, rc);
            }
            if (f)
            {
                gf.addEdge(v, u, f);
            }
        }
    }

    return gf;
}

void F_Graph::push(int u, int v, F_Edge *edge)
{

    // Forward Edge
    if (edge->getV() == v)
    {
        int new_flow = min(e[u], edge->getResidualCapacity());
        edge->setFlow(edge->getFlow() + new_flow);
        e[u] = e[u] - new_flow;
        e[v] = e[v] + new_flow;
    }

    // Backwards Edge
    else if (edge->getV() == u)
    {
        int new_flow = min(e[u], edge->getFlow());
        edge->setFlow(edge->getFlow() - new_flow);
        e[u] = e[u] - new_flow;
        e[v] = e[v] + new_flow;
    }
}

void F_Graph::relabel(int u)
{
    int min_height = INT_MAX;
    // Percorrer todos os arcos de adjacencia na rede residual
    // Forward existe de ainda há residualCapacity
    // Backwards existe se há flow
    for (int v = 0; v < N[u].size(); v++)
    {
        F_Edge *edge = N[u][v];

        // Forward Edge case
        if (edge->getV() != u)
        {
            if (edge->getResidualCapacity())
            {
                min_height = min(min_height, h[edge->getV()]);
            }
        }

        // If its not a forward edge it's a backwards one
        else if (edge->getFlow())
        {
            min_height = min(min_height, h[edge->getU()]);
        }
    }

    h[u] = 1 + min_height;
}

void F_Graph::pushRelabelInitialize(int s)
{
    // Initialize
    for (int u = 0; u < V; u++)
    {
        for (vector<F_Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            itr->setFlow(0);
        }
        e[u] = 0;
        h[u] = 0;
    }

    for (vector<F_Edge>::iterator itr = adj[s].begin(); itr != adj[s].end(); ++itr)
    {
        e[s] = e[s] - itr->getCapacity();
        e[itr->getV()] = itr->getCapacity();
        itr->setFlow(itr->getCapacity());
    }

    h[s] = V;
}

void F_Graph::printGraph()
{
    cout << "(vertex, flow, capacity)" << endl;
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