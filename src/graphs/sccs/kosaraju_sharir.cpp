#include <iostream>
#include <queue>

#include "../graph.h"
#include "../vector_utils.h"

using namespace std;

// Wrapper function for DFS method
vector<int> Graph::getDFSClosingOrder()
{
    int current_time = 0;
    vector<int> times(V, -1);
    vector<int> pi(V, -1);

    for (int i = 0; i < V; i++)
    {
        if (times[i] == -1)
        {
            DFS(i, &pi, &times, &current_time);
        }
    }

    vector<int> closing_order(V, 0);

    for (int i = 0; i < V; i++)
    {
        closing_order[V - times[i]] = i;
    }

    return closing_order;
}

// Perform a DFS on the graph following an order
vector<int> Graph::orderedDFS(vector<int> order)
{
    int current_time = 0;
    vector<int> times(V, -1);
    vector<int> pi(V, -1);

    for (vector<int>::iterator itr = order.begin(); itr != order.end(); ++itr)
    {
        if (times[*itr] == -1)
        {
            DFS(*itr, &pi, &times, &current_time);
        }
    }

    return pi;
}

int main(int argc, char const *argv[])
{
    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 0);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 4);
    g.addEdge(6, 7);

    vector<int> pi = g.getTranspose().orderedDFS(g.getDFSClosingOrder());
    printVector(pi);
    int number_of_sccs = 0;
    for (vector<int>::iterator itr = pi.begin(); itr != pi.end(); ++itr)
    {
        if (*itr == -1)
        {
            number_of_sccs++;
        }
    }
    cout << "There's " << number_of_sccs << " sccs in this graph." << endl;
    return 0;
}