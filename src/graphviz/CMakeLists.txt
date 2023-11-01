set(SRCS
        graphviz.cpp
)

add_library(graphviz ${SRCS})
target_include_directories(graphviz PRIVATE ${CMAKE_BINARY_DIR})