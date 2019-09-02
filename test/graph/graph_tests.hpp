#pragma once

#include "graph.hpp"

TEST (GraphTests, CanInstantiateAGraph)
{
  graph::Graph<int, double> graph;
}

TEST (GraphTests, EmptyGraphDoesNotContainGivenNode)
{
  graph::Graph<int, double> graph;
  EXPECT_FALSE(graph.contains(1));
}

TEST (GraphTests, AddNodeWorks)
{
  graph::Graph<int, double> graph;
  graph.add_node(1);
  EXPECT_EQ(1, graph.get_num_nodes());
  EXPECT_TRUE(graph.contains(1));
}

TEST (GraphTests, AddEdgeWorks)
{
  graph::Graph<int, double> graph;
  graph.add_edge(1, 2, 10);
  graph.add_edge(1, 3, 20);
  EXPECT_EQ(3, graph.get_num_nodes());
  EXPECT_EQ(2, graph.get_num_edges());
}

TEST (GraphTests, GetEdgesWorks)
{
  graph::Graph<int, double> graph;

  graph.add_edge(1, 2, 10);
  graph.add_edge(1, 3, 20);
  graph.add_edge(2, 3, 30);

  auto edges = graph.get_edges(1);

  EXPECT_EQ(2, edges.size());
  
  for (auto const & edge : edges)
  {
    EXPECT_EQ(1, edge.get_node_one());
    EXPECT_NE(1, edge.get_node_two());
  }
}
