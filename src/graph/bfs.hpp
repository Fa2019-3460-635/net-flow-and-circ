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

      void reset()
      {
        color = bfs_color::WHITE;
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
    std::vector<Graph::edge> bfs_shortest_path(Graph G, int source, int sink)
    {
      std::vector<Graph::edge> shortest_path;

      std::vector<bfs_node> bfs_nodes;
      int number_of_nodes = G.get_number_of_nodes();

      for(int i =0; i < number_of_nodes;++i)
      {
        bfs_node new_bfs_node;
        new_bfs_node.reset();
        bfs_nodes.push_back(new_bfs_node);
      }

      bfs_nodes[source].color = bfs_node::bfs_color::GRAY;
      bfs_nodes[source].distance = 0;
      bfs_nodes[source].parent = -1;

      std::queue<bfs_node*> node_queue;
      node_queue.push(&bfs_nodes[source]);


      return shortest_path;
    }

    void reset_bfs_nodes()
    {
      
    }
  };

}  // namespace graph