#include <iostream>
#include "../../../array_utils.h"
#include "../../weighted_graph.h"

using namespace std;

// dij(k) = wij, se k = 0
// dij(k) = min(dij(k-1), dik(k-1) + dkj(k-1))

void W_Graph::floydWarshall()
{
    int **D = this->buildAdjMatrix();
    int **PI = this->buildPIMatrix();

    fillMatrixDiag(D, V - 1, 0); // Also for checking for negative loops in the end

    int i, j, k;

    for (k = 0; k < V; k++)
    {
        // Printing D(k) and PI(k) Matrices
        cout << "D "
             << "(" << k << ")"
             << " Matrix" << endl;
        printMatrix(D, V - 1, V - 1);
        cout << "PI "
             << "(" << k << ")"
             << " Matrix" << endl;
        printMatrix(PI, V - 1, V - 1);

        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (D[i][k] != INT_MAX && D[k][j] != INT_MAX && D[i][j] > D[i][k] + D[k][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    PI[i][j] = k;
                }
            }
        }
    }

    // If the final Matrix does not have the whole diag with 0s it means there's a negative loop
}

int main(int argc, char const *argv[])
{
    W_Graph g(6);
    int offset = -1;
    g.addEdge(1 + offset, 5 + offset, -1);
    g.addEdge(2 + offset, 1 + offset, 1);
    g.addEdge(2 + offset, 4 + offset, 2);
    g.addEdge(3 + offset, 2 + offset, 2);
    g.addEdge(3 + offset, 6 + offset, -8);
    g.addEdge(4 + offset, 1 + offset, -4);
    g.addEdge(4 + offset, 5 + offset, 3);
    g.addEdge(5 + offset, 2 + offset, 7);
    g.addEdge(6 + offset, 2 + offset, 5);
    g.addEdge(6 + offset, 3 + offset, 10);
    g.floydWarshall(); // O(n^3)
    // Se (i,j) != "i" (na matrix de adjacencicas) entao pertence ao fecho transitivo do grafo
    // O fecho transitivo de um grafo é o conjunto de vértices (i,j)
    // tal que existe um caminho de i para j
    return 0;
}
