target_sources(${CONTAINERS_LIB} 
	PRIVATE
		vector.cpp
		doubly_linked_list.cpp
	PUBLIC
		vector.hpp
		doubly_linked_list.hpp
)

target_include_directories(${CONTAINERS_LIB} PUBLIC
	"${PROJECT_SOURCE_DIR}/src"
)
