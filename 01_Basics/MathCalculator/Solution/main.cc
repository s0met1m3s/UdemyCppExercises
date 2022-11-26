#include <cmath>
#include <iomanip>
#include <iostream>

double calculate_pi(std::uint32_t num_iterations);

void print_dec_to_bin(std::uint8_t value);

int main()
{
    std::uint32_t num_iterations = 1'000'000;
    double pi = 3.14159265358979323846;
    double pi_calculated = calculate_pi(num_iterations);

    std::cout << std::setprecision(30);
    std::cout << "pi (calculated): " << pi_calculated << '\n';
    std::cout << "pi (correct): " << pi << '\n';

    std::uint8_t dec = 0b10001110;
    print_dec_to_bin(dec);
}

double calculate_pi(std::uint32_t num_iterations)
{
    double result = 0.0;

    for (std::uint32_t k = 0; k < num_iterations; k++)
    {
        result += (1.0 / (4.0 * k + 1.0)) - (1.0 / (4.0 * k + 3.0));
    }

    return result * 4.0;
}

void print_dec_to_bin(std::uint8_t value)
{
    std::cout << "Binary: 0b";

    for (std::int8_t i = 7; i >= 0; i--)
    {
        std::uint8_t current_exponent =
            static_cast<std::uint8_t>(std::pow(2, i));

        if (current_exponent <= value)
        {
            std::cout << "1";
            value -= current_exponent;
        }
        else
        {
            std::cout << "0";
        }
    }

    std::cout << "\n";
}
