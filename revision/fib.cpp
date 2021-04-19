#include <iostream>

using namespace std;

int fib1(int n)
{
    if (n == 1 || n == 0)
    {
        return 1;
    }
    else
    {
        return fib1(n - 1) + fib1(n - 2);
    }
}

int fib2(int n)
{
    if (n == 1 || n == 0)
        return 1;

    int buff[n];
    buff[0] = 1;
    buff[1] = 1;

    for (int i; i <= n; i++)
    {
        buff[i] = buff[i - 1] + buff[i - 2];
    }

    return buff[n];
}

int fib3(int n)
{
    if (n == 1 || n == 0)
    {
        return 1;
    }
    int p, c = 1;
    int fib;
    for (int i = 2; i <= n; i++)
    {
        fib = p + c;
        p = c;
        c = fib;
    }
}

int main(int argc, char const *argv[])
{
    // cout << fib1(100) << endl;
    // cout << fib2(100) << endl;
    // cout << fib3(100) << endl;
    return 0;
}
