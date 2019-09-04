add_subdirectory(graph)
add_subdirectory(utility)

set(
    sources
    main.cpp
)

add_executable(
    main
    ${sources}
)

target_include_directories(
    main
    PRIVATE
    graph
    utility
)

target_link_libraries(
    main
    PRIVATE
    graph
    utility
)
