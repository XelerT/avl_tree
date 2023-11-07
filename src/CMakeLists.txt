set(SRC_LIST
        avl
        graphviz
        ui
        utils
        set_comparison
)

foreach(SRC ${SRC_LIST})
        add_subdirectory(${SRC})
endforeach()

set(SRC_LIST "${SRC_LIST}" PARENT_SCOPE)