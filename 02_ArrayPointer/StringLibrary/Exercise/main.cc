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
