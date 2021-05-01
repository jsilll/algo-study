#include <iostream>
#include <list>
#include <stack>
#include "../../array_utils.h"
#include "../graph.h"

using namespace std;

void Graph::TarjanUtil(int u, int d[], int low[], stack<int> *st, bool stackMember[])
{
    static int visited = 1;

    d[u] = low[u] = visited++;

    st->push(u);
    stackMember[u] = true;

    for (vector<int>::iterator i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;

        if (d[v] == -1)
        {
            TarjanUtil(v, d, low, st, stackMember);
            low[u] = min(low[u], low[v]);
        }

        else if (stackMember[v] == true)
            low[u] = min(low[u], d[v]);
    }

    int w = 0;
    if (low[u] == d[u])
    {
        while (st->top() != u)
        {
            w = (int)st->top();
            cout << w << " ";
            stackMember[w] = false;
            st->pop();
        }
        w = (int)st->top();
        cout << w << endl;
        stackMember[w] = false;
        st->pop();
    }
}

void Graph::Tarjan(int s)
{
    int *d = new int[V];   // Number of already visited vertexes when v is discovered
    int *low = new int[V]; // Lowest value of d[] reachable by backwards or corss edges
    bool *stackMember = new bool[V];
    stack<int> *st = new stack<int>();

    // Initalizing values
    for (int i = 0; i < V; i++)
    {
        d[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }

    cout << "SCCs in order of discovery" << endl;
    // Starting algo
    TarjanUtil(s, d, low, st, stackMember);
    for (int v = 0; v < V; v++)
        if (d[v] == -1)
            TarjanUtil(v, d, low, st, stackMember);
    cout << "Low Array" << endl;
    printArray(low, V - 1);
}

int main()
{
    int offset = -1;
    Graph g(6);
    g.addEdge(1 + offset, 2 + offset);
    g.addEdge(2 + offset, 1 + offset);
    g.addEdge(3 + offset, 2 + offset);
    g.addEdge(3 + offset, 6 + offset);
    g.addEdge(4 + offset, 1 + offset);
    g.addEdge(5 + offset, 3 + offset);
    g.addEdge(5 + offset, 4 + offset);
    g.addEdge(6 + offset, 5 + offset);
    g.Tarjan(5 + offset);
    return 0;
}