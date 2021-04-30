#include <iostream>
#include <queue>
#include <vector>

#include "../vector_utils.h"
#include "weighted_graph.h"
#include "graph.h"

// Algoritmo de Khan
// Usar uma queue e comecar pelas sources do grafo
// explorar todos os vertices adjacentes ao vértice atual
// e para vértice visto diminuir a aresta que os liga, se o vértice
// já não tiver mais arestas adicioná-lo à fila de exploração
//
// Alternativa
// Fazer uma DFS e adicionar os vértices ao inicio da ordem
// topológica à medida que os vamos fechando

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
