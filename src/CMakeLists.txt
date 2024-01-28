add_library(CookieSearchLib CLIParser/CLIParser.cpp)

add_executable(CookieSearch main.cpp)
target_link_libraries(CookieSearch PRIVATE CookieSearchLib)