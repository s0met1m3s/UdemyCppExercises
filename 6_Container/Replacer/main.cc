#include <filesystem>
#include <iostream>
#include <string>

#include "utils.hpp"

namespace fs = std::filesystem;

auto replace_with(std::string &s, const std::string &old_substr, const std::string &new_substr)
{
    for (std::size_t pos = 0; pos <= s.size() - old_substr.size();)
    {
        if (s[pos] == old_substr[0] && s.substr(pos, old_substr.size()) == old_substr)
        {
            s.replace(pos, old_substr.size(), new_substr), pos += new_substr.size();
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
