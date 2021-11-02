#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

using PairType = std::pair<std::string, std::size_t>;
using CountedWordsVec = std::vector<PairType>;
using CountedWordsMap = std::map<std::string, std::size_t>;

std::string readFile(std::string_view FilePath);

void cleanText(std::string &Text);

void replaceAll(std::string &Text, std::string_view What, std::string_view With);

template <typename T>
void splitText(const std::string &Text, char Delimiter, T Result);

std::vector<std::string> splitText(const std::string &Text, char Delimiter);

CountedWordsMap countWords(const std::vector<std::string> &words);

CountedWordsVec mapToVector(CountedWordsMap countedWords);

void sortWordCounts(CountedWordsVec &wordCounts);

int main()
{
    auto Text = readFile("C:/Users/Jan/Dropbox/_Coding/UdemyCppExt/6_Container/WordCount/Text.txt");
    std::cout << Text << std::endl << std::endl;

    cleanText(Text);
    std::cout << Text << std::endl << std::endl;

    auto splittedText = splitText(Text, ' ');
    printVector(splittedText);

    auto countedWords = countWords(splittedText);
    printMap(countedWords);

    auto countedWordsVector = mapToVector(countedWords);

    sortWordCounts(countedWordsVector);
    printVector(countedWordsVector);

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
    auto iss = std::istringstream(Text);
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

CountedWordsMap countWords(const std::vector<std::string> &words)
{
    auto Result = CountedWordsMap{};

    for (const auto &word : words)
    {
        Result[word]++;
    }

    return Result;
}

CountedWordsVec mapToVector(CountedWordsMap countedWords)
{
    auto countedWordsVector = CountedWordsVec(countedWords.size());

    auto i = std::size_t{};
    for (const auto &Pair : countedWords)
    {
        countedWordsVector[i] = Pair;
        i++;
    }

    return countedWordsVector;
}

void sortWordCounts(CountedWordsVec &wordCounts)
{
    auto cmp = [](PairType const &a, PairType const &b) -> bool { return a.second > b.second; };

    std::sort(wordCounts.begin(), wordCounts.end(), cmp);
}
