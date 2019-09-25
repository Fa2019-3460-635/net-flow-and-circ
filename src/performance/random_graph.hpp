#pragma once

#include "graph.hpp"

class RandomGraph : public graph::Graph
{
public:
  /**
   * Instantiates a graph with the given numbers of vertices and edges.
   * The starting and ending points of each edge are randomly selected,
   * and the weights are randomly generated.
   */
  RandomGraph (int num_vertices, int num_edges);
};