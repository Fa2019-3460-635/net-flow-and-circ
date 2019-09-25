#pragma once

#include <vector>

#include "flow_network.hpp"

namespace graph {

  class Bfs
  {
  public:

    /**
     * @brief Finds the shortest path from source to sink.
     *
     * The shortest path is determined by the number of edges
     * not by weight.
     *
     * @param G: the graph in question
     * @param source: The start node
     * @param sink: The destination node
     * @return A vector with the shortest path between source and sink,
     * an empty vector, otherwise.
     */
    static std::vector<int> bfs_shortest_path(graph::Graph &G, int source, int sink);

  };

}  // namespace graph
