#pragma once

#include <gtest/gtest.h>
#include <sstream>

#include "circulationgraph.hpp"

TEST(CirculationGraphs, MustParseStreamCorrectly)
{
    std::string text = R"(-7 1 10 2 3
-8 2 6
10
)";
    std::stringstream text_stream(text);

    graph::CirculationGraph circulation_graph;

    circulation_graph.parse(text_stream);

    auto adjacency_list = circulation_graph.get_adjacency_list();

    ASSERT_EQ(adjacency_list.size(), 5);

    EXPECT_EQ(adjacency_list[0][0].node, 2);
    EXPECT_EQ(adjacency_list[0][0].weight, 7);
    EXPECT_EQ(adjacency_list[0][1].node, 3);
    EXPECT_EQ(adjacency_list[0][1].weight, 8);

    EXPECT_EQ(adjacency_list[1].size(), 0);

    EXPECT_EQ(adjacency_list[2][0].node, 3);
    EXPECT_EQ(adjacency_list[2][0].weight, 10);
    EXPECT_EQ(adjacency_list[2][1].node, 4);
    EXPECT_EQ(adjacency_list[2][1].weight, 3);

    EXPECT_EQ(adjacency_list[3][0].node, 4);
    EXPECT_EQ(adjacency_list[3][0].weight, 6);

    EXPECT_EQ(adjacency_list[4][0].node, 1);
    EXPECT_EQ(adjacency_list[4][0].weight, 10);

}
