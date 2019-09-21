cmake_minimum_required(VERSION 3.4.1)

project(tox4k)

add_library(${PROJECT_NAME} SHARED
    native-lib.cpp
)
