#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#include "algo.hpp"
#include "utils.hpp"


int main()
{
    auto vec1 = std::vector<int>(5, 0);
    auto vec2 = std::vector<int>(5, 0);

    std::cout << std::boolalpha << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << std::dec
              << std::endl;

    mystd::fill_n(vec1.begin(), 5, 1);
    print_vector(vec1);

    mystd::iota(vec2.begin(), vec2.end(), 0);
    print_vector(vec2);

    std::cout << std::boolalpha << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << std::dec
              << std::endl;

    mystd::copy(vec2.begin(), vec2.end(), vec1.begin());

    std::cout << std::boolalpha << mystd::equal(vec1.begin(), vec1.end(), vec2.begin()) << std::dec
              << std::endl;

    auto sum = mystd::accumulate(vec1.begin(), vec1.end(), 0);
    std::cout << sum << std::endl;

    auto inner_product = mystd::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
    std::cout << inner_product << std::endl;

    return 0;
}
