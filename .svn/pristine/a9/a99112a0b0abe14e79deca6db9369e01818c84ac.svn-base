#include "png.h"
#include "rgbapixel.h"
#include <iostream>
using namespace std;

int main() {
    PNG in("./in.png");
    PNG out(in.width(), in.height());
    RGBAPixel *ptr1, *ptr2;
    for (int x = 0; x < out.width(); x++) {
        for (int y = 0; y < out.height(); y++) {
            ptr1 = out(x, y);
            ptr2 = in(in.width() - 1 - x, in.height() - 1 - y);
            ptr1->red = ptr2->red;
            ptr1->green = ptr2->green;
            ptr1->blue = ptr2->blue;
            ptr1->alpha = ptr2->alpha;
        }
    }
    out.writeToFile("./out.png");
}
