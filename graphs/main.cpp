#include <iostream>
#include <queue>
#include <list>
#include "graph.h"

vector<int> topologicalSort(Graph *g)
{
    int V = g->getV();
    vector<int> in_degree(V, 0);

    for (int u = 0; u < V; u++)
    {
        vector<int> adj = g->getAdjacent(u);
        for (vector<int>::iterator itr = adj.begin(); itr != adj.end(); ++itr)
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

        vector<int> adj = g->getAdjacent(u);
        for (vector<int>::iterator itr = adj.begin(); itr != adj.end(); ++itr)
        {
            if (--in_degree[*itr] == 0)
                q.push(*itr);
        }
        cnt++;
    }

    return top_order;
}

int main(int argc, char const *argv[])
{
    Graph g(10);
    g.addEdge(0, 9);
    g.addEdge(0, 8);
    g.addEdge(0, 7);
    g.addEdge(0, 6);
    vector<int> top_order = topologicalSort(&g);
    cout << "Topological Order" << endl;
    for (vector<int>::iterator itr = top_order.begin(); itr != top_order.end(); itr++)
    {
        cout << *itr << ", ";
    }
    cout << endl;
    return 0;
}
