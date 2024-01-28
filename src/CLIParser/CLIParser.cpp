#include "CLIParser.h"
#include <exception>
#include <stdexcept>

CLIParser::CLIParser(int argc, const char** argv, const std::vector<std::string> &required_options)
{
    for (int i = 1; i < argc; i += 2) {
        const std::string option(argv[i]);
        if (i + 1 == argc)
            throw std::invalid_argument("Option " + option + " needs a value.");
        if (option[0] != '-')
            throw std::invalid_argument("Expected an option (starting with '-'), got " + option);

        const std::string value(argv[i + 1]);
        if (value[0] == '-')
            throw std::invalid_argument("Expected a value, got an option: " + option);

        parsed_options[option] = value;
    }

    for (const auto& option : required_options) {
        if (parsed_options.find(option) == parsed_options.end())
            throw std::invalid_argument("Missing option '" + option + "'");
    }
}

std::string CLIParser::get_option(const std::string &option)
{
    return parsed_options[option];
}
