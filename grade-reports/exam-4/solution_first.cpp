#include "common.h"
#include <iostream>
#include <algorithm>
#include <vector>
/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;
bool findPath(Node<int> *&subroot, int val, vector<Node<int>*> & path) {
//    cout << subroot -> data << val << endl;
    if (subroot == NULL) 
        return false;
    if (subroot -> data == val) {
        path.push_back(subroot);
        return true;
    }
    
    if (subroot -> left != NULL) {
        if (findPath(subroot->left, val, path)) {
            path.push_back(subroot);
            return true;
        }
    }
    if (subroot -> right != NULL) {
        if (findPath(subroot->right, val, path)) {
            path.push_back(subroot);
            return true;
        }
    }
    return false;
}

Node<int>* findLCA(Node<int> *&root, int val1, int val2)
{
	// YOUR CODE HERE!
    if (root == NULL)
        return NULL;
    vector<Node<int>*> path1;
    bool exist1 = findPath(root, val1, path1);
    vector<Node<int>*> path2;
    bool exist2 = findPath(root, val2, path2);
    //cout << (exist1) << endl;
    //cout << (exist2) << endl;
    if ((exist1 && exist2)) {
        cout << path1.size();
        cout << path2.size();
        int length = min(path1.size(), path2.size());
        int i;
        bool flg= false;
        for (i = 1; i < length; i++) {
            if (path1[path1.size() - i]->data != path2[path2.size() - i]->data) {
                cout << "not";
                break;
            }
        }
        cout << i << endl;
        if (flg)
            cout << "wrong" ;
        cout << i << endl;
        return path1[path1.size() - i + 1];    
    }
    else {
        return NULL;
    }
}

