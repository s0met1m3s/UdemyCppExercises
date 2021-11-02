#include <iostream>

#include "Image.h"

int main()
{
    Image image1(400, 400);

    image1.resize_image(500, 300);
    image1.fill_image(125);
    // image1.draw_rectangle(100, 100, 200, 200, 255);
    image1.draw_circle(200, 200, 10, 255);
    image1.save_image("image.bmp");

    return 0;
}
