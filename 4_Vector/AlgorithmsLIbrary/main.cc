#include <cstdint>
#include <iostream>
#include <vector>

#include "utils.hpp"

bool all_of(const std::vector<std::int32_t> &vector, const std::int32_t value);
bool any_of(const std::vector<std::int32_t> &vector, const std::int32_t value);
bool none_of(const std::vector<std::int32_t> &vector, const std::int32_t value);
std::size_t count(const std::vector<std::int32_t> &vector, const std::int32_t value);
std::vector<std::int32_t> inclusive_scan(const std::vector<std::int32_t> &vector);

int main()
{
    auto vector = std::vector<std::int32_t>{3, 1, 4, 1, 5, 9, 2, 6};

    std::cout << std::boolalpha;
    std::cout << "all_of: " << all_of(vector, 5) << std::endl;
    std::cout << "any_of: " << any_of(vector, 5) << std::endl;
    std::cout << "none_of: " << none_of(vector, 5) << std::endl;
    auto Scan_values = inclusive_scan(vector);
    std::cout << "inclusive_scan: " << std::endl;
    print_vector(Scan_values);

    return 0;
}

bool all_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
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

bool any_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
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

bool none_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
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

std::size_t count(const std::vector<std::int32_t> &vector, const std::int32_t value)
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

std::vector<std::int32_t> inclusive_scan(const std::vector<std::int32_t> &vector)
{
    auto Result = std::vector<std::int32_t>(vector.size(), 0);

    Result[0] = vector[0];

    for (std::size_t i = 1; i < vector.size(); i++)
    {
        Result[i] = Result[i - 1] + vector[i];
    }

    return Result;
}
