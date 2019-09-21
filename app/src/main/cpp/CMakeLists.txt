cmake_minimum_required(VERSION 3.14.1)

project(tox4k)

include(FetchContent)

FetchContent_Declare(
    Sodium
    GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
)
set(SODIUM_DISABLE_TESTS ON CACHE INTERNAL "")
FetchContent_MakeAvailable(Sodium)

add_library(${PROJECT_NAME} SHARED
    native-lib.cpp
)

target_link_libraries(${PROJECT_NAME}
    sodium
)
