#include <iostream>

std::uint32_t Modulo(std::uint32_t NumberA, std::uint32_t NumberB);
std::uint32_t SumOfDigits(std::uint32_t Number);
std::uint32_t CrossSum(std::uint32_t Number);

int main()
{
    std::uint32_t InputNumber = 0;

    std::cout << "Please enter a unsinged integer: ";
    std::cin >> InputNumber;

    std::cout << InputNumber << " % 3: " << Modulo(InputNumber, 3) << std::endl;
    std::cout << "SumOfDigits: " << SumOfDigits(InputNumber) << std::endl;
    std::cout << "CrossSum: " << CrossSum(InputNumber) << std::endl;
}

std::uint32_t Modulo(std::uint32_t NumberA, std::uint32_t NumberB)
{
    std::uint32_t Result = 0;
    std::uint32_t Divisor = NumberA / NumberB;

    Result = NumberA - NumberB * Divisor;

    return Result;
}

std::uint32_t SumOfDigits(std::uint32_t Number)
{
    std::uint32_t NumDigits = 0;

    while (Number > 0)
    {
        Number /= 10;
        NumDigits++;
    }

    return NumDigits;
}

std::uint32_t CrossSum(std::uint32_t Number)
{
    std::uint32_t Sum = 0;

    while (Number > 0)
    {
        std::uint32_t CurrentDigit = Number % 10;

        Sum += CurrentDigit;
        Number /= 10;
    }

    return Sum;
}
