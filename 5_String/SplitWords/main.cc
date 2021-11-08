#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

using WordCountPair = std::pair<std::string, std::size_t>;

void clean_text(std::string &text);

void replace_all(std::string &text, std::string_view what, std::string_view with);

template <typename T>
void split_text(const std::string &text, char delimiter, T result);

std::vector<std::string> split_text(const std::string &text, char delimiter);

int main()
{
    auto text = readFile("/mnt/c/Users/Jan/Dropbox/_Coding/UdemyCppExt/5_String/SplitWords/text.txt");
    std::cout << text << std::endl << std::endl;

    clean_text(text);
    std::cout << text << std::endl << std::endl;

    const auto splittedText = split_text(text, ' ');
    print_vector(splittedText);

    return 0;
}

void clean_text(std::string &text)
{
    replace_all(text, ".", "");
    replace_all(text, ",", "");
    replace_all(text, "!", "");
    replace_all(text, "?", "");
    replace_all(text, "\n", "");
    replace_all(text, "\t", "");
}

void replace_all(std::string &text, std::string_view what, std::string_view with)
{
    for (std::size_t pos = 0; std::string::npos != pos; pos += with.length())
    {
        text.replace(pos, what.length(), with.data(), with.length());
        pos = text.find(what.data(), pos, what.length());
    }
}

std::vector<std::string> split_text(const std::string &text, char delimiter)
{
    auto elems = std::vector<std::string>{};

    auto iss = std::istringstream{text};
    auto item = std::string{};

    while (std::getline(iss, item, delimiter))
    {
        *std::back_inserter(elems)++ = item;
    }

    return elems;
}
