#include "CookieSearch.h"
#include <iostream>
int main(int argc, const char** argv) {
    auto active = cookie_search_cli(argc, argv);
    
    // Print most active cookies to stdout.
    for (const auto& cookie : active)
        std::cout << cookie << '\n';

    return 0;
}