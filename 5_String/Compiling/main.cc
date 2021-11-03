#include <algorithm>
#include <array>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"

namespace fs = std::filesystem;

using FileVec = std::vector<fs::path>;

FileVec get_files_in_dir(const fs::path &dir);

bool is_source_file(const fs::path &file);

void compile_file(fs::path source_file);

fs::path link_files(FileVec source_files);

void run(const fs::path &executable_path);

int main()
{
    fs::path dir = fs::current_path();
    dir /= "test";

    auto files = get_files_in_dir(dir);

    printVector(files);

    for (const auto &file : files)
    {
        compile_file(file);
    }

    auto executable_path = link_files(files);

    run(executable_path);
}

bool is_source_file(const fs::path &file)
{
    const auto allowed_extensions = std::array<std::string, 3>{".cc", ".cxx", ".cpp"};

    return std::any_of(allowed_extensions.begin(), allowed_extensions.end(), [&](auto extension) {
        return file.extension() == extension;
    });
}

std::vector<fs::path> get_files_in_dir(const fs::path &dir)
{
    auto files = std::vector<fs::path>{};

    for (auto it = fs::directory_iterator(dir); it != fs::directory_iterator{}; ++it)
    {
        if (is_source_file((*it).path()) && fs::is_regular_file((*it).path()))
        {
            files.push_back(*it);
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

    std::system(command.data());
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
    std::system(reinterpret_cast<const char *>(executable_path.c_str()));
}
