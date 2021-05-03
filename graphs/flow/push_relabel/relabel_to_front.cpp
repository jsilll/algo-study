#include <iostream>
#include <list>

#include "../../../vector_utils.h"
#include "../flow_graph.h"

using namespace std;

void F_Graph::push(int u, int v, F_Edge *edge, int *e, int *h)
{
    // Forward Edge
    if (edge->getV() == v)
    {
        int new_flow = min(e[u], edge->getResidualCapacity());
        edge->setFlow(edge->getFlow() + new_flow);
        e[u] = e[u] - new_flow;
        e[v] = e[v] + new_flow;
    }

    // Backwards Edge
    else if (edge->getV() == u)
    {
        int new_flow = min(e[u], edge->getFlow());
        edge->setFlow(edge->getFlow() - new_flow);
        e[u] = e[u] - new_flow;
        e[v] = e[v] + new_flow;
    }
}

void F_Graph::relabel(int u, int *h, vector<F_Edge *> *N)
{
    int min_height = INT_MAX;
    // Percorrer todos os arcos de adjacencia na rede residual
    // Forward existe de ainda há residualCapacity
    // Backwards existe se há flow
    for (int v = 0; v < N[u].size(); v++)
    {
        F_Edge *edge = N[u][v];

        // Forward Edge case
        if (edge->getV() != u)
        {
            if (edge->getResidualCapacity())
            {
                min_height = min(min_height, h[edge->getV()]);
            }
        }

        // If its not a forward edge it's a backwards one
        else if (edge->getFlow())
        {
            min_height = min(min_height, h[edge->getU()]);
        }
    }

    h[u] = 1 + min_height;
}

void F_Graph::pushRelabelInitialize(int s, int *e, int *h)
{
    // Initialize
    for (int u = 0; u < V; u++)
    {
        for (vector<F_Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            itr->setFlow(0);
        }
        e[u] = 0;
        h[u] = 0;
    }

    for (vector<F_Edge>::iterator itr = adj[s].begin(); itr != adj[s].end(); ++itr)
    {
        e[s] = e[s] - itr->getCapacity();
        e[itr->getV()] = itr->getCapacity();
        itr->setFlow(itr->getCapacity());
    }

    h[s] = V;
}

bool F_Graph::discharge(int u, int *e, int *h, vector<F_Edge *> *N, vector<F_Edge *>::iterator *N_current)
{
    // Nao é o mais eficiente possivel porque
    // itera sempre por todos e nao recomeca onde ficou
    // desde o ultimo
    bool discharged = false;
    while (e[u] > 0)
    {
        discharged = true;
        if (N_current[u] == N[u].end())
        {
            relabel(u, h, N);
            N_current[u] = N[u].begin(); // Reset iterator
        }

        // Forward Edge case
        int v = (*N_current[u])->getV();
        if (v != u)
        {
            if ((*N_current[u])->getResidualCapacity() && h[u] == h[v] + 1)
            {
                push(u, v, *N_current[u], e, h);
            }
        }

        // Backwards Edge case
        else
        {
            v = (*N_current[u])->getU();
            if ((*N_current[u])->getFlow() && h[u] == h[v] + 1)
            {
                // caso de refluxo
                push(u, v, *N_current[u], e, h);
            }
        }

        N_current[u]++;
    }

    return discharged;
}

void F_Graph::relabelToFront(int s, int t)
{
    // Needed for push_relabel algos
    int *e = new int[V];
    int *h = new int[V];
    vector<F_Edge *> *N = new vector<F_Edge *>[V];
    vector<F_Edge *>::iterator *N_current = new vector<F_Edge *>::iterator[V];

    pushRelabelInitialize(s, e, h);

    // Initialize N List (specific for relabelToFront algo)
    // Initialize N_current list
    // Setting up L for V - {s, t} in 0 -> V order
    // Vai-se tornando numa ordenação topológica da
    // rede residual admissível
    list<int> L;
    for (int u = 0; u < V; u++)
    {
        for (vector<F_Edge>::iterator itr = adj[u].begin(); itr != adj[u].end(); ++itr)
        {
            N[u].push_back(&(*itr));           // As forward edge
            N[itr->getV()].push_back(&(*itr)); // As backwards edge
        }

        N_current[u] = N[u].begin();

        if (u != s && u != t)
        {
            L.push_back(u);
        }
    }

    list<int>::iterator itr = L.begin();
    while (itr != L.end())
    {
        int u = (*itr);
        int h_old = h[*itr];

        if (discharge(u, e, h, N, N_current))
        {
            // Printing the discharged vertex
            cout << "Discharge " << u << endl;
            cout << "e : ";
            printArray(e, V - 1);
            cout << "h : ";
            printArray(h, V - 1);
            this->printGraph();
        }

        if (h_old != h[u])
        {
            L.erase(itr);
            L.push_front(u);
            itr = L.begin();

            // Printing L list
            cout << "L list:" << endl;
            for (auto i : L)
            {
                cout << i << " ";
            }
            cout << endl;
            cout << endl;
        }
        itr++;
    }
}

int main(int argc, char const *argv[])
{
    F_Graph g(5);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 3, 7);
    g.addEdge(1, 3, 7);
    g.addEdge(1, 2, 6);
    g.addEdge(2, 3, 4);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 1, 3);
    g.addEdge(3, 4, 4);
    g.relabelToFront(0, 4);
    
    // Também se pode computar o corte mínimo encontrando um h'
    // tal que h' != h(v) para todo o v em V e h' < V
    // Calcular o corte mínimo com uma bfs na rede residual
    vector<int> d(5, -1);
    vector<int> pi(5, -1);
    W_Graph gf = g.buildResidualNetwork();
    gf.bfs(0, 4, &d, &pi);
    cout << "Corte Minimo:" << endl;
    printVector(d);
    return 0;
}
