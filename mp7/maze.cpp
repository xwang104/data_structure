/* Your code here! */
#include "dsets.h"
#include "maze.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "png.h"

using namespace std;

SquareMaze::SquareMaze() {
    _maze.clear();
    height = 0;
    width = 0;
}

// random generator function:
int myrandom (int i) { return std::rand()%i;}

void SquareMaze::makeMaze(int width, int height) {
    /*initialize the maze as square grid*/
    _maze.clear();
    this->height = height;
    this->width = width;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            _maze.push_back(MazeCell(true, true));
        }
    }

    /*make the maze as disjoint sets and each cell as a set*/
    int n = height * width;
    DisjointSets maze_cells;
    maze_cells.addelements(n);

    /*random_shuffle the walls*/
    vector<int> walls;
    for (int i = 0; i < 2 * n; i++) {
        walls.push_back(i);
    }
    srand( unsigned (time(0)));
    random_shuffle(walls.begin(), walls.end(), myrandom);
    for (int w : walls) {
        /*get the position of the cell*/
        int c = w % n;
        int d = w / n;
        int x = c % width;
        int y = c / width;
        /*skip perimeter of the grid*/
        if ((y == (height - 1) && d == 1) || (x == (width - 1) && d == 0))
            continue;
        if (d == 1) {
            int a = y * width + x;
            int b = (y + 1) * width + x;
            if (maze_cells.find(a) != maze_cells.find(b)) {
                _maze[a].down = false;
                maze_cells.setunion(a, b);
            }
        }
        else if (d == 0) {
            int a = y * width + x;
            int b = y * width + x + 1;
            if (maze_cells.find(a) != maze_cells.find(b)) {
                _maze[a].right = false;
                maze_cells.setunion(a, b);
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
        return false;
    if (dir == 0) {
        if (x > width - 2)
            return false;
        if (_maze[y * width + x].right == true)
            return false;
        else
            return true;
    }
    else if (dir == 1) {
        if (y > height - 2)
            return false;
        if (_maze[y * width + x].down == true)
            return false;
        else
            return true;
    }
    else if (dir == 2) {
        if (x < 1)
            return false;
        if (_maze[y * width + x - 1].right == true)
            return false;
        else
            return true;
    }
    else if (dir == 3) {
        if (y < 1)
            return false;
        if (_maze[(y - 1) * width + x].down == true)
            return false;
        else
            return true;
    }
    else {
        cout << "wrong input" << endl;
        return false;
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir == 0)
        _maze[y * width + x].right = exists;
    else if (dir == 1)
        _maze[y * width + x].down = exists;
    else
        cout << "wrong input" << endl;
}

vector<int> SquareMaze::solveMaze() {
    vector<int> res;
    /*make a struct to record the parent of the cell and the length to root*/
    struct PathInfo
    {
        int parent;
        int length;
        PathInfo() {parent = -1; length = 0;}
        PathInfo(int p, int l) {parent = p; length = l;}
    };
    /*initilize a path info vector and start from top-left cell*/
    vector<PathInfo> path_info;
    for (int i = 0; i < width * height; i++)
        path_info.push_back(PathInfo());
    /*initialize a visited vector*/
    vector<bool> visited;
    for (int i = 0; i < width * height; i++) 
        visited.push_back(false);
    /*make a queue for bfs*/
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        if (visited[c])
            continue;
        visited[c] = true;
        int x = c % width;
        int y = c / width;
        if (canTravel(x, y, 0) && !visited[y * width + x + 1]) {
            q.push(y * width + x + 1);
            path_info[y * width + x + 1] = PathInfo(c, path_info[c].length + 1);
        }
        if (canTravel(x, y, 1) && !visited[(y + 1) * width + x]) {
            q.push((y + 1) * width + x);
            path_info[(y + 1) * width + x] = PathInfo(c, path_info[c].length + 1);
        }
        if (canTravel(x, y, 2) && !visited[y * width + x - 1]) {
            q.push(y * width + x - 1);
            path_info[y * width + x - 1] = PathInfo(c, path_info[c].length + 1);
        }
        if (canTravel(x, y, 3) && !visited[(y - 1) * width + x]) {
            q.push((y - 1) * width + x);
            path_info[(y - 1) * width + x] = PathInfo(c, path_info[c].length + 1);
        }
    }

    int max_length = -1;
    int des = width;
    for (int x = width - 1; x >= 0; x--) {
        int tmp_length = path_info[(height - 1) * width + x].length;
        if (tmp_length >= max_length) {
            des = x;
            max_length = tmp_length;
        }
    }
    int cur = (height - 1) * width + des;
    while (true) {
        if (cur == 0)
            break;
        int pt = path_info[cur].parent;
        int cx = cur % width;
        int cy = cur / width;
        int px = pt % width;
        int py = pt / width;
        if (cx - px == 1)
            res.push_back(0);
        else if (cx - px == -1) 
            res.push_back(2);
        else if (cy - py == 1)
            res.push_back(1);
        else if (cy - py == -1)
            res.push_back(3);
        cur = pt;
    }
    reverse(res.begin(), res.end());
    return res;
}

PNG* SquareMaze::drawMaze() const {
    PNG* maze_pic = new PNG(width * 10 + 1, height * 10 + 1);
    for (int i = 0; i < height * 10 + 1; i++) {
        (*maze_pic)(0, i)->red = 0;
        (*maze_pic)(0, i)->green = 0;
        (*maze_pic)(0, i)->blue = 0;
    }
    for (int i = 10; i < width * 10 + 1; i++) {
        (*maze_pic)(i, 0)->red = 0;
        (*maze_pic)(i, 0)->green = 0;
        (*maze_pic)(i, 0)->blue = 0;        
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (_maze[y * width + x].right == true) {
                for (int i = 0; i < 11; i++) {
                    (*maze_pic)((x + 1) * 10, y * 10 + i)->red = 0;
                    (*maze_pic)((x + 1) * 10, y * 10 + i)->green = 0;
                    (*maze_pic)((x + 1) * 10, y * 10 + i)->blue = 0;                       
                }
            }
            if (_maze[y * width + x].down == true) {
                for (int i = 0; i < 11; i++) {
                    (*maze_pic)(x * 10 + i, (y + 1) * 10)->red = 0;
                    (*maze_pic)(x * 10 + i, (y + 1) * 10)->green = 0;
                    (*maze_pic)(x * 10 + i, (y + 1) * 10)->blue = 0;                       
                }                
            }
        }
    }
    return maze_pic;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* maz_sol = drawMaze();
    vector<int> solution = solveMaze();
    int x = 5;
    int y = 5;
    for (int dir : solution) {
        for (int i = 0; i < 10; i++) {
            (*maz_sol)(x, y)->red = 255;
            (*maz_sol)(x, y)->green = 0;
            (*maz_sol)(x, y)->blue = 0;
            if (dir == 0) x++;
            else if (dir == 1) y++;
            else if (dir == 2) x--;
            else if (dir == 3) y--;
        }
    }
    (*maz_sol)(x, y)->red = 255;
    (*maz_sol)(x, y)->green = 0;
    (*maz_sol)(x, y)->blue = 0;
    int exit_x = x / 10;
    for (int i = 1; i < 10; i++) {
        (*maz_sol)(exit_x * 10 + i, height * 10) -> red = 255;
        (*maz_sol)(exit_x * 10 + i, height * 10) -> green = 255;
        (*maz_sol)(exit_x * 10 + i, height * 10) -> blue = 255;
    }
    return maz_sol;
}

