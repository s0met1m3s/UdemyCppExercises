#include <iostream>

void printArray(int *, std::size_t);

bool allOf(int *, std::size_t, int);
bool anyOf(int *, std::size_t, int);
bool noneOf(int *, std::size_t, int);
std::size_t count(int *, std::size_t, int);
int *inclusiveScan(int *, std::size_t);

int main()
{
    int Values[] = {3, 1, 4, 1, 5, 9, 2, 6};
    std::size_t Length = 8;

    std::cout << std::boolalpha;
    std::cout << "allOf: " << allOf(Values, Length, 5) << std::endl;
    std::cout << "anyOf: " << anyOf(Values, Length, 5) << std::endl;
    std::cout << "noneOf: " << noneOf(Values, Length, 5) << std::endl;
    int *ScanValues = inclusiveScan(Values, Length);
    std::cout << "inclusiveScan: " << std::endl;
    printArray(ScanValues, Length);

    delete[] ScanValues;
    ScanValues = nullptr;

    return 0;
}

void printArray(int *Array, std::size_t Length)
{
    for (std::size_t i = 0; i < Length; i++)
    {
        std::cout << Array[i] << std::endl;
    }

    std::cout << std::endl;
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
    std::size_t Temp = 0U;

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
    int *Result = new int[Length];

    Result[0] = Array[0];

    for (std::size_t i = 1; i < Length; i++)
    {
        Result[i] = Result[i - 1] + Array[i];
    }

    return Result;
}
