#include <iostream>
#include "hash_table.cpp"

using std::cout;
using std::endl;

int main()
{
    HashTable HT;

    if (HT.isEmpty())
    {
        cout << "Correct answer. Good job" << endl;
    }
    else
    {
        cout << "Oh oh. We need to check out the code!" << endl;
    }

    HT.insertItem(905, "Jim");
    HT.insertItem(201, "Tom");
    HT.insertItem(332, "Bob");
    HT.insertItem(124, "Sally");
    HT.insertItem(107, "Sandy");
    HT.insertItem(929, "Barb");
    HT.insertItem(928, "Rob");
    HT.insertItem(928, "Rick");

    HT.printTable();

    HT.removeItem(332);
    HT.removeItem(100);

    if (HT.isEmpty())
    {
        cout << "Oh oh. We need to check out the code!" << endl;
    }
    else
    {
        cout << "Correct answer! Good job!" << endl;
    }

    return 0;
}