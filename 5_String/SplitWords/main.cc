#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

using WordCountPair = std::pair<std::string, std::size_t>;

std::string readFile(std::string_view file_path);

void cleanText(std::string &text);

void replaceAll(std::string &text, std::string_view What, std::string_view With);

template <typename T>
void splitText(const std::string &text, char Delimiter, T Result);

std::vector<std::string> splitText(const std::string &text, char Delimiter);

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

std::string readFile(std::string_view file_path)
{
    auto str = std::string{};
    auto text = std::string{};

    auto iffile = std::ifstream{};
    iffile.open(file_path.data());

    if (iffile.is_open())
    {
        while (std::getline(iffile, str))
        {
            text += str + '\n';
        }
    }

    iffile.close();

    return text;
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

void replaceAll(std::string &text, std::string_view What, std::string_view With)
{
    for (std::size_t pos = 0; std::string::npos != pos; pos += With.length())
    {
        text.replace(pos, What.length(), With.data(), With.length());
        pos = text.find(What.data(), pos, What.length());
    }
}

template <typename T>
void splitText(const std::string &text, char Delimiter, T Result)
{
    auto iss = std::istringstream{text};
    auto item = std::string{};

    while (std::getline(iss, item, Delimiter))
    {
        *Result++ = item;
    }
}

std::vector<std::string> splitText(const std::string &text, char Delimiter)
{
    auto elems = std::vector<std::string>{};
    splitText(text, Delimiter, std::back_inserter(elems));

    return elems;
}
