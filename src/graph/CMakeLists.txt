set (CMAKE_CXX_STANDARD 11)

set(
  sources
  graph.cpp
  bfs.cpp
  fordfulkerson.cpp
  flow_network.cpp
  circulationgraph.cpp
  circulation.cpp
)

set(
  headers
  graph.hpp
  bfs.hpp
  fordfulkerson.hpp
  flow_network.hpp
  circulationgraph.hpp
  circulation.hpp
)

add_library(graph
    ${sources}
    ${headers}
)

target_include_directories(graph PUBLIC .)
