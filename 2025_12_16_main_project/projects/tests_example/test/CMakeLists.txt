set(SOURCES
	test_bubble.cpp
)
set(TEST_TARGET test_bubble)
add_executable( ${TEST_TARGET} ${SOURCES})
target_link_libraries(${TEST_TARGET}
	gtest_main
	${SORT_LIB}
)

add_test(${TEST_TARGET} ${TEST_TARGET})

