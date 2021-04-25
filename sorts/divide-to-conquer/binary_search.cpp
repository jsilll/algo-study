#include <iostream>

using namespace std;

int binarySearch(int arr[], int l, int r, int key)
{
    if (l <= r)
    {
        int m = (l + r) / 2;
        if (arr[m] == key)
        {
            return m;
        }

        if (arr[m] < key)
        {
            return binarySearch(arr, m + 1, r, key);
        }

        else
        {
            return binarySearch(arr, l, m - 1, key);
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    int arr[] = {5, 6, 7, 11, 12, 13};
    cout << binarySearch(arr, 0, 6 - 1, 13) << endl;
    return 0;
}
