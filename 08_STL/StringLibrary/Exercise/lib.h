#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string_view>

namespace mystd
{

std::string to_upper_case(std::string_view text);

std::string to_lower_case(std::string_view text);

std::size_t string_length(std::string_view text);

bool string_equal(std::string_view string1, std::string_view string2);

} // namespace mystd
