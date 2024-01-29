#ifndef SORTEDCSVPARSER_H
#define SORTEDCSVPARSER_H
#include "SortedDataParser.h"
#include <string>
#include <unordered_map>

// Assumes CSV file is sorted by key.
class SortedCSVParser : public SortedDataParser {
public:
    SortedCSVParser(const std::string& filename);

    virtual std::vector<std::string>::iterator begin() override;
    virtual std::vector<std::string>::iterator end() override;

    // Extract column information from a line
    virtual std::string extract_from_line(const std::string line, const std::string& column) const override;
private:
    std::unordered_map<std::string, uint32_t> columns;
    std::vector<std::string> lines;
};

#endif //SORTEDCSVPARSER_H