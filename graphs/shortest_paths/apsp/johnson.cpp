#include <iostream>
#include "../../../array_utils.h"
#include "../../../vector_utils.h"
#include "../../letter_to_int.h"
#include "../../weighted_graph.h"
#include "../../pq_compare.h"

using namespace std;

// Utiliza os algoritmos de Dijkstra e de Bellman-Ford
// Baseado em re-pesagem dos arcos

// Se arcos com peso não negativo usar Dijkstra
// Caso contrário calcular, novo conjunto de pesos não negativos w'
// de forma a manter todos os caminhos mais curtos no grafo

void W_Graph::johnson()
{
    W_Graph g_positive(V + 1);

    for (int u = 0; u < V; u++)
    {
        for (vector<Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            g_positive.addEdge(u, itr->getV(), itr->getW());
        }
    }

    for (int i = 0; i < V; i++)
    {
        g_positive.addEdge(V, i, 0);
    }

    int *d = new int[V + 1];
    int *pi = new int[V + 1];
    if (!g_positive.bellmanFord(V, d, pi)) // We can also use the dag specific algo
    {
        cout << "There's a negative cycle in the graph" << endl;
        return;
    }

    W_Graph g_final(V);
    // Temos a certeza de que nao há ciclos negativos no grafo
    // Iterating through all the edges
    for (int u = 0; u < V; u++)
    {
        vector<Edge> adj_u = g_positive.getAdjacent(u);
        for (vector<Edge>::iterator itr = adj_u.begin(); itr != adj_u.end(); ++itr)
        {
            int v = itr->getV();
            g_final.addEdge(u, v, itr->getW() + d[u] - d[v]);
        }
    }

    int **D = g_final.buildAdjMatrix();
    int **PI = g_final.buildPIMatrix();

    cout << "Weights after reweighting" << endl;
    printMatrix(D, V - 1, V - 1);

    for (int i = 0; i < V; i++)
    {
        g_final.dijkstra(i, d, pi);
        for (int j = 0; j < V; j++)
        {
            D[i][j] = d[j];
            PI[i][j] = pi[j];
        }
    }

    cout << "D Matrix" << endl;
    printMatrix(D, V - 1, V - 1);
    cout << "PI Matrix" << endl;
    printMatrix(PI, V - 1, V - 1);
}

int main(int argc, char const *argv[])
{
    // Repesagem
    // Caminhos mais curtos mantém-se após a repesagem. Se p é
    // um caminho mais curto com função de peso w, então, também é caminho
    // mais curto com função de peso w'
    W_Graph g(6);
    g.addEdge(0, 1, -2);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 2, 5);
    g.addEdge(2, 5, -3);
    g.addEdge(3, 1, 2);
    g.addEdge(4, 3, -3);
    g.addEdge(4, 2, 2);
    g.addEdge(5, 4, 2);
    g.johnson();
    return 0;
}

// W_Graph g(6);
// g.addEdge(l2i('A'), l2i('B'), 6);
// g.addEdge(l2i('A'), l2i('C'), 2);
// g.addEdge(l2i('B'), l2i('D'), 3);
// g.addEdge(l2i('C'), l2i('D'), -1);
// g.addEdge(l2i('D'), l2i('E'), 4);
// g.addEdge(l2i('E'), l2i('F'), -2);
// g.addEdge(l2i('F'), l2i('A'), -2);
// g.addEdge(l2i('F'), l2i('C'), 1);
// g.johnson();

// W_Graph g(5);
// g.addEdge(0, 1, 10);
// g.addEdge(0, 4, 5);
// g.addEdge(1, 2, 1);
// g.addEdge(1, 4, 2);
// g.addEdge(2, 3, 4);
// g.addEdge(3, 2, 6);
// g.addEdge(4, 1, 3);
// g.addEdge(4, 2, 9);
// g.addEdge(4, 3, 2);
// g.johnson();

// Isto esta aqui so para ser mais facil de compilar
void W_Graph::dijkstra(int s, int *d, int *pi)
{
    // Initialize Single Source
    for (int v = 0; v < V; v++)
    {
        d[v] = INT_MAX;
        pi[v] = -1;
    }

    d[s] = 0;

    // Initializing priority queue
    bool *pqMember = new bool[V];
    priority_queue<priorityPair, vector<priorityPair>, pq_LowestDistanceFirst_Lexical> pq;
    for (int v = 0; v < V; v++)
    {
        if (v != s)
        {
            pqMember[v] = true;
            pq.push(make_pair(INT_MAX, v));
        }
    }
    pq.push(make_pair(0, s));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        pqMember[u] = false;

        // Iterate through its edges
        for (vector<Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            // Check if d[u] != INT_MAX otherwise sum may overflow
            if (d[u] != INT_MAX && d[itr->getV()] > d[u] + itr->getW())
            {
                d[itr->getV()] = d[u] + itr->getW();
                pi[itr->getV()] = u;
                pq.push(make_pair(d[itr->getV()], itr->getV())); // Lazy decrease key

                if (pqMember[itr->getV()]) // We only update the vertex prio if its still in the heap
                {
                    pq.push(make_pair(d[itr->getV()], itr->getV())); // Lazy decrease key
                }
            }
        }
    }
}

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

    for (int u = 0; u < V - 1; u++)
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