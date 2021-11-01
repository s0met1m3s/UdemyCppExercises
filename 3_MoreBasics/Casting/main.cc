#include <iostream>

double mean(int, int);

int main()
{
    int a = 1;
    int b = 3;

    double m = mean(a, b);
    std::cout << "mean: " << m << std::endl;

    return 0;
}

double mean(int a, int b)
{
    return (static_cast<double>(a) + static_cast<double>(b)) / 2.0;
}
