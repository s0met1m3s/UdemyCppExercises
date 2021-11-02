#include <iostream>

#include "utils.hpp"

bool allOf(int *Array, std::size_t Length, int Value);
bool anyOf(int *Array, std::size_t Length, int Value);
bool noneOf(int *Array, std::size_t Length, int Value);
std::size_t count(int *Array, std::size_t Length, int Value);
int *inclusiveScan(int *Array, std::size_t Length);

int main()
{
    int Array[] = {3, 1, 4, 1, 5, 9, 2, 6};
    std::size_t Length = 8;

    std::cout << std::boolalpha;
    std::cout << "allOf: " << allOf(Array, Length, 5) << std::endl;
    std::cout << "anyOf: " << anyOf(Array, Length, 5) << std::endl;
    std::cout << "noneOf: " << noneOf(Array, Length, 5) << std::endl;
    int *ScanValues = inclusiveScan(Array, Length);
    std::cout << "inclusiveScan: " << std::endl;
    printArray(ScanValues, Length);

    delete[] ScanValues;
    ScanValues = nullptr;

    return 0;
}


bool allOf(int *Array, std::size_t Length, int Value)
{
    for (std::size_t i = 0; i < Length; i++)
    {
        if (Array[i] != Value)
        {
            return false;
        }
    }

    return true;
}

bool anyOf(int *Array, std::size_t Length, int Value)
{
    for (std::size_t i = 0; i < Length; i++)
    {
        if (Array[i] == Value)
        {
            return true;
        }
    }

    return false;
}

bool noneOf(int *Array, std::size_t Length, int Value)
{
    for (std::size_t i = 0; i < Length; i++)
    {
        if (Array[i] == Value)
        {
            return false;
        }
    }

    return true;
}

std::size_t count(int *Array, std::size_t Length, int Value)
{
    std::size_t Temp = 0;

    for (std::size_t i = 0; i < Length; i++)
    {
        if (Array[i] == Value)
        {
            Temp++;
        }
    }

    return Temp;
}

int *inclusiveScan(int *Array, std::size_t Length)
{
    int *Result = new int[Length]{};

    Result[0] = Array[0];

    for (std::size_t i = 1; i < Length; i++)
    {
        Result[i] = Result[i - 1] + Array[i];
    }

    return Result;
}
