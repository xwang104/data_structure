#include "common.h"
#include "quadtree.h"
#include "rgbapixel.h"
#include "png.h"
#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

int Quadtree::tallyNeighbors(RGBAPixel const & target, 
    QuadtreeNode const * curNode, int tolerance) const {
    //YOUR CODE HERE
    if (curNode == NULL) 
        return 0;
    if (curNode -> nwChild == NULL) {
        int distance = 100;
        if (distance <= tolerance)
            return 1;
        else
            return 0;
    }
    else {
        return tallyNeighbors(target, curNode->nwChild, tolerance) + \
 tallyNeighbors(target, curNode->neChild, tolerance) + \
 tallyNeighbors(target, curNode->swChild, tolerance) + \
 tallyNeighbors(target, curNode->seChild, tolerance);
    }
}

void Quadtree::prunish(int tolerance, double percent) {
    //YOUR CODE HERE

} 

void Quadtree::prunish(QuadtreeNode * curNode, int tolerance, int res, double percent) {
    //YOUR CODE HERE
}
