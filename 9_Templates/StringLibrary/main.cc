#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

template <typename StringType, typename ViewType>
struct is_char_based
    : public std::conjunction<std::is_same<std::string, StringType>, std::is_same<std::string_view, ViewType>>
{
};

template <typename StringType, typename ViewType>
struct is_wchar_based
    : public std::conjunction<std::is_same<std::wstring, StringType>, std::is_same<std::wstring_view, ViewType>>
{
};

template <typename StringType, typename ViewType>
struct is_string : public std::disjunction<is_char_based<StringType, ViewType>, is_wchar_based<StringType, ViewType>>
{
};

template <typename StringType, typename ViewType>
StringType to_upper_case(ViewType text);

template <typename StringType, typename ViewType>
StringType to_lower_case(ViewType text);

int main()
{
    auto input_text = std::string{};
    std::cout << "Please enter any text: ";
    std::cin >> input_text;

    std::cout << "to_upper_case: " << to_upper_case<std::string, std::string_view>(input_text) << std::endl;
    std::cout << "to_lower_case: " << to_lower_case<std::string, std::string_view>(input_text) << std::endl;

    auto input_text_w = std::wstring(input_text.begin(), input_text.end());
    to_upper_case<std::wstring, std::wstring_view>(input_text_w);
    to_lower_case<std::wstring, std::wstring_view>(input_text_w);

    // auto input_text_c = input_text.c_str();
    // to_upper_case(input_text_c);
    // to_lower_case(input_text_c);

    return 0;
}

template <typename StringType, typename ViewType>
StringType to_upper_case(ViewType text)
{
    static_assert(is_string<StringType, ViewType>::value, "Must be of type std::string or std::wstring");

    auto result = StringType(text);
    std::transform(std::begin(result), std::end(result), std::begin(result), toupper);
    return result;
}

template <typename StringType, typename ViewType>
StringType to_lower_case(ViewType text)
{
    static_assert(is_string<StringType, ViewType>::value, "Must be of type std::string or std::wstring");

    auto result = StringType(text);
    std::transform(std::begin(result), std::end(result), std::begin(result), tolower);
    return result;
}
