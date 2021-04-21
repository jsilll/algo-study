#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

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

#endif