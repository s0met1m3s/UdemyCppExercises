#pragma once

#include <algorithm>
#include <string>
#include <string_view>
#include <type_traits>

template <typename StringType, typename ViewType>
struct is_char_based;

template <typename StringType, typename ViewType>
struct is_wchar_based;

template <typename StringType, typename ViewType>
struct is_string;

template <typename StringType, typename ViewType>
StringType to_upper_case(ViewType text)
{
    static_assert(is_string<StringType, ViewType>::value,
                  "Strings must hold char or wchar_t values");

    auto result = StringType{text};
    std::transform(result.begin(), result.end(), result.begin(), toupper);
    return result;
}

template <typename StringType, typename ViewType>
StringType to_lower_case(ViewType text)
{
    static_assert(is_string<StringType, ViewType>::value,
                  "Strings must hold char or wchar_t values");

    auto result = StringType{text};
    std::transform(result.begin(), result.end(), result.begin(), tolower);
    return result;
}
