#include <algorithm>
#include <filesystem>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

namespace fs = std::filesystem;

using WordCountPair = std::pair<std::string, std::size_t>;
using WordCountVec = std::vector<WordCountPair>;
using counted_wordsMap = std::map<std::string, std::size_t>;

void clean_text(std::string &text);

void replace_all(std::string &text, std::string_view what, std::string_view with);

template <typename T>
void split_text(const std::string &text, char delimiter, T result);

std::vector<std::string> split_text(const std::string &text, char delimiter);

counted_wordsMap count_words(const std::vector<std::string> &words);

WordCountVec mapto_vector(counted_wordsMap counted_words);

void sortword_counts(WordCountVec &word_counts);

int main()
{
    auto current_path = fs::current_path();
    current_path /= "text.txt";

    auto text = readFile(current_path.string());
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

template <typename T>
void split_text(const std::string &text, char delimiter, T result)
{
    auto iss = std::istringstream(text);
    auto item = std::string{};

    while (std::getline(iss, item, delimiter))
    {
        *result++ = item;
    }
}

std::vector<std::string> split_text(const std::string &text, char delimiter)
{
    auto elems = std::vector<std::string>{};
    split_text(text, delimiter, std::back_inserter(elems));

    return elems;
}

counted_wordsMap count_words(const std::vector<std::string> &words)
{
    auto result = counted_wordsMap{};

    for (const auto &word : words)
    {
        result[word]++;
    }

    return result;
}

WordCountVec mapto_vector(counted_wordsMap counted_words)
{
    auto countedwords_vector = WordCountVec(counted_words.size());

    auto i = std::size_t{};
    for (const auto &pair : counted_words)
    {
        countedwords_vector[i] = pair;
        i++;
    }

    return countedwords_vector;
}

void sortword_counts(WordCountVec &word_counts)
{
    auto cmp = [](WordCountPair const &a, WordCountPair const &b) { return a.second > b.second; };

    std::sort(word_counts.begin(), word_counts.end(), cmp);
}
