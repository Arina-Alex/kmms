set(SOURCES
	numbers_test.cpp
)
set(TEST_TARGET numbers_test)
add_executable(${TEST_TARGET} ${SOURCES})
target_link_libraries(${TEST_TARGET}
	gtest_main
	
	${LIBRARY}
)

add_test(${TEST_TARGET} ${TEST_TARGET})