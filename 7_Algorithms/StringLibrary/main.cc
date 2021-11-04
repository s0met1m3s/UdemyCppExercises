#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>

std::string toupper_case(std::string_view text);
std::string tolower_case(std::string_view text);

int main()
{
    auto input_text = std::string{};

    std::cout << "Please enter any Result: ";
    std::cin >> input_text;

    std::cout << "toupper_case: " << toupper_case(input_text) << std::endl;
    std::cout << "tolower_case: " << tolower_case(input_text) << std::endl;

    return 0;
}

std::string toupper_case(std::string_view text)
{
    auto Result = std::string(text);
    std::transform(std::begin(Result), std::end(Result), std::begin(Result), toupper);
    return Result;
}

std::string tolower_case(std::string_view text)
{
    auto Result = std::string(text);
    std::transform(std::begin(Result), std::end(Result), std::begin(Result), tolower);
    return Result;
}
