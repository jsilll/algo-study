#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>

using namespace std;

class Heap
{
    vector<int> vec;

    int parent(int i);
    int left(int i);
    int right(int i);
    void swap(int i, int j);
    void buildMaxHeap();
    void maxHeapify(int i);

public:
    Heap();
    Heap(vector<int> _vec);
    ~Heap();

    // Basic operations
    int getSize();
    int extractMax();
    int getMax();
    void increaseKey(int i, int key);
    void printHeap();

    // Algos
    vector<int> heapSort();
};

Heap::Heap()
{
    vec = vector<int>();
}

Heap::~Heap()
{
    vec.clear();
}

Heap::Heap(vector<int> _vec)
{
    vec = vector<int>(_vec.size(), 0);
    for (int i = 0; i < _vec.size(); i++)
    {
        vec[i] = _vec[i];
    }
    buildMaxHeap();
}

// For any heap A[Parent(i)] >= A[i]
int Heap::parent(int i)
{
    return (i - 1) / 2;
}

int Heap::left(int i)
{
    return 2 * i + 1;
}

int Heap::right(int i)
{
    return 2 * i + 2;
}

void Heap::swap(int i, int j)
{
    int aux = vec[i];
    vec[i] = vec[j];
    vec[j] = aux;
}

// Transforms the tree with root i into a heap
void Heap::maxHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < vec.size() && vec[l] > vec[i])
    {
        largest = l;
    }

    if (r < vec.size() && vec[r] > vec[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        swap(i, largest);
        maxHeapify(largest);
    }
}

void Heap::buildMaxHeap()
{
    for (int i = vec.size() / 2; i >= 0; i--)
    {
        maxHeapify(i);
    }
}

int Heap::getSize()
{
    if (!vec.empty())
    {
        return vec[0];
    }
    return -1;
}

int Heap::getMax()
{
    return vec.size();
}

int Heap::extractMax()
{
    if (!vec.empty())
    {
        int max = vec[0];
        vec[0] = vec[vec.size() - 1];
        vec.erase(vec.end() - 1);
        maxHeapify(0);
        return max;
    }
    return -1;
}

void Heap::increaseKey(int i, int key)
{
    if (i < vec.size())
    {
        vec[i] = key;
        while (i > 0 && vec[parent(i)] < vec[i])
        {
            swap(i, parent(i));
            i = parent(i);
        }
    }
}

vector<int> Heap::heapSort()
{
    vector<int> sort(vec.size(), -1);

    for (int i = vec.size() - 1; i >= 0; i--)
    {
        sort[i] = extractMax();
        maxHeapify(0);
    }

    return sort;
}

void Heap::printHeap()
{
    for (vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
}

#endif