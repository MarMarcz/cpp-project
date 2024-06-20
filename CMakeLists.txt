cmake_minimum_required(VERSION 3.10)
project(cpp-project)

# Ustaw opcje kompilacji
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dodaj pliki źródłowe projektu
add_executable(cpp-project src/main.cpp src/functions.cpp)
enable_testing()
add_subdirectory(tests)