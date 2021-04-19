#include <iostream>
#include "array_utils.h"

using namespace std;

// For any heap A[Parent(i)] >= A[i]
int parent(int i)
{
    return i / 2;
}

int left(int i)
{
    return 2 * 1;
}

int right(int i)
{
    return 2 * i + 1;
}

// Transforms the tree with root i into a heap
void maxHeapify(int arr[], int i, int j)
{
    int l = left(i);
    int r = right(i);
    int largest = -1;

    if (l <= j && arr[l] > arr[i])
    {
        largest = l;
    }

    else
    {
        largest = i;
    }

    if (r <= j && arr[r] > arr[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        swap(arr, i, largest);
        maxHeapify(arr, largest, j);
    }
}

void buildMaxHeap(int arr[], int l, int r)
{
    for (int i = (r - l) / 2; i = l; i--)
    {
        maxHeapify(arr, i, r);
    }
}

void heapSort(int arr[], int l, int r)
{
    int heap_size = r;
    buildMaxHeap(arr, l, r);
    for (int i = r; i > 0; i--)
    {
        swap(arr, 0, i);
        maxHeapify(arr, 0, --heap_size);
    }
}

int heapMaximum(int arr[])
{
    return arr[0];
}

int heapExtractMax(int arr[], int l, int *r)
{
    int max = arr[0];
    arr[1] = arr[*r];
    *r--;
    maxHeapify(arr, 0, *r);
    return max;
}

void heapIncreaseKey(int arr[], int i, int key)
{
    arr[i] = key;
    while (i > 0 && arr[parent(i)] < arr[i])
    {
        swap(arr, i, parent(i));
        i = parent(i);
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    heapSort(arr, 0, 5);
    printArray(arr, 5);
    return 0;
}
