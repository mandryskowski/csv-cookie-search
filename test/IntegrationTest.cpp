#include <gtest/gtest.h>
#include <CookieSearch.h>
#include <iostream>
#include <fstream>
TEST(IntegrationTest, WorksForGivenTestCase) {
    std::ofstream file ("_integration_test_file.csv");
    file << "cookie,timestamp\nAtY0laUfhglK3lC7,2018-12-09T14:19:00+00:00\nSAZuXPGUrfbcn5UA,2018-12-09T10:13:00+00:00\n" \
            "5UAVanZf6UtGyKVS,2018-12-09T07:25:00+00:00\nAtY0laUfhglK3lC7,2018-12-09T06:19:00+00:00\nSAZuXPGUrfbcn5UA,2018-12-08T22:03:00+00:00\n" \
            "4sMM2LxV07bPJzwf,2018-12-08T21:30:00+00:00\nfbcn5UAVanZf6UtG,2018-12-08T09:30:00+00:00\n4sMM2LxV07bPJzwf,2018-12-07T23:30:00+00:00\0";
    file.close();

    {
        const char* argv[] = {"./program", "-f", "_integration_test_file.csv", "-d", "2018-12-09"};
        EXPECT_EQ(cookie_search_cli(sizeof(argv) / sizeof(argv[0]), &argv[0])[0], "AtY0laUfhglK3lC7");
    }

    {
        const char* argv[] = {"./program", "-f", "_integration_test_file.csv", "-d", "2018-12-08"};
        std::vector<std::string> result = {"SAZuXPGUrfbcn5UA", "4sMM2LxV07bPJzwf", "fbcn5UAVanZf6UtG"};
        EXPECT_EQ(cookie_search_cli(sizeof(argv) / sizeof(argv[0]), &argv[0]), result);
    }
    
    
    {
        const char* argv[] = {"./program", "-f", "_integration_test_file.csv", "-d", "2018-12-07"};
        EXPECT_EQ(cookie_search_cli(sizeof(argv) / sizeof(argv[0]), &argv[0])[0], "4sMM2LxV07bPJzwff");
    }
    

    remove("_integration_test_file.csv");
}

