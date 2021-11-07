# Exercise

Implement the following functions:

```cpp
using WordCountPair = std::pair<std::string, std::size_t>;

void cleanText(std::string &text);

void replaceAll(std::string &text, std::string_view what, std::string_view with);

template <typename T>
void splitText(const std::string &text, char delimiter, T result);

std::vector<std::string> splitText(const std::string &text, char delimiter);
```

## Main Function

```cpp
int main()
{
    auto text =
        readFile("C:/Users/Jan/Dropbox/_Coding/udemy_cppExt/6_Container/word_count/text.txt");
    std::cout << text << std::endl << std::endl;

    cleanText(text);
    std::cout << text << std::endl << std::endl;

    const auto splittedText = splitText(text, ' ');
    print_vector(splittedText);

    return 0;
}
```
