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
double calculate_pi(std::uint32_t Num_iterations);

int main()
{
    std::uint32_t Num_iterations = 100'000'000;
    double Pi = 3.14159265358979323846;
    double Pi_calculated = calculate_pi(Num_iterations);

    std::cout << std::setprecision(30);
    std::cout << "PI (calculated): " << Pi_calculated << std::endl;
    std::cout << "PI (correct): " << Pi << std::endl;
}

double calculate_pi(std::uint32_t Num_iterations)
{
    double Result = 0.0;

    for (std::uint32_t k = 0; k < Num_iterations; k++)
    {
        Result += (1.0 / (4.0 * k + 1.0)) - (1.0 / (4.0 * k + 3.0));
    }

    return Result * 4.0;
}
