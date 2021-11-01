#include <iostream>
#include <string>

int main()
{
    const auto String1 = std::to_string(42);
    const auto String2 = std::to_string(42L);
    const auto String3 = std::to_string(42U);
    const auto String4 = std::to_string(42.0);
    const auto String5 = std::to_string(42.0F);

    const auto Number1 = std::stoi(String1);
    const auto Number2 = std::stod(String4);
    const auto Number3 = std::stof(String5);

    return 0;
}
