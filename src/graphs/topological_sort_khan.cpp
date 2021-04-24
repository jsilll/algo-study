#include <iostream>
#include <queue>
#include <vector>

#include "graph.h"
#include "vector_utils.h"

// Algoritmo de Khan
// Usar uma queue e comecar pelas sources do grafo
// explorar todos os vertices adjacentes ao vértice atual
// e para vértice visto diminuir a aresta que os liga, se o vértice
// já não tiver mais arestas adicioná-lo à fila de exploração
//
// Alternativa
// Fazer uma DFS e adicionar os vértices ao inicio da ordem
// topológica à medida que os vamos fechando

vector<int> Graph::topologicalSort()
{
    vector<int> in_degree(V, 0);

    for (int u = 0; u < V; u++)
    {
        for (vector<int>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            in_degree[*itr]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    int cnt = 0;

    vector<int> top_order;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        for (vector<int>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            if (--in_degree[*itr] == 0)
                q.push(*itr);
        }
        cnt++;
    }

    return top_order;
}

int main(int argc, char const *argv[])
{
    Graph g(10);
    g.addEdge(0, 9);
    g.addEdge(0, 8);
    g.addEdge(0, 7);
    g.addEdge(0, 6);
    vector<int> top_order = g.topologicalSort();
    g.printGraph();
    printVector(top_order);
    return 0;
}
