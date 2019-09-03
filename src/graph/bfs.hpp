#pragma once

#include <list>
#include <map>
#include <vector>

#include "edge.hpp"
#include "graph.hpp"

namespace graph {

template <typename Key_t, typename Weight_t>
class Bfs {
  struct bfs_node {
    enum bfs_color { WHITE, GRAY, BLACK };

    reset() {
      bfs_color = bfs_color::WHITE;
      distance = 0;
      path.clear();
      parent = nullptr;
    }

    bfs_color node_color;
    int distance;
    std::vector<int> path;
    Key_t parent;
  };

 public:
  using edge_type = Edge<Key_t, Weight_t>;
  std::vector<bfs_node> bfs_node_vector;

 private:
  /*
   Return a vector that has the path from source node to
   the destination
   node. This path contains the least 
   ammount of EDGES. Edge weight does not
   get taken into
   account in this algorithm.
  */
  std::vector<Key_t> bfs_shortest_path(graph::Graph<Key_t, Weight_t> graph,
                                       Key_t source, Key_t destination) {
    std::map<Key_t, bfs_node> nodes;
    std::map<Key_t, std::list<edge_type>> adjacency_list =
        graph.get_adjavency_list();

    // iterate through adjacency list and add nodes
    for (std::map<Key_t, std::list<edge_type>>::iterator iter =
             adjacency_list.begin();
         iter != adjacency_list.end(); ++iter) {
      nodes[iter->first];
      nodes.at(iter->first).reset();
    }

    return shortest_path;
  }

  void reset_bfs_nodes() {
    for (auto iter = bfs_node_vector.begin(); iter != bfs_node_vector.end();
         ++iter) {
      iter->node_color = bfs_node::bfs_color::WHITE;
      iter->distance = 0;
      iter->parent = nullptr;
      iter->path.clear();
    }
  }
};

}  // namespace graph