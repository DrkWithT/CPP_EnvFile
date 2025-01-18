cmake_minimum_required(VERSION 3.28)

project(CPPEnvfile VERSION 0.2.0 LANGUAGES CXX)

set(MY_INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/includes")
set(MY_LIBRARIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

if (DEBUG_BUILD)
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -g -Og)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -O3)
endif ()

add_subdirectory(src)
