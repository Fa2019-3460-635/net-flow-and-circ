#include <iostream>
#include "tree.hpp"

void bfs_measurements (Tree & measurements)
{
  // configure test parameters
  int const NUM_SAMPLES = 100000;
  int const MAX_NUM_EDGES = 10000;
  int const MAX_NUM_VERTICES = 10000;

  // record number of samples
  measurements.add({"bfs", "num_samples"}, std::to_string(NUM_SAMPLES));

  // take the measurements
  for (int i = 0; i < NUM_SAMPLES; ++i)
  {
    // TODO: Randomize
    int num_edges = 5;
    int num_vertices = 5;

    // Generate a random grapn

    // Measure duration of BFS algorithm

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