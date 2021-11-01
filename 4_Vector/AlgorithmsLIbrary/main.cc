#include <iostream>
#include <vector>

#include "utils.h"

bool allOf(std::vector<int> &, int);
bool anyOf(std::vector<int> &, int);
bool noneOf(std::vector<int> &, int);
std::size_t count(std::vector<int> &, int);
std::vector<int> inclusiveScan(std::vector<int> &);

int main()
{
    auto Vector = std::vector<int>{3, 1, 4, 1, 5, 9, 2, 6};

    std::cout << std::boolalpha;
    std::cout << "allOf: " << allOf(Vector, 5) << std::endl;
    std::cout << "anyOf: " << anyOf(Vector, 5) << std::endl;
    std::cout << "noneOf: " << noneOf(Vector, 5) << std::endl;
    auto ScanValues = inclusiveScan(Vector);
    std::cout << "inclusiveScan: " << std::endl;
    printVector(ScanValues);

    return 0;
}

bool allOf(std::vector<int> &Vector, int Value)
{
    for (std::size_t i = 0; i < Vector.size(); i++)
    {
        if (Vector[i] != Value)
        {
            return false;
        }
    }

    return true;
}

bool anyOf(std::vector<int> &Vector, int Value)
{
    for (std::size_t i = 0; i < Vector.size(); i++)
    {
        if (Vector[i] == Value)
        {
            return true;
        }
    }

    return false;
}

bool noneOf(std::vector<int> &Vector, int Value)
{
    for (std::size_t i = 0; i < Vector.size(); i++)
    {
        if (Vector[i] == Value)
        {
            return false;
        }
    }

    return true;
}

std::size_t count(std::vector<int> &Vector, int Value)
{
    std::size_t Temp = 0U;

    for (std::size_t i = 0; i < Vector.size(); i++)
    {
        if (Vector[i] == Value)
        {
            Temp++;
        }
    }

    return Temp;
}

std::vector<int> inclusiveScan(std::vector<int> &Vector)
{
    auto Result = std::vector<int>(Vector.size(), 0);

    Result[0] = Vector[0];

    for (std::size_t i = 1; i < Vector.size(); i++)
    {
        Result[i] = Result[i - 1] + Vector[i];
    }

    return Result;
}
