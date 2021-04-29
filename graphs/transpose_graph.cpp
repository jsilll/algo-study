#include <iostream>

#include "graph.h"
#include "weighted_graph.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Graph g(10);
    g.addEdge(0, 9);
    g.addEdge(0, 8);
    g.addEdge(0, 7);
    g.addEdge(0, 6);
    g.printGraph();
    cout << "Transposed graph" << endl;
    g.getTranspose().printGraph();
    return 0;
}
