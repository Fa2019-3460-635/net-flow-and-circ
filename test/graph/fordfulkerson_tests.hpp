#pragma once
#include "gtest/gtest.h"

#include "graph.hpp"
#include "bfs.hpp"
#include "fordfulkerson.hpp"

TEST(FordFulkerson, MaxFlow001)
{
    std::vector<std::vector<graph::Graph::edge>> list = {
        {{1,10}, {2,5}, {3,15}},//0
        {{4,9}, {5,15}, {2,4}},//1
        {{5,8}, {3,4}},//2
        {{6,30}},//3
        {{5,4}, {7,10}},//4
        {{6,4}, {7,10}},//5
        {{2,6}, {7,10}},//6
        {}//7
    };

    auto G = graph::Graph(list);
    int max_flow = graph::FordFulkerson::max_flow(G);

    EXPECT_EQ(max_flow, 28);
}


