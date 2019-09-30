set(sources
  all_tests.cpp
)

set(headers
  graph_tests.hpp
  bfs_tests.hpp
  fordfulkerson_tests.hpp
  circulationgraph_tests.hpp
  circulation_tests.hpp
)

add_executable(graph-tests
  ${sources}
  ${headers}
)
target_link_libraries(graph-tests PRIVATE graph performance gtest_main)
add_test(NAME graph-tests COMMAND graph-tests)
