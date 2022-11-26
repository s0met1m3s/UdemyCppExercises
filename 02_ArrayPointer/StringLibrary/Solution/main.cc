#include <iostream>

/* CHARS */
#include "string_utils.hpp"

/* CHAR ARRAYS */

char *to_upper_case(char *text);

char *to_lower_case(char *text);

std::size_t string_length(char *text);

char *char_search(char *text, char character);

bool string_equal(char *string1, char *string2);

int main()
{
    char input_text[50]{};
    char compare_text1[50]{"jan"};
    char compare_text2[50]{"ja"};

    std::cout << "Please enter any text: ";
    std::cin >> input_text;

    std::cout << "to_upper_case: " << to_upper_case(input_text) << '\n';
    std::cout << "to_lower_case: " << to_lower_case(input_text) << '\n';
    std::cout << "string_length: " << string_length(input_text) << '\n';
    std::cout << "char_search: " << char_search(input_text, 'a') << '\n';
    std::cout << std::boolalpha;
    std::cout << "equal(jan, jan): " << string_equal(input_text, compare_text1)
              << '\n';
    std::cout << "equal(jan, ja): " << string_equal(input_text, compare_text2)
              << '\n';

    return 0;
}

char *to_upper_case(char *text)
{
    if (text == nullptr)
    {
        return nullptr;
    }

    char *current_character = text;

    while (*current_character != '\0')
    {
        *current_character = to_upper_case(*current_character);

        current_character++;
    }

    return text;
}

char *to_lower_case(char *text)
{
    if (text == nullptr)
    {
        return nullptr;
    }

    char *current_character = text;

    while (*current_character != '\0')
    {
        *current_character = to_lower_case(*current_character);

        current_character++;
    }

    return text;
}

std::size_t string_length(char *text)
{
    if (text == nullptr)
    {
        return 0;
    }

    std::size_t length = 0;

    while (*text != '\0')
    {
        length++;
        text++;
    }

    return length;
}

char *char_search(char *text, char character)
{
    if (text == nullptr)
    {
        return nullptr;
    }

    while ((*text != character) && (*text != '\0'))
    {
        text++;
    }

    return text;
}

bool string_equal(char *string1, char *string2)
{
    if (string1 == nullptr || string2 == nullptr)
    {
        return false;
    }

    std::size_t length1 = string_length(string1);
    std::size_t length2 = string_length(string2);

    if (length1 != length2)
    {
        return false;
    }

    while (*string1 != '\0')
    {
        if (*string1 != *string2)
        {
            return false;
        }

        string1++;
        string2++;
    }

    return true;
}
