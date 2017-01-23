#include "rgbapixel.h"
RGBAPixel::RGBAPixel(){
    this->red=255;
    (*this).blue=255;
    green=255;
    alpha=255;
}
RGBAPixel::RGBAPixel(uint8_t red, uint8_t green, uint8_t blue){
    this->red=red;
    this->green=green;
    this->blue=blue;
    alpha = 255;
}
