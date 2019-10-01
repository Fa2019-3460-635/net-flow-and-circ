#pragma once

#include "gtest/gtest.h"

#include "bfs.hpp"
#include "flow_network.hpp"
#include "fordfulkerson.hpp"
#include "graph.hpp"
#include "random.hpp"

bool edge_exists (std::vector<std::vector<graph::Graph::edge>> const & l, int n1, int n2)
{
  // filter out node keys that are out of range
  if (n1 < 0 || n2 < 0 || n1 >= l.size() || n2 >= l.size())
    return false;

  for (auto const & edge : l.at(n1))
    if (edge.node == n2)
      return true;
  return false;
}

std::vector<std::vector<graph::Graph::edge>>
generate_flow_network (int minimum_capacity)
{
  int v = Random::nonneg_int(2, 100);

  // construct adjacency list with given number of vertices
 std::vector<std::vector<graph::Graph::edge>> graph (v);

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
      edge.weight = Random::nonneg_int(minimum_capacity, 1000);
      graph.at(i).push_back(edge);
    }
  }

  return graph;
}

std::vector<std::vector<graph::Graph::edge>>
merge_flow_networks (
  std::vector<std::vector<graph::Graph::edge>> const & fn1,
  std::vector<std::vector<graph::Graph::edge>> const & fn2
  )
{
  std::vector<std::vector<graph::Graph::edge>> merged (fn1);
  for (auto const & node : fn2)
  {
    std::vector<graph::Graph::edge> edges;
    for (auto const & edge : node)
    {
      graph::Graph::edge new_edge;
      new_edge.node = edge.node + fn1.size();
      new_edge.weight = edge.weight;
      edges.push_back(new_edge);
    }
    merged.push_back(edges);
  }
  return merged;
}

TEST(FordFulkersonGeneratedTests, GeneratedTests)
{
  int const BOTTLENECK_CAPACITY = 100;
  int const NUM_GENERATED_TESTS = 1000;

  for (int i = 0; i < NUM_GENERATED_TESTS; ++i)
  {
    // merge two disconnected graphs
    auto fn1 = generate_flow_network(BOTTLENECK_CAPACITY + 1);
    auto fn2 = generate_flow_network(BOTTLENECK_CAPACITY + 1);
    auto adjacency_list = merge_flow_networks(fn1, fn2);

    // add a "bottleneck" edge connecting the two sub-graphs
    int starting = graph::FlowNetwork(fn1).find_sink();
    graph::Graph::edge bottleneck;
    bottleneck.node = fn1.size();
    bottleneck.weight = Random::nonneg_int(0, BOTTLENECK_CAPACITY);
    adjacency_list.at(starting).push_back(bottleneck);

    // run Ford Fulkerson to find the maximum flow
    graph::FlowNetwork flow_network = graph::FlowNetwork::transform_to_single_source_sink(graph::FlowNetwork(adjacency_list));

    int max_flow = graph::FordFulkerson::max_flow(flow_network);

    EXPECT_EQ(bottleneck.weight, max_flow);
    std::cout << "Success. Generated test case for Ford Fulkerson. " << i << " / " << NUM_GENERATED_TESTS << '\n';
  }

  std::cout << "Executed " << NUM_GENERATED_TESTS << " randomly generated Ford Folkerson tests.\n";
}