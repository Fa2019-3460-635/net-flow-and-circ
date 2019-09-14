set (CMAKE_CXX_STANDARD 11)

set(
  sources
  bfs.cpp
  edge.cpp
  graph.cpp
)

set(
  headers
  bfs.hpp
  edge.hpp
  graph.hpp
)

add_library(graph
    ${sources}
    ${headers}
)

target_include_directories(graph PUBLIC .)
