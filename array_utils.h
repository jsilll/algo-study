#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <iostream>
#include <climits>

using namespace std;

void printArray(int *A, int size)
{
    for (int i = 0; i <= size; i++)
    {
        if (A[i] != INT_MAX)
        {
            cout << A[i] << " ";
        }
        else
        {
            cout << "i ";
        }
    }
    cout << endl;
}

void fillMatrixDiag(int **M, int n, int m)
{
    for (int i = 0; i <= n; i++)
    {
        M[i][i] = m;
    }
}

void printMatrix(int **M, int n, int m)
{
    for (int i = 0; i <= n; i++)
    {
        printArray(M[i], m);
    }
}

void swap(int arr[], int i, int j)
{
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

#endif