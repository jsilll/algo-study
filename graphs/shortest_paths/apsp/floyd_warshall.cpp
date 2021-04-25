#include <iostream>
#include "../../weighted_graph.h"
#include "../../../array_utils.h"

using namespace std;

// dij(k) = wij, se k = 0
// dij(k) = min(dij(k-1), dik(k-1) + dkj(k-1))

void Graph::floydWarshall()
{
    int **D = new int *[V];
    int i, j, k;

    for (i = 0; i < V; i++)
    {
        D[i] = new int[V];
        for (j = 0; j < V; j++)
            D[i][j] = adj[i][j];
    }

    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (D[i][j] > D[i][k] + D[k][j] && D[i][k] != INT_MAX && D[k][j] != INT_MAX)
                    D[i][j] = D[i][k] + D[k][j];
            }
        }
    }

    printMatrix(D, V - 1, V - 1);
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
    g.floydWarshall(); // O(n^3)
    // Se (i,j) != i entao pertence ao fecho transitivo do grafo
    // O fecho transitivo de um grafo é o conjunto de vértices (i,j)
    // tal que existe um caminho de i para j
    return 0;
}
