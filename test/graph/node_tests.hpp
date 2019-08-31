#include "gtest/gtest.h"

#include "node.hpp"

TEST (NodeTests, CanConstructNode)
{
	graph::Node<int> node(5);
}

TEST (NodeTests, GetKeyReturnsNodesKey)
{
	graph::Node<double> node (2.5);
  EXPECT_EQ(2.5, node.get_key());
}
