#include <iostream>
#include <map>

#include "../../array_utils.h"
#include "../letter_to_int.h"
#include "../pq_compare.h"
#include "prim_graph.h"

using namespace std;

// Greedy Algo, dijkstra modificado
void Graph::prim(int s, int *d, int *pi)
{
    // Initialize Single Source
    for (int v = 0; v < V; v++)
    {
        d[v] = INT_MAX;
        pi[v] = -1;
    }

    d[s] = 0;

    // Initialize tree edges array
    int *tree_edges = new int[V];
    for (int v = 0; v < V; v++)
    {
        tree_edges[v] = -1;
    }

    priority_queue<priorityPair, vector<priorityPair>, pq_LowestDistanceFirst_Lexical> pq;
    pq.push(make_pair(0, s));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        // Iterate through its edges
        for (vector<int>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            int v = edges[*itr].getV() + edges[*itr].getU() - u; // either getV() or getU() will == u
            int w = edges[*itr].getW();
            if (d[v] > w && v != pi[u]) // We cant go backwards in the tree
            {
                d[v] = w;
                pi[v] = u;
                tree_edges[v] = *itr;
                pq.push(make_pair(d[v], v)); // Lazy decrease key
            }
        }
    }

    // Printate Mambos
    cout << "Minimum Spanning Tree Edges (u, v, w)" << endl;
    for (int u = 0; u < V; u++)
    {
        if (u != s)
        {
            cout << "(" << i2l(edges[tree_edges[u]].getU()) << ", " << i2l(edges[tree_edges[u]].getV()) << ", " << edges[tree_edges[u]].getW() << ")" << endl;
        }
    }

    cout << "Cost Array" << endl;
    printArray(d, V - 1);
    cout << "Parents Array" << endl;
    printArray(pi, V - 1);
}

int main(int argc, char const *argv[])
{
    Graph g(9);
    int *d = new int[9];
    int *pi = new int[9];
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
    g.prim(8, d, pi);
    return 0;
}
