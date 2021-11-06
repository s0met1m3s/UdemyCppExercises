#include <algorithm>
#include <array>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"

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

auto number_of_source_files(const FileVec &files)
{
    return std::count_if(files.begin(), files.end(), [](const auto &file) {
        return (is_c_source_file(file) || is_cpp_source_file(file));
    });
}

auto number_of_header_files(const FileVec &files)
{
    return std::count_if(files.begin(), files.end(), [](const auto &file) {
        return (is_c_header_file(file) || is_cpp_header_file(file));
    });
}

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

template <std::size_t N>
bool file_extension_check(const std::array<std::string, N> &allowed_extensions,
                          const fs::path &file)
{
    return std::any_of(allowed_extensions.begin(),
                       allowed_extensions.end(),
                       [&](const auto &extension) { return file.extension() == extension; });
}

bool is_c_source_file(const fs::path &file)
{
    const auto allowed_extensions = std::array<std::string, 1>{".c"};

    return file_extension_check(allowed_extensions, file);
}

bool is_cpp_source_file(const fs::path &file)
{
    const auto allowed_extensions = std::array<std::string, 3>{".cc", ".cxx", ".cpp"};

    return file_extension_check(allowed_extensions, file);
}

bool is_c_header_file(const fs::path &file)
{
    const auto allowed_extensions = std::array<std::string, 1>{".h"};

    return file_extension_check(allowed_extensions, file);
}

bool is_cpp_header_file(const fs::path &file)
{
    const auto allowed_extensions = std::array<std::string, 4>{".h", ".hh", ".hpp", ".hxx"};

    return file_extension_check(allowed_extensions, file);
}

std::vector<fs::path> get_source_files_in_dir(const fs::path &dir)
{
    auto files = std::vector<fs::path>{};

    for (auto it = fs::directory_iterator(dir); it != fs::directory_iterator{}; ++it)
    {
        auto current_file = *it;

        if (is_cpp_source_file(current_file.path()) && fs::is_regular_file(current_file.path()))
        {
            files.push_back(current_file);
        }
    }

    return files;
}

void compile_file(fs::path source_file)
{
    const std::string source_filename = source_file.string();
    std::string command = "g++ -c " + source_file.string();

    source_file.replace_extension("o");
    const std::string object_filename = source_file.string();
    command += " -o " + object_filename;

    std::system(command.c_str());
}

fs::path link_files(FileVec source_files)
{
    std::string command = "g++ ";

    for (auto &source_file : source_files)
    {
        source_file.replace_extension("o");
        const std::string object_filename = source_file.string();

        command += object_filename + " ";
    }

    fs::path executable_path = source_files[0].parent_path();
    executable_path /= "test.exe";

    command += " -o " + executable_path.string();
    std::system(command.data());

    return executable_path;
}

void run(const fs::path &executable_path)
{
    const auto executable_path_str = executable_path.string();

    std::system(executable_path_str.c_str());
}
