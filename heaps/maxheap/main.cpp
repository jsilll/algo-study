#include <iostream>
#include "maxheap.cpp"

using std::cout;
using std::endl;

int main()
{
    MaxHeap *PriorityQueue = new MaxHeap();

    if (PriorityQueue->isEmpty())
    {
        cout << "Yes, this is the correct answer" << endl;
    }
    else
    {
        cout << "We have a problem with our isEmpty function." << endl;
    }

    PriorityQueue->insertItem(10);
    PriorityQueue->insertItem(120);
    PriorityQueue->insertItem(34);
    PriorityQueue->insertItem(41);
    PriorityQueue->insertItem(5);
    cout << PriorityQueue->getMax() << endl;
    PriorityQueue->extractMax();
    cout << PriorityQueue->getMax() << endl;

    if (PriorityQueue->isEmpty())
    {
        cout << "We have a problem with our isEmpty function." << endl;
    }
    else
    {
        cout << "Yes, this is the correct answer" << endl;
    }

    return 0;
}