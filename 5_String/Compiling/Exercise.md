# Exercise

Implement the following functions:

```cpp
namespace fs = std::filesystem;

using FileVec = std::vector<fs::path>;

FileVec get_source_files_in_dir(const fs::path &dir);

bool is_source_file(const fs::path &file);

void compile_file(fs::path source_file);

fs::path link_files(FileVec source_files);

void run(const fs::path &executable_path);
```

## Main Function

```cpp
int main(int argc, char **argv)
{
    fs::path dir;

    if (argc != 2)
    {
        dir /= fs::current_path();
        dir /= "test";
    }
    else
    {
        auto input_path = std::string(argv[1]);
        dir = fs::path(input_path);
    }

    auto files = get_source_files_in_dir(dir);

    print_vector(files);

    for (const auto &file : files)
    {
        compile_file(file);
    }

    const auto executable_path = link_files(files);

    run(executable_path);
}
```
