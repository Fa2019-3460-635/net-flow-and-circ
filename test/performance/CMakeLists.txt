set(sources
  all_tests.cpp
)

set(headers
	tree_tests.hpp
)

set(executable_name performance-tests)

add_executable(${executable_name}
  ${sources}
  ${headers}
)
target_link_libraries(${executable_name} PRIVATE performance gtest_main)

add_test(NAME ${executable_name} COMMAND ${executable_name})
