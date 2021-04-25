#include <iostream>
#include <list>
#include <stack>
#include "../graph.h"

using namespace std;

void Graph::TarjanUtil(int u, int d[], int low[], stack<int> *st, bool stackMember[])
{
    static int visited = 0;

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
        cout << w << "\n";
        stackMember[w] = false;
        st->pop();
    }
}

void Graph::Tarjan()
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

    // Starting algo
    for (int v = 0; v < V; v++)
        if (d[v] == -1)
            TarjanUtil(v, d, low, st, stackMember);
}

int main()
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
    g.Tarjan();

    return 0;
}