cmake_minimum_required (VERSION 3.5)

# Set the project name variable to project1.
project(project1)

# Add your CMAKE_C_FLAGS AND CMAKE_SXX_FLAGS here
# You should include -Wall -Werror -Wshadow
# Make SURE to use -std=c11 and -std=c++11 where relevant.
# -Wall -Wextra -Wshadow -Werror
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror -I../include -g")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror -I../include -g")

# Add our include directory to CMake's search paths.
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Compile dyn_array_lib so we can use it.
add_library(dyn_array SHARED src/dyn_array.c include/dyn_array.h) 
add_library(process_scheduling SHARED src/process_scheduling.c include/process_scheduling.h)

set_target_properties(dyn_array PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(process_scheduling PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Compile the analysis executable.
add_executable(analysis src/analysis.c)

# link the dyn_array library we compiled against our analysis executable.
target_link_libraries(analysis dyn_array process_scheduling)

# Compile the the tester executable.
add_executable(${PROJECT_NAME}_test test/tests.cpp)

# Link ${PROJECT_NAME}_test with dyn_array and gtest and pthread libraries
target_compile_definitions(${PROJECT_NAME}_test PRIVATE GRAD_TESTS=0)
target_link_libraries(${PROJECT_NAME}_test dyn_array process_scheduling gtest pthread)

enable_testing()
add_test(NAME    ${PROJECT_NAME}_test 
         COMMAND ${PROJECT_NAME}_test)