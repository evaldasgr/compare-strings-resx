// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2020 Evaldas Granickas <evaldasgr@gmail.com>

#include <fstream>
#include <iostream>
#include <set>

bool read(const char* filename, std::set<std::string>& set);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage:" << std::endl
                  << "compare-strings-resx file1 file2" << std::endl;
        return 1;
    }

    std::set<std::string> presentInFile1, presentInFile2;
    if (!read(argv[1], presentInFile1) || !read(argv[2], presentInFile2))
        return 1;

    for (const auto& s : presentInFile1)
    {
        if (!presentInFile2.contains(s))
            std::cout << s << std::endl;
    }

    return 0;
}

bool read(const char* filename, std::set<std::string>& set)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open \"" << filename << "\"."
                  << std::endl;
        return false;
    }

    std::string contents((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    std::size_t tag = 0;
    while (true)
    {
        static constexpr std::string_view Tag = "<data";
        tag = contents.find(Tag, tag);
        if (tag == std::string::npos)
            break;
        tag += Tag.size();

        static constexpr std::string_view Key = "name=\"";
        std::size_t value = contents.find(Key, tag);
        if (value == std::string::npos)
            break;
        value += Key.size();

        std::size_t end = contents.find(">", tag);
        if (end == std::string::npos)
            break;
        else if (value > end)
            continue;

        end = contents.find("\"", value);
        if (end == std::string::npos)
            break;

        set.insert(contents.substr(value, end - value));
    }

    return true;
}
