set (CMAKE_CXX_STANDARD 11)

set(
  sources
  edge.cpp
  graph.cpp
  bfs.cpp
)
set(
  headers
  edge.hpp
  graph.hpp
  bfs.hpp
)

add_library(graph
    ${sources}
    ${headers}
)

target_include_directories(graph PUBLIC .)
