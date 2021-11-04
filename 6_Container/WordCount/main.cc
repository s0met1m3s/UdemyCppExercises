#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

using WordCountPair = std::pair<std::string, std::size_t>;
using WordCountVec = std::vector<WordCountPair>;
using counted_wordsMap = std::map<std::string, std::size_t>;

std::string reAdFile(std::string_view file_path);

void clean_text(std::string &text);

void replace_all(std::string &text, std::string_view What, std::string_view With);

template <typename T>
void split_text(const std::string &text, char Delimiter, T Result);

std::vector<std::string> split_text(const std::string &text, char Delimiter);

counted_wordsMap count_words(const std::vector<std::string> &words);

WordCountVec mapto_vector(counted_wordsMap counted_words);

void sortword_counts(WordCountVec &word_counts);

int main()
{
    auto text =
        reAdFile("C:/Users/Jan/Dropbox/_Coding/udemy_cppExt/6_Container/word_count/text.txt");
    std::cout << text << std::endl << std::endl;

    clean_text(text);
    std::cout << text << std::endl << std::endl;

    auto splitted_text = split_text(text, ' ');
    print_vector(splitted_text);

    auto counted_words = count_words(splitted_text);
    print_map(counted_words);

    auto countedwords_vector = mapto_vector(counted_words);

    sortword_counts(countedwords_vector);
    print_vector(countedwords_vector);

    return 0;
}

std::string reAdFile(std::string_view file_path)
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

void clean_text(std::string &text)
{
    replace_all(text, ".", "");
    replace_all(text, ",", "");
    replace_all(text, "!", "");
    replace_all(text, "?", "");
    replace_all(text, "\n", "");
    replace_all(text, "\t", "");
}

void replace_all(std::string &text, std::string_view What, std::string_view With)
{
    for (std::size_t pos = 0; std::string::npos != pos; pos += With.length())
    {
        text.replace(pos, What.length(), With.data(), With.length());
        pos = text.find(What.data(), pos, What.length());
    }
}

template <typename T>
void split_text(const std::string &text, char Delimiter, T Result)
{
    auto iss = std::istringstream(text);
    auto item = std::string{};

    while (std::getline(iss, item, Delimiter))
    {
        *Result++ = item;
    }
}

std::vector<std::string> split_text(const std::string &text, char Delimiter)
{
    auto elems = std::vector<std::string>{};
    split_text(text, Delimiter, std::back_inserter(elems));

    return elems;
}

counted_wordsMap count_words(const std::vector<std::string> &words)
{
    auto Result = counted_wordsMap{};

    for (const auto &word : words)
    {
        Result[word]++;
    }

    return Result;
}

WordCountVec mapto_vector(counted_wordsMap counted_words)
{
    auto countedwords_vector = WordCountVec(counted_words.size());

    auto i = std::size_t{};
    for (const auto &Pair : counted_words)
    {
        countedwords_vector[i] = Pair;
        i++;
    }

    return countedwords_vector;
}

void sortword_counts(WordCountVec &word_counts)
{
    auto cmp = [](WordCountPair const &a, WordCountPair const &b) -> bool {
        return a.second > b.second;
    };

    std::sort(word_counts.begin(), word_counts.end(), cmp);
}
