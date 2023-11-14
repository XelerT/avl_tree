set(SRCS
        set_comparison.cpp
)

add_library(set_comparison ${SRCS})
target_include_directories(set_comparison PRIVATE ${CMAKE_BINARY_DIR})