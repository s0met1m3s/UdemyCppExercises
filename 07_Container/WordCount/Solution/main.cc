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

using WordVector = std::vector<std::string>;
using WordCountPair = std::pair<std::string, std::size_t>;
using WordCountVec = std::vector<WordCountPair>;
using CountedWordsMap = std::map<std::string, std::size_t>;

void clean_text(std::string &text);

void replace_all(std::string &text,
                 std::string_view what,
                 std::string_view with);

WordVector split_text(const std::string &text, char delimiter);

CountedWordsMap count_words(const WordVector &words);

WordCountVec map_to_vector(const CountedWordsMap &counted_words);

void sort_word_counts(WordCountVec &word_counts);

int main()
{
    auto current_path = fs::current_path();
    current_path /= "text.txt";

    auto text = readFile(current_path.string());
    std::cout << text << '\n' << '\n';

    clean_text(text);
    std::cout << text << '\n' << '\n';

    auto splitted_text = split_text(text, ' ');
    print_vector(splitted_text);

    auto counted_words = count_words(splitted_text);
    print_map(counted_words);

    auto countedwords_vector = map_to_vector(counted_words);

    sort_word_counts(countedwords_vector);
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

void replace_all(std::string &text,
                 std::string_view what,
                 std::string_view with)
{
    for (std::size_t pos = 0; pos != std::string::npos; pos += with.length())
    {
        pos = text.find(what.data(), pos, what.length());

        if (pos != std::string::npos)
        {
            text.replace(pos, what.length(), with.data(), with.length());
        }
    }
}

WordVector split_text(const std::string &text, char delimiter)
{
    auto words = WordVector{};

    auto iss = std::istringstream{text};
    auto item = std::string{};

    while (std::getline(iss, item, delimiter))
    {
        words.push_back(item);
    }

    return words;
}

CountedWordsMap count_words(const WordVector &words)
{
    auto result = CountedWordsMap{};

    for (const auto &word : words)
    {
        result[word]++;
    }

    return result;
}

WordCountVec map_to_vector(const CountedWordsMap &counted_words)
{
    auto result = WordCountVec(counted_words.size());

    auto i = std::size_t{0};
    for (const auto &pair : counted_words)
    {
        result[i] = pair;
        i++;
    }

    return result;
}

bool compare(const WordCountPair &pair1, const WordCountPair &pair2)
{
    return pair1.second > pair2.second;
}

void sort_word_counts(WordCountVec &word_counts)
{
    std::sort(word_counts.begin(), word_counts.end(), compare);
}
