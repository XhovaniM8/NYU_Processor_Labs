cmake_minimum_required(VERSION 3.30)

include(cmake/BootstrapVcpkg.cmake)

project(week-two-lab)

find_package(nyu-cmake CONFIG REQUIRED)

add_subdirectory(rtl)
add_subdirectory(dv)