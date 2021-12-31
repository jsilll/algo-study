#include <iostream>
#include <list>
#include <cstring>

using namespace std;

// Hashtable to implement 905, Jimmy

class HashTable
{
private:
    static const int hashGroups = 10;
    list<pair<int, string>> table[hashGroups]; // List 1, index 0; List 2, index 1 ...
public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};

bool HashTable::isEmpty() const
{
    int sum{};
    for (int i{}; i < hashGroups; i++)
    {
        sum += table[i].size();
    }

    return sum == 0;
}

int HashTable::hashFunction(int key)
{
    return key % hashGroups;
}

void HashTable::insertItem(int key, string value)
{
    int hashValue = hashFunction(key);
    auto &cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++)
    {
        if (bItr->first == key)
        {
            keyExists = true;
            bItr->second = value;
            cout << "[WARNING] key exists. Value replaced." << endl;
            break;
        }
    }

    if (!keyExists)
    {
        cell.emplace_back(key, value);
    }

    return;
}

void HashTable::removeItem(int key)
{
    int hashValue = hashFunction(key);
    auto &cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++)
    {
        if (bItr->first == key)
        {
            keyExists = true;
            bItr = cell.erase(bItr);
            cout << "[WARNING] Pair removed." << endl;
            break;
        }
    }

    if (!keyExists)
    {
        cout << "[WARNING] Key not found. Pair not removed." << endl;
    }

    return;
}

void HashTable::printTable()
{
    for (int i{}; i < hashGroups; i++)
    {
        if (table[i].size() == 0)
        {
            continue;
        }

        for (pair<int, string> p : table[i])
        {
            cout << "[INFO] Key: " << p.first << " Value: " << p.second << endl;
        }
    }
}