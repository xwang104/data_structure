#include "linkedlist.h"
#include <iostream>
using namespace std;

bool removeAt(LinkedList &mylist, int pos)
{
	// YOUR CODE HERE!
	Node* h = mylist.head;
        if (h == NULL)
            return 0;
        if (h -> next == NULL) {
            if (pos == 0) {
                delete h;
                mylist.head = NULL;
                return 1;
            }
            else 
                return 0;
        for (int i = 0; i < (pos - 1); i++) {
            if (h != NULL) {
                h = h -> next;
            }
            else
                return 0;
        }
            if (h -> next == NULL)
                return 0;
            Node* tmp = h -> next;
            h -> next = tmp -> next;
            delete tmp;
	return 1;
}
