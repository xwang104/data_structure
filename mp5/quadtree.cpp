/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include <cstdint>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

#include "quadtree.h"
#include "png.h"

/*default constructor*/
Quadtree::Quadtree() {
    root = NULL;
}

/*constructor takes a PNG*/
Quadtree::Quadtree(PNG const & source, int resolution) {
    _constructTree(source, resolution);
}

/*copy constructor*/
Quadtree::Quadtree(Quadtree const & other) {
    root = _copy(other.root);
}

/*destructor*/
Quadtree::~Quadtree() {
    _clear();
}

/*assign operator*/
Quadtree const & Quadtree::operator= (Quadtree const & other) {
    if (this != &other) {
        _clear();
        root = _copy(other.root);
    }
    return *this;
}

/*build tree from a PNG*/
void Quadtree::buildTree(PNG const & source, int resolution) {
    _clear();
    _constructTree(source, resolution);
}

/*destroy everything*/
void Quadtree::_clear() {
    _clear(root);
    root = NULL;
}

/*destroy a subtree*/
void Quadtree::_clear(QuadtreeNode* current) {
    if (current != NULL) {
        _clear(current -> nwChild);
        _clear(current -> neChild);
        _clear(current -> swChild);
        _clear(current -> seChild);
        delete current;
    }
}

/*build tree from another tree*/
Quadtree::QuadtreeNode* Quadtree::_copy(const QuadtreeNode* current) {
    if (current == NULL) {
        return NULL;
    }
    else {
        QuadtreeNode* nw = _copy(current -> nwChild);
        QuadtreeNode* ne = _copy(current -> neChild);
        QuadtreeNode* sw = _copy(current -> swChild);
        QuadtreeNode* se = _copy(current -> seChild);
        QuadtreeNode* newNode = new QuadtreeNode(current -> element, nw, ne, sw, se, current -> resolution);
        return newNode;
    }

}


/*build tree from a PNG by making a vector of RGBAPixels first*/
void Quadtree::_constructTree(PNG const & source, int resolution) {
    if (resolution == 0) {
        _clear();
        return;
    }
    vector<QuadtreeNode*> nodes;
    for (int y = 0; y < resolution; y++) {
        for (int x = 0; x < resolution; x++) {
            nodes.push_back(new QuadtreeNode((*source(x, y)), NULL, NULL, NULL, NULL, 1));
        }
    }
    _constructTree(nodes, resolution, 1);
}

/*build tree from a vector of RGBAPixels*/
void Quadtree::_constructTree(vector<QuadtreeNode*> & nodes, int resolution, int level) {
    if (resolution == 0) {
        _clear();
        return;
    }
    if (resolution == 1) {
        root = nodes[0];
        return;
    }
    vector<QuadtreeNode*> newNodes;
    int newRes = resolution / 2;
    for (int i = 0; i < newRes; i++) {
        for (int j = 0; j < newRes; j++) {
            /*get nwNode position*/
            int nw_x = 2 * j;
            int nw_y = 2 * i;
            /*get the pointers to each of the four child*/
            QuadtreeNode* nw = nodes[nw_y * resolution + nw_x];
            QuadtreeNode* ne = nodes[nw_y * resolution + nw_x + 1];
            QuadtreeNode* sw = nodes[(nw_y + 1) * resolution + nw_x];
            QuadtreeNode* se = nodes[(nw_y + 1) * resolution + nw_x + 1];
            /*average color*/
            uint8_t red = ((nw -> element).red + (ne -> element).red + (sw -> element).red + (se -> element).red) / 4;
            uint8_t green = ((nw -> element).green + (ne -> element).green + (sw -> element).green + (se -> element).green) / 4;
            uint8_t blue = ((nw -> element).blue + (ne -> element).blue + (sw -> element).blue + (se -> element).blue) / 4;
            /*make a new node and push to the vector*/
            newNodes.push_back(new QuadtreeNode(RGBAPixel(red, green, blue), nw, ne, sw, se, pow(2, level)));
        }
    }
    _constructTree(newNodes, newRes, level + 1);
}

RGBAPixel Quadtree::getPixel(int x, int y) const {
    /*empty Quadtree*/
    if (root == NULL) {
        return RGBAPixel();
    }
    /*the supplied coordinates fall outside of the bounds of the underlying bitmap*/
    if (x >= root -> resolution || y >= root -> resolution) {
        return RGBAPixel();
    }
    /*search the Quadtree*/
    return getPixel(x, y, root);
}

