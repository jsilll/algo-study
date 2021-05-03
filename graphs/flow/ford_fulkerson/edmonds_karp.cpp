#include <iostream>
#include "../../../vector_utils.h"
#include "../flow_graph.h"

using namespace std;

// Escolher o melhor caminho <=> escolher o caminho
// com menor número de arcos

int F_Graph::edmondsKarp(int s, int t)
{
    int total_flow = 0, new_flow;
    W_Graph gf = this->buildResidualNetwork();
    vector<int> d(V, -1);
    vector<int> pi(V, -1);
    gf.bfs(s, t, &d, &pi);
    while (d[V - 1] != -1) // means we reached the sink
    {
        vector<F_Edge *> increase_path;
        int max_flow = INT_MAX; // max posible flow to increase after bfs call
        int v = t;
        int parent = pi[v];

        while (parent != -1) // Percorrer o caminho do sink para a source
        {
            for (int i = 0; i < adj[parent].size(); i++)
            {
                if (adj[parent][i].getV() == v)
                {
                    max_flow = min(max_flow, adj[parent][i].getResidualCapacity());
                    increase_path.push_back(&adj[parent][i]);
                    break;
                }
            }
            v = parent;
            parent = pi[v];
        }

        total_flow += max_flow;

        // Aumentar os fluxos das arestas do caminho encontrado
        for (int i = 0; i < increase_path.size(); i++)
        {
            increase_path[i]->setFlow(increase_path[i]->getFlow() + max_flow);
        }

        // Resetting the vectors
        for (int i = 0; i < V; i++)
        {
            d[i] = -1;
            pi[i] = -1;
        }

        W_Graph gf = this->buildResidualNetwork();
        gf.bfs(s, t, &d, &pi);
    }

    cout << "Fluxo Máximo: " << total_flow << endl;
    cout << "Corte Minimo:" << endl;
    printVector(d);

    return total_flow;
}

int main(int argc, char const *argv[])
{
    F_Graph g(6);
    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);
    g.edmondsKarp(0, 5); // O(VE^2)
    g.printGraph();
    return 0;
}

// Tambem pode ser usado para os problemas de
// correspondencia bipartida maxima

// Problema da Fuga