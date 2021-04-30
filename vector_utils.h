#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include "graphs/letter_to_int.h"
#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> vec)
{
    for (vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++)
    {
        cout << *itr << ", ";
    }
    cout << endl;
}

void printVectori2l(vector<int> vec)
{
    for (vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++)
    {
        cout << i2l(*itr) << ", ";
    }
    cout << endl;
}

#endif