cmake_minimum_required(VERSION 3.5)

project(CXX_geek LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tokenize_string src/tokenize_string.cpp)
add_executable(string_contain_only_letters src/string_contain_only_letters.cpp)
