#include <iostream>

std::uint32_t Modulo(std::uint32_t, std::uint32_t);
std::uint32_t SumOfDigits(std::uint32_t);
std::uint32_t CrossSum(std::uint32_t);

int main()
{
    std::uint32_t InputNumber;

    std::cout << "Please enter a unsinged integer: ";
    std::cin >> InputNumber;

    std::cout << InputNumber << " % 3: " << Modulo(InputNumber, 3) << std::endl;
    std::cout << "SumOfDigits: " << SumOfDigits(InputNumber) << std::endl;
    std::cout << "CrossSum: " << CrossSum(InputNumber) << std::endl;
}

std::uint32_t Modulo(std::uint32_t InputNumberA, std::uint32_t InputNumberB)
{
    std::uint32_t Result = 0;
    std::uint32_t Divisor = InputNumberA / InputNumberB;

    Result = InputNumberA - InputNumberB * Divisor;

    return Result;
}

std::uint32_t SumOfDigits(std::uint32_t InputNumber)
{
    std::uint32_t NumDigits = 0;

    while (InputNumber > 0)
    {
        InputNumber /= 10;
        NumDigits++;
    }

    return NumDigits;
}

std::uint32_t CrossSum(std::uint32_t InputNumber)
{
    std::uint32_t Sum = 0;

    while (InputNumber > 0)
    {
        std::uint32_t CurrentDigit = InputNumber % 10;

        Sum += CurrentDigit;
        InputNumber /= 10;
    }

    return Sum;
}
