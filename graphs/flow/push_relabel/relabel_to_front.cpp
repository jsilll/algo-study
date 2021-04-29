#include <iostream>
#include <stack>

#include "../../flow_graph.h"

using namespace std;

void F_Graph::discharge(int u)
{
    // Pode e devia estar mais eficiente, porque tem de
    // construir a rede residual sempre que é chamado

    // Percorrer todos os arcos na rede residual
    // Forward existe de ainda há residualCapacity
    // Backwards existe se há flow

    vector<F_Edge *>::iterator itr = N[u].begin();
    while (e[u] > 0)
    {
        if (itr == N[u].end())
        {
            relabel(u);
            itr = N[u].begin();
        }

        // Forward Edge case
        int v = (*itr)->getV();
        if (v != u)
        {
            if ((*itr)->getResidualCapacity() && h[u] == h[v] + 1)
            {
                push(u, v, *itr);
            }
        }

        // Backwards Edge case
        else
        {
            v = (*itr)->getU();
            if ((*itr)->getFlow() && h[u] == h[v] + 1)
            {
                // caso de refluxo
                push(u, v, *itr);
            }
        }

        itr++;
    }
}

// ver se consigo calcular o corte minimo no final do algoritmo
void F_Graph::relabelToFront(int s, int t)
{
    pushRelabelInitialize(s);

    // Initialize N List (specific for relabelToFront algo)
    for (int u = 0; u < V; u++)
    {
        for (vector<F_Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            N[u].push_back(&(*itr));           // As forward edge
            N[itr->getV()].push_back(&(*itr)); // As backwards edge
        }
    }

    stack<int> L;
    for (int u = V - 1; u > -1; u--)
    {
        if (u != s && u != t)
        {
            L.push(u);
        }
    }

    // Algorithm begin
    int u;
    if (!L.empty())
    {
        u = L.top();
        L.pop();
    }
    else
    {
        return;
    }

    while (1)
    {
        int u_old = u;
        int h_old = h[u];

        discharge(u);

        // Debuggings e mambos
        cout << "Discharge " << u << endl;
        cout << "e : ";
        printArray(e, V - 1);
        this->printGraph();
        cout << endl;

        if (!L.empty())
        {
            u = L.top();
            L.pop();
        }

        // Mesmo que a altura tenha sido alterada
        // se nao houver mais nenhum na queue nao importa
        else
        {
            break;
        }

        if (h[u_old] != h_old)
        {
            L.push(u_old);
        }
    }
}

int main(int argc, char const *argv[])
{
    F_Graph g(5);
    g.addEdge(0, 1, 12);
    g.addEdge(0, 2, 14);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 4, 16);
    g.addEdge(2, 3, 8);
    g.addEdge(3, 4, 10);
    g.addEdge(3, 1, 7);
    g.relabelToFront(0, 4);
    return 0;
}
