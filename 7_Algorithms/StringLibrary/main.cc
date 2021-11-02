#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>

std::string toUpperCase(std::string_view Text);
std::string toLowerCase(std::string_view Text);

int main()
{
    auto InputText = std::string{};

    std::cout << "Please enter any Result: ";
    std::cin >> InputText;

    std::cout << "toUpperCase: " << toUpperCase(InputText) << std::endl;
    std::cout << "toLowerCase: " << toLowerCase(InputText) << std::endl;

    return 0;
}

std::string toUpperCase(std::string_view Text)
{
    auto Result = std::string(Text);
    std::transform(std::begin(Result), std::end(Result), std::begin(Result), toupper);
    return Result;
}

std::string toLowerCase(std::string_view Text)
{
    auto Result = std::string(Text);
    std::transform(std::begin(Result), std::end(Result), std::begin(Result), tolower);
    return Result;
}
