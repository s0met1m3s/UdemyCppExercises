#pragma once

#include <type_traits>
#include <string>
#include <string_view>
#include <algorithm>

template <typename StringType, typename ViewType>
struct is_char_based
    : public std::conjunction<std::is_same<std::string, StringType>,
                              std::is_same<std::string_view, ViewType>>
{
};

template <typename StringType, typename ViewType>
struct is_wchar_based
    : public std::conjunction<std::is_same<std::wstring, StringType>,
                              std::is_same<std::wstring_view, ViewType>>
{
};

template <typename StringType, typename ViewType>
struct is_string : public std::disjunction<is_char_based<StringType, ViewType>,
                                           is_wchar_based<StringType, ViewType>>
{
};

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
