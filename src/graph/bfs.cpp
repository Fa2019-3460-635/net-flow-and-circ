#include "bfs.hpp"

#include <algorithm>
#include <limits>
#include <vector>
#include <queue>

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

std::vector<int> Bfs::bfs_shortest_path(Graph & graph, int source, int sink)
{
  auto adjacency_list = graph.get_adjacency_list();

  // initialize the data structures
  std::vector<bool> discovered (adjacency_list.size(), false);
  std::vector<int> previous_node (adjacency_list.size(), -1);
  std::queue<int> node_queue;
  discovered.at(source) = true;
  node_queue.push(source);

  // conduct the breadth-first search
  while (!node_queue.empty())
  {
    // get next node
    int current = node_queue.front();
    node_queue.pop();

    // stop if sink is found
    if (current == sink)
      break;

    // process neighbors
    for (auto const & edge : adjacency_list.at(current))
      if (!discovered.at(edge.node))
      {
        discovered.at(edge.node) = true;
        previous_node.at(edge.node) = current;
        node_queue.push(edge.node);
      }
  }

  // return empty path if sink was unreachable
  if (!discovered.at(sink))
    return {};

  // otherwise, reconstruct the path
  std::vector<int> path;
  for (int i = sink; i != -1; i = previous_node.at(i))
    path.push_back(i);
  std::reverse(std::begin(path), std::end(path));
  return path;
}

Bfs::bfs_fordfulkerson_data Bfs::bfs_fordfulkerson(FlowNetwork &G, int source, int sink)
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
        int adjacent_capacity = edges[i].weight;

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