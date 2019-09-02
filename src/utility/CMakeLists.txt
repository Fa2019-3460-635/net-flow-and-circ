set (CMAKE_CXX_STANDARD 11)

set(
  sources
  program_options.cpp
)

set(
  headers
  program_options.hpp
)

add_library(utility
    ${sources}
    ${headers}
)

target_include_directories(utility PUBLIC .)
