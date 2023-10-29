cmake_minimum_required(VERSION 3.14)

project(avl_tree)

# version

if (NOT CMAKE_CXX_STANDARD AND NOT CMAKE_CXX_COMPILER)
        set(CMAKE_CXX_STANDARD 20)
endif()

set(default_build_type "Debug")
set(GTESTS False CACHE BOOL "To build unitests")

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# flags

set(CMAKE_CXX_FLAGS_DEBUG "-Wall")

# collect srcs 

add_subdirectory(src)
message(STATUS "Collected srcs: ${SRC_LIST}")

message("Building avl_tree in ${CMAKE_BUILD_TYPE}.")
        
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# srcs

foreach(SRC ${SRC_LIST})
        target_include_directories(${SRC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/${SRC})
        target_include_directories(${SRC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
                
        install(TARGETS ${SRC} DESTINATION bin)
endforeach()
        
# create main.cpp

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} ${SRC_LIST})
        
install(TARGETS ${PROJECT_NAME})

# tests

option(COE_BUILD_TESTS "Enable/disable tests" ON)
if (COE_BUILD_TESTS)
        add_subdirectory(tests)
endif()
# 

install()