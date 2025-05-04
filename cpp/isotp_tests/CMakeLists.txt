# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

set(prj_name "isotp-cpp-tests")
set(prj_root ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Project name and language
project(${prj_name} LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define an array of test names
set(test_names
	test_isotp_send
)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g")

file(GLOB uut_srcs "${CMAKE_CURRENT_SOURCE_DIR}/../*.cpp")
# Iterate over test_names and create an executable for each test
foreach(test_name IN LISTS test_names)
	add_executable(${test_name} ${CMAKE_CURRENT_SOURCE_DIR}/${test_name}.cpp ${uut_srcs})
	target_include_directories(${test_name} PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/..
	)
	add_test(NAME cpp_test_${test_name} COMMAND ${test_name})
endforeach()

# Enable testing
enable_testing()

# Link libraries if needed (example: pthread)
# target_link_libraries(${prj_name} PRIVATE pthread)