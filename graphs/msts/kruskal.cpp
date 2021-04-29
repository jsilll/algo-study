#include <iostream>

#include <bits/stdc++.h>
#include "../weighted_graph.h"
#include "../../vector_utils.h"

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
    return (e1->getU() + e1->getV()) < (e2->getU() + e2->getV());
}

void W_Graph::kruskal()
{
    vector<int> components(V, -1); // É preciso uma melhor estrura (set) para melhorar a complexidade
    vector<Edge *> edges;

    // Initializing components vector
    for (int u = 0; u < V; u++)
    {
        components[u] = u;
    }

    // Initializing Edges Vector
    for (int u = 0; u < V; u++)
    {
        for (vector<Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            edges.push_back(&(*itr));
        }
    }

    sort(edges.begin(), edges.end(), compareEdges);

    int seen_vertex = 1;
    cout << "(u, v, w)" << endl;
    for (vector<Edge *>::iterator itr = edges.begin(); itr != edges.end(); ++itr)
    {
        if (components[(*itr)->getV()] != components[(*itr)->getU()])
        {
            // Adicionar a aresta a A
            cout << "(" << (*itr)->getU() << ", " << (*itr)->getV() << ", " << (*itr)->getW() << ")" << endl;
            seen_vertex++;

            // Mudar o component de todos os vertices (nada eficiente)
            int old_component = components[(*itr)->getU()];
            int new_component = components[(*itr)->getV()];
            for (int u = 0; u < V; u++)
            {
                if (components[u] == old_component)
                {
                    components[u] = new_component;
                }
            }
        }
    }

    cout << seen_vertex << endl;
}

int main(int argc, char const *argv[])
{
    W_Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 3);
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 4, 6);
    g.addEdge(4, 5, 5);
    g.kruskal();
    return 0;
}
