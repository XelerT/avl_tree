cmake_minimum_required(VERSION 3.14)

option(SET_DISTANCE "Enable/disable compiling set." OFF)
if (SET_DISTANCE)
        project(set)
else()
        project(avl_tree)
endif()

#build flags
include(cmake/build_flags.cmake)

# version
set(CMAKE_CXX_STANDARD 20)

message("CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")
message("CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")

set(default_build_type "Debug")
set(GTESTS False CACHE BOOL "To build unitests")

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# collect dependencies

add_subdirectory(dep)
message(STATUS "Collected deps: ${DEP_LIST}")
        
# deps

foreach(DEP ${DEP_LIST})
        target_include_directories(${DEP} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dep/${DEP}/include)
        target_include_directories(${DEP} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dep/)
        install(TARGETS ${DEP} DESTINATION bin)
endforeach()

# collect srcs 

add_subdirectory(src)
message(STATUS "Collected srcs: ${SRC_LIST}")

message("Building avl_tree in ${CMAKE_BUILD_TYPE}.")
        
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# srcs

foreach(SRC ${SRC_LIST})
        target_include_directories(${SRC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/${SRC})
        target_include_directories(${SRC} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
                
        install(TARGETS ${SRC} DESTINATION bin)
endforeach()

# create main.cpp

if (SET_DISTANCE)
        add_executable(${PROJECT_NAME} std_set.cpp)
else()
        add_executable(${PROJECT_NAME} main.cpp)
endif()

target_link_libraries(${PROJECT_NAME} ${SRC_LIST} ${DEP_LIST})

# tests

option(UNITESTS "Enable/disable tests" OFF)
if (UNITESTS)
        add_subdirectory(tests)
endif()
#

install()