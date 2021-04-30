#ifndef PQ_COMPARE_H
#define PQ_COMPARE_H

// make_pair(d[v], v)
typedef pair<int, int> priorityPair;

class pq_LowestDistanceFirst_Lexical
{
public:
    bool operator()(priorityPair p1, priorityPair p2)
    {
        if (p1.first != p2.first)
        {
            return p1.first > p2.first;
        }

        return p1.second > p2.second;
    }
};

#endif