cmake_minimum_required(VERSION 3.14.1)

project(tox4k)

include(FetchContent)

FetchContent_Declare(
    Toxcore
    GIT_REPOSITORY https://github.com/TokTok/c-toxcore.git
    GIT_TAG 7aab0d9 # v0.2.10
    PATCH_COMMAND git apply ${CMAKE_CURRENT_SOURCE_DIR}/patch/cmake.patch
)
set(BUILD_TOXAV FALSE CACHE INTERNAL "")
set(BOOTSTRAP_DAEMON FALSE CACHE INTERNAL "")
FetchContent_MakeAvailable(Toxcore)

add_library(${PROJECT_NAME} SHARED
    src/api_version.cpp
    src/numeric_constants.cpp
    src/startup_options.cpp
)

target_link_libraries(${PROJECT_NAME}
    toxcore_static
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
            -pedantic-errors;
            -Wall;
            -Wconversion;
            -Werror;
            -Wextra;
            -Wnon-virtual-dtor;
            -Wshadow;
        >
)
