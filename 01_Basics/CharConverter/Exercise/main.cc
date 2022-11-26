#include <iostream>

bool is_numeric(char character);

bool is_alpha(char character);

bool is_alpha_numeric(char character);

bool is_upper_case(char character);

bool is_lower_case(char character);

char to_upper_case(char character);

char to_lower_case(char character);

int main()
{
    char input_character;

    std::cout << "Please enter any ASCII character: ";
    std::cin >> input_character;

    std::cout << std::boolalpha;
    std::cout << "is_numeric: " << is_numeric(input_character) << '\n';
    std::cout << "is_alpha: " << is_alpha(input_character) << '\n';
    std::cout << "is_alpha_numeric: " << is_alpha_numeric(input_character)
              << '\n';
    std::cout << "is_upper_case: " << is_upper_case(input_character) << '\n';
    std::cout << "is_lower_case: " << is_lower_case(input_character) << '\n';
    std::cout << std::dec;
    std::cout << "to_upper_case: " << to_upper_case(input_character) << '\n';
    std::cout << "to_lower_case: " << to_lower_case(input_character) << '\n';

    return 0;
}
