#ifndef CLIPARSER_H
#define CLIPARSER_H
#include <string>
#include <vector>
#include <unordered_map>

class CLIParser {
public:
    CLIParser(int argc, const char** argv, const std::vector<std::string>& required_options = {});
    std::string get_option(const std::string&) const;

private:

    std::unordered_map<std::string, std::string> parsed_options;
};

#endif // CLIPARSER_H