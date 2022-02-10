#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>

bool is_numeric(const char character);

bool is_alpha(const char character);

bool is_alpha_numeric(const char character);

bool is_upper_case(const char character);

bool is_lower_case(const char character);

char to_upper_case(char character);

char to_lower_case(char character);

std::string to_upper_case(std::string_view text);

std::string to_lower_case(std::string_view text);

std::size_t string_length(std::string_view text);

const char *char_search(std::string_view text, const char character);

bool string_equal(std::string_view string1, std::string_view string2);

int main()
{
    auto input_text = std::string{};
    auto compare_text1 = std::string{"jan"};
    auto compare_text2 = std::string{"ja"};

    std::cout << "Please enter any result: ";
    std::cin >> input_text;

    std::cout << "to_upper_case: " << to_upper_case(input_text) << '\n';
    std::cout << "to_lower_case: " << to_lower_case(input_text) << '\n';
    std::cout << "string_length: " << string_length(input_text) << '\n';
    std::cout << "char_search: " << char_search(input_text, 'a') << '\n';
    std::cout << std::boolalpha;
    std::cout << "equal(jan, jan): " << string_equal(input_text, compare_text1) << '\n';
    std::cout << "equal(jan, ja): " << string_equal(input_text, compare_text2) << '\n';

    return 0;
}

bool is_numeric(const char character)
{
    if ((character >= '0') && (character <= '9'))
    {
        return true;
    }

    return false;
}

bool is_alpha(const char character)
{
    if (is_upper_case(character) || is_lower_case(character))
    {
        return true;
    }

    return false;
}

bool is_alpha_numeric(const char character)
{
    return is_numeric(character) || is_alpha(character);
}

bool is_upper_case(const char character)
{
    if ((character >= 'A') && (character <= 'Z'))
    {
        return true;
    }

    return false;
}

bool is_lower_case(const char character)
{
    if ((character >= 'a') && (character <= 'z'))
    {
        return true;
    }

    return false;
}

char to_upper_case_(char character)
{
    if (is_lower_case(character))
    {
        return static_cast<std::int8_t>(character - 32);
    }

    return character;
}

char to_lower_case_(char character)
{
    if (is_upper_case(character))
    {
        return static_cast<std::int8_t>(character + 32);
    }

    return character;
}

std::string to_upper_case(std::string_view text)
{
    auto result = std::string{text};

    std::transform(text.begin(), text.end(), result.begin(), to_upper_case_);

    return result;
}

std::string to_lower_case(std::string_view text)
{
    auto result = std::string{text};

    std::transform(text.begin(), text.end(), result.begin(), to_lower_case_);

    return result;
}

std::size_t string_length(std::string_view text)
{
    return static_cast<std::size_t>(std::distance(text.begin(), text.end()));
}

const char *char_search(std::string_view text, const char character)
{
    return std::find(text.begin(), text.end(), character);
}

bool string_equal(std::string_view string1, std::string_view string2)
{
    return std::equal(string1.begin(), string1.end(), string2.begin());
}
