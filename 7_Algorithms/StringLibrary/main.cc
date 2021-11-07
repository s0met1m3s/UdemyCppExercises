#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>

std::string toupper_case(std::string_view text);

std::string tolower_case(std::string_view text);

std::size_t string_length(std::string_view text);

const char *char_search(std::string_view text, char character);

bool string_equal(std::string_view string1, std::string_view string2);

int main()
{
    auto input_text = std::string{};
    auto compare_text1 = std::string{"jan"};
    auto compare_text2 = std::string{"ja"};

    std::cout << "Please enter any result: ";
    std::cin >> input_text;

    std::cout << "toupper_case: " << toupper_case(input_text) << std::endl;
    std::cout << "tolower_case: " << tolower_case(input_text) << std::endl;
    std::cout << "string_length: " << string_length(input_text) << std::endl;
    std::cout << "char_search: " << char_search(input_text, 'a') << std::endl;
    std::cout << std::boolalpha;
    std::cout << "equal(jan, jan): " << string_equal(input_text, compare_text1) << std::endl;
    std::cout << "equal(jan, ja): " << string_equal(input_text, compare_text2) << std::endl;

    return 0;
}

std::string toupper_case(std::string_view text)
{
    auto result = std::string(text);
    std::transform(std::begin(result), std::end(result), std::begin(result), toupper);
    return result;
}

std::string tolower_case(std::string_view text)
{
    auto result = std::string(text);
    std::transform(std::begin(result), std::end(result), std::begin(result), tolower);
    return result;
}

std::size_t string_length(std::string_view text)
{
    return static_cast<std::size_t>(std::distance(text.begin(), text.end()));
}

const char *char_search(std::string_view text, char character)
{
    return std::find(text.begin(), text.end(), character);
}

bool string_equal(std::string_view string1, std::string_view string2)
{
    return std::equal(string1.begin(), string1.end(), string2.begin());
}
