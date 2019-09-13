set (CMAKE_CXX_STANDARD 11)

set(
  sources
  edge.cpp
  graph.cpp
  random_graph_generator.cpp
)
set(
  headers
  edge.hpp
  graph.hpp
  random_graph_generator.hpp
)

add_library(graph
    ${sources}
    ${headers}
)

target_include_directories(graph PUBLIC .)
