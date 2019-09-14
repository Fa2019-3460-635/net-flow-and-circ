#include <iostream>

#include "bfs.hpp"
#include "random.hpp"
#include "random_graph.hpp"
#include "tree.hpp"

void bfs_measurements (Tree & measurements)
{
  // configure test parameters
  int const NUM_SAMPLES = 1000;

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
    graph::Bfs::bfs_shortest_path(graph, source, sink);

    // Record Sample Data
    std::string label = "Sample " + std::to_string(i);
    measurements.add({"bfs", label, "num_edges"}, std::to_string(num_edges));
    measurements.add({"bfs", label, "num_vertices"}, std::to_string(num_vertices));
    //measurements.add({"bfs", label, "milliseconds"}, std::to_string(milliseconds));
  }
}

int main ()
{
	Tree measurement_data;
  bfs_measurements(measurement_data);
  measurement_data.write(std::cout);
}