/*get pixel from a subtree*/
RGBAPixel Quadtree::getPixel(int x, int y, QuadtreeNode* current) const {
    /*leaf node*/
    if (current -> nwChild == NULL) {
        return current -> element;
    }
    /*check internal nodes*/
    int res = current -> resolution;
    if (x < res / 2 && y < res / 2) {
        return getPixel(x, y, current -> nwChild);
    }
    else if (x >= res / 2 && y < res / 2) {
        return getPixel(x - res / 2, y, current -> neChild);
    }
    else if (x < res / 2 && y >= res / 2) {
        return getPixel(x, y - res / 2, current -> swChild);
    }
    else {
        return getPixel(x - res / 2, y - res / 2, current -> seChild);
    }
}

PNG Quadtree::decompress() const {
    if (root == NULL) {
        return PNG();
    }
    int size = root -> resolution;
    PNG picture(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            RGBAPixel color = getPixel(i, j);
            picture(i, j) -> red = color.red;
            picture(i, j) -> green = color.green;
            picture(i, j) -> blue = color.blue;
        }
    }
    return picture;
}

void Quadtree::clockwiseRotate() {
    clockwiseRotate(root);
}

void Quadtree::clockwiseRotate(QuadtreeNode* current) {
    if (current == NULL || current -> nwChild == NULL) {
        return;
    }
    clockwiseRotate(current -> nwChild);
    clockwiseRotate(current -> neChild);
    clockwiseRotate(current -> swChild);
    clockwiseRotate(current -> seChild);
    QuadtreeNode* tmp = current -> nwChild;
    current -> nwChild = current -> swChild;
    current -> swChild = current -> seChild;
    current -> seChild = current -> neChild;
    current -> neChild = tmp;
}

void Quadtree::prune(int tolerance) {
    prune(root, tolerance);
}

void Quadtree::prune(QuadtreeNode* current, int tolerance) {
    if (current == NULL || current -> nwChild == NULL) {
        return;
    }
    if (doPrune(current, current, tolerance)) {
        _clear(current -> nwChild);
        _clear(current -> neChild);
        _clear(current -> swChild);
        _clear(current -> seChild);
        current -> nwChild = NULL;
        current -> neChild = NULL;
        current -> swChild = NULL;
        current -> seChild = NULL;
    }
    else {
        prune(current -> nwChild, tolerance);
        prune(current -> neChild, tolerance);
        prune(current -> swChild, tolerance);
        prune(current -> seChild, tolerance);
    }
}

bool Quadtree::doPrune(QuadtreeNode* avg, QuadtreeNode* current, int tolerance) const {
    if (current == NULL) {
        return true;
    }
    if (current -> nwChild == NULL) {
        int diff = difference(avg -> element, current -> element);
        return (diff <= tolerance);
    }
    else {
        return (doPrune(avg, current -> nwChild, tolerance) && doPrune(avg, current -> neChild, tolerance)\
         && doPrune(avg, current -> swChild, tolerance) && doPrune(avg, current -> seChild, tolerance));
    }
}

int Quadtree::difference(const RGBAPixel & a, const RGBAPixel & b) const {
    return (a.red - b.red) * (a.red - b.red) + (a.green - b.green) * (a.green - b.green) + (a.blue - b.blue) * (a.blue - b.blue);
}

int Quadtree::pruneSize(int tolerance) const {
    return pruneSize(root, tolerance);
}

int Quadtree::pruneSize(QuadtreeNode* current, int tolerance) const {
    if (current == NULL) {
        return 0;
    }
    if (current -> nwChild == NULL) {
        return 1;
    }
    if (doPrune(current, current, tolerance)) {
        return 1;
    }
    int cnt = 0;
    cnt += pruneSize(current -> nwChild, tolerance);
    cnt += pruneSize(current -> neChild, tolerance);
    cnt += pruneSize(current -> swChild, tolerance);
    cnt += pruneSize(current -> seChild, tolerance);
    return cnt;
}

int Quadtree::idealPrune(int numLeaves) const {
    int max = 3 * 255 * 255;
    return idealPrune(numLeaves, 0, max);
}

int Quadtree::idealPrune(int numLeaves, int beg, int end) const {
    while (beg + 1 < end) {
        int mid = (beg + end) / 2;
        int num = pruneSize(mid);
        if (num > numLeaves) {
            beg = mid + 1;
        }
        else {
            end = mid;
        }
    }
    if (pruneSize(beg) <= numLeaves)
        return beg;
    else 
        return end;
}

