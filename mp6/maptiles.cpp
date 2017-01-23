/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */

    vector<Point<3>> points;
    map<Point<3>, int> color_img_map;
    for (int i = 0; i < int(theTiles.size()); i++) {
        RGBAPixel avg =theTiles[i].getAverageColor();
        Point<3> imgavg(avg.red, avg.green, avg.blue);
        points.push_back(imgavg);
        color_img_map[imgavg] = i;
    }
    KDTree<3> tree(points);

    int rows = theSource.getRows();
    int cols = theSource.getColumns();
    MosaicCanvas* mosaic = new MosaicCanvas(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            RGBAPixel rgcolor = theSource.getRegionColor(i, j);
            Point<3> target(rgcolor.red, rgcolor.green, rgcolor.blue);
            Point<3> bestMatch = tree.findNearestNeighbor(target);
            int idx = color_img_map[bestMatch];
            mosaic->setTile(i, j, theTiles[idx]);
        }
    }
    return mosaic;

}

