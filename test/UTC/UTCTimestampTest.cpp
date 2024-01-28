#include <gtest/gtest.h>
#include <UTC/UTCTimestamp.h>

TEST(UTCTimestampTest, ReturnsTrue) {
    EXPECT_EQ(UTCTimestamp("xd").xd(), true);
}