#include <iostream>
#include "../../weighted_graph.h"
#include "../../../vector_utils.h"
#include "../../../array_utils.h"

using namespace std;

// Se relaxar todas as arestas de um caminho mais curto, por ordem
// entao, no final, a estimativa para a distancia, para cada vertice,
// corresponde à distância mínima

// Se o grafo é um DAG, qualquer caminho mais curto do
// grafo é um sub-sequência da ordenação topológica

void Graph::orderedRelax(int s, vector<int> order)
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

    // Actual algorithm
    for (vector<int>::iterator u = order.begin(); u != order.end(); ++u)
    {
        for (int v = 0; v < V; v++)
        {
            // Relax operation
            if (adj[*u][v] != INT_MAX && d[v] > d[*u] + adj[*u][v])
            {
                d[v] = d[*u] + adj[*u][v];
                pi[v] = *u;
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
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(3, 4, -1);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, -2);
    g.orderedRelax(0, g.topologicalSort());
    return 0;
}
