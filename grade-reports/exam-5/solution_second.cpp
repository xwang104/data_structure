#include <iostream>
#include <vector>
#include <set>
using namespace std;

int find(vector<int> uptree, int index)
{
    if (uptree[index]<=0)
      return index;
    else return find(uptree, uptree[index]);
}

int componentsUpTree(vector<int> uptree)
{
    // Your code here!
    int cnt = 0;
    for (int i = 0; i < uptree.size(); i++) {
        if (uptree[i] < 0)
            cnt++;
    }
    return cnt;
}

