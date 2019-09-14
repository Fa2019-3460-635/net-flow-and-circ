#include <fstream>
#include <iostream>

#include "bfs.hpp"
#include "random.hpp"
#include "random_graph.hpp"
#include "timer.hpp"
#include "tree.hpp"

//==============================================================================
// function prototypes
//==============================================================================

/**
 * Randomly generates a set of graphs, a starting node, and an ending node.
 * Measures the milliseconds that elapse while the BFS algorithm is applied
 * to each graph.
 * Writes the graph size and BFS duration to the given output stream using the
 * following JSON schema:
 *
 * "bfs": {
 *   "0": {
 *     "milliseconds": "0.001",
 *     "num_edges": "10",
 *     "num_vertices": "100"
 *   }, 
 *   "1": {
 *     "milliseconds": "0.001",
 *     "num_edges": "20",
 *     "num_vertices": "200"
 *   },  
 *   ...
 * }
 *
 */
void bfs_measurements (std::ostream &);

//==============================================================================
// main function
//==============================================================================

int main ()
{
  // measure the BFS algorithm
  bfs_measurements(std::cout);
}

//==============================================================================
// helper function implementations
//==============================================================================

void bfs_measurements (std::ostream & out_stream)
{
  Tree measurements;

  // configure test parameters
  int const NUM_SAMPLES = 10000;
  int const MIN_NUM_EDGES = 10;
  int const MAX_NUM_EDGES = 1000;
  int const MIN_NUM_VERTICES = 10;
  int const MAX_NUM_VERTICES = 100;

  // record number of samples
  measurements.add({"bfs", "num_samples"}, std::to_string(NUM_SAMPLES));

  // take the measurements
  for (int i = 0; i < NUM_SAMPLES; ++i)
  {
    // Generate a random grapn
    int num_vertices = Random::nonneg_int(MIN_NUM_VERTICES, MAX_NUM_VERTICES);
    int num_edges = Random::nonneg_int(MAX_NUM_VERTICES, MAX_NUM_EDGES);
    RandomGraph graph (num_vertices, num_edges);

    // Generate random source and sink vertices
    int source = 0, sink = 0;
    while (source == sink)
    {
      source = Random::nonneg_int(0, num_vertices - 1);
      sink = Random::nonneg_int(0, num_vertices - 1);
    }

    // Measure duration of BFS algorithm
    Timer timer;
    auto start_ms = timer.milliseconds();
    graph::Bfs::bfs_shortest_path(graph, source, sink);
    auto end_ms = timer.milliseconds();

    // Record Sample Data
    std::string label = std::to_string(i);
    measurements.add({"bfs", label, "num_edges"},    std::to_string(num_edges));
    measurements.add({"bfs", label, "num_vertices"}, std::to_string(num_vertices));
    measurements.add({"bfs", label, "milliseconds"}, std::to_string(end_ms - start_ms));
  }

  // write the measurements to the output stream
  measurements.write(out_stream);
}
