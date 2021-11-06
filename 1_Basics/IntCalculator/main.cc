#include <iostream>

std::uint32_t Modulo(std::uint32_t number_a, std::uint32_t number_b);
std::uint32_t Sum_of_digits(std::uint32_t number);
std::uint32_t Cross_sum(std::uint32_t number);

int main()
{
    std::uint32_t Input_number = 0;

    std::cout << "Please enter a unsinged integer: ";
    std::cin >> Input_number;

    std::cout << Input_number << " % 3: " << Modulo(Input_number, 3) << std::endl;
    std::cout << "Sum_of_digits: " << Sum_of_digits(Input_number) << std::endl;
    std::cout << "Cross_sum: " << Cross_sum(Input_number) << std::endl;
}

std::uint32_t Modulo(std::uint32_t number_a, std::uint32_t number_b)
{
    std::uint32_t result = 0;
    std::uint32_t Divisor = number_a / number_b;

    result = number_a - number_b * Divisor;

    return result;
}

std::uint32_t Sum_of_digits(std::uint32_t number)
{
    std::uint32_t Num_digits = 0;

    while (number > 0)
    {
        number /= 10;
        Num_digits++;
    }

    return Num_digits;
}

std::uint32_t Cross_sum(std::uint32_t number)
{
    std::uint32_t Sum = 0;

    while (number > 0)
    {
        std::uint32_t Current_digit = number % 10;

        Sum += Current_digit;
        number /= 10;
    }

    return Sum;
}
