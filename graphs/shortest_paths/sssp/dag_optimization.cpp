// This file has a bug somewhere
#include <iostream>
#include "../../../vector_utils.h"
#include "../../../array_utils.h"
#include "../../weighted_graph.h"

using namespace std;

// Se relaxar todas as arestas de um caminho mais curto, por ordem top.<
// entao, no final, a estimativa para a distancia, para cada vertice,
// corresponde à distância mínima

// Se o grafo é um DAG, qualquer caminho mais curto do
// grafo é um sub-sequência da ordenação topológica

void W_Graph::orderedRelax(int s, vector<int> order)
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
    for (vector<int>::iterator itr1 = order.begin(); itr1 != order.end(); ++itr1)
    {
        int u = *itr1;
        for (vector<Edge>::iterator itr2 = adj[u].begin(); itr2 != adj[u].end(); ++itr2)
        {
            int v = itr2->getV();
            int w_uv = itr2->getW();

            // Relax Operation
            if (d[v] > d[u] + w_uv)
            {
                d[v] = d[u] + w_uv;
                pi[v] = u;
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
    W_Graph g(6);
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
