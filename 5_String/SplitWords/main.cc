#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

using PairType = std::pair<std::string, std::size_t>;

std::string readFile(std::string_view FilePath);

void cleanText(std::string &Text);

void replaceAll(std::string &Text, std::string_view What, std::string_view With);

template <typename T>
void splitText(const std::string &Text, char Delimiter, T Result);

std::vector<std::string> splitText(const std::string &Text, char Delimiter);

int main()
{
    auto Text = readFile("C:/Users/Jan/Dropbox/_Coding/UdemyCppExt/6_Container/WordCount/Text.txt");
    std::cout << Text << std::endl << std::endl;

    cleanText(Text);
    std::cout << Text << std::endl << std::endl;

    auto splittedText = splitText(Text, ' ');
    printVector(splittedText);

    return 0;
}

std::string readFile(std::string_view FilePath)
{
    auto str = std::string{};
    auto Text = std::string{};

    auto iffile = std::ifstream{};
    iffile.open(FilePath.data());

    if (iffile.is_open())
    {
        while (std::getline(iffile, str))
        {
            Text += str + '\n';
        }
    }

    iffile.close();

    return Text;
}

void cleanText(std::string &Text)
{
    replaceAll(Text, ".", "");
    replaceAll(Text, ",", "");
    replaceAll(Text, "!", "");
    replaceAll(Text, "?", "");
    replaceAll(Text, "\n", "");
    replaceAll(Text, "\t", "");
}

void replaceAll(std::string &Text, std::string_view What, std::string_view With)
{
    for (std::size_t pos = 0; std::string::npos != pos; pos += With.length())
    {
        Text.replace(pos, What.length(), With.data(), With.length());
        pos = Text.find(What.data(), pos, What.length());
    }
}

template <typename T>
void splitText(const std::string &Text, char Delimiter, T Result)
{
    auto iss = std::istringstream{Text};
    auto item = std::string{};

    while (std::getline(iss, item, Delimiter))
    {
        *Result++ = item;
    }
}

std::vector<std::string> splitText(const std::string &Text, char Delimiter)
{
    auto elems = std::vector<std::string>{};
    splitText(Text, Delimiter, std::back_inserter(elems));

    return elems;
}
