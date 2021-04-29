#include <iostream>
#include <queue>

#include "../graph.h"
#include "../../vector_utils.h"

using namespace std;

// Calculates the shortest paths from node source and all the other nodes
// When the algo finishes, the distance vector must correpond with the size of the
// shortest paths from source s to the vertex v
// Calculates the BF tree from with root s

int main(int argc, char const *argv[])
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    vector<int> d(4, -1);
    vector<int> pi(4, -1);
    g.bfs(2, &d, &pi);
    cout << "d vector" << endl;
    printVector(d);
    cout << "pi vector" << endl;
    printVector(pi);
    return 0;
}
