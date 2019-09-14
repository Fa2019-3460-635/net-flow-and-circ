set (CMAKE_CXX_STANDARD 11)

set(
  sources
  bfs.cpp
  edge.cpp
  graph.cpp
  random_graph_generator.cpp
)

set(
  headers
  bfs.hpp
  edge.hpp
  graph.hpp
  random_graph_generator.hpp
)

add_library(graph
    ${sources}
    ${headers}
)

target_include_directories(graph PUBLIC .)
