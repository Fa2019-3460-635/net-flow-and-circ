set (CMAKE_CXX_STANDARD 11)

set(
  sources
  graph.cpp
  bfs.cpp
  fordfulkerson.cpp
  flow_network.cpp
)
set(
  headers
  graph.hpp
  bfs.hpp
  fordfulkerson.hpp
  flow_network.hpp
)

add_library(graph
    ${sources}
    ${headers}
)

target_include_directories(graph PUBLIC .)
