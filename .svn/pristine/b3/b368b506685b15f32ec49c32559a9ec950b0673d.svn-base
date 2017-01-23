#include "common.h"
#include <iostream>

using namespace std;

void updateDiff(Node<int> *&root)
{
	// YOUR CODE HERE!
    if (root == NULL || (root -> left == NULL && root -> right == NULL)) {
        return;
    }
    updateDiff(root -> left);
    updateDiff(root -> right);
    if (root -> left != NULL) {
        root -> data = root -> data - (root -> left -> data); 
    }
    if (root -> right != NULL) {
        root -> data = root -> data - (root -> right -> data);
    }
    return;
}
