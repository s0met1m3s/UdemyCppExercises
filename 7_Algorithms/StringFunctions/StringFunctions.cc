#include <algorithm>

#include "StringFunctions.hpp"

namespace mystd
{

bool is_palindrom(std::string_view str)
{
    return std::equal(str.cbegin(), str.cend(), str.crbegin());
}

bool starts_with(std::string_view str, std::string_view substr)
{
    return std::equal(substr.cbegin(), substr.cend(), str.cbegin());
}

bool ends_with(std::string_view str, std::string_view substr)
{
    return std::equal(substr.crbegin(), substr.crend(), str.crbegin());
}

bool contains(std::string_view str, std::string_view substr)
{
    const auto substr_length = substr.length();

    for (auto it = str.cbegin(); it < str.cend() - substr_length + 1U;)
    {
        auto found = std::equal(substr.cbegin(), substr.cend(), it);

        if (found)
        {
            return true;
        }

        ++it;
    }

    return false;
}

std::size_t num_occurences(std::string_view str, std::string_view substr)
{
    auto occurences = std::size_t{0};
    const auto substr_length = substr.length();

    for (auto it = str.cbegin(); it < str.cend() - substr_length + 1U;)
    {
        auto found = std::equal(substr.cbegin(), substr.cend(), it);

        if (found)
        {
            ++occurences;
            std::advance(it, substr_length);
        }
        else
        {
            ++it;
        }
    }

    return occurences;
}

} // namespace mystd
