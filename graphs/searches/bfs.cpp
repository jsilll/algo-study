#include <iostream>
#include <queue>

#include "../../vector_utils.h"
#include "../graph.h"

using namespace std;

// Calculates the shortest paths from node source and all the other nodes
// When the algo finishes, the distance vector must correpond with the size of the
// shortest paths from source s to the vertex v
// Calculates the BF tree from with root s

int main(int argc, char const *argv[])
{
    Graph g(8);
    g.addEdge(l2i('A'), l2i('B'));
    g.addEdge(l2i('A'), l2i('C'));
    g.addEdge(l2i('A'), l2i('D'));
    g.addEdge(l2i('B'), l2i('E'));
    g.addEdge(l2i('B'), l2i('F'));
    g.addEdge(l2i('C'), l2i('F'));
    g.addEdge(l2i('E'), l2i('F'));
    g.addEdge(l2i('D'), l2i('G'));
    g.addEdge(l2i('D'), l2i('H'));
    g.addEdge(l2i('G'), l2i('H'));
    vector<int> d(8, -1);
    vector<int> pi(8, -1);
    g.bfs(3, &d, &pi);
    cout << "d vector" << endl;
    printVector(d);
    cout << "pi vector" << endl;
    printVector(pi);
    return 0;
}
