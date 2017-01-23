#include "linkedlist.h"

void merge(LinkedList* lst1,
           LinkedList* lst2,
           LinkedList* mrg)
{
	// YOUR CODE HERE!
	mrg = NULL;
	if (lst1 == NULL) {
            mrg->head = lst2->head;
            lst2 = NULL;
        }
        if (lst2 == NULL) {
            mrg->head = lst1->head;
            lst1 = NULL;
        }
        Node* a = lst1->head;
        Node* b = lst2->head;
        Node* prev = NULL;
        while (a != NULL and b != NULL) {
            if (a->data < b->data) {
                if (mrg == NULL) {
                    mrg = a;
                    a = a->next;
                    prev = mrg;
                }
                else {
                    prev -> next = a;
                    a = a -> next;
                    prev = prev -> next;
                }
            }
            else {
                if (mrg == NULL) {
                    mrg = b;
                    b = b->next;
                    prev = mrg;
                }
                else {
                    prev -> next = b;
                    b = b->next;
                    prev = prev -> next;
                }
            }
        }
        if (a != NULL) {
            prev -> next = a;
        }
        if (b != NULL) {
            prev -> next = b;
        }
        lst1 = NULL;
        lst2 = NULL;
	return;
}
