# Start of root CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

# Setting the project name based on the root folder name
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Common build flags
set(CMAKE_CXX_FLAGS         "-Wall -Wextra -std=c++17")

# Individual build type flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -g3")
set(CMAKE_CXX_FLAGS_TEST    "${CMAKE_CXX_FLAGS} -O0 -g3 -D__test_build__ --coverage")

# List of components
set(COMPONENTS 
  )

add_executable(${PROJECT_NAME} main.cpp)

# Add component subdirectories using loop
foreach(COMPONENT ${COMPONENTS})
    add_subdirectory(components/${COMPONENT})
endforeach()

# Linking to coverage report tool in case of test build
if(CMAKE_BUILD_TYPE MATCHES Test)
    target_link_libraries(${PROJECT_NAME} gcov)
endif()

# Printing the size of build after building
add_custom_command(TARGET ${PROJECT_NAME} 
    POST_BUILD COMMAND size $<TARGET_FILE:${PROJECT_NAME}>)

# End of root CMakeLists.txt
