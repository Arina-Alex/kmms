project(test_example)

set(SORT_LIB ilya_lib)
add_library(${SORT_LIB})

add_subdirectory(src)
add_subdirectory(test)

