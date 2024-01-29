#include <gtest/gtest.h>
#include <UTC/UTCTimestamp.h>
#include <stdexcept>

TEST(UTCTimestampTest, ForbidsWrongYear) {
    EXPECT_THROW(UTCTimestamp("1410-01-01"), std::out_of_range);
}
TEST(UTCTimestampTest, ForbidsWrongMonth) {
    EXPECT_THROW(UTCTimestamp("2024-13-01"), std::out_of_range);
}
TEST(UTCTimestampTest, ForbidsWrongDay) {
    EXPECT_THROW(UTCTimestamp("2024-01-40"), std::out_of_range);
    EXPECT_THROW(UTCTimestamp("2024-02-30"), std::out_of_range);
}
TEST(UTCTimestampTest, ComparesDayCorrectly) {
    EXPECT_EQ(UTCTimestamp("2024-01-29T13:52:03").just_day(), UTCTimestamp("2024-01-29"));
}
TEST(UTCTimestampTest, ComparesDayCorrectlyWithTimeZone) {
    EXPECT_EQ(UTCTimestamp("2024-01-29T02:52:03+03:00").just_day(), UTCTimestamp("2024-01-28"));
}