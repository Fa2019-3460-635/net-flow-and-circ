#include <deque>
#include <fstream>
#include <iostream>

#include "bfs.hpp"
#include "fordfulkerson.hpp"
#include "random.hpp"
#include "random_flow_network.hpp"
#include "random_graph.hpp"
#include "timer.hpp"
#include "tree.hpp"

/**
 * Randomly generates a set of graphs, a starting node, and an ending node.
 *
 * Measures the milliseconds that elapse while the BFS algorithm is applied
 * to each graph.
 *
 * Writes the graph size and BFS duration to the given output stream using
 * a JSON schema.
 */
void bfs_measurements (std::ostream & out_stream)
{
  int const NUM_SAMPLES = 10;
  int const MIN_NUM_VERTICES = 2;
  int const MAX_NUM_VERTICES = 1000;

  Tree measurements;

  // record number of samples
  measurements.add({"bfs", "num_samples"}, std::to_string(NUM_SAMPLES));

  // take the measurements
  for (int i = 0; i < NUM_SAMPLES; ++i)
  {
    std::cout << "BFS Measurements: Sample " << i << " / " << NUM_SAMPLES << '\n';

    // Generate a random graph
    int num_vertices = Random::nonneg_int(MIN_NUM_VERTICES, MAX_NUM_VERTICES);
    int num_edges = num_vertices * num_vertices;
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

/**
 * Randomly generates a set of flow networks, converting each flow network
 * to "single-source-single-node".  This way, the flow networks are compatible
 * with the Ford-Fulkerson module.
 *
 * Measures the duration of the Ford-Fulkeson algorithm as it processes each
 * random flow network.
 *
 * Writes the measurements to given output stream using a JSON schema.
 */
void ff_measurements_sparse (std::ostream & out_stream)
{
  int const NUM_SAMPLES = 10;
  int const MIN_NUM_VERTICES = 10;
  int const MAX_NUM_VERTICES = 1000;

  Tree measurements;

  // record number of samples
  measurements.add({"ff", "sparse", "num_samples"}, std::to_string(NUM_SAMPLES));

  // take the measurements
  for (int i = 0; i < NUM_SAMPLES; ++i)
  {
    std::cout << "FF Measurements (sparse): Sample " << i << " of " << NUM_SAMPLES << '\n';

    // Generate a random grapn
    int num_vertices = Random::nonneg_int(MIN_NUM_VERTICES, MAX_NUM_VERTICES);
    int num_edges = num_vertices;
    graph::FlowNetwork network = RandomFlowNetwork::get_random_flow_network(num_vertices, num_edges);

    // Measure duration of BFS algorithm
    Timer timer;
    auto start_ms = timer.milliseconds();
    graph::FordFulkerson::max_flow(network);
    auto end_ms = timer.milliseconds();

    // Record Sample Data
    std::string label = std::to_string(i);
    measurements.add({"ff", "sparse", label, "num_edges"},    std::to_string(network.get_number_of_edges()));
    measurements.add({"ff", "sparse", label, "num_vertices"}, std::to_string(num_vertices));
    measurements.add({"ff", "sparse", label, "milliseconds"}, std::to_string(end_ms - start_ms));
  }

  // write the measurements to the output stream
  measurements.write(out_stream);
}

/**
 * Randomly generates a set of flow networks, converting each flow network
 * to "single-source-single-node".  This way, the flow networks are compatible
 * with the Ford-Fulkerson module.
 *
 * Measures the duration of the Ford-Fulkeson algorithm as it processes each
 * random flow network.
 *
 * Writes the measurements to given output stream using a JSON schema.
 */
void ff_measurements_dense (std::ostream & out_stream)
{
  Tree measurements;

  // configure test parameters
  int const NUM_SAMPLES = 10;
  int const MIN_NUM_VERTICES = 10;
  int const MAX_NUM_VERTICES = 1000;

  // record number of samples
  measurements.add({"ff", "dense", "num_samples"}, std::to_string(NUM_SAMPLES));

  // take the measurements
  for (int i = 0; i < NUM_SAMPLES; ++i)
  {
    std::cout << "FF Measurements (dense): Sample " << i << " of " << NUM_SAMPLES << '\n';

    // Generate a connected graph
    int num_vertices = Random::nonneg_int(MIN_NUM_VERTICES, MAX_NUM_VERTICES);
    graph::FlowNetwork network = RandomFlowNetwork::get_procedurally_generated_connected_graph(num_vertices);

    // Measure duration of BFS algorithm
    Timer timer;
    auto start_ms = timer.milliseconds();
    graph::FordFulkerson::max_flow(network);
    auto end_ms = timer.milliseconds();

    // Record Sample Data
    std::string label = std::to_string(i);
    measurements.add({"ff", "dense", label, "num_edges"},    std::to_string(network.get_number_of_edges()));
    measurements.add({"ff", "dense", label, "num_vertices"}, std::to_string(num_vertices));
    measurements.add({"ff", "dense", label, "milliseconds"}, std::to_string(end_ms - start_ms));
  }

  // write the measurements to the output stream
  measurements.write(out_stream);
}

//==============================================================================
// main function
//==============================================================================

int main ()
{
  // measure the performance of breadth-first search
  {
    std::cout << "Measuring BFS algorithm.\n";
    std::ofstream out_file ("data.bfs.json");
    bfs_measurements(out_file);
  }
  
  // measure the performance of Edmonds-Karp algorithm (for sparse graphs)
  {
    std::cout << "Measuring Ford-Fulkerson algorithm (for sparse graphs).\n";
    std::ofstream out_file ("data.ff.sparse.json");
    ff_measurements_sparse(out_file);
  }

  // measure the performance of Edmonds-Karp algorithm (for dense graphs)
  {
    std::cout << "Measuring Ford-Fulkerson algorithm (for dense graphs).\n";
    std::ofstream out_file("data.ff.dense.json");
    ff_measurements_dense(out_file);
  }
  
  std::cout << "Done.\n";
}
