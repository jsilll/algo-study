#include <iostream>
#include "../../weighted_graph.h"
#include "../../../array_utils.h"
using namespace std;

typedef pair<int, int> priorityPair;

// Todos os arcos devem ter pesos positivos
// Greedy Algorithm
// Os caminhos mais curtos respetiam a sub-estrutura ótima

void Graph::dijkstra(int s)
{
    // Initialize Single Source
    int *d = new int[V];
    int *pi = new int[V];

    for (int v = 0; v < V; v++)
    {
        d[v] = INT_MAX;
        pi[v] = -1;
    }

    d[s] = 0;

    priority_queue<priorityPair, vector<priorityPair>, greater<priorityPair>> pq;
    pq.push(make_pair(0, s));

    while (!pq.empty())
    {
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();

        for (int v = 0; v < V; v++)
        {
            if (adj[u][v] >= 0) // Make sure there's an edge
            {
                // Relax operation, its being applied more than once for every edge and it shouldnt
                if (d[v] > d[u] + adj[u][v])
                {
                    d[v] = d[u] + adj[u][v];
                    pi[v] = u;
                    pq.push(make_pair(d[v], v)); // Now we must update all the paths that use this one (sub-optimal structure)
                }
            }
        }
    }
    cout << "Distances Array" << endl;
    printArray(d, V - 1);
    cout << "Parents Array" << endl;
    printArray(pi, V - 1);
}

int main(int argc, char const *argv[])
{
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 2, 6);
    g.addEdge(4, 1, 3);
    g.addEdge(4, 2, 9);
    g.addEdge(4, 3, 2);
    g.dijkstra(0); // O((V+E) * log(V)), not really
    // g.printGraph(); debugging
    return 0;
}