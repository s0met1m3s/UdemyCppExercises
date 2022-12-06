#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

#include "lib.h"

int main()
{
    auto in_text = std::string{};
    const auto compare_text1 = std::string{"jan"};
    const auto compare_text2 = std::string{"ja"};

    std::cout << "Please enter any result: ";
    std::cin >> in_text;

    std::cout << "to_upper_case: " << mystd::to_upper_case(in_text) << '\n';
    std::cout << "to_lower_case: " << mystd::to_lower_case(in_text) << '\n';
    std::cout << "string_length: " << mystd::string_length(in_text) << '\n';
    std::cout << std::boolalpha;
    std::cout << "eq1: " << mystd::string_equal(in_text, compare_text1) << '\n';
    std::cout << "eq2: " << mystd::string_equal(in_text, compare_text2) << '\n';

    return 0;
}
