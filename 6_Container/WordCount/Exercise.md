# Exercise

Implement the following functions:

```cpp
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
```

## Main Function

```cpp
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
```
