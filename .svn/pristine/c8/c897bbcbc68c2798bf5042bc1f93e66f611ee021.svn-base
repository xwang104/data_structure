#include "common.h"
#include <iostream>
#include <queue>

/*
  As a reminder, useful STL queue methods include:
  empty : Test whether container is empty (public member function)
  size : Return size (public member function)
  front : Access next element (public member function)
  push : Insert element (public member function)
  pop : Remove next element (public member function)
*/

using namespace std;

int removeAt(queue<int> &q, int pos)
{
	// YOUR CODE HERE!
    if (pos < 0 || pos >= q.size())
        return -1;
    int res;
    int size = q.size();
    for (int i = 0; i < size; i++) {
        if (i == pos) {
            res = q.front();
            q.pop();
        }
        else {
            int tmp = q.front();
            q.pop();
            q.push(tmp);
        }
    }
    return res;
}
