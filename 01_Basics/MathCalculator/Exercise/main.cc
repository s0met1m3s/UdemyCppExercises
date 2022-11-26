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
