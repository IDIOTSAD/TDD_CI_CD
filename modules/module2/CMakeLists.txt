################################################################################
# Project Name: module2
#
# Components:
#    - ExampleComponent: Wrapper class of ExampleLibrary
#
################################################################################

# Project information
cmake_minimum_required(VERSION 3.10)
set(PACKAGE_NAME module2)
project(${PACKAGE_NAME} LANGUAGES CXX)

# Export aliases
set(MODULE2_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "MODULE2_PATH")
set(MODULE2_INCLUDE_PATH
        "${MODULE2_PATH}/include" CACHE PATH "MODULE2_INCLUDE_PATH")
set(MODULE2_RESOURCES_PATH
        "${MODULE2_PATH}/resources" CACHE PATH "MODULE2_RESOURCES_PATH")
set(MODULE2_TEST_PATH
        "${MODULE2_PATH}/test" CACHE PATH "MODULE2_TEST_PATH")

# Paths
add_definitions(-DMODULE2_SOURCE_DIR="${MODULE2_PATH}")
add_definitions(-DMODULE2_RESOURCES_DIR="${MODULE2_RESOURCES_PATH}")

# Source files
set(MODULE2_SOURCE_FILES
        src/Stitching.cpp
        )
add_library(${PACKAGE_NAME}
        ${MODULE2_SOURCE_FILES}
        )

# Header files, including 3rdParty
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

target_include_directories(${PACKAGE_NAME} PRIVATE
        ${MODULE2_INCLUDE_PATH}
        )
target_link_libraries(${PACKAGE_NAME} PRIVATE
        ${EASY_PROFILER_LIBS}
        ${SPDLOG_LIBS}
        ${OpenCV_LIBS}
        stdc++fs
        )

# Compile options
target_compile_options(${PACKAGE_NAME} PRIVATE
        -Wall -Wextra -Wpedantic -Werror
        )
set_target_properties(${PACKAGE_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        )

# Unit tests
add_subdirectory(test)
