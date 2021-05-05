#include <iostream>
#include <queue>

#include "../../array_utils.h"
#include "../../vector_utils.h"
#include "../graph.h"

using namespace std;

// Perform a DFS on the graph following an order
vector<int> Graph::orderedDFS(int *order)
{
    int current_time = 0;
    vector<int> times(V, -1);
    vector<int> pi(V, -1);

    for (int u = 0; u < V; u++)
    {
        if (times[order[u]] == -1)
        {
            dfsUtil(order[u], &pi, &times, &current_time);
        }
        current_time++;
    }
    return pi;
}

void Graph::kosarajuSharir()
{
    int *top_order = this->topologicalSort();
    printVector(this->getTranspose().orderedDFS(top_order));
}

int main(int argc, char const *argv[])
{
    Graph g(8);
    g.addEdge(0, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 3);
    g.addEdge(5, 6);
    g.addEdge(6, 1);
    g.addEdge(6, 7);
    g.addEdge(7, 2);
    g.addEdge(2, 1);
    g.addEdge(2, 6);
    cout << "DF Tree" << endl;
    g.kosarajuSharir();
    return 0;
}