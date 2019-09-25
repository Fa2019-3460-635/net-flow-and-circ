#include "bfs.hpp"

#include <algorithm>
#include <limits>
#include <vector>
#include <queue>

namespace graph {

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

} // namespace graph