# Exercise

Implement the following functions:

```cpp
namespace fs = std::filesystem;

auto replace_with(std::string &s, const std::string &old_substr, const std::string &new_substr);
```

## Main Function

```cpp
int main()
{
    auto current_path = fs::current_path();
    current_path /= "text.txt";

    auto text = readFile(current_path.string());

    std::cout << text << std::endl << std::endl;

    replace_with(text, "Lorem", "Morem");
    replace_with(text, "dolor", "molor");

    std::cout << text << std::endl;

    return 0;
}
```
