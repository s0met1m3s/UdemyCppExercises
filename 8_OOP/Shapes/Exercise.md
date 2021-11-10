# Exercise

Implement the following classes.

```cpp
struct Shape
{
public:
    Shape() = default;
    ~Shape() noexcept = default;

    virtual double get_area() const = 0;
    double midpoint_distance(const Shape *other) const;
    virtual Coordiante get_midpoint() const = 0;
};

struct Circle : Shape
{
    Circle(std::uint32_t x_midpoint_, std::uint32_t y_midpoint_, std::uint32_t radius_);
    ~Circle() noexcept = default;

    virtual double get_area() const final;
    virtual Coordiante get_midpoint() const final;

    std::uint32_t x_midpoint;
    std::uint32_t y_midpoint;
    std::uint32_t radius;
};

struct Rectangle : Shape
{
    Rectangle(std::uint32_t x1_, std::uint32_t y1_, std::uint32_t x2_, std::uint32_t y2_);
    ~Rectangle() noexcept = default;

    virtual double get_area() const final;
    virtual Coordiante get_midpoint() const final;

    std::uint32_t x1;
    std::uint32_t y1;
    std::uint32_t x2;
    std::uint32_t y2;
};
```

Implement the member functions for the Shape, Rectangle, and Circle class.

## Main Function

```cpp
int main()
{
    Circle circle1(200, 200, 20);
    Circle circle2(250, 250, 20);

    Rectangle rectangle1(100, 100, 150, 150);
    Rectangle rectangle2(300, 300, 350, 350);

    std::cout << "Distance c1-c2: " << circle1.midpoint_distance(&circle2) << std::endl;
    std::cout << "Distance c1-r1: " << circle1.midpoint_distance(&rectangle1) << std::endl;
    std::cout << "Distance r1-r2: " << rectangle1.midpoint_distance(&rectangle2) << std::endl;
    std::cout << "Distance r1-x2: " << rectangle1.midpoint_distance(&circle2) << std::endl;

    return 0;
}
```
