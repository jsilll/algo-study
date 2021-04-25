#ifndef WEIGHTED_GRAPG_H
#define WEIGHTED_GRAPG_H

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    int **adj;
    int V;

public:
    //Basic Operations
    Graph(int V);
    ~Graph();
    void addEdge(int i, int j, int w);
    Graph getTranspose();
    void printGraph();
    vector<int> topologicalSort();

    // Algos
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
    adj = new int *[V];
    for (int i = 0; i < V; i++)
    {
        adj[i] = new int[V];
        for (int j = 0; j < V; j++)
            adj[i][j] = INT_MAX;
    }
}

void Graph::addEdge(int i, int j, int w)
{
    adj[i][j] = w;
    // adj[j][i] = w; directed graph
}

Graph::~Graph()
{
    for (int i = 0; i < V; i++)
        delete[] adj[i];
    delete[] adj;
}

Graph Graph::getTranspose()
{
    Graph gt(V);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            gt.addEdge(j, i, adj[i][j]);
        }
    }

    return gt;
}

void Graph::printGraph()
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (adj[i][j] != INT_MAX)
            {
                cout << adj[i][j] << " ";
            }
            else
            {
                cout << "i ";
            }
        }
        cout << "\n";
    }
}

vector<int> Graph::topologicalSort()
{
    vector<int> in_degree(V, 0);

    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (adj[u][v] != INT_MAX)
            {
                in_degree[v]++;
            }
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

#endif