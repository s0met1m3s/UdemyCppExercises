#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

using WordCountPair = std::pair<std::string, std::size_t>;

void cleanText(std::string &text);

void replaceAll(std::string &text, std::string_view what, std::string_view with);

template <typename T>
void splitText(const std::string &text, char delimiter, T result);

std::vector<std::string> splitText(const std::string &text, char delimiter);

int main()
{
    auto text =
        readFile("C:/Users/Jan/Dropbox/_Coding/udemy_cppExt/6_Container/word_count/text.txt");
    std::cout << text << std::endl << std::endl;

    cleanText(text);
    std::cout << text << std::endl << std::endl;

    auto splittedText = splitText(text, ' ');
    print_vector(splittedText);

    return 0;
}

void cleanText(std::string &text)
{
    replaceAll(text, ".", "");
    replaceAll(text, ",", "");
    replaceAll(text, "!", "");
    replaceAll(text, "?", "");
    replaceAll(text, "\n", "");
    replaceAll(text, "\t", "");
}

void replaceAll(std::string &text, std::string_view what, std::string_view with)
{
    for (std::size_t pos = 0; std::string::npos != pos; pos += with.length())
    {
        text.replace(pos, what.length(), with.data(), with.length());
        pos = text.find(what.data(), pos, what.length());
    }
}

template <typename T>
void splitText(const std::string &text, char delimiter, T result)
{
    auto iss = std::istringstream{text};
    auto item = std::string{};

    while (std::getline(iss, item, delimiter))
    {
        *result++ = item;
    }
}

std::vector<std::string> splitText(const std::string &text, char delimiter)
{
    auto elems = std::vector<std::string>{};
    splitText(text, delimiter, std::back_inserter(elems));

    return elems;
}
