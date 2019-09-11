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

      void reset()
      {
        color = bfs_color::WHITE;
        distance = -1;
        path.clear();
        parent = -1;
        node_number = -1;

        distance = 0;
        path.clear();
        parent = 0;
      }
    };

  public:
    /*
     Return a vector that has the path from source node to
     the destination
     node. This path contains the least
     ammount of EDGES. Edge weight does not
     get taken into
     account in this algorithm.
    */
    static std::vector<int> bfs_shortest_path(graph::Graph &G, int source, int sink);

    void reset_bfs_nodes()
    {

    }
  };

}  // namespace graph