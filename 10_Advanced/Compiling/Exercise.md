# Exercise

Implement the following functions:

```cpp
namespace fs = std::filesystem;

using FileVec = std::vector<fs::path>;

FileVec get_source_files_in_dir(const fs::path &dir);

bool is_c_source_file(const fs::path &file);

bool is_cpp_source_file(const fs::path &file);

bool is_c_header_file(const fs::path &file);

bool is_cpp_header_file(const fs::path &file);

void compile_file(fs::path source_file);

fs::path link_files(FileVec source_files);

void run(const fs::path &executable_path);

auto number_of_source_files(const FileVec &files);

auto number_of_header_files(const FileVec &files);
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
        const auto input_path = std::string(argv[1]);
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

    auto all_files = FileVec{};
    for (auto it = fs::directory_iterator(dir); it != fs::directory_iterator{}; ++it)
    {
        all_files.push_back(*it);
    }

    const auto number_sources = number_of_source_files(all_files);
    const auto number_headers = number_of_header_files(all_files);

    std::cout << number_sources << std::endl;
    std::cout << number_headers << std::endl;
}
```
