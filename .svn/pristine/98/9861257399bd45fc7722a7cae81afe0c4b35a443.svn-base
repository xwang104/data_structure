/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        _nodes.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (_nodes[elem] < 0) return elem;
    else return _nodes[elem] = find(_nodes[elem]);
} 

void DisjointSets::setunion(int a, int b) {
    int root1 = find(a);
    int root2 = find(b);
    int newSize = _nodes[root1] + _nodes[root2];
    if (_nodes[root1] <= _nodes[root2]) {
        _nodes[root2] = root1;
        _nodes[root1] = newSize;
    }
    else {
        _nodes[root1] = root2;
        _nodes[root2] = newSize;
    }
}

