#include "../../../vector_utils.h"
#include "../flow_graph.h"
#include <iostream>

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
        int max_flow = INT_MAX; // max posible flow to increase after bfs call
        int v = t;
        int u = pi[v];
        vector<F_Edge *> forward_edges;
        vector<F_Edge *> backwards_edges;
        bool found_edge = false;

        cout << "Found Increase Path:" << endl;
        while (u != -1) // Percorrer o caminho do sink para a source
        {

            found_edge = false;

            // Forward Edge
            for (int i = 0; i < adj[u].size(); i++)
            {
                if (adj[u][i].getV() == v)
                {
                    max_flow = min(max_flow, adj[u][i].getResidualCapacity());
                    forward_edges.push_back(&adj[u][i]);
                    cout << "(" << adj[u][i].getU() << ", " << adj[u][i].getV() << ")";
                    found_edge = true;
                    break;
                }
            }

            if (!found_edge)
            {
                // Backwards Edge
                for (int i = 0; i < adj[v].size(); i++)
                {
                    if (adj[v][i].getV() == u)
                    {
                        max_flow = min(max_flow, adj[v][i].getFlow());
                        backwards_edges.push_back(&adj[v][i]);
                        cout << "(" << adj[u][i].getU() << ", " << adj[u][i].getV() << ")";
                        break;
                    }
                }
            }

            v = u;
            u = pi[v];
        }
        cout << endl;

        total_flow += max_flow;

        // Increase flow in forward edges
        for (int i = 0; i < forward_edges.size(); i++)
        {
            forward_edges[i]->setFlow(forward_edges[i]->getFlow() + max_flow);
        }

        // Decrease flow in backwards edges
        for (int i = 0; i < backwards_edges.size(); i++)
        {
            backwards_edges[i]->setFlow(backwards_edges[i]->getFlow() - max_flow);
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
    g.addEdge(0, 1, 8);
    g.addEdge(0, 2, 9);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 5, 7);
    g.addEdge(4, 5, 8);
    g.edmondsKarp(0, 5); // O(VE^2)
    g.printGraph();
    return 0;
}

// Tambem pode ser usado para os problemas de
// correspondencia bipartida maxima

// Problema da Fuga