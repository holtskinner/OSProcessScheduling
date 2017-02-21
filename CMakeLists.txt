cmake_minimum_required(VERSION 2.8)
# Set the project name variable to project1.

# Add your CMAKE_C_FLAGS AND CMAKE_SXX_FLAGS here
# You should include -Wall -Werror -Wshadow
# Make SURE to use -std=c11 and -std=c++11 where relevant.

# Add our include directory to CMake's search paths.

# Compile dyn_array_lib so we can use it.

# Compile the analysis executable.

# link the dyn_array library we compiled against our analysis executable.

# Compile the the tester executable.

# Link ${PROJECT_NAME}_test with dyn_array and gtest and pthread libraries
