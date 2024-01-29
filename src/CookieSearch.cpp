#include "CookieSearch.h"
#include "CLIParser/CLIParser.h"
#include "UTC/UTCTimestamp.h"
#include <fstream>
#include <algorithm>
#include "SortedCSVParser/SortedCSVParser.h"
#include <iostream>
std::vector<std::string> active_cookies(SortedDataParser& parser, std::vector<std::string>::iterator it, std::vector<std::string>::iterator end)
{
    // Keep track of the number of occurences for every cookie.
    std::unordered_map<std::string, uint32_t> cookie_count;
    // Most active cookies in the current iteration. If a cookie reaches a new highest occurence count, the list gets reset.
    std::vector<std::string> most_active;
    // Current highest occurence count.
    int highest_activity = 0;

    // For every matching line
    while(it != end) {
        // Extract the cookie ID
        std::string cookie = parser.extract_from_line(*(it++), "cookie");

        // Create an entry in the hash map or increment the occurence count if it exists.
        if (cookie_count.find(cookie) == cookie_count.end())
            cookie_count[cookie] = 1;
        else
            cookie_count[cookie]++;

        // If new highest occurence count reached, clear the list and make a new singleton with this cookie.
        if (cookie_count[cookie] > highest_activity) {
            highest_activity++;
            most_active = {cookie};
        } else { // Otherwise, add to the most active list
            most_active.push_back(cookie);
        }
    }

    return most_active;
}


std::vector<std::string> cookie_search_cli(int argc, const char** argv) {
    const CLIParser cli(argc, argv, {"-f", "-d"});
    UTCTimestamp timestamp(cli.get_option("-d"));
    std::string filename = cli.get_option("-f");
    SortedCSVParser csv_parser(filename);

    // Find first and last entry matching date.
    auto lb = std::lower_bound(csv_parser.begin(), csv_parser.end(), timestamp, [csv_parser](const std::string& line, const UTCTimestamp timestamp){ return timestamp < UTCTimestamp(csv_parser.extract_from_line(line, "timestamp")).just_day(); });
    auto ub = std::upper_bound(csv_parser.begin(), csv_parser.end(), timestamp, [csv_parser](const UTCTimestamp timestamp, const std::string& line){ return UTCTimestamp(csv_parser.extract_from_line(line, "timestamp")).just_day() < timestamp; });

    // Find the most active cookies among the ones that match the date.
    return active_cookies(csv_parser, lb, ub); 
}