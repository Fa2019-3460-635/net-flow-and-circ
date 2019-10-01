#pragma once

#include "gtest/gtest.h"

#include "bfs.hpp"
#include "graph.hpp"
#include "random.hpp"

#include <tuple>

std::tuple<int, int, std::vector<std::vector<graph::Graph::edge>>>
get_random_bfs_test_graph ()
{
  // generate random number of nodes along the path
  int num_nodes = Random::nonneg_int(2, 1000);
  std::vector<std::vector<graph::Graph::edge>> adjacency_list (num_nodes);

  // length of path is 1 less than the number of nodes along the path
  int path_length = num_nodes - 1;

  // add the edges making up the path
  for (int i = 1; i < num_nodes; ++i)
  {
    graph::Graph::edge edge;
    edge.node = i;
    edge.weight = Random::nonneg_int(0, 1000);
    adjacency_list.at(i - 1).push_back(edge);
  }

  // add a random number of nodes
  int num_extra_nodes = Random::nonneg_int(0, 1000);
  for (int i = 0; i < num_extra_nodes; ++i)
    adjacency_list.push_back({});

  // create a random number of random edges with the only requirement
  // being that none of them shall point to a node in the original
  // path
  int num_edges = Random::nonneg_int(0, num_extra_nodes);
  for (int i = 0; i < num_edges; ++i)
  {
    int starting_node = Random::nonneg_int(0, adjacency_list.size() - 1);

    graph::Graph::edge edge;
    edge.node = Random::nonneg_int(num_nodes, adjacency_list.size() - 1);
    edge.weight = Random::nonneg_int(0, 1000);

    adjacency_list.at(starting_node).push_back(edge);
  }

  return std::make_tuple(0, num_nodes - 1, adjacency_list);
}

TEST(BFS_Generated_Tests, GeneratedTests)
{
  int const NUM_RANDOM_BFS_TESTS = 1000;
  for (int i = 0; i < NUM_RANDOM_BFS_TESTS; ++i)
  {
    // generate a random graph
    auto test_case = get_random_bfs_test_graph();
    graph::Graph graph (std::get<2>(test_case));

    // run BFS
    auto path = graph::Bfs::bfs_shortest_path(graph, std::get<0>(test_case), std::get<1>(test_case));

    int path_length = std::get<1>(test_case) + 1;
    EXPECT_EQ(path_length, path.size());
    std::cout << "Success. Generated test case for BFS. " << i << " / " << NUM_RANDOM_BFS_TESTS << '\n';
  }

  std::cout << "Executed " << NUM_RANDOM_BFS_TESTS << " randomly generated BFS tests.\n";
}