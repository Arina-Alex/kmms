target_sources(${SORT_LIB}
	PRIVATE
		bubble_sort.cpp
	PUBLIC
		bubble_sort.hpp
)

target_include_directories(${SORT_LIB} PUBLIC
	"${PROJECT_SOURCE_DIR}/src"
)
