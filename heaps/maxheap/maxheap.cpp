#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class MaxHeap
{
private:
    int _size{};
    vector<int> vect = {-1};

    int p(int i) { return i >> 1; };       // i // 2
    int l(int i) { return i << 1; };       // i * 2
    int r(int i) { return (i << 1) + 1; }; // i * 2 + 1

public:
    bool isEmpty() const { return _size == 0; };
    int getMax() const { return vect[1]; };
    void insertItem(int val);
    void shiftUp(int i);
    int extractMax();
    void shiftDown(int i);
    void printMaxHeap();
};

void MaxHeap::shiftUp(int i)
{
    if (i > _size)
    {
        return;
    }
    if (i == 1)
    {
        return;
    }
    if (vect[i] > vect[p(i)])
    {
        std::swap(vect[p(i)], vect[i]);
    }
    shiftUp(p(i));
}

void MaxHeap::insertItem(int val)
{
    if (_size + 1 >= vect.size())
    {
        vect.push_back(0);
    }
    vect[++_size] = val;
    shiftUp(_size);
    return;
}

void MaxHeap::shiftDown(int i)
{
    if (i > _size)
    {
        return;
    }

    int swapId = i;

    if (l(i) <= _size && vect[i] < vect[l(i)])
    {
        swapId = l(i);
    }

    if (r(i) <= _size && vect[swapId] < vect[r(i)])
    {
        swapId = r(i);
    }

    if (swapId != i)
    {
        std::swap(vect[i], vect[swapId]);
        shiftDown(swapId);
    }
    return;
}

int MaxHeap::extractMax()
{
    int maxNum = vect[1];
    std::swap(vect[1], vect[_size--]);
    shiftDown(1);
    return maxNum;
}

void MaxHeap::printMaxHeap()
{
    for (int i : vect)
    {
        cout << i << " ";
    }
    cout << endl;
}