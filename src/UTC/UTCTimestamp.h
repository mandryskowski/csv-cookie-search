#ifndef UTCTIMESTAMP_H
#define UTCTIMESTAMP_H
#include <string>

class UTCTimestamp {
public:
    UTCTimestamp(std::string str);
    UTCTimestamp just_day() const;

private:
    UTCTimestamp(uint64_t epoch_time);
    uint64_t epoch_time;

    friend bool operator==(const UTCTimestamp& lhs, const UTCTimestamp& rhs);
    friend bool operator<(const UTCTimestamp& lhs, const UTCTimestamp& rhs);
    friend bool operator<=(const UTCTimestamp& lhs, const UTCTimestamp& rhs);
};

bool operator==(const UTCTimestamp& lhs, const UTCTimestamp& rhs);
bool operator<(const UTCTimestamp& lhs, const UTCTimestamp& rhs);
bool operator<=(const UTCTimestamp& lhs, const UTCTimestamp& rhs);

#endif // UTCTIMESTAMP_H