#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils.hpp"

void unique_elements(const std::vector<std::int32_t> &vector);

void remove_duplicates(std::vector<std::int32_t> &vector);

void rotate_left(std::vector<std::int32_t> &vector);

void rotate_right(std::vector<std::int32_t> &vector);

void swap_boundary_values(std::vector<std::int32_t> &vector);

int main()
{
    auto vector = std::vector<std::int32_t>{1, 1, 2, 3, 3, 4};

    std::cout << "unique_elements: " << '\n';
    unique_elements(vector);

    std::cout << "remove_duplicates: " << '\n';
    remove_duplicates(vector);
    print_vector(vector);

    std::cout << "rotate_left: " << '\n';
    rotate_left(vector);
    print_vector(vector);

    std::cout << "rotate_right: " << '\n';
    rotate_right(vector);
    print_vector(vector);

    return 0;
}

void unique_elements(const std::vector<std::int32_t> &vector)
{
    for (std::size_t i = 0; i < vector.size(); i++)
    {
        auto unique = true;
        auto current_value = vector[i];

        for (std::size_t j = 0; j < vector.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            if (current_value == vector[j])
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

void remove_duplicates(std::vector<std::int32_t> &vector)
{
    for (std::size_t i = 0; i < vector.size(); i++)
    {
        auto duplicate_index = static_cast<std::size_t>(-1);
        const auto current_value = vector[i];

        for (std::size_t j = i + 1; j < vector.size(); j++)
        {
            if (current_value == vector[j])
            {
                duplicate_index = j;
                vector.pop_back();
                break;
            }
        }

        if (duplicate_index == static_cast<std::size_t>(-1))
        {
            continue;
        }

        for (std::size_t j = duplicate_index; j < vector.size(); j++)
        {
            vector[j] = vector[j + 1];
        }

        vector[vector.size()] = 0;
    }
}

void rotate_left(std::vector<std::int32_t> &vector)
{
    const auto first_element = vector[0];

    for (std::size_t i = 1; i < vector.size(); i++)
    {
        vector[i - 1] = vector[i];
    }

    vector[vector.size() - 1] = first_element;
}

void rotate_right(std::vector<std::int32_t> &vector)
{
    const auto last_element = vector[vector.size() - 1];

    for (std::size_t i = vector.size() - 1; i > 0; i--)
    {
        vector[i] = vector[i - 1];
    }

    vector[0] = last_element;
}

void swap_boundary_values(std::vector<std::int32_t> &vector)
{
    auto &front_value = vector.front();
    auto &back_value = vector.back();

    const auto temp = back_value;
    back_value = front_value;
    front_value = temp;
}
