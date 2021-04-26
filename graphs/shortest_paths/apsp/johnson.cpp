// Has a bug somewhere
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
    if (!g_positive.bellmanFord(V, d, pi))
    {
        cout << "There's a negative cycle in the graph" << endl;
        return;
    }

    // Temos a certeza de que nao há ciclos negativos no grafo
    W_Graph g_final(V + 1);
    // Iterating through all the edges
    for (int u = 0; u < V + 1; u++)
    {
        vector<Edge> adj_u = g_positive.getAdjacent(u);
        for (vector<Edge>::iterator itr = adj_u.begin(); itr != adj_u.end(); ++itr)
        {
            int v = itr->getV();
            int w_uv = itr->getW();
            g_final.addEdge(u, v, w_uv + d[u] - d[v]);
        }
    }

    int **D = g_final.buildAdjMatrix();
    for (int i = 0; i < V + 1; i++)
    {
        g_final.dijkstra(i, d, pi);
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
    g.johnson();
    return 0;
}

// Problemas a compilar, isto nao devia estar aqui

typedef pair<int, int> priorityPair;

void W_Graph::dijkstra(int s, int *d, int *pi)
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

        // Iterate through its edges
        for (vector<Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            // Must be positive
            if (d[itr->getV()] > d[u] + itr->getW())
            {
                d[itr->getV()] = d[u] + itr->getW();
                pi[itr->getV()] = u;
                // Relax operation, its being applied more than once for every edge and it shouldnt, cuz of how heap (??)
                pq.push(make_pair(d[itr->getV()], itr->getV())); // Now we must update all the paths that use this one (sub-optimal structure)
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
                if (D[u][v] != INT_MAX && d[v] > d[u] + D[u][v])
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
    return true;
}