cmake_minimum_required(VERSION 3.14...3.28)

project(
  CookieSearch
  VERSION 1.0
  LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(test)
add_test(NAME example_test COMMAND test)