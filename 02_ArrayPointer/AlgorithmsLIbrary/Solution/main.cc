#include <cstdint>
#include <iostream>

#include "utils.hpp"

bool all_of(const std::int32_t *array,
            const std::size_t length,
            const std::int32_t value);

bool any_of(const std::int32_t *array,
            const std::size_t length,
            const std::int32_t value);

bool none_of(const std::int32_t *array,
             const std::size_t length,
             const std::int32_t value);

std::size_t count(const std::int32_t *array,
                  const std::size_t length,
                  const std::int32_t value);

std::int32_t *inclusive_scan(const std::int32_t *array,
                             const std::size_t length);

int main()
{
    const std::int32_t array[]{3, 1, 4, 1, 5, 9, 2, 6};
    const std::size_t length = 8;

    std::cout << std::boolalpha;
    std::cout << "all_of: " << all_of(array, length, 5) << '\n';
    std::cout << "any_of: " << any_of(array, length, 5) << '\n';
    std::cout << "none_of: " << none_of(array, length, 5) << '\n';
    auto scan_values = inclusive_scan(array, length);
    std::cout << "inclusive_scan: " << '\n';
    print_array(scan_values, length);

    delete[] scan_values;
    scan_values = nullptr;

    return 0;
}

bool all_of(std::int32_t *array, std::size_t length, std::int32_t value)
{
    if (array == nullptr)
    {
        return false;
    }

    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] != value)
        {
            return false;
        }
    }

    return true;
}

bool any_of(std::int32_t *array, std::size_t length, std::int32_t value)
{
    if (array == nullptr)
    {
        return false;
    }

    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            return true;
        }
    }

    return false;
}

bool none_of(std::int32_t *array, std::size_t length, std::int32_t value)
{
    if (array == nullptr)
    {
        return false;
    }

    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            return false;
        }
    }

    return true;
}

std::size_t count(std::int32_t *array, std::size_t length, std::int32_t value)
{
    if (array == nullptr)
    {
        return 0;
    }

    std::size_t counter = 0;

    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            counter++;
        }
    }

    return counter;
}

std::int32_t *inclusive_scan(std::int32_t *array, std::size_t length)
{
    if (array == nullptr)
    {
        return nullptr;
    }

    std::int32_t *result = new std::int32_t[length]{};

    result[0] = array[0];

    for (std::size_t i = 1; i < length; i++)
    {
        result[i] = result[i - 1] + array[i];
    }

    return result;
}
