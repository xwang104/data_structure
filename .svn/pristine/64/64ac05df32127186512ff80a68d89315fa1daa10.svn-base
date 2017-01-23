#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
using namespace std;

/* STL Sets have several methods you may (or may not) need:
 *
 * begin() -- return iterator from beginning
 * count(x) -- return number of instances of x in the set (will be 0 or 1)
 * insert(x) -- insert an element x into the set
 * erase(x) -- remove an element x from the set
 * empty() -- test if the set is empty
 * size() -- return number of elements in set
 */

set<string> findNeighbors(string curr,  set<string>& numList)
{
    set<string> neighbors;
    int N = curr.size();
    for(int i = 0; i < N; i++)
    {
        for(char c = '0'; c <= '9'; c++)
        {
            if(c == curr[i])
                continue;
            string oneChange = curr.substr(0,i) + (c) + curr.substr(i+1);
            if(numList.count(oneChange))
            {
                neighbors.insert(oneChange);
                numList.erase(oneChange);
            }
        }
    }
    return neighbors;
}

int sequenceLength(string beginNumber, string endNumber, set<string>& numList) {

    // YOUR CODE HERE!
    if (beginNumber == endNumber)
        return 1;
    vector<string> q;
    q.insert(q.begin(), beginNumber);

    set<string> visited;
    visited.insert(beginNumber);

    map<string, string> parent;

    while (!q.empty()) {
    	int size = q.size();
        string num = q[size - 1];
        q.pop_back();
        set<string> neighbors = findNeighbors(num, numList);
        for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
            string neib = *it;
            if (visited.count(neib) == 0) {
                q.insert(q.begin(), neib);
                visited.insert(neib);
                parent[neib] = num;
            }
        }
    }

    int cnt = 2;
    string tmp = endNumber;
    while (parent[tmp] != beginNumber) {    
        tmp = parent[tmp];
        cnt++;    
    }
    return cnt;
}
