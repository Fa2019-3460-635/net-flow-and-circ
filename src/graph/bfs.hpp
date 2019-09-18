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

      /**
       * @brief Reset all the members of the bfs_node struct
       * to defaults
       */
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

    /**
     * @brief give the shortest path and minimum capacity
     *
     * @param G: The graph in question
     * @param source: the start node
     * @param sink: the destination node
     * @return A struct with the shortest path from source to sink represented as a std::vector<int>
     * and the minimum capacity.
     */
    static bfs_fordfulkerson_data bfs_fordfulkerson(graph::Graph &G, int source, int sink);

  };

}  // namespace graph
