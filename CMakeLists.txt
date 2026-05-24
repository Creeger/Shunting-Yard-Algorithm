cmake_minimum_required(VERSION 3.16)

project(shuntingYard)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(shuntingYard  src/main.cpp src/shuntingYard.cpp)

set(CMAKE_BUILD_TYPE Debug)
enable_testing()

add_executable(tests tests/main.cpp tests/test_tokenizer.cpp tests/test_shuntingYard.cpp src/shuntingYard.cpp)

target_include_directories(tests PRIVATE include)

add_test(NAME TokenizerTests COMMAND runTests)


add_library(sntYrd STATIC src/shuntingYard.cpp)

target_include_directories(sntYrd
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
