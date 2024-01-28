#include <gtest/gtest.h>
#include <CLIParser/CLIParser.h>
#include <stdexcept>

TEST(CLIParserTest, ParsesOption) {
    const char* argv[] = {"./program", "-o", "value"};
    EXPECT_EQ(CLIParser(sizeof(argv) / sizeof(argv[0]), &argv[0]).get_option("-o"), "value");
}

TEST(CLIParserTest, ForbidsMissingRequiredOption) {
    const char* argv[] = {"./program"};
    EXPECT_THROW(CLIParser(sizeof(argv) / sizeof(argv[0]), &argv[0], {"-o"}), std::invalid_argument);
}

TEST(CLIParserTest, ForbidsMissingValue) {
    const char* argv[] = {"./program", "-o"};
    EXPECT_THROW(CLIParser(sizeof(argv) / sizeof(argv[0]), &argv[0]), std::invalid_argument);
}

TEST(CLIParserTest, ForbidsOptionAsValue) {
    const char* argv[] = {"./program", "-o", "-p"};
    EXPECT_THROW(CLIParser(sizeof(argv) / sizeof(argv[0]), &argv[0]), std::invalid_argument);
}

TEST(CLIParserTest, ParsesMultipleOptions) {
    const char* argv[] = {"./program", "-o", "val1", "-p", "val2"};
    CLIParser parser(sizeof(argv) / sizeof(argv[0]), &argv[0]);
    EXPECT_EQ(parser.get_option("-o"), "val1");
    EXPECT_EQ(parser.get_option("-p"), "val2");
}