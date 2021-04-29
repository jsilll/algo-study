// E PRECISO CORRIGIR UNS PROBLEMAS NESTE MAMBO
#include <iostream>
#include <map>

#include "../weighted_graph.h"
#include "../../letter_to_int.h"

using namespace std;

typedef pair<int, int> priorityPair;

// Greedy Algo, dijkstra modificado
void W_Graph::prim(int s, int *d, int *pi)
{
    // Initialize Single Source
    for (int v = 0; v < V; v++)
    {
        d[v] = INT_MAX;
        pi[v] = -1;
    }

    d[s] = 0;

    Edge **tree_edges = new Edge *[V];

    priority_queue<priorityPair, vector<priorityPair>, greater<priorityPair>> pq;
    pq.push(make_pair(0, s));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        // Iterate through its edges
        for (vector<Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            int v = itr->getV() + itr->getU() - u; // either getV() or getU() == u
            int w = itr->getW();
            if (d[v] > w && tree_edges[v] != &(*itr))
            {
                d[v] = w;
                pi[v] = u;
                tree_edges[v] = &(*itr);
                pq.push(make_pair(d[v], v)); // Lazy decrease key
            }
        }
    }

    cout << "Minimum Spanning Tree Edges (u, v, w)" << endl;
    for (int u = 0; u < V; u++)
    {
        if (u != s)
        {
            cout << "(" << i2l(tree_edges[u]->getU()) << ", " << i2l(tree_edges[u]->getV()) << ", " << tree_edges[u]->getW() << ")" << endl;
        }
    }

    cout << "Cost Array" << endl;
    printArray(d, V - 1);
    cout << "Parents Array" << endl;
    printArray(pi, V - 1);
}

int main(int argc, char const *argv[])
{
    W_Graph g(9);
    int *d = new int[9];
    int *pi = new int[9];
    g.addEdgeUndirected(l2i('A'), l2i('B'), 4);
    g.addEdgeUndirected(l2i('A'), l2i('H'), 8);
    g.addEdgeUndirected(l2i('B'), l2i('C'), 8);
    g.addEdgeUndirected(l2i('B'), l2i('H'), 11);
    g.addEdgeUndirected(l2i('C'), l2i('D'), 7);
    g.addEdgeUndirected(l2i('C'), l2i('F'), 4);
    g.addEdgeUndirected(l2i('C'), l2i('I'), 2);
    g.addEdgeUndirected(l2i('D'), l2i('F'), 14);
    g.addEdgeUndirected(l2i('D'), l2i('E'), 9);
    g.addEdgeUndirected(l2i('E'), l2i('F'), 10);
    g.addEdgeUndirected(l2i('F'), l2i('G'), 2);
    g.addEdgeUndirected(l2i('F'), l2i('G'), 2);
    g.addEdgeUndirected(l2i('G'), l2i('H'), 1);
    g.addEdgeUndirected(l2i('G'), l2i('I'), 6);
    g.addEdgeUndirected(l2i('H'), l2i('I'), 7);
    g.prim(8, d, pi);
    return 0;
}
