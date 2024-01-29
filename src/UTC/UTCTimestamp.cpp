#include "UTCTimestamp.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

static void parse_separated(const std::string& str, const std::vector<int*>& format, const char separator);

UTCTimestamp::UTCTimestamp(std::string str)
{
    // Separate input string into time zone and date+time
    std::string time_zone_string;
    if (str.find("+") != std::string::npos) {
        time_zone_string = str.substr(str.find("+") + 1);
        str = str.substr(0, str.find("+"));
    }

    // Separate what's remaining into date and time
    const std::string day_string = str.substr(0, str.find("T"));
    const std::string time_string = day_string.length() == str.length() ? std::string() : str.substr(day_string.length() + 1);

    std::tm tm{}; // Zero initialise
    int tz_hour = 0, tz_min = 0;

    // Parse date, then time, tnen time zone.
    parse_separated(day_string, {&tm.tm_year, &tm.tm_mon, &tm.tm_mday}, '-');
    parse_separated(time_string, {&tm.tm_hour, &tm.tm_min, &tm.tm_sec}, ':');
    parse_separated(time_zone_string, {&tz_hour, &tz_min}, ':');

    // Basic input validation. Not comprehensive; requires more testing and consideration of edge cases (leap years).
    const int month_lenghts[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (tm.tm_year < 1900) throw std::out_of_range("Invalid year");
    if (tm.tm_mon < 1 || tm.tm_mon > 12) throw std::out_of_range("Invalid month");
    if (tm.tm_mday < 1 || tm.tm_mday > month_lenghts[tm.tm_mon - 1]) throw std::out_of_range("Invalid day");
    if (tm.tm_hour < 0 || tm.tm_hour > 23) throw std::out_of_range("Invalid hour");
    if (tm.tm_min < 0 || tm.tm_min > 59) throw std::out_of_range("Invalid minute");
    if (tm.tm_sec < 0 || tm.tm_sec > 59) throw std::out_of_range("Invalid second");
    // Timezones range from -12 to 14 inclusive [-12, 14]
    if (tz_hour < -12 || tz_hour > 14) throw std::out_of_range("Invalid timezone hour");
    if (tz_min < 0 || tz_min > 59) throw std::out_of_range("Invalid timezone minute");

    // std::mktime will allow negative hours/minutes and produce a valid epoch time with this operation
    tm.tm_hour -= tz_hour;
    tm.tm_min -= tz_min;

    tm.tm_year -= 1900; // tm_year represents years since 1900.
    tm.tm_mon -= 1; // tm_year represents months since January (so counting from 0).

    epoch_time = std::mktime(&tm);
}

UTCTimestamp UTCTimestamp::just_day() const
{
    return UTCTimestamp(epoch_time - epoch_time % 86400);
}

UTCTimestamp::UTCTimestamp(uint64_t epoch_time): epoch_time(epoch_time) {}

static void parse_separated(const std::string& str, const std::vector<int*>& format, const char separator) {
    std::istringstream ss(str);
    std::string token;
    for (int i = 0; i < format.size(); i++) {
        if (!std::getline(ss, token, separator))
            break;

        *format[i] = std::stoi(token);
    }
}

bool operator==(const UTCTimestamp& lhs, const UTCTimestamp& rhs)
{
    return lhs.epoch_time == rhs.epoch_time;
}

bool operator<(const UTCTimestamp &lhs, const UTCTimestamp &rhs)
{
    return lhs.epoch_time < rhs.epoch_time;
}

bool operator<=(const UTCTimestamp &lhs, const UTCTimestamp &rhs)
{
    return lhs.epoch_time <= rhs.epoch_time;
}
