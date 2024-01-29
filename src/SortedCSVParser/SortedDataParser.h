#ifndef SORTEDDATAPARSER_H
#define SORTEDDATAPARSER_H
#include <string>
#include <functional>

class SortedDataParser {
public:
    virtual std::vector<std::string>::iterator begin() = 0;
    virtual std::vector<std::string>::iterator end() = 0;
    virtual std::string extract_from_line(const std::string line, const std::string& column) const = 0;
};

#endif // SORTEDDATAPARSER_H