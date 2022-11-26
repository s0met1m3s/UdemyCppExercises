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
