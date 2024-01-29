add_library(CookieSearchLib CLIParser/CLIParser.cpp UTC/UTCTimestamp.cpp)

add_executable(CookieSearch main.cpp)
target_link_libraries(CookieSearch PRIVATE CookieSearchLib)