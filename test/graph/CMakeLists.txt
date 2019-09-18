set(sources
  all_tests.cpp
)

set(headers
  edge_tests.hpp
  graph_tests.hpp
  bfs_tests.hpp
  fordfulkerson_tests.hpp
)

add_executable(graph-tests
  ${sources}
  ${headers}
)
target_link_libraries(graph-tests PRIVATE graph gtest_main)
add_test(NAME graph-tests COMMAND graph-tests)
