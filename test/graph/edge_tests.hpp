#include "gtest/gtest.h"

#include "edge.hpp"
#include "node.hpp"

TEST (EdgeTests, CanConstructAnEdge)
{
  graph::Edge<int, double> edge (1, 2, 10);
}

TEST (EdgeTests, GetWeightReturnsCorrectValue)
{
  graph::Edge<int, double> edge (1, 2, 10);
  EXPECT_EQ(10, edge.get_weight());
}

TEST (EdgeTests, GetNodeOne)
{
  graph::Edge<int, double> edge (1, 2, 10);
  EXPECT_EQ(1, edge.get_node_one());
}

TEST (EdgeTests, GetNodeTwo)
{
  graph::Edge<int, double> edge (1, 2, 10);
  EXPECT_EQ(2, edge.get_node_two());
}
