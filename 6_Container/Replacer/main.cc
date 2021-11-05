#include <filesystem>
#include <iostream>
#include <string>

#include "utils.hpp"

namespace fs = std::filesystem;

auto replace_with(std::string &s, std::string const &oldVal, std::string const &newVal)
{
    for (std::size_t pos = 0; pos <= s.size() - oldVal.size();)
    {
        if (s[pos] == oldVal[0] && s.substr(pos, oldVal.size()) == oldVal)
        {
            s.replace(pos, oldVal.size(), newVal), pos += newVal.size();
        }
        else
        {
            ++pos;
        }
    }
}

int main()
{
    auto current_path = fs::current_path();
    current_path /= "text.txt";

    auto text = readFile(current_path.string());

    std::cout << text << std::endl << std::endl;

    replace_with(text, "Lorem", "Morem");
    replace_with(text, "dolor", "molor");

    std::cout << text << std::endl;

    return 0;
}
