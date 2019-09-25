#include "fordfulkerson.hpp"
#include "bfs.hpp"

#include <limits>

namespace graph {

std::pair<std::vector<int>, int>
get_path (FlowNetwork & G, int source, int sink)
{
  // get the path
  std::vector<int> path = Bfs::bfs_shortest_path(G, source, sink);

  // return infinite capacity if there is no path
  int minimum_capacity = std::numeric_limits<int>::max();
  if (path.empty())
    return {path, minimum_capacity};

  // get the minimum capacity of the path
  Graph::AdjacencyList & adj_list = G.get_adjacency_list();
  for (std::size_t i = 0; i < path.size() - 1; ++i)
  {
    int node = path.at(i);
    for (auto const & edge : adj_list.at(node))
      if (edge.node == path.at(i + 1))
        if (minimum_capacity > edge.weight)
          minimum_capacity = edge.weight;
  }

  return {path, minimum_capacity};
}

int FordFulkerson::max_flow (FlowNetwork & G)
{
  int source = G.find_source();
  int sink = G.find_sink();

  while (true)
  {
    // obtain the shortest path as well as the flow along that path
    auto ff_data = get_path(G, source, sink);
    auto path = ff_data.first;
    auto minimum_capacity = ff_data.second;

    // stop iterating if there is no path
    if (path.empty())
      break;

    // decrease forward capacities
    for(int i = 0; i < path.size() - 1; ++i)
      G.reduce_edge_capacity(path.at(i), path.at(i + 1), minimum_capacity);

    // increase backward capacities
    for(int i = path.size() - 1; i > 0; --i)
      G.increase_edge_capacity(path.at(i), path.at(i - 1), minimum_capacity);
  }

  // total flow equals the outward capacity of the sink
  return G.total_capacity_out(sink);
}

} // namespace graph