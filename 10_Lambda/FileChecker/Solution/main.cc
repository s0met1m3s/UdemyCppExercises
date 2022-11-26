#include <algorithm>
#include <array>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"

namespace fs = std::filesystem;
using FileVec = std::vector<fs::path>;

bool is_c_source_file(const fs::path &file);

bool is_cpp_source_file(const fs::path &file);

bool is_c_header_file(const fs::path &file);

bool is_cpp_header_file(const fs::path &file);

bool number_of_source_files(const FileVec &files);

bool number_of_header_files(const FileVec &files);

int main(int argc, char **argv)
{
    auto dir = fs::path{};

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

    auto all_files = FileVec{};
    for (auto it = fs::directory_iterator(dir); it != fs::directory_iterator{};
         ++it)
    {
        all_files.push_back(*it);
    }

    const auto number_sources = number_of_source_files(all_files);
    const auto number_headers = number_of_header_files(all_files);

    std::cout << number_sources << '\n';
    std::cout << number_headers << '\n';

    for (const auto &file : all_files)
    {
        std::cout << "File: " << file << '\n';
        std::cout << std::boolalpha;
        std::cout << "is_c_header_file: " << is_c_header_file(file) << '\n';
        std::cout << "is_c_source_file: " << is_c_source_file(file) << '\n';
        std::cout << "is_cpp_header_file: " << is_cpp_header_file(file) << '\n';
        std::cout << "is_cpp_source_file: " << is_cpp_source_file(file) << '\n'
                  << '\n';
    }
}

bool number_of_source_files(const FileVec &files)
{
    return std::count_if(files.begin(), files.end(), [](const auto &file) {
        return (is_c_source_file(file) || is_cpp_source_file(file));
    });
}

bool number_of_header_files(const FileVec &files)
{
    return std::count_if(files.begin(), files.end(), [](const auto &file) {
        return (is_c_header_file(file) || is_cpp_header_file(file));
    });
}

template <std::size_t N>
bool file_extension_check(const std::array<std::string, N> &allowed_extension,
                          const fs::path &file)
{
    return std::any_of(allowed_extension.begin(),
                       allowed_extension.end(),
                       [&file](const auto &extension) {
                           return file.extension() == extension;
                       });
}

bool is_c_source_file(const fs::path &file)
{
    const auto allowed_extension = std::array<std::string, 1>{".c"};

    return file_extension_check(allowed_extension, file);
}

bool is_cpp_source_file(const fs::path &file)
{
    const auto allowed_extension =
        std::array<std::string, 3>{".cc", ".cpp", ".cxx"};

    return file_extension_check(allowed_extension, file);
}

bool is_c_header_file(const fs::path &file)
{
    const auto allowed_extension = std::array<std::string, 1>{".h"};

    return file_extension_check(allowed_extension, file);
}

bool is_cpp_header_file(const fs::path &file)
{
    const auto allowed_extension =
        std::array<std::string, 4>{".h", ".hh", ".hxx", ".hpp"};

    return file_extension_check(allowed_extension, file);
}
