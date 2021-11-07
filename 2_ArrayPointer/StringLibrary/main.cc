#include <iostream>

/* CHARS */

bool is_numeric(char character);

bool is_alpha(char character);

bool is_alpha_numeric(char character);

bool is_upper_case(char character);

bool is_lower_case(char character);

char to_upper_case(char character);

char to_lower_case(char character);

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

    std::cout << "to_upper_case: " << to_upper_case(input_text) << std::endl;
    std::cout << "to_lower_case: " << to_lower_case(input_text) << std::endl;
    std::cout << "string_length: " << string_length(input_text) << std::endl;
    std::cout << "char_search: " << char_search(input_text, 'a') << std::endl;
    std::cout << std::boolalpha;
    std::cout << "equal(jan, jan): " << string_equal(input_text, compare_text1) << std::endl;
    std::cout << "equal(jan, ja): " << string_equal(input_text, compare_text2) << std::endl;

    return 0;
}

/* CHARS */

bool is_numeric(char character)
{
    if ((character >= '0') && (character <= '9'))
    {
        return true;
    }

    return false;
}

bool is_alpha(char character)
{
    if (is_upper_case(character) || is_lower_case(character))
    {
        return true;
    }

    return false;
}

bool is_alpha_numeric(char character)
{
    return is_numeric(character) || is_alpha(character);
}

bool is_upper_case(char character)
{
    if ((character >= 'A') && (character <= 'Z'))
    {
        return true;
    }

    return false;
}

bool is_lower_case(char character)
{
    if ((character >= 'a') && (character <= 'z'))
    {
        return true;
    }

    return false;
}

char to_upper_case(char character)
{
    if (is_lower_case(character))
    {
        return character - 32;
    }

    return character;
}

char to_lower_case(char character)
{
    if (is_upper_case(character))
    {
        return character + 32;
    }

    return character;
}

/* CHAR ARRAYS */

char *to_upper_case(char *text)
{
    char *current_character = text;

    while (*current_character != '\0')
    {
        if (is_lower_case(*current_character))
        {
            *current_character = *current_character - 32;
        }

        current_character++;
    }

    return text;
}

char *to_lower_case(char *text)
{
    char *current_character = text;

    while (*current_character != '\0')
    {
        if (is_upper_case(*current_character))
        {
            *current_character = *current_character + 32;
        }

        current_character++;
    }

    return text;
}

std::size_t string_length(char *text)
{
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
    while ((*text != character) && (*text != '\0'))
    {
        text++;
    }

    return text;
}

bool string_equal(char *string1, char *string2)
{
    std::size_t len1 = string_length(string1);
    std::size_t len2 = string_length(string2);

    if (len1 != len2)
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
