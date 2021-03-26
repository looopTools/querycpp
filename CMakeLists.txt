cmake_minimum_required(VERSION 3.10)

project(querycpp VERSION 1.0.0 DESCRIPTION "Query C++ SQL query builder")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(querycpp STATIC
    src/database_data_type.cpp
    src/column.cpp
    src/table.cpp
    src/query.cpp
)

target_include_directories(querycpp PRIVATE include/querycpp)
