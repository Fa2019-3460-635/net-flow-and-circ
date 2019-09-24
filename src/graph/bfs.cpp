#include "bfs.hpp"

#include <limits>

namespace graph {

/**
 * A data structure for holding intermediate data for the Breadth-First Search.
 */
struct bfs_node
{
  bfs_node ()
  : bfs_node(0)
  {}

  bfs_node (int node_number)
  : discovered(false),
    node_number(node_number),
    minimum_capacity(0)
  {}

  bool discovered;
  std::vector<int> path;
  int node_number;
  int minimum_capacity;

  /**
   * @brief Reset all the members of the bfs_node struct
   *        to defaults
   */
  void reset()
  {
    discovered = false;
    node_number = -1;
    path.clear();
  }
};


std::vector<int> Bfs::bfs_shortest_path(Graph &G, int source, int sink)
{
  auto adjacency_list = G.get_adjacency_list();

  // create an adjacency list of "bfs_node" instances
  std::vector<bfs_node> bfs_nodes;
  for (int i = 0; i < adjacency_list.size(); ++i)
    bfs_nodes.emplace_back(i);

  // create a queue of discovered nodes, and initialize with the source node
  std::queue<bfs_node *> node_queue;
  node_queue.push(&bfs_nodes[source]);

  while(!node_queue.empty())
  {
    // get current node
    bfs_node *current_node = node_queue.front();
    node_queue.pop();
    int node_num = current_node->node_number;
    auto & edges = adjacency_list[node_num];

    // iterate through edges connected to current node
    for (auto & edge : edges)
    {
      auto & dest = bfs_nodes[edge.node];
      if (!dest.discovered)
      {
        dest.discovered = true;
        dest.path = current_node->path;
        dest.path.push_back(node_num);
        if (dest.node_number == sink)
        {
          dest.path.push_back(dest.node_number);
          return dest.path;
        }
        node_queue.push(&dest);
      }

    }

  }
  std::vector<int> empty_vector;
  return empty_vector;
}

Bfs::bfs_fordfulkerson_data Bfs::bfs_fordfulkerson(Graph &G, int source, int sink)
{
  Bfs::bfs_fordfulkerson_data fordfolkerson_data;
  int minimum_capacity;

  auto adjacency_list = G.get_adjacency_list();

  // create an adjacency list of "bfs_node" instances
  std::vector<bfs_node> bfs_nodes;
  for (int i = 0; i < adjacency_list.size(); ++i)
    bfs_nodes.emplace_back(i);

  // initialize the "source" node
  bfs_nodes[source].minimum_capacity = std::numeric_limits<int>::max(); // simulates infinity

  // create a queue of discovered nodes, and initialize with the source node
  std::queue<bfs_node *> node_queue;
  node_queue.push(&bfs_nodes[source]);

  while (!node_queue.empty())
  {
    bfs_node *current_node = node_queue.front();
    node_queue.pop();

    auto & edges = adjacency_list[current_node->node_number];

    // for each node adjacent to current node
    for(int i = 0; i < edges.size(); ++i)
    { 
      // if the adjacent node hasn't been visited yet
      bfs_node & adjacent_node = bfs_nodes[edges[i].node];
      if(!adjacent_node.discovered)
      {
        adjacent_node.discovered = true;
        adjacent_node.path = current_node->path;
        adjacent_node.path.push_back(current_node->node_number);
        adjacent_node.minimum_capacity = current_node->minimum_capacity;
        int adjacent_capacity = edges[i].capacity;

        if(adjacent_capacity < adjacent_node.minimum_capacity) {/* Check if new capacity is less than old capacity*/
          adjacent_node.minimum_capacity = adjacent_capacity;
        }

        if(adjacent_node.node_number == sink) {
          adjacent_node.path.push_back(adjacent_node.node_number);
          fordfolkerson_data.path = adjacent_node.path;
          fordfolkerson_data.minimum_capacity = adjacent_node.minimum_capacity;
          return fordfolkerson_data;
        }
        node_queue.push(&adjacent_node);
      }
    }

  }
  std::vector<int> empty_vector;
  fordfolkerson_data.path = empty_vector;
  return fordfolkerson_data;
}

} // namespace graph