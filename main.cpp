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

    std::string line;
    while (std::getline(file, line))
    {
        std::size_t pos = 0;
        while (true)
        {
            static constexpr std::string_view Prefix = "<data name=\"";
            pos = line.find(Prefix, pos);
            if (pos == std::string::npos)
                break;
            pos += Prefix.size();

            auto end = line.find("\"", pos);
            if (end == std::string::npos)
                break;

            set.insert(line.substr(pos, end - pos));
        }
    }

    return true;
}
