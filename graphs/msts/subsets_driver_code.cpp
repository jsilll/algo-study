#include <iostream>
#include "subsets.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int N = 10;
    subset *subsets = new subset[(N * sizeof(subset))];

    // Initialize
    for (int i = 0; i < N; i++)
    {
        subsets[i].rank = 0;
        subsets[i].parent = i;
    }

    for (int i = 0; i < 3; i++)
    {
        mergeSubSets(subsets, 2 ^ i, 2 ^ (i + 1));
    }

    for (int i = 0; i < 3; i++)
    {
        mergeSubSets(subsets, 3 * i, 3 * (i + 1));
    }

    mergeSubSets(subsets, 5, 7);
    mergeSubSets(subsets, 1, 6);
    mergeSubSets(subsets, 1, 5);
    findSubSetRoot(subsets, 4);

    printSubSets(subsets, N);

    return 0;
}