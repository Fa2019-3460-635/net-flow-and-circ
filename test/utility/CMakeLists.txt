add_executable(utility-tests all_tests.cpp) 
target_link_libraries(utility-tests PRIVATE utility gtest_main)
add_test(NAME utility-tests COMMAND utility-tests)
