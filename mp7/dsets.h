/* Your code here! */
#ifndef DSETS_H
#define DSETS_H

#include <vector>
#include <iostream>
using namespace std;

class  DisjointSets 
{
public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
private:
    vector<int> _nodes;
};

#endif
