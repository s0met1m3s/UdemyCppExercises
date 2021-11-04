#include <iostream>

#include "utils.hpp"

bool all_of(int *array, std::size_t length, int value);
bool any_of(int *array, std::size_t length, int value);
bool none_of(int *array, std::size_t length, int value);
std::size_t count(int *array, std::size_t length, int value);
int *inclusive_scan(int *array, std::size_t length);

int main()
{
    int array[] = {3, 1, 4, 1, 5, 9, 2, 6};
    std::size_t length = 8;

    std::cout << std::boolalpha;
    std::cout << "all_of: " << all_of(array, length, 5) << std::endl;
    std::cout << "any_of: " << any_of(array, length, 5) << std::endl;
    std::cout << "none_of: " << none_of(array, length, 5) << std::endl;
    int *Scan_values = inclusive_scan(array, length);
    std::cout << "inclusive_scan: " << std::endl;
    print_array(Scan_values, length);

    delete[] Scan_values;
    Scan_values = nullptr;

    return 0;
}


bool all_of(int *array, std::size_t length, int value)
{
    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] != value)
        {
            return false;
        }
    }

    return true;
}

bool any_of(int *array, std::size_t length, int value)
{
    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            return true;
        }
    }

    return false;
}

bool none_of(int *array, std::size_t length, int value)
{
    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            return false;
        }
    }

    return true;
}

std::size_t count(int *array, std::size_t length, int value)
{
    std::size_t temp = 0;

    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            temp++;
        }
    }

    return temp;
}

int *inclusive_scan(int *array, std::size_t length)
{
    int *Result = new int[length]{};

    Result[0] = array[0];

    for (std::size_t i = 1; i < length; i++)
    {
        Result[i] = Result[i - 1] + array[i];
    }

    return Result;
}
