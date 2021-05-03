#include <bits/stdc++.h>
#include <string.h>

using namespace std;
#define RANGE 255

void countSort(char arr[])
{
    char output[strlen(arr)];

    int count[RANGE + 1];
    memset(count, 0, sizeof(count));

    for (int i = 0; arr[i]; ++i)
        ++count[arr[i]];

    for (int i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];

    for (int i = 0; arr[i]; ++i)
    {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    for (int i = sizeof(arr) - 1; i >= 0; --i)
    {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }

    for (int i = 0; arr[i]; ++i)
        arr[i] = output[i];
}

// Driver  code
int main()
{
    char arr[] = "geeksforgeeks";

    countSort(arr);

    cout << "Sorted character array is " << arr;
    return 0;
}