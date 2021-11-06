#include <cmath>
#include <iomanip>
#include <iostream>

/**
 * @brief Calculates a series that converges to pi / 4.
 *
 * pi / 4 = sum from 0 to n: (1 / (4k + 1)) - (1 / (4k + 3))
 *
 * @return
 */
double calculate_pi(std::uint32_t Num_iterations);

void print_dec_to_bin(std::uint8_t value);

void print_dec_to_hex(std::uint8_t value);

int main()
{
    std::uint32_t Num_iterations = 100'000'000;
    double pi = 3.14159265358979323846;
    double pi_calculated = calculate_pi(Num_iterations);

    std::cout << std::setprecision(30);
    std::cout << "pi (calculated): " << pi_calculated << std::endl;
    std::cout << "pi (correct): " << pi << std::endl;

    std::uint8_t dec = 0b10001110;
    print_dec_to_bin(dec);

    std::uint8_t hex = 0x08;
    print_dec_to_hex(hex);
}

double calculate_pi(std::uint32_t Num_iterations)
{
    double result = 0.0;

    for (std::uint32_t k = 0; k < Num_iterations; k++)
    {
        result += (1.0 / (4.0 * k + 1.0)) - (1.0 / (4.0 * k + 3.0));
    }

    return result * 4.0;
}

void print_dec_to_bin(std::uint8_t value)
{
    printf("Binary: 0b");

    for (std::int8_t i = 7; i >= 0; i--)
    {
        std::uint8_t current_exponent = std::pow(2, i);

        if (current_exponent <= value)
        {
            printf("1");
            value -= current_exponent;
        }
        else
        {
            printf("0");
        }
    }

    printf("\n");
}

void print_dec_to_hex(std::uint8_t value)
{
    printf("Hex: 0x");

    for (std::int8_t i = 1; i >= 0; i--)
    {
        std::uint8_t current_exponent = std::pow(16, i);

        for (std::uint8_t j = 15; j >= 1; j--)
        {
            std::uint8_t temp = current_exponent * j;

            if (temp <= value)
            {
                printf("%X", j);

                value -= temp;
                break;
            }
        }
    }

    printf("\n");
}
