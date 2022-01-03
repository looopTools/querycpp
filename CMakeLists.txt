cmake_minimum_required(VERSION 3.10)

project(querycpp VERSION 1.1.0 DESCRIPTION "Query C++ SQL query builder" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

add_library(querycpp STATIC
    src/querycpp/column.cpp
    src/querycpp/table.cpp
    src/querycpp/query.cpp
    )
  
target_include_directories(querycpp PRIVATE include)
  
# Setting up google test dependency

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Setting up all tests
enable_testing()  

add_executable(test_helpers ../test/test_helpers/test_helpers.cpp)
add_executable(test_sql_string ../test/test_sql_string/test_sql_string.cpp)
add_executable(test_column ../test/test_column/test_column.cpp)
add_executable(test_table ../test/test_table/test_table.cpp)
add_executable(test_query ../test/test_query/test_query.cpp)

target_include_directories(test_helpers PRIVATE include)             
target_link_libraries(test_helpers querycpp fmt gtest_main)

target_include_directories(test_sql_string PRIVATE include)             
target_link_libraries(test_sql_string querycpp fmt gtest_main)

target_include_directories(test_column PRIVATE include)             
target_link_libraries(test_column querycpp fmt gtest_main)

target_include_directories(test_table PRIVATE include)             
target_link_libraries(test_table querycpp fmt gtest_main)

target_include_directories(test_query PRIVATE include)             
target_link_libraries(test_query querycpp fmt gtest_main)

add_test(NAME test_helpers COMMAND test_helpers)
add_test(NAME test_sql_string COMMAND test_sql_string)
add_test(NAME test_column COMMAND test_column)
add_test(NAME test_table COMMAND test_table)
add_test(NAME test_query COMMAND test_query)
