cmake_minimum_required(VERSION 2.8)

project(net-flow-and-circ)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)

################################
# Create Doxygen documentation #
################################

# based on instructions at https://vicrucann.github.io/tutorials/quick-cmake-doxygen/
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)

if(DOXYGEN_FOUND)
    #set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
#    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else(DOXYGEN_FOUND)
    message("")
endif(DOXYGEN_FOUND)

#############################################
# commands for generating performance plots #
#############################################

set(PERFORMANCE_PLOTS
  "plot.bfs.png"
  "plot.ff.sparse.png"
  "plot.ff.dense.png"
)

# command for building the plots (by taking measurements and then running
# python scripts)
add_custom_command(
  OUTPUT
    ${PERFORMANCE_PLOTS}
  COMMAND ./bin/measurements
  COMMAND cp ../report/plot.py ./
  COMMAND pipenv install matplotlib
  COMMAND pipenv run python plot.py
)

# target for building the plots
add_custom_target(plots DEPENDS ${PERFORMANCE_PLOTS} measurements)
