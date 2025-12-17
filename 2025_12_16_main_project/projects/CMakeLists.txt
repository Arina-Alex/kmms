cmake_minimum_required(VERSION 3.2...3.27.5)

project(2025_12_16_main_project)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(bubble_sort)
add_subdirectory(bubble_sort_mf)
add_subdirectory(obuchaika)
add_subdirectory(tests_example)

set(CMAKE_SUPPRESS_REGENERATION true)

