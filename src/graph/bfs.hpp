#pragma once

#include <vector>
#include <queue>

#include "edge.hpp"
#include "graph.hpp"

namespace graph {

  class Bfs {
  public:

    struct bfs_node {
      enum bfs_color { WHITE, GRAY, BLACK };

      bfs_color color;
      int distance;
      std::vector<int> path;
      int parent;
      int node_number;
      int minimum_capacity;

      void reset();
    };

    struct bfs_fordfulkerson_data
    {
      std::vector<int> path;
      int minimum_capacity;
    };

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
    static bfs_fordfulkerson_data bfs_fordfulkerson(graph::Graph &G, int source, int sink);

    void reset_bfs_nodes();
  };

}  // namespace graph
