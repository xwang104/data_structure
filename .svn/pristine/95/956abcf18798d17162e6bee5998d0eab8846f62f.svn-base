/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include "png.h"

using namespace std;

class  SquareMaze
{
public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
private:
    struct MazeCell
    {
        bool down;
        bool right;
        MazeCell(bool down, bool right) : down(down), right(right) 
        {
        }
    };
    vector<MazeCell> _maze;
    int height;
    int width;
};

#endif
