target_sources(${LIBRARY}
	PRIVATE
		super_puper_long_numbers.cpp
	PUBLIC
		super_puper_long_numbers.hpp
)

target_include_directories(${LIBRARY} PUBLIC
	"${PROJECT_SOURCE_DIR}/src"
)