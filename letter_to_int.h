#ifndef LETTER_TO_INT_H
#define LETTER_TO_INT_H

#include <iostream>

using namespace std;

int l2i(char c)
{
    int ord = int(c);
    if (65 <= ord && ord <= 90)
    {
        return (ord - 65) % 26;
    }

    if (97 <= ord && ord <= 122)
    {
        return (ord - 97) % 26;
    }

    return -1;
}

char i2l(int i)
{
    return char(i + 65);
}

#endif