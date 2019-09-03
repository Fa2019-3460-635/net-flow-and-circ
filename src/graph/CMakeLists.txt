set (CMAKE_CXX_STANDARD 11)

add_library(graph
  edge.cpp
  graph.cpp
  bfs.cpp
)

target_include_directories(graph PUBLIC .)
