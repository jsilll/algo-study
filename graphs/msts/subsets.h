#ifndef SUBSETS_H
#define SUBSETS_H

#include <iostream>

using namespace std;

class subset
{
public:
    int parent;
    int rank;
};

int findSubSetRoot(subset subsets[], int i) // O(log(V))
{
    if (subsets[i].parent != i)
        subsets[i].parent = findSubSetRoot(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void mergeSubSets(subset subsets[], int x, int y) // O(log(V))
{
    int rootX = findSubSetRoot(subsets, x);
    int rootY = findSubSetRoot(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;

    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;

    else
    {
        // Desempatar à esquerda
        // subsets[rootY].parent = rootX;
        // subsets[rootX].rank++;

        // Desempatar à direita
        subsets[rootX].parent = rootY;
        subsets[rootY].rank++;
    }
}

void printSubSets(subset subsets[], int l)
{
    cout << "Ranks" << endl;
    for (int i = 0; i < l; i++)
    {
        cout << subsets[i].rank << " ";
    }
    cout << endl;
    cout << "PIs" << endl;
    for (int i = 0; i < l; i++)
    {
        cout << subsets[i].parent << " ";
    }
    cout << endl;
}

#endif