#include <iostream>
#include <stack>

#include "../../../vector_utils.h"
#include "../../flow_graph.h"

using namespace std;

void F_Graph::discharge(int u)
{
    // Nao é o mais eficiente possivel porque
    // itera sempre por todos e nao recomeca onde ficou
    // desde o ultimo

    while (e[u] > 0)
    {
        if (N_current[u] == N[u].end())
        {
            relabel(u);
            N_current[u] = N[u].begin(); // Reset iterator
        }

        // Forward Edge case
        int v = (*N_current[u])->getV();
        if (v != u)
        {
            if ((*N_current[u])->getResidualCapacity() && h[u] == h[v] + 1)
            {
                push(u, v, *N_current[u]);
            }
        }

        // Backwards Edge case
        else
        {
            v = (*N_current[u])->getU();
            if ((*N_current[u])->getFlow() && h[u] == h[v] + 1)
            {
                // caso de refluxo
                push(u, v, *N_current[u]);
            }
        }

        N_current[u]++;
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

    // Initialize N_current list
    for (int u = 0; u < V; u++)
    {
        N_current[u] = N[u].begin();
    }

    // Setting up L for V - {s, t} in 0 -> V order
    // Vai-se tornando numa ordenação topológica da
    // rede residual admissível
    stack<int> L;
    for (int u = V - 1; u > -1; u--)
    {
        if (u != s && u != t)
        {
            L.push(u);
        }
    }

    // Actual Algorithm
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

    while (1) // assim nao avalia sempre se u != NULL
    {
        int u_old = u;
        int h_old = h[u];

        discharge(u);

        // Prints e mambos
        cout << "Discharge " << u << endl;
        cout << "e : ";
        printArray(e, V - 1);
        cout << "h : ";
        printArray(h, V - 1);
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

    // Calcular o corte mínimo com uma bfs na rede residual
    vector<int> d(5, -1);
    vector<int> pi(5, -1);
    W_Graph gf = g.buildResidualNetwork();
    gf.bfs(0, 4, &d, &pi);
    cout << "Corte Minimo:" << endl;
    printVector(d);
    return 0;
}
