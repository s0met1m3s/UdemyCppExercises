#include <cmath>
#include <iomanip>
#include <iostream>

/**
 * @brief Calculates a series that converges to PI / 4.
 *
 * PI / 4 = Sum from 0 to n: (1 / (4k + 1)) - (1 / (4k + 3))
 *
 * @return
 */
double calculatePi(std::uint32_t NumIterations);

int main()
{
    std::uint32_t NumIterations = 100'000'000;
    double Pi = 3.14159265358979323846;
    double PiCalculated = calculatePi(NumIterations);

    std::cout << std::setprecision(30);
    std::cout << "PI (calculated): " << PiCalculated << std::endl;
    std::cout << "PI (correct): " << Pi << std::endl;
}

double calculatePi(std::uint32_t NumIterations)
{
    double Result = 0.0;

    for (std::uint32_t k = 0; k < NumIterations; k++)
    {
        Result += (1.0 / (4.0 * k + 1.0)) - (1.0 / (4.0 * k + 3.0));
    }

    return Result * 4.0;
}
