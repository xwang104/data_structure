/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 * */
#include<iostream>
using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node* tmp = t->right;
    t->right = tmp->left;
    tmp->left = t;
    t->height--;
    t = tmp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node* tmp = t->left;
    t->left = tmp->right;
    tmp->right = t;
    t->height --;
    t = tmp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if (subtree == NULL) 
        return;
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balance == -2) {
        int leftBalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (leftBalance == -1){
           // cout << subtree->key << endl;
           // cout << heightOrNeg1(subtree->right) <<endl;
           // cout << heightOrNeg1(subtree->left) << endl;
            rotateRight(subtree);
        }
        else 
            rotateLeftRight(subtree);
    }
    else if (balance == 2) {
        int rightBalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (rightBalance == 1) {
           // cout << subtree->key << endl;
           // cout << heightOrNeg1(subtree->right) <<endl;
           // cout << heightOrNeg1(subtree->left) << endl; 
            rotateLeft(subtree);
        }
        else
            rotateRightLeft(subtree);
    }
    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL) {
        subtree = new Node(key, value);
    }
    else if (key < subtree->key) {
        insert(subtree->left, key, value);
    }
    else if (key > subtree->key) {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* & iop = rightMostChild(subtree->left);
            swap(subtree, iop);
            remove(iop, key);
        } else {
            /* one-child remove */
            Node* tmp = subtree;
            if (subtree->left == NULL)
                subtree = subtree->right;
            else 
                subtree = subtree->left;
            delete tmp;
        }
    }
    rebalance(subtree);
}

template <class K, class V>
typename AVLTree<K, V>::Node* & AVLTree<K, V>::rightMostChild(Node* & subRoot) {
    if (subRoot->right == NULL)
        return subRoot;
    else
        return rightMostChild(subRoot->right);
}
