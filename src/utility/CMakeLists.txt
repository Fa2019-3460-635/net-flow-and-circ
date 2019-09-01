set (CMAKE_CXX_STANDARD 11)

add_library(utility
  program_options.cpp

)

target_include_directories(utility PUBLIC .)
