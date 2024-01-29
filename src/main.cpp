#include "CLIParser/CLIParser.h"
#include "UTC/UTCTimestamp.h"
#include <fstream>
#include <algorithm>
#include "SortedCSVParser/SortedCSVParser.h"
#include <iostream>
std::vector<std::string> active_cookies(SortedDataParser& parser, std::vector<std::string>::iterator it, std::vector<std::string>::iterator end)
{
    std::unordered_map<std::string, uint32_t> cookie_count;
    std::vector<std::string> most_active;
    int highest_activity = 0;

    while(it != end) {
        std::string cookie = parser.extract_from_line(*(it++), "cookie");

        if (cookie_count.find(cookie) == cookie_count.end())
            cookie_count[cookie] = 1;
        else
            cookie_count[cookie]++;

        if (cookie_count[cookie] > highest_activity) {
            highest_activity++;
            most_active = {cookie};
        } else {
            most_active.push_back(cookie);
        }
    }

    return most_active;
}


int main(int argc, const char** argv) {
    const CLIParser cli(argc, argv, {"-f", "-d"});
    UTCTimestamp timestamp(cli.get_option("-d"));
    std::string filename = cli.get_option("-f");
    SortedCSVParser csv_parser(filename);

    // Find first and last entry matching date.
    auto lb = std::lower_bound(csv_parser.begin(), csv_parser.end(), timestamp, [csv_parser](const std::string& line, const UTCTimestamp timestamp){ return timestamp < UTCTimestamp(csv_parser.extract_from_line(line, "timestamp")).just_day(); });
    auto ub = std::upper_bound(csv_parser.begin(), csv_parser.end(), timestamp, [csv_parser](const UTCTimestamp timestamp, const std::string& line){ return UTCTimestamp(csv_parser.extract_from_line(line, "timestamp")).just_day() < timestamp; });

    // Find the most active cookies among the ones that match the date.
    auto active = active_cookies(csv_parser, lb, ub); 

    // Print most active cookies to stdout.
    for (auto cookie : active)
        std::cout << cookie << '\n';
    
    return 0;
}