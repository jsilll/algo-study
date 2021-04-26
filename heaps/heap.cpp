#include <iostream>

#include "heap.h"

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Heap h(vec);
    h.printHeap();
    cout << h.getMax() << endl;
    h.extractMax();
    h.printHeap();
    h.increaseKey(8, 10);
    h.printHeap();
    h.insert(20);
    h.printHeap();
    return 0;
}
