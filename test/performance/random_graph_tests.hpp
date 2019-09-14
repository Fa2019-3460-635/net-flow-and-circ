#include "random_graph.hpp"
#include "gtest/gtest.h"

TEST (RandomGraphTests, ConstructedGraphHasCorrectSize)
{
  int num_vertices = 10;
  int num_edges = 50;
  RandomGraph g (num_vertices, num_edges);

  EXPECT_EQ(num_vertices, g.get_number_of_nodes());
  EXPECT_EQ(num_edges, g.get_number_of_edges());
}
