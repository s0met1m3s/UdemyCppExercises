#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include "lib.h"

int main()
{
    auto vector = std::vector<std::int32_t>{1, 1, 2, 3, 3, 4};

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
