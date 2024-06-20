add_executable(tests tests/test.cpp src/functions.cpp)
target_link_libraries(tests gtest gtest_main)

# Dodaj testy do CTest
include(GoogleTest)
gtest_discover_tests(tests)
