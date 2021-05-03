#include <iostream>
#include <climits>
#include <vector>
#include <queue>

#include "../weighted_graph.h"

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

public:
    F_Graph(int V);
    ~F_Graph();

    // Basic Operations
    void addEdge(int u, int v, int capacity);
    vector<F_Edge> getAdjacent(int v);
    void printGraph();

    // Ford-Fulkerson
    F_Graph getTranspose();
    W_Graph buildResidualNetwork();
    int edmondsKarp(int s, int t);

    // Push Relabel
    void push(int u, int v, F_Edge *edge, int *e, int *h);
    void relabel(int u, int *h, vector<F_Edge *> *N);
    void pushRelabelInitialize(int s, int *e, int *h);
    bool discharge(int u, int *e, int *h, vector<F_Edge *> *N, vector<F_Edge *>::iterator *N_current);
    void pushRelabel(int s, int t);
    void relabelToFront(int s, int t);
};

F_Graph::F_Graph(int V)
{
    this->V = V;
    this->E = 0;
    adj = new vector<F_Edge>[V];
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