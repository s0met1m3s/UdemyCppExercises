#include <iostream>
#include <vector>

#include "utils.hpp"

bool all_of(const std::vector<int> &vector, const int value);
bool any_of(const std::vector<int> &vector, const int value);
bool none_of(const std::vector<int> &vector, const int value);
std::size_t count(const std::vector<int> &vector, const int value);
std::vector<int> inclusive_scan(const std::vector<int> &vector);

int main()
{
    auto vector = std::vector<int>{3, 1, 4, 1, 5, 9, 2, 6};

    std::cout << std::boolalpha;
    std::cout << "all_of: " << all_of(vector, 5) << std::endl;
    std::cout << "any_of: " << any_of(vector, 5) << std::endl;
    std::cout << "none_of: " << none_of(vector, 5) << std::endl;
    auto Scan_values = inclusive_scan(vector);
    std::cout << "inclusive_scan: " << std::endl;
    print_vector(Scan_values);

    return 0;
}

bool all_of(const std::vector<int> &vector, const int value)
{
    for (std::size_t i = 0; i < vector.size(); i++)
    {
        if (vector[i] != value)
        {
            return false;
        }
    }

    return true;
}

bool any_of(const std::vector<int> &vector, const int value)
{
    for (std::size_t i = 0; i < vector.size(); i++)
    {
        if (vector[i] == value)
        {
            return true;
        }
    }

    return false;
}

bool none_of(const std::vector<int> &vector, const int value)
{
    for (std::size_t i = 0; i < vector.size(); i++)
    {
        if (vector[i] == value)
        {
            return false;
        }
    }

    return true;
}

std::size_t count(const std::vector<int> &vector, const int value)
{
    std::size_t temp = 0;

    for (std::size_t i = 0; i < vector.size(); i++)
    {
        if (vector[i] == value)
        {
            temp++;
        }
    }

    return temp;
}

std::vector<int> inclusive_scan(const std::vector<int> &vector)
{
    auto Result = std::vector<int>(vector.size(), 0);

    Result[0] = vector[0];

    for (std::size_t i = 1; i < vector.size(); i++)
    {
        Result[i] = Result[i - 1] + vector[i];
    }

    return Result;
}
