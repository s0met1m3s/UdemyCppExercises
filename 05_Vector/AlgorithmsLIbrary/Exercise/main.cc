#include <cstdint>
#include <iostream>
#include <vector>

#include "utils.hpp"

bool all_of(const std::vector<std::int32_t> &vector, const std::int32_t value);

bool any_of(const std::vector<std::int32_t> &vector, const std::int32_t value);

bool none_of(const std::vector<std::int32_t> &vector, const std::int32_t value);

std::size_t count(const std::vector<std::int32_t> &vector,
                  const std::int32_t value);

std::vector<std::int32_t> inclusive_scan(
    const std::vector<std::int32_t> &vector);

int main()
{
    const auto vector = std::vector<std::int32_t>{3, 1, 4, 1, 5, 9, 2, 6};

    std::cout << std::boolalpha;
    std::cout << "all_of: " << all_of(vector, 5) << '\n';
    std::cout << "any_of: " << any_of(vector, 5) << '\n';
    std::cout << "none_of: " << none_of(vector, 5) << '\n';
    auto scan_values = inclusive_scan(vector);
    std::cout << "inclusive_scan: " << '\n';
    print_vector(scan_values);

    return 0;
}
