#include <iostream>
#include "../heaps/heap.h"
#include "../vector_utils.h"

using namespace std;

// Driver code for the heapsort, the algo is implemented in heap.h
int main(int argc, char const *argv[])
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Heap h(vec);
    printVector(h.heapSort());
    return 0;
}
