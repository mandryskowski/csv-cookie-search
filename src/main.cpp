#include "CLIParser/CLIParser.h"
#include "UTC/UTCTimestamp.h"
int main(int argc, const char** argv) {
    CLIParser cli(argc, argv, {"-f", "-d"});
    UTCTimestamp timestamp(cli.get_option("-d"));
    std::string filename = cli.get_option("-f");


    return 0;
}