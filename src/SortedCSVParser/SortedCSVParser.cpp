#include "SortedCSVParser.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

SortedCSVParser::SortedCSVParser(const std::string &filename)
{
    {
        std::ifstream file(filename);

        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
    }

    {
        std::istringstream ss(lines[0]);
        std::string column;
        int id = 0;
        while (std::getline(ss, column, ',')) {
            columns[column] = id++;
        }
    }

}

std::vector<std::string>::iterator SortedCSVParser::begin()
{
    return lines.begin() + 1;
}


std::vector<std::string>::iterator SortedCSVParser::end()
{
    return lines.end();
}

std::string SortedCSVParser::extract_from_line(const std::string line, const std::string& column) const
{
    std::istringstream ss(line);
    std::string this_column;
    for (int i = columns.at(column); i >= 0; i--) {
        if (!std::getline(ss, this_column, ','))
            throw std::ios_base::failure("Corrupted CSV");
    }

    return this_column;
}
