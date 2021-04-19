#include <iostream>

using namespace std;

void printArray(int A[], int size)
{
    for (int i = 0; i <= size; i++)
        cout << A[i] << " ";
    cout << endl;
}

void swap(int arr[], int i, int j)
{
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}
