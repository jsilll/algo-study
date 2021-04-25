#include <iostream>
#include "../../weighted_graph.h"
#include "../../../array_utils.h"
#include "../../../vector_utils.h"

using namespace std;

// Utiliza os algoritmos de Dijkstra e de Bellman-Ford
// Baseado em re-pesagem dos arcos

// Se arcos com peso não negativo usar Dijkstra
// Caso contrário calcular, novo conjunto de pesos não negativos w'
// de forma a manter todos os caminhos mais curtos no grafo

void Graph::johnson()
{
    Graph g_positive(V + 1);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (adj[i][j] != INT_MAX)
            {
                g_positive.addEdge(i, j, 0);
            }
        }
    }

    for (int i = 0; i < V; i++)
    {
        g_positive.addEdge(V, i, 0);
    }

    int *d = new int[V + 1];
    int *pi = new int[V + 1];
    if (!g_positive.bellmanFord(V, d, pi))
    {
        cout << "There's a negative cycle in the graph" << endl;
        return;
    }

    // Temos a certeza de que nao há ciclos negativos no grafo
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            g_positive.addEdge(i, j, adj[i][j] + d[i] - d[j]);
        }
    }

    int **D = new int *[V + 1];
    for (int i = 0; i < V + 1; i++)
    {
        D[i] = new int[V + 1];
    }

    for (int i = 0; i < V + 1; i++)
    {
        g_positive.dijkstra(i, d, pi);
        for (int j = 0; j < V + 1; j++)
        {
            D[j][i] = d[j];
        }
    }

    printMatrix(D, V, V);
}

int main(int argc, char const *argv[])
{
    // Repesagem
    // Caminhos mais curtos mantém-se após a repesagem. Se p é
    // um caminho mais curto com função de peso w, então, também é caminho
    // mais curto com função de peso w'
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
    g.johnson();
    return 0;
}

// Problemas a compilar, isto nao devia estar aqui

typedef pair<int, int> priorityPair;

void Graph::dijkstra(int s, int *d, int *pi)
{
    // Initialize Single Source
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
            // Must be positive
            // Relax operation, its being applied more than once for every edge and it shouldnt
            if (0 <= adj[u][v] && adj[u][v] != INT_MAX && d[v] > d[u] + adj[u][v])
            {
                d[v] = d[u] + adj[u][v];
                pi[v] = u;
                pq.push(make_pair(d[v], v)); // Now we must update all the paths that use this one (sub-optimal structure)
            }
        }
    }
}

bool Graph::bellmanFord(int s, int *d, int *pi)
{
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
                if (adj[u][v] != INT_MAX && d[v] > d[u] + adj[u][v])
                {
                    d[v] = d[u] + adj[u][v];
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
            if (adj[u][v] != INT_MAX && d[v] > d[u] + adj[u][v])
            {
                return false;
            }
        }
    }
    return true;
}