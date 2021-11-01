#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.h"

using PairType = std::pair<std::string, std::size_t>;

std::string readFile(std::string_view filePath);

void cleanText(std::string &text);

std::size_t replaceAll(std::string &inout, std::string_view what, std::string_view with);

template <typename T> void splitText(const std::string &s, char delim, T result);

std::vector<std::string> splitText(const std::string &s, char delim);

std::map<std::string, std::size_t> countWords(const std::vector<std::string> &words);

std::vector<PairType> mapToVector(std::map<std::string, std::size_t> countedWords);

void sortWordCounts(std::vector<PairType> &wordCounts);

int main()
{
    auto text = readFile("C:/Users/Jan/Dropbox/_Coding/UdemyCppExt/6_Container/WordCount/text.txt");
    std::cout << text << std::endl << std::endl;

    cleanText(text);
    std::cout << text << std::endl << std::endl;

    auto splittedText = splitText(text, ' ');
    printVector(splittedText);

    auto countedWords = countWords(splittedText);
    printMap(countedWords);

    auto countedWordsVector = mapToVector(countedWords);

    sortWordCounts(countedWordsVector);
    printVector(countedWordsVector);

    return 0;
}

std::string readFile(std::string_view filePath)
{
    std::string str;
    std::string text;

    std::ifstream iffile;
    iffile.open(filePath.data());

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

std::size_t replaceAll(std::string &inout, std::string_view what, std::string_view with)
{
    std::size_t count{};

    for (std::string::size_type pos{};
         inout.npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length(), ++count)
    {
        inout.replace(pos, what.length(), with.data(), with.length());
    }

    return count;
}

template <typename T> void splitText(const std::string &s, char delim, T result)
{
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim))
    {
        *result++ = item;
    }
}

std::vector<std::string> splitText(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    splitText(s, delim, std::back_inserter(elems));
    return elems;
}

std::map<std::string, std::size_t> countWords(const std::vector<std::string> &words)
{
    auto result = std::map<std::string, std::size_t>();

    for (const auto &word : words)
    {
        result[word]++;
    }

    return result;
}

std::vector<PairType> mapToVector(std::map<std::string, std::size_t> countedWords)
{
    auto countedWordsVector = std::vector<PairType>(countedWords.size());

    auto i = static_cast<std::size_t>(0);
    for (const auto &Pair : countedWords)
    {
        countedWordsVector[i] = Pair;
        i++;
    }

    return countedWordsVector;
}

void sortWordCounts(std::vector<PairType> &wordCounts)
{
    auto cmp = [](PairType const &a, PairType const &b) { return a.second > b.second; };

    std::sort(wordCounts.begin(), wordCounts.end(), cmp);
}
