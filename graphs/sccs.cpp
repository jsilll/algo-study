#include <iostream>
#include <queue>

#include "graph.h"
#include "vector_utils.h"

using namespace std;

// Transpor o grafo
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

void Graph::DFS(int v, vector<int> *pi, vector<int> *times, int *current_time)
{
    for (vector<int>::iterator itr = adj[v].begin(); itr != adj[v].end(); ++itr)
    {
        if (times[0][*itr] == -1)
        {
            pi[0][*itr] = v;
            DFS(*itr, pi, times, current_time);
        }
    }
    times[0][v] = ++(*current_time);
}

vector<int> Graph::getDFSClosingOrder()
{
    int current_time = 0;
    vector<int> times(V, -1);
    vector<int> pi(V, -1);

    for (int i = 0; i < V; i++)
    {
        if (times[i] == -1)
        {
            DFS(i, &pi, &times, &current_time);
        }
    }

    vector<int> closing_order(V, 0);

    for (int i = 0; i < V; i++)
    {
        closing_order[V - times[i]] = i;
    }

    return closing_order;
}

vector<int> Graph::orderedDFS(vector<int> order)
{
    int current_time = 0;
    vector<int> times(V, -1);
    vector<int> pi(V, -1);

    for (vector<int>::iterator itr = order.begin(); itr != order.end(); ++itr)
    {
        if (times[*itr] == -1)
        {
            DFS(*itr, &pi, &times, &current_time);
        }
    }

    return pi;
}

int main(int argc, char const *argv[])
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 0);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    // Graph u = g.getTranspose();
    // g.printGraph();
    // cout << endl;
    // u.printGraph();

    vector<int> pi = g.getTranspose().orderedDFS(g.getDFSClosingOrder());
    printVector(pi);
    return 0;
}