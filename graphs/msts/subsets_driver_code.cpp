#include "subsets.h"
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char const *argv[])
{
    int N = 13;
    subset *subsets = new subset[(N * sizeof(subset))];

    // Initialize
    for (int i = 0; i < N; i++)
    {
        subsets[i].rank = 0;
        subsets[i].parent = i;
    }

    // Codigo aqui
    for (int i = 1; i < 7; i++)
    {
        mergeSubSets(subsets, 2 * i - 1, 2 * i);
    }

    mergeSubSets(subsets, 4, 11);
    mergeSubSets(subsets, 2, 9);
    mergeSubSets(subsets, 1, 6);
    mergeSubSets(subsets, 11, 5);
    findSubSetRoot(subsets, 3);

    // Final Print
    printSubSets(subsets, N);
    return 0;
}