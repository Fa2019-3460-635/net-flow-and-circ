set (CMAKE_CXX_STANDARD 11)

set(
  sources
  edge.cpp
  graph.cpp
  bfs.cpp
<<<<<<< HEAD
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
=======
>>>>>>> 5931076495bb91f56bf64b1a8038314c4e03392a
)

target_include_directories(graph PUBLIC .)
