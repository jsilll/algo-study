#include <iostream>

#include "graph.h"

using namespace std;

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

int main(int argc, char const *argv[])
{
    Graph g(10);
    g.addEdge(0, 9);
    g.addEdge(0, 8);
    g.addEdge(0, 7);
    g.addEdge(0, 6);
    g.printGraph();
    cout << "Transposed graph" << endl;
    g.getTranspose().printGraph();
    return 0;
}
