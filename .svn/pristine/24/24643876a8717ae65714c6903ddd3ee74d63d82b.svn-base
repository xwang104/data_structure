#ifndef IMAGE_H
#define IMAGE_H

#include "png.h"
class Image : public PNG
{
    public:
        Image():PNG() {}
        Image(size_t width, size_t height) : PNG(width, height) {}
        void flipleft();
        void adjustbrightness(int r, int g, int b);
        void invertcolors();
};
#endif
