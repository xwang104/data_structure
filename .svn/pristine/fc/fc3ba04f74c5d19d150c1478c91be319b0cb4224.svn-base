/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H
#include <vector>
#include "png.h"
using namespace std;

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:

    Quadtree();
    Quadtree(PNG const & source, int resolution);
    Quadtree(Quadtree const & other);
    ~Quadtree();
    Quadtree const & operator= (Quadtree const & other);
    void buildTree(PNG const & source, int resolution);
    RGBAPixel getPixel(int x, int y) const;
    PNG decompress() const;
    void clockwiseRotate();
    void prune(int tolerance);
    int pruneSize(int tolerance) const;
    int idealPrune(int numLeaves) const;

  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */

        int resolution = 0; /**resolution of their underlying bitmaps */

        QuadtreeNode() {
            nwChild = NULL;
            neChild = NULL;
            swChild = NULL;
            seChild = NULL;
        }
        QuadtreeNode(const RGBAPixel & elem, QuadtreeNode* nw, QuadtreeNode* ne, QuadtreeNode* sw, QuadtreeNode* se, int res) {
            element = elem;
            nwChild = nw;
            neChild = ne;
            swChild = sw;
            seChild = se;
            resolution = res;
        }
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    /*destroy everything */
    void _clear();
    /*destroy a subtree */
    void _clear(QuadtreeNode* current);
    /*build tree from another tree*/
    QuadtreeNode* _copy(const QuadtreeNode* current);
    /*build tree from a PNG*/
    void _constructTree(PNG const & source, int resolution);
    /*build tree from a vector of RGBPixels */
    void _constructTree(vector<QuadtreeNode*> & nodes, int resolution, int level);
    /*get pixel from a subtree */
    RGBAPixel getPixel(int x, int y, QuadtreeNode* current) const;
    /*rotate a subtree*/
    void clockwiseRotate(QuadtreeNode* current);
    /*prune a subtree*/
    void prune(QuadtreeNode* current, int tolerance);
    /*determine whether prune a subtree*/
    bool doPrune(QuadtreeNode* avg, QuadtreeNode* current, int tolerance) const;
    /*calculate color difference*/
    int difference(const RGBAPixel & a, const RGBAPixel & b) const;
    /*calculate the number of leaves after prune in a subtree*/
    int pruneSize(QuadtreeNode* current, int tolerance) const;
    /*binary search for tolerance*/
    int idealPrune(int numLeaves, int beg, int end) const;

/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif

