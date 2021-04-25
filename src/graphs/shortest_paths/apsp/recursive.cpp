#include <iostream>
#include "../../weighted_graph.h"
#include "../../../array_utils.h"

using namespace std;

// D Matrix
// PI Matrix

// Solucao recursiva (m denota máximo de m arcos no caminho)
// dij (m) = min(dij(m-1), min(dik(m-1) + wkj)), 0 <= k < V

void Graph::extendShortestPaths(int **D, int **PI)
{

    int D_new[V][V];
    int PI_new[V][V];

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            for (int k = 0; k < V; k++)
            {
                D_new[i][j] = D[i][j];
                PI_new[i][j] = PI[i][j];
                if (adj[i][j] != INT_MAX && D_new[i][j] < D[i][k] + adj[k][j])
                {
                    D_new[i][j] = D[i][k] + adj[k][j];
                    PI_new[i][j] = k;
                }
            }
        }
    }

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            D[i][j] = D_new[i][j];
            PI[i][j] = PI_new[i][j];
        }
    }
}

void Graph::shortestPaths()
{
    // Calculate number of edges in the graph

    int **D = new int *[V];
    int **PI = new int *[V];

    int edges = 0;
    for (int i = 0; i < V; i++)
    {
        D[i] = new int[V];
        PI[i] = new int[V];
        for (int j = 0; j < V; j++)
        {
            D[i][j] = adj[i][j];
            PI[i][j] = -1;

            if (adj[i][j] != INT_MAX)
            {
                edges++;
            }
        }
    }

    for (int i = 0; i < edges; i++)
    {
        extendShortestPaths(D, PI);
    }

    cout << "D Matrix" << endl;
    printMatrix(D, V - 1, V - 1);
    cout << "PI Matrix" << endl;
    printMatrix(PI, V - 1, V - 1);
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

    int number_edges = 9;
    int D[5][5];
    int PI[5][5];

    g.shortestPaths();
    return 0;
}
