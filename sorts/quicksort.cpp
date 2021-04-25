#include <iostream>
#include "array_utils.h"

using namespace std;

int partition(int arr[], int l, int r)
{
    int v = arr[r];
    int i = l;
    for (int j = l; j < r; j++)
    {
        if (arr[j] <= v)
        {
            swap(arr, i, j);
            i++;
        }
    }
    swap(arr, i, r);
    return i;
}

void quickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = partition(arr, l, r);
        quickSort(arr, l, m - 1);
        quickSort(arr, m + 1, r);
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {5, 6, 7, 11, 12, 13};
    quickSort(arr, 0, 5);
    printArray(arr, 5);
    return 0;
}
