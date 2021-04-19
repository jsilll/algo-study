#include <iostream>

using namespace std;

int linearSearch(int arr[], int l, int r, int key)
{
    for (int i = l; i < r; i++)
    {
        if (arr[i] == key)
        {
            return i;
        }
    }

    return -1;
}

int main(int argc, char const *argv[])
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    cout << linearSearch(arr, 0, 6, 5) << endl;
    return 0;
}
