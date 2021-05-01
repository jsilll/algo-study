#include <iostream>
#include <queue>
#include <vector>

#include "../array_utils.h"
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
    int V = 8;
    Graph g(8);
    g.addEdge(0, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 3);
    g.addEdge(5, 6);
    g.addEdge(6, 1);
    g.addEdge(6, 7);
    g.addEdge(7, 2);
    g.addEdge(2, 1);
    g.addEdge(2, 6);
    cout << "Topological Order" << endl;
    printArray(g.topologicalSort(), V - 1);
    return 0;
}
