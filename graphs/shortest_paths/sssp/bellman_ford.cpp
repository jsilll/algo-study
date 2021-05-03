#include <iostream>
#include "../../../array_utils.h"
#include "../../weighted_graph.h"
using namespace std;

// Permite pesos negativos e identifica a existência de ciclos negativos
// Baseado em sequência da passos de relaxação
// Apenas requer manutenção da estimativa associada a cada vértice

bool W_Graph::bellmanFord(int s, int *d, int *pi)
{

    int **D = this->buildAdjMatrix();

    // Initialize Single Source
    for (int v = 0; v < V; v++)
    {
        d[v] = INT_MAX;
        pi[v] = -1;
    }

    d[s] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        for (int u = 0; u < V; u++)
        {
            for (int v = 0; v < V; v++)
            {
                // Relax operation
                if (D[u][v] != INT_MAX && d[u] != INT_MAX && d[v] > d[u] + D[u][v])
                {
                    d[v] = d[u] + D[u][v];
                    pi[v] = u;
                }
            }
        }
    }

    // Check for negative loops
    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (D[u][v] != INT_MAX && d[v] > d[u] + D[u][v])
            {
                return false;
            }
        }
    }

    cout << "Distances Array" << endl;
    printArray(d, V - 1);
    cout << "Parents Array" << endl;
    printArray(pi, V - 1);

    return true;
}

int main(int argc, char const *argv[])
{
    W_Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 2, 6);
    g.addEdge(4, 1, 3);
    g.addEdge(4, 2, 9);
    g.addEdge(4, 3, 2);

    int *d = new int[5];
    int *pi = new int[5];

    g.bellmanFord(0, d, pi); // supostamente O(V^3)
    return 0;
}