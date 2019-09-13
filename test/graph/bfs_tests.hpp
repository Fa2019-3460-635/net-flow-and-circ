#pragma once

#include "gtest/gtest.h"

#include "bfs.hpp"
#include "graph.hpp"

TEST(Bfs, ShortestPathTest001)
{
    std::vector<std::vector<graph::Graph::edge>> list = {
        {{1, 10}, {2, 10}}, //node 0
        {{2, 10}, {2, 10}}, //node 1
        {{3, 20}, {4, 15}}, //node 2
        {{4, 2}},           //node 3
        {{5, 12}},          //node 4
        {{-1, -1}}          //node 5
    };

    auto G = graph::Graph(list);
    auto shortest_path = graph::Bfs::bfs_shortest_path(G, 0, 5);

    for (const auto & node: shortest_path)
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    EXPECT_EQ(shortest_path.size(), 4);
    EXPECT_EQ(shortest_path[0], 0);
    EXPECT_EQ(shortest_path[1], 2);
    EXPECT_EQ(shortest_path[2], 4);
    EXPECT_EQ(shortest_path[3], 5);

}
