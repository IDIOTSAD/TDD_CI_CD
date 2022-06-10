cmake_minimum_required(VERSION 3.10)
project(SVSLAM LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

#------------------------------------------
# CXX build flags
#------------------------------------------
set(CMAKE_VERBOSE_MAKEFILE no)
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_BUILD_TYPE)
    # Terminate build if build option is invalid (i.e. Not Debug or Release)
    if (NOT CMAKE_BUILD_TYPE MATCHES "Debug" AND NOT CMAKE_BUILD_TYPE MATCHES "Release")
        message(FATAL_ERROR "Invalid build type: should be either Debug or Release")
    endif (NOT CMAKE_BUILD_TYPE MATCHES "Debug" AND NOT CMAKE_BUILD_TYPE MATCHES "Release")

    message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif (CMAKE_BUILD_TYPE)

# Default build type (Release)
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Build type: Release (default)")
    set(CMAKE_BUILD_TYPE "Release" CACHE
            STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release") # Set the possible values of build type for cmake-gui
endif (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "-g -O0 -fPIC")
    add_definitions(-DBUILD_DEBUG=1)
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_CXX_FLAGS "-g -O3 -DNDEBUG -fPIC")
    add_definitions(-DBUILD_DEBUG=0)
endif ()

#----------------------------------------
# Load third party libraries
#----------------------------------------

# Define system-installed library paths
list(APPEND CMAKE_PREFIX_PATH /usr)

# Load libraries
include(cmake_files/find_eigen3)
include(cmake_files/find_image_exts) # ${IMAGE_LIBS} - png, jpeg, tiff, zlib
include(cmake_files/find_yaml_cpp)
include(cmake_files/find_opencv)
include(cmake_files/find_ceres)
include(cmake_files/find_gl) # ${GL_LIBS} - OpenGL, GLUT, GLEW
include(cmake_files/find_pangolin)
include(cmake_files/find_gtest)
include(cmake_files/find_easy_profiler)
include(cmake_files/find_doxygen)
include(cmake_files/find_spdlog)

include_directories("modules")

#----------------------------------------
# Build internal libraries
#----------------------------------------
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(modules/module1)
add_subdirectory(modules/module2)
#add_compile_options(-Wall -std=c++17 -O2 -fPIC)

#----------------------------------------
# Executables
#----------------------------------------

add_executable(exec_stitching
        examples/exec_stitching.cpp
        )
target_include_directories(exec_stitching PRIVATE
        ${MODULE2_INCLUDE_PATH}
        )
target_link_libraries(exec_stitching PRIVATE
        module2
        )

add_executable(exec_matrix_mul
        examples/exec_matrix_mul.cpp
        )
target_include_directories(exec_matrix_mul PRIVATE
        ${MODULE1_INCLUDE_PATH}
        )
target_link_libraries(exec_matrix_mul PRIVATE
        module1
        )