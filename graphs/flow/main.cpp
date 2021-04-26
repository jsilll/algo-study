#include <iostream>
#include "../flow_graph.h"

using namespace std;

// Uma rede de fluxo é um grafo dirigido em que cada arco (u,v) corresponde uma capacidade c(u,v)
// Tem dois vértices especiais, a fonte e o destino (sumidouro/sink)
// Todos os vértices de G pertencem a um caminho de s para t (é tudo um scc)
// O grafo é ligado, |E| >= |V| - 1

// Um fluxo de G = (V, E) é uma funcao f:V^2 -> R tal que:
// f(u,v) <= c(u,v), f(u,v) = -f(v, u)
// sum(f(u,v)) for all u,v in G - {source, sink} = 0

// Algoritmo de fluxo maximo, uma fonte e um destino
// Se houver mais do que um destino e/ou mais do que uma fonte
// definir uma super fonte que se fornece todas as fontes e as capacidades das arestas sao infinitas
// definir um suer destino ao qual se ligam todos os destinos, com cada uma das arestas com capacidade infinita

// Valor do fluxo : |sum(f(s,v)) for all v in G|
// por outras palavras, é a soma dos fluxos que saem da source

// Fluxo Máximo : soma das capacidadades das arestas que acabam no sink

// Capacidade de residual de uma aresta é o fluxo adicional que ainda se pode
// envia de u para v cf(u,v) = c(u,v) - f(u,v)

// Redes residuais
// Caminhos de aumento
// Cortes em redes de fluxo
// Teorema do Fluxo-Máximo Corte-Mínimo
// Algoritmo Genérico de Ford-Fulkerson

int main(int argc, char const *argv[])
{
    F_Graph g(10);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 2, 6);
    g.addEdge(4, 1, 3);
    g.addEdge(4, 2, 9);
    g.addEdge(4, 3, 2);
    g.printGraph();
    return 0;
}
