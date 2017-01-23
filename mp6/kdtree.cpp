/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include<iostream>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if (first[curDim] < second[curDim])
        return true;
    else if (first[curDim] > second[curDim])
        return false;
    else 
        return first < second;

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    int diff = distance(potential, target) - distance(currentBest, target);
    if (diff < 0)
        return true;
    else if (diff > 0)
        return false;
    else
        return potential < currentBest;

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    for (auto p : newPoints)
        points.push_back(p);
    buildTree(0, points.size() - 1, 0);
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNearestNeighbor(query, 0, points.size() - 1, 0);
}

template <int Dim>
int KDTree<Dim>::distance(const Point<Dim>& first,
                                const Point<Dim>& second) const
{
    int res = 0;
    for (int i = 0; i < Dim; i++) {
        res += (first[i] - second[i]) * (first[i] - second[i]);
    }
    return res;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & pts, int left, int right, int pivotIndex, int curDim) {
    Point<Dim> pivotValue = pts[pivotIndex];
    pts[pivotIndex] = pts[right];
    pts[right] = pivotValue;
    int storeidx = left;
    for (int i = left; i < right; i++) {
        if (smallerDimVal(pts[i], pivotValue, curDim)) {
            Point<Dim> tmp = pts[storeidx];
            pts[storeidx] = pts[i];
            pts[i] = tmp;
            storeidx++;
        }
    }
    pts[right] = pts[storeidx];
    pts[storeidx] = pivotValue;
    return storeidx;
}

template <int Dim>
void KDTree<Dim>::select(vector<Point<Dim>> & pts, int left, int right, int curDim, int n) {
    if (left == right)
        return;
    int pivotIndex = (left + right) / 2;
    pivotIndex = partition(pts, left, right, pivotIndex, curDim);
    if (pivotIndex == n)
        return;
    else if (n < pivotIndex) 
        select(pts, left, pivotIndex - 1, curDim, n);
    else
        select(pts, pivotIndex + 1, right, curDim, n);
}


template <int Dim>
void KDTree<Dim>::buildTree(int left, int right, int curDim) {
    if (left >= right)
        return;
    //printTree(cout);
    select(points, left, right, curDim, (left + right) /2);
    int mid = (left + right) / 2;
    buildTree(left, mid - 1, (curDim + 1) % Dim);
    buildTree(mid + 1, right, (curDim + 1) % Dim);
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int left, int right, int curDim) const {
    Point<Dim> currentBest;
    if (left >= right) {
        return points[left];
    }
    int mid = (left + right) / 2;
    bool lefttree = true;
    if (smallerDimVal(query, points[mid], curDim)) {
        currentBest = findNearestNeighbor(query, left, mid - 1, (curDim + 1) % Dim);
    }
    else {
        lefttree = false;
        currentBest = findNearestNeighbor(query, mid + 1, right, (curDim + 1) % Dim);
    }
    if (shouldReplace(query, currentBest, points[mid])) {
        currentBest = points[mid];
    }
    int curDistance = distance(query, currentBest);
    int planeDistance = (query[curDim] - points[mid][curDim]) * (query[curDim] - points[mid][curDim]);
    if (planeDistance <= curDistance) {
        Point<Dim> otherBest;
        if (lefttree)
            otherBest = findNearestNeighbor(query, mid + 1, right, (curDim + 1) % Dim);
        else
            otherBest = findNearestNeighbor(query, left, mid - 1, (curDim + 1) % Dim);
        if (shouldReplace(query, currentBest, otherBest))
            currentBest = otherBest;
    }
    return currentBest;
}

