#include <iostream>

#include "../../vector_utils.h"
#include "../graph.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int V = 4;
    Graph g(V);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    int current_time = 0;
    vector<int> times(V, -1);
    vector<int> pi(V, -1);
    // By your boy Tarjan
    g.dfs(&pi, &times, &current_time);
    cout << "Times vector" << endl;
    printVector(times);
    cout << "Pi vector" << endl;
    printVector(pi);
    return 0;
}
