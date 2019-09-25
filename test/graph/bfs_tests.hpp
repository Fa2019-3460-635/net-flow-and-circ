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

/**
 * Verify that BFS returns empty path vector if there is no path.
 */
TEST (Bfs, ShortestPathTest002)
{
    std::istringstream input (
        "1 10 2 20\n"
        "\n"
        "\n"
        "2 10"
    );
    graph::Graph g;
    g.parse(input);

    auto shortest_path = graph::Bfs::bfs_shortest_path(g, 0, 3);
    EXPECT_EQ(0, shortest_path.size());
}

/**
 * Verify that shortest path has correct size.
 */
TEST (Bfs, ShortestPathTest003)
{
    std::istringstream input (
        "1 4 2 2\n"
        "2 3 3 2 4 3\n"
        "1 1 3 4 4 5\n"
        "\n"
        "3 1"
    );
    graph::Graph g;
    g.parse(input);

    auto shortest_path = graph::Bfs::bfs_shortest_path(g, 0, 4);
    EXPECT_EQ(3, shortest_path.size());
}

/**
 * Verify that correct shortest path is returned.
 */
TEST (Bfs, ShortestPathTest004)
{
    std::istringstream input (
        "\n"
        "2 40 3 8 4 10\n"
        "5 6 7 10\n"
        "2 4 4 12 6 2\n"
        "6 1\n"
        "3 2 6 2 7 4\n"
        "8 4 9 3\n"
        "8 20 10 1\n"
        "5 0 10 20\n"
        "4 6 8 10 10 2\n"
        ""
    );
    graph::Graph g;
    g.parse(input);   

    auto shortest_path = graph::Bfs::bfs_shortest_path(g, 1, 5);
    std::vector<int> expected {1, 2, 5};
    EXPECT_EQ(expected, shortest_path);
}