cmake_minimum_required(VERSION 3.24)

# Include vcpkg setup if needed
include(cmake/BootstrapVcpkg.cmake)

# Specify the project
project(week-four-lab VERSION 1.0.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages
find_package(nyu-cmake CONFIG REQUIRED)

# Define the interface library
add_library(lab4 INTERFACE)

# Add subdirectories
add_subdirectory(rtl)

# Conditional testing setup
if(NYU_BUILD_TESTS)
  enable_testing()
  add_subdirectory(dv)
endif()
