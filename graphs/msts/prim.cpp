#include <iostream>
#include <map>

#include "../../array_utils.h"
#include "../letter_to_int.h"
#include "../pq_compare.h"
#include "prim_graph.h"

using namespace std;

// Greedy Algo, dijkstra modificado
void Graph::prim(int s, int *key, int *pi)
{
    bool *pqMember = new bool[V];

    // Initialize Single Source
    for (int v = 0; v < V; v++)
    {
        key[v] = INT_MAX;
        pi[v] = -1;
    }

    key[s] = 0;

    // Initialize tree edges array
    int *tree_edges = new int[V];
    for (int v = 0; v < V; v++)
    {
        tree_edges[v] = -1;
    }

    // Initializing priority queue
    priority_queue<priorityPair, vector<priorityPair>, pq_LowestDistanceFirst_Lexical> pq;
    for (int v = 0; v < V; v++)
    {
        if (v != s)
        {
            pqMember[v] = true;
            pq.push(make_pair(INT_MAX, v));
        }
    }
    pq.push(make_pair(0, s));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        pqMember[u] = false;

        // Iterate through its edges
        for (vector<int>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            int v = edges[*itr].getV() + edges[*itr].getU() - u; // either getV() or getU() will == u
            int w = edges[*itr].getW();
            if (pqMember[v] && key[v] > w) // We cant go backwards in the tree
            {
                key[v] = w;
                pi[v] = u;
                tree_edges[v] = *itr;
                pq.push(make_pair(key[v], v)); // Lazy decrease key
            }
        }
    }

    // Printate Mambos
    cout << "Minimum Spanning Tree Edges (u, v, w)" << endl;
    for (int u = 0; u < V; u++)
    {
        if (u != s)
        {
            cout << "(" << edges[tree_edges[u]].getU() << ", " << edges[tree_edges[u]].getV() << ", " << edges[tree_edges[u]].getW() << ")" << endl;
        }
    }

    cout << "Cost Array" << endl;
    printArray(key, V - 1);
    cout << "Parents Array" << endl;
    printArray(pi, V - 1);
}

int main(int argc, char const *argv[])
{
    int V = 6;
    Graph g(V);
    int *key = new int[V];
    int *pi = new int[V];
    int offset = -1;
    // Nao interessa a ordem como colocamos as arestas
    g.addEdge(1 + offset, 2 + offset, 6);
    g.addEdge(1 + offset, 4 + offset, 7);
    g.addEdge(2 + offset, 3 + offset, 5);
    g.addEdge(2 + offset, 4 + offset, 5);
    g.addEdge(2 + offset, 5 + offset, 1);
    g.addEdge(3 + offset, 5 + offset, 5);
    g.addEdge(3 + offset, 6 + offset, 5);
    g.addEdge(4 + offset, 5 + offset, 1);
    g.addEdge(5 + offset, 6 + offset, 1);
    g.prim(1 + offset, key, pi);
    return 0;
}

// Graph g(9);
// int *key = new int[9];
// int *pi = new int[9];
// g.addEdge(l2i('A'), l2i('B'), 4);
// g.addEdge(l2i('A'), l2i('H'), 8);
// g.addEdge(l2i('B'), l2i('C'), 8);
// g.addEdge(l2i('B'), l2i('H'), 11);
// g.addEdge(l2i('C'), l2i('D'), 7);
// g.addEdge(l2i('C'), l2i('F'), 4);
// g.addEdge(l2i('C'), l2i('I'), 2);
// g.addEdge(l2i('D'), l2i('F'), 14);
// g.addEdge(l2i('D'), l2i('E'), 9);
// g.addEdge(l2i('E'), l2i('F'), 10);
// g.addEdge(l2i('F'), l2i('G'), 2);
// g.addEdge(l2i('F'), l2i('G'), 2);
// g.addEdge(l2i('G'), l2i('H'), 1);
// g.addEdge(l2i('G'), l2i('I'), 6);
// g.addEdge(l2i('H'), l2i('I'), 7);
// g.prim(8, key, pi);