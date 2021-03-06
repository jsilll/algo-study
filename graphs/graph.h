#ifndef GRAPG_H
#define GRAPG_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

#include "../vector_utils.h"

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
    void addEdgeDouble(int v, int u);
    int getV();
    int getE();
    vector<int> getAdjacent(int v);
    void printGraph();

    // General Purpose Algos
    vector<int> topologicalSortKhan();
    int *topologicalSort();
    Graph getTranspose();

    // Searches
    void dfsUtil(int v, vector<int> *pi, vector<int> *times, int *current_time);
    void dfs(vector<int> *pi, vector<int> *times, int *current_time);
    void bfs(int s, vector<int> *d, vector<int> *pi);

    // SCCS
    void tarjanUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]);
    void tarjan(int s);
    vector<int> orderedDFS(int *order);
    void kosarajuSharir();
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

void Graph::addEdgeDouble(int v, int u)
{
    adj[v].push_back(u);
    adj[u].push_back(v);
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

vector<int> Graph::topologicalSortKhan()
{
    vector<int> in_degree(V, 0);

    for (int u = 0; u < V; u++)
    {
        for (vector<int>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            in_degree[*itr]++;
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

        for (vector<int>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            if (--in_degree[*itr] == 0)
                q.push(*itr);
        }
        cnt++;
    }

    return top_order;
}

int *Graph::topologicalSort()
{
    int current_time = 0;
    vector<int> times(V, -1);
    vector<int> pi(V, -1);
    this->dfs(&pi, &times, &current_time);
    int *order = new int[V];
    for (int u = 0; u < V; u++)
    {
        order[V - 1 - times[u]] = u;
    }
    return order;
}

Graph Graph::getTranspose()
{
    Graph u(V);

    for (int i = 0; i < V; i++)
    {
        for (vector<int>::iterator itr = adj[i].begin(); itr != adj[i].end(); ++itr)
        {
            u.addEdge(*itr, i);
        }
    }

    return u;
}

void Graph::dfsUtil(int v, vector<int> *pi, vector<int> *times, int *current_time)
{
    (*times)[v] = 0;
    for (vector<int>::iterator itr = adj[v].begin(); itr != adj[v].end(); ++itr)
    {
        if ((*times)[*itr] == -1)
        {
            (*pi)[*itr] = v;
            dfsUtil(*itr, pi, times, current_time);
        }
    }
    (*times)[v] = (*current_time)++;
}

void Graph::dfs(vector<int> *pi, vector<int> *times, int *current_time)
{
    for (int u = 0; u < V; u++)
    {
        if ((*times)[u] == -1)
        {
            dfsUtil(u, pi, times, current_time);
        }
        (*current_time)++;
    }
}

void Graph::bfs(int s, vector<int> *d, vector<int> *pi)
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

        for (vector<int>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            int v = *itr;
            if (visited[v] == false)
            {
                visited[v] = true;
                q.push(v);
                (*d)[v] = (*d)[u] + 1;
                (*pi)[v] = u;
            }
        }
    }
}

#endif