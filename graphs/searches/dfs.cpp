#include <iostream>
#include "graph.h"

using namespace std;

// Recursive version of DFS, the iterative version should implement a stack
void Graph::DFS(int v, vector<int> *pi, vector<int> *times, int *current_time)
{
    for (vector<int>::iterator itr = adj[v].begin(); itr != adj[v].end(); ++itr)
    {
        if ((*times)[*itr] == -1)
        {
            (*times)[v] = 0; // It's currently being visited
            (*pi)[*itr] = v;
            DFS(*itr, pi, times, current_time);
        }
    }
    (*times)[v] = ++(*current_time);
}

int main(int argc, char const *argv[])
{
    // No driver code implemented yet
    return 0;
}
