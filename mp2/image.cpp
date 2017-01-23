#include "image.h"
using namespace std;

void Image::flipleft() {
    int width = this->width();
    int height = this->height();
    int tmp;
    for (int x = 0; x < width / 2; x++) {
        for (int y = 0; y < height; y++) {
            tmp = (*this)(x, y)->red;
            (*this)(x, y)->red = (*this)(width - 1 - x, y)->red;
            (*this)(width - 1 - x, y)->red = tmp;
            tmp = (*this)(x, y)->green;
            (*this)(x, y)->green = (*this)(width - 1 - x, y)->green;
            (*this)(width - 1 - x, y)->green = tmp;
            tmp = (*this)(x, y)->blue;
            (*this)(x, y)->blue = (*this)(width - 1 - x, y)->blue;
            (*this)(width - 1 - x, y)->blue = tmp;
        }
    }
}


void Image::adjustbrightness(int r, int g, int b){
    int width = this->width();
    int height = this->height();
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height;y++) {
            int red = (*this)(x, y)->red + r;
            (*this)(x, y)->red = max(0, min(red, 255));
            int green = (*this)(x, y)->green + g;
            (*this)(x, y)->green = max(0, min(green, 255));
            int blue = (*this)(x, y)->blue + b;
            (*this)(x, y)->blue = max(0, min(blue, 255));
        }
    }
}

void Image::invertcolors() {
    int width = this->width();
    int height = this->height();
    for (int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            (*this)(x, y)->red = 255 - (*this)(x, y)->red;
            (*this)(x, y)->green = 255 - (*this)(x, y)->green;
            (*this)(x, y)->blue = 255 - (*this)(x, y)->blue;
        }
    }
}
