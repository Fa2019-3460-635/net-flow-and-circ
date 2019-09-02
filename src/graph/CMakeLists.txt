set (CMAKE_CXX_STANDARD 11)

set(
  sources
  edge.cpp
  graph.cpp
)
set(
  headers
  edge.hpp
  graph.hpp
)

add_library(graph
    ${sources}
    ${headers}
)

target_include_directories(graph PUBLIC .)
