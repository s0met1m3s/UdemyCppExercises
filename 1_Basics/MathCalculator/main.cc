#include <cmath>
#include <iomanip>
#include <iostream>

double calculate_pi(std::uint32_t num_iterations);

void print_dec_to_bin(std::uint8_t value);

void print_dec_to_hex(std::uint8_t value);

int main()
{
    std::uint32_t num_iterations = 1'000'000;
    double pi = 3.14159265358979323846;
    double pi_calculated = calculate_pi(num_iterations);

    std::cout << std::setprecision(30);
    std::cout << "pi (calculated): " << pi_calculated << std::endl;
    std::cout << "pi (correct): " << pi << std::endl;

    std::uint8_t dec = 0b10001110;
    print_dec_to_bin(dec);

    std::uint8_t hex = 0x8E;
    print_dec_to_hex(hex);
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
        std::uint8_t current_exponent = std::pow(2, i);

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

void print_dec_to_hex(std::uint8_t value)
{
    std::cout << "Hex: 0x";

    for (std::int8_t i = 1; i >= 0; i--)
    {
        std::uint8_t current_exponent = std::pow(16, i);

        for (std::uint8_t j = 15; j >= 1; j--)
        {
            std::uint8_t temp = current_exponent * j;

            if (temp <= value)
            {
                std::cout << std::hex << std::uppercase << static_cast<std::uint32_t>(j) << std::dec;

                value -= temp;
                break;
            }
        }
    }

    std::cout << "\n";
}
