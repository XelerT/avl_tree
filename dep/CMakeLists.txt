set(DEP_LIST
        fmt
)

foreach(DEP ${DEP_LIST})
        add_subdirectory(${DEP})
endforeach()

set(DEP_LIST "${DEP_LIST}" PARENT_SCOPE)
