set(SRCS
        spin.cpp
)

add_library(avl ${SRCS})
target_include_directories(avl PRIVATE ${CMAKE_BINARY_DIR})