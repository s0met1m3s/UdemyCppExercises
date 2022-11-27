#include <cstring>
#include <iostream>

#include "utils.hpp"

void print_unique_elements(const std::int32_t *array, const std::size_t length);

void remove_duplicates(std::int32_t *array, std::size_t &length);

void rotate_left(std::int32_t *array, const std::size_t length);

void rotate_right(std::int32_t *array, const std::size_t length);

int main()
{
    std::size_t length = 6;
    std::int32_t array[]{1, 1, 2, 3, 3, 4};

    std::cout << "print_unique_elements: " << '\n';
    print_unique_elements(array, length);

    remove_duplicates(array, length);
    print_array(array, length);

    rotate_left(array, length);
    print_array(array, length);

    rotate_right(array, length);
    print_array(array, length);

    return 0;
}

void print_unique_elements(const std::int32_t *array, const std::size_t length)
{
    if (array == nullptr)
    {
        return;
    }

    for (std::size_t i = 0; i < length; i++)
    {
        bool unique = true;
        std::int32_t current_value = array[i];

        for (std::size_t j = 0; j < length; j++)
        {
            if (i == j)
            {
                continue;
            }

            if (current_value == array[j])
            {
                unique = false;
            }
        }

        if (unique == true)
        {
            std::cout << "unique: " << current_value << '\n';
        }
    }
}

void remove_duplicates(std::int32_t *array, std::size_t &length)
{
    if (array == nullptr)
    {
        return;
    }

    for (std::size_t i = 0; i < length; i++)
    {
        std::size_t duplicate_index = -1;
        std::int32_t current_value = array[i];

        for (std::size_t j = i + 1; j < length; j++)
        {
            if (current_value == array[j])
            {
                duplicate_index = j;
                length--;
                break;
            }
        }

        if (duplicate_index == static_cast<std::size_t>(-1))
        {
            continue;
        }

        for (std::size_t j = duplicate_index; j < length; j++)
        {
            array[j] = array[j + 1];
        }

        array[length] = 0;
    }
}

void rotate_left(std::int32_t *array, std::size_t length)
{
    if (array == nullptr)
    {
        return;
    }

    std::int32_t first_element = array[0];

    for (std::size_t i = 1; i < length; i++)
    {
        array[i - 1] = array[i];
    }

    array[length - 1] = first_element;
}

void rotate_right(std::int32_t *array, std::size_t length)
{
    if (array == nullptr)
    {
        return;
    }

    std::int32_t last_element = array[length - 1];

    for (std::size_t i = length - 1; i > 0; i--)
    {
        array[i] = array[i - 1];
    }

    array[0] = last_element;
}
