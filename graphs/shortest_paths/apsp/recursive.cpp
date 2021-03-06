#include <iostream>
#include "../../../array_utils.h"
#include "../../weighted_graph.h"

using namespace std;

// D Matrix
// PI Matrix

// Solucao recursiva (m denota máximo de m arcos no caminho)
// dij (m) = min(dij(m-1), min(dik(m-1) + wkj)), 0 <= k < V

void W_Graph::extendShortestPaths(int **D, int **PI)
{
    static int **adj_matrix = this->buildAdjMatrix(); // Only called once
    int D_new[V][V];
    int PI_new[V][V];

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            D_new[i][j] = D[i][j];
            PI_new[i][j] = PI[i][j];

            for (int k = 0; k < V; k++)
            {
                if (adj_matrix[k][j] != INT_MAX && D[i][k] != INT_MAX && D_new[i][j] > D[i][k] + adj_matrix[k][j])
                {
                    D_new[i][j] = D[i][k] + adj_matrix[k][j];
                    PI_new[i][j] = k;
                }
            }
        }
    }

    // Copying final matrices for returning
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            D[i][j] = D_new[i][j];
            PI[i][j] = PI_new[i][j];
        }
    }
}

void W_Graph::shortestPaths()
{
    // Calculate number of edges in the graph
    int **D = this->buildAdjMatrix();
    int **PI = this->buildPIMatrix();

    int edges = 0;
    for (int u = 0; u < V; u++)
    {
        edges += adj[u].size();
    }

    for (int i = 0; i < edges; i++) // Each iteration we can use one more vertex/edge for the path
    {
        extendShortestPaths(D, PI);
    }

    fillMatrixDiag(D, V - 1, 0);
    fillMatrixDiag(PI, V - 1, -1);

    cout << "D Matrix" << endl;
    printMatrix(D, V - 1, V - 1);
    cout << "PI Matrix" << endl;
    printMatrix(PI, V - 1, V - 1);
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
    g.shortestPaths();
    return 0;
}
