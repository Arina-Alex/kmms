project(bubble_sort)

add_executable(${PROJECT_NAME}
    main.cpp
    io.cpp
    sort.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE .)