add_executable(graph-tests all_tests.cpp) 
target_link_libraries(graph-tests PRIVATE graph gtest_main)
add_test(NAME graph-tests COMMAND graph-tests)
