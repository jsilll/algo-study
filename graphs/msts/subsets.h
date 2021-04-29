#ifndef SUBSETS_H
#define SUBSETS_H

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

void mergeSubSets(subset subsets[], int u, int v) // O(log(V))
{
    int rootU = findSubSetRoot(subsets, u);
    int rootV = findSubSetRoot(subsets, v);

    if (subsets[rootU].rank < subsets[rootV].rank)
        subsets[rootU].parent = rootV;

    else if (subsets[rootU].rank > subsets[rootV].rank)
        subsets[rootV].parent = rootU;

    else
    {
        subsets[rootV].parent = rootU;
        subsets[rootU].rank++;
    }
}

#endif