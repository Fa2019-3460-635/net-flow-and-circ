add_subdirectory(graph)
add_subdirectory(utility)

set(
    exec_name
    project_one
)

set(
    sources
    main.cpp
)

add_executable(
    ${exec_name}
    ${sources}
)

target_include_directories(
    ${exec_name}
    PRIVATE
    graph
    utility
)

target_link_libraries(
    ${exec_name}
    PRIVATE
    graph
    utility
)
