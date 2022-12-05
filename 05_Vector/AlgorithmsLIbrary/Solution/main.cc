#include <cstdint>
#include <iostream>
#include <vector>

#include "utils.hpp"

bool all_of(const std::vector<std::int32_t> &vector, const std::int32_t value);

bool any_of(const std::vector<std::int32_t> &vector, const std::int32_t value);

bool none_of(const std::vector<std::int32_t> &vector, const std::int32_t value);

std::size_t count(const std::vector<std::int32_t> &vector,
                  const std::int32_t value);

int main()
{
    const auto vector = std::vector<std::int32_t>{3, 1, 4, 1, 5, 9, 2, 6};

    std::cout << std::boolalpha;
    std::cout << "all_of: " << all_of(vector, 5) << '\n';
    std::cout << "any_of: " << any_of(vector, 5) << '\n';
    std::cout << "none_of: " << none_of(vector, 5) << '\n';

    return 0;
}

bool all_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
{
    for (const auto &current_value : vector)
    {
        if (current_value != value)
        {
            return false;
        }
    }

    return true;
}

bool any_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
{
    for (const auto &current_value : vector)
    {
        if (current_value == value)
        {
            return true;
        }
    }

    return false;
}

bool none_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
{
    for (const auto &current_value : vector)
    {
        if (current_value == value)
        {
            return false;
        }
    }

    return true;
}

std::size_t count(const std::vector<std::int32_t> &vector,
                  const std::int32_t value)
{
    auto counter = std::size_t{0};

    for (const auto &current_value : vector)
    {
        if (current_value == value)
        {
            counter++;
        }
    }

    return counter;
}
