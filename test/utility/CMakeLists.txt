set(sources
  all_tests.cpp
)

set(headers
  program_options_tests.hpp
)

add_executable(utility-tests
  ${sources}
  ${headers}
)

target_link_libraries(utility-tests PRIVATE utility gtest_main)
add_test(NAME utility-tests COMMAND utility-tests)
target_compile_options(utility-tests 
PRIVATE 
"-Wno-write-strings" # these get thrown because we are mocking argv
)
