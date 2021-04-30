#include <iostream>
#include <bits/stdc++.h>

#include "../../vector_utils.h"
#include "../weighted_graph.h"
#include "../letter_to_int.h"
#include "subsets.h"

using namespace std;

bool compareEdges(Edge *e1, Edge *e2)
{
    if (e1->getW() < e2->getW())
    {
        return true;
    }

    if (e1->getW() > e2->getW())
    {
        return false;
    }

    // Ordem Lexicografica para desempatar A->0, B->1 ...

    if (e1->getU() < e2->getU())
    {
        return true;
    }

    if (e1->getU() > e2->getU())
    {
        return false;
    }

    return e1->getV() < e2->getV();
}

void W_Graph::kruskal()
{
    subset *subsets = new subset[(V * sizeof(subset))];
    vector<Edge *> edges;

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Initializing Edges Vector
    for (int u = 0; u < V; u++)
    {
        for (vector<Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            edges.push_back(&(*itr));
        }
    }

    // Sort all the edges by weigth and lexicografically
    sort(edges.begin(), edges.end(), compareEdges);

    cout << "Minimum Spanning Tree Edges (u, v, w)" << endl;
    for (vector<Edge *>::iterator itr = edges.begin(); itr != edges.end(); ++itr)
    {
        int rootU = findSubSetRoot(subsets, (*itr)->getU());
        int rootV = findSubSetRoot(subsets, (*itr)->getV());

        if (rootU != rootV)
        {
            // Adicionar a aresta a A
            cout << "(" << i2l((*itr)->getU()) << ", " << i2l((*itr)->getV()) << ", " << (*itr)->getW() << ")" << endl;

            // Juntar os dois subsets
            mergeSubSets(subsets, rootU, rootV);
        }
    }
}

int main(int argc, char const *argv[])
{
    // Escrever as arestas lexicograficamente ex: A -> B e nao B -> A
    W_Graph g(9);
    g.addEdge(l2i('A'), l2i('B'), 4);
    g.addEdge(l2i('A'), l2i('H'), 8);
    g.addEdge(l2i('B'), l2i('C'), 8);
    g.addEdge(l2i('B'), l2i('H'), 11);
    g.addEdge(l2i('C'), l2i('D'), 7);
    g.addEdge(l2i('C'), l2i('F'), 4);
    g.addEdge(l2i('C'), l2i('I'), 2);
    g.addEdge(l2i('D'), l2i('F'), 14);
    g.addEdge(l2i('D'), l2i('E'), 9);
    g.addEdge(l2i('E'), l2i('F'), 10);
    g.addEdge(l2i('F'), l2i('G'), 2);
    g.addEdge(l2i('F'), l2i('G'), 2);
    g.addEdge(l2i('G'), l2i('H'), 1);
    g.addEdge(l2i('G'), l2i('I'), 6);
    g.addEdge(l2i('H'), l2i('I'), 7);
    g.kruskal();
    return 0;
}

// W_Graph g(6);
// g.addEdge(0, 1, 4);
// g.addEdge(0, 2, 1);
// g.addEdge(0, 3, 3);
// g.addEdge(1, 2, 4);
// g.addEdge(1, 3, 4);
// g.addEdge(2, 3, 2);
// g.addEdge(2, 4, 4);
// g.addEdge(3, 4, 6);
// g.addEdge(4, 5, 5);
// g.kruskal(); // O(E log(V))