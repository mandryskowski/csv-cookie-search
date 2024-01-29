add_library(CookieSearchLib CookieSearch.cpp CLIParser/CLIParser.cpp UTC/UTCTimestamp.cpp SortedCSVParser/SortedCSVParser.cpp)

add_executable(CookieSearch main.cpp)
target_link_libraries(CookieSearch PRIVATE CookieSearchLib)