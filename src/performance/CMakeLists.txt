set(
	sources
	random_graph_generator.cpp
  tree.cpp
)

set(
	headers
	random_graph_generator.hpp
  tree.hpp
)

add_library(
	performance
	${sources}
	${headers}
)

target_include_directories(performance PUBLIC .)

target_compile_options(performance PRIVATE -std=c++11)

target_link_libraries(performance PRIVATE graph)

add_executable(
  measurements
  measurements.cpp
)
target_link_libraries(measurements PRIVATE performance)
