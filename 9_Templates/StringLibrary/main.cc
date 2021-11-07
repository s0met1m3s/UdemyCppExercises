#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

template <typename StringType, typename ViewType>
struct is_char_based : public std::conjunction<std::is_same<std::string, StringType>,
                                               std::is_same<std::string_view, ViewType>>
{
};

template <typename StringType, typename ViewType>
struct is_wchar_based : public std::conjunction<std::is_same<std::wstring, StringType>,
                                                std::is_same<std::wstring_view, ViewType>>
{
};

template <typename StringType, typename ViewType>
struct is_string : public std::disjunction<is_char_based<StringType, ViewType>,
                                           is_wchar_based<StringType, ViewType>>
{
};

template <typename StringType, typename ViewType>
StringType toupper_case(ViewType text);

template <typename StringType, typename ViewType>
StringType tolower_case(ViewType text);

int main()
{
    auto input_text = std::string{};
    std::cout << "Please enter any text: ";
    std::cin >> input_text;

    std::cout << "toupper_case: " << toupper_case<std::string, std::string_view>(input_text)
              << std::endl;
    std::cout << "tolower_case: " << tolower_case<std::string, std::string_view>(input_text)
              << std::endl;

    auto input_text_w = std::wstring(input_text.begin(), input_text.end());
    toupper_case<std::wstring, std::wstring_view>(input_text_w);
    tolower_case<std::wstring, std::wstring_view>(input_text_w);

    // auto input_text_c = input_text.c_str();
    // toupper_case(input_text_c);
    // tolower_case(input_text_c);

    return 0;
}

template <typename StringType, typename ViewType>
StringType toupper_case(ViewType text)
{
    static_assert(is_string<StringType, ViewType>::value,
                  "Must be of type std::string or std::wstring");

    auto result = StringType(text);
    std::transform(std::begin(result), std::end(result), std::begin(result), toupper);
    return result;
}

template <typename StringType, typename ViewType>
StringType tolower_case(ViewType text)
{
    static_assert(is_string<StringType, ViewType>::value,
                  "Must be of type std::string or std::wstring");

    auto result = StringType(text);
    std::transform(std::begin(result), std::end(result), std::begin(result), tolower);
    return result;
}
