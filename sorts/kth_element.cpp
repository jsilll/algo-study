#include <iostream>
#include "array_utils.h"

using namespace std;

int leftPartition(int arr[], int l, int r, int v)
{
    int i = l;
    for (int j = l; j <= r; j++)
    {
        if (arr[j] < v)
        {
            swap(arr, i, j);
            i++;
        }
    }

    return i;
}

int rightPartition(int arr[], int l, int r, int v)
{
    int i = l;
    for (int j = l; j <= r; j++)
    {
        if (arr[j] == v)
        {
            swap(arr, i, j);
            i++;
        }
    }
    return i;
}

void partition(int arr[], int l, int r, int v, int *i, int *j)
{
    *i = leftPartition(arr, l, r, v);
    *j = rightPartition(arr, *i, r, v);
}

int select(int arr[], int l, int r, int k)
{
    int v = arr[v];
    int i, j;
    partition(arr, l, r, v, &i, &j);
    if (k <= (i - l))
    {
        return select(arr, l, i, k);
    }
    else if (k <= (j - l))
    {
        return v;
    }
    else
    {
        return select(arr, j, r, k - (j - l));
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {5, 6, 7, 11, 12, 13};
    int v = arr[5];
    int i, j;
    cout << select(arr, 0, 5, 3) << endl;
    return 0;
}
