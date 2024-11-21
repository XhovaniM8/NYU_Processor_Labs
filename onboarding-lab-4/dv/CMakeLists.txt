# Find Catch2 test framework
find_package(Catch2 3 REQUIRED CONFIG)

# Add executable for tests
add_executable(tests)

# Add source files to the test executable
target_sources(tests PRIVATE
    exercise1.cpp
    exercise2.cpp
    exercise3.cpp
    exercise4.cpp
)

# Link the SystemVerilog library to the test executable
nyu_link_sv(tests PRIVATE lab4)

# Specify top modules for Verilator
nyu_target_verilate(tests
    TOP_MODULES Exercise1 Exercise2 Exercise3 Exercise4
)

# Link Catch2 to the tests executable
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# Enable test discovery
include(Catch)
catch_discover_tests(tests)
