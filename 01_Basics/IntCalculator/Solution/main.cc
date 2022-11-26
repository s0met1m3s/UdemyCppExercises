#include <cmath>
#include <cstdint>
#include <iostream>

std::uint32_t modulo(std::uint32_t number_a, std::uint32_t number_b);

std::uint32_t sum_of_digits(std::uint32_t number);

std::uint32_t cross_sum(std::uint32_t number);

int main()
{
    std::uint32_t input_number = 0;

    std::cout << "Please enter a unsinged integer: ";
    std::cin >> input_number;

    std::cout << input_number << " % 3: " << modulo(input_number, 3) << '\n';
    std::cout << "sum_of_digits: " << sum_of_digits(input_number) << '\n';
    std::cout << "cross_sum: " << cross_sum(input_number) << '\n';
}

std::uint32_t modulo(std::uint32_t number_a, std::uint32_t number_b)
{
    std::uint32_t result = 0;
    std::uint32_t divisor = number_a / number_b;

    result = number_a - number_b * divisor;

    return result;
}

std::uint32_t sum_of_digits(std::uint32_t number)
{
    std::uint32_t num_digits = 0;

    while (number > 0)
    {
        number /= 10;
        num_digits++;
    }

    return num_digits;
}

std::uint32_t cross_sum(std::uint32_t number)
{
    std::uint32_t sum = 0;

    while (number > 0)
    {
        std::uint32_t current_digit = number % 10;

        sum += current_digit;

        number /= 10;
    }

    return sum;
}
