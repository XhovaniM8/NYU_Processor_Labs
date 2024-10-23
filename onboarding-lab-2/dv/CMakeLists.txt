find_package(Catch2 3 CONFIG REQUIRED)

add_executable(tests)

nyu_link_sv(tests PRIVATE lab2)
nyu_target_verilate(tests
  TOP_MODULES
    Exercise1
    Exercise2
    Exercise3
    Exercise4
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_compile_features(tests PRIVATE cxx_std_23)

include(Catch)
catch_discover_tests(tests)
