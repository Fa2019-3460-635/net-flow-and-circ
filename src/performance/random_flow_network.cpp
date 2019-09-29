#include "random_flow_network.hpp"
#include "random.hpp"

#include <algorithm>

using adj_list = std::vector<std::vector<graph::Graph::edge>>;

namespace {

  int const MAX_WEIGHT = 1000;

  /**
   * @brief Helper function for determining whether or there is a directed edge
   *        connecting the two given nodes.
   * 
   * @param n1 starting node
   * @param n2 ending node
   * 
   * @return Returns true iff only the given adjacency list contains the given
   *         directed edge.
   */
  bool edge_exists (adj_list const & l, int n1, int n2)
  {
    // filter out node keys that are out of range
    if (n1 < 0 || n2 < 0 || n1 >= l.size() || n2 >= l.size())
      return false;

    for (auto const & edge : l.at(n1))
      if (edge.node == n2)
        return true;
    return false;
  }

} // unnamed namespace

graph::FlowNetwork
RandomFlowNetwork::get_random_flow_network (int v, int e)
{
  adj_list graph (v - 2);

  // generate edges with random starting points, ending points, and weights
  int num_edges = e - 2;
  for (int i = 0; i < num_edges; ++i)
  {
    // add a random edge
    while (true)
    {
      int n1 = Random::nonneg_int(0, graph.size() - 1);
      int n2 = Random::nonneg_int(0, graph.size() - 1);
      if (edge_exists(graph, n1, n2) || edge_exists(graph, n2, n1) || n1 == n2)
        continue;

      // create edge from n1 to n2, with random weight
      graph::Graph::edge edge;
      edge.weight = Random::nonneg_int(0, MAX_WEIGHT);
      edge.node = n2;
      graph.at(n1).push_back(edge);
      break;
    }
  }

  // add guaranteed source
  graph::Graph::edge edge_from_source;
  edge_from_source.weight = Random::nonneg_int(0, MAX_WEIGHT);
  edge_from_source.node = Random::nonneg_int(0, graph.size() - 1);
  graph.push_back({edge_from_source});

  // add guaranteed sink
  graph::Graph::edge edge_to_sink;
  edge_to_sink.weight = Random::nonneg_int(0, MAX_WEIGHT);
  edge_to_sink.node = Random::nonneg_int(0, graph.size());
  graph.at(Random::nonneg_int(0, graph.size() - 1)).push_back(edge_to_sink);
  graph.push_back({});

  return graph::FlowNetwork::transform_to_single_source_sink(graph::FlowNetwork(graph));
}

graph::FlowNetwork
RandomFlowNetwork::get_procedurally_generated_connected_graph (int v)
{
  // construct adjacency list with given number of vertices
  adj_list graph (v);

  // add edges to the graph
  for (int i = 0; i < graph.size(); ++i)
  {
    for (int j = 0; j < graph.size(); ++j)
    {
      // skip edge if starting node is also ending node
      if (i == j)
        continue;

      // skip edge if an anti-parallel edge already exists
      if (edge_exists(graph, j, i))
        continue;

      // add an edge from i to j with a random weight
      graph::Graph::edge edge;
      edge.node = j;
      edge.weight = Random::nonneg_int(0, MAX_WEIGHT);
      graph.at(i).push_back(edge);
    }
  }

  return {graph};
}
