#include <iostream>

#include "Image.hpp"
#include "Shape.hpp"

int main()
{
    Circle circle1(200, 200, 20);
    Circle circle2(250, 250, 20);

    Rectangle rectangle1(100, 100, 150, 150);
    Rectangle rectangle2(300, 300, 350, 350);

    std::cout << "Distance c1-c2: " << circle1.midpoint_distance(&circle2) << std::endl;
    std::cout << "Distance r1-r2: " << rectangle1.midpoint_distance(&rectangle2) << std::endl;

    Image image1(400, 400);
    image1.fill_image(125);

    image1.draw_rectangle(rectangle1, 255);
    image1.draw_circle(circle1, 255);
    image1.fill_rectangle(rectangle2, 255);
    image1.fill_circle(circle2, 255);
    image1.save_image("image.bmp");

    return 0;
}
