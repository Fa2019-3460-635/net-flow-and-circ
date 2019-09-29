#pragma once
#include "gtest/gtest.h"

#include "flow_network.hpp"
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

    graph::FlowNetwork G (list);
    int max_flow = graph::FordFulkerson::max_flow(G);

    EXPECT_EQ(max_flow, 28);
}

TEST(FordFulkerson, MaxFlow002)
{
    std::vector<std::vector<graph::Graph::edge>> list = {
        {{1, 25}, {2, 25}},//0
        {{3, 58}},//1
        {{4,5}, {5, 15}},//2
        {{6, 19}, {7, 63}},//3
        {{6,8}},//4
        {{4, 20}, {6, 32}, {8, 16}},//5
        {{9, 70}},//6
        {{9, 30}},//7
        {{9, 25}},//8
        {}//9
    };

    graph::FlowNetwork G (list);
    int max_flow = graph::FordFulkerson::max_flow(G);

    EXPECT_EQ(max_flow, 45);
}

TEST(FordFulkerson, MaxFlow003)
{
    std::vector<std::vector<graph::Graph::edge>> list = {
        {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}, {6, 60}},//0
        {{2, 10}, {7, 60}},//1
        {{3, 20}, {7, 50}},//2
        {{4, 30}, {7, 40}},//3
        {{5, 40}, {7, 30}},//4
        {{6, 50}, {7, 20}},//5
        {{7, 10}},//6
        {}//7
    };

    graph::FlowNetwork G (list);
    int max_flow = graph::FordFulkerson::max_flow(G);

    EXPECT_EQ(max_flow, 120);
}

TEST(FordFulkerson, MaxFlow004)
{
    std::vector<std::vector<graph::Graph::edge>> list = {
        {{1, 100}, {2, 100}},//0
        {{2, 1}, {3, 100}},//1
        {{3, 100}},//2
        {}//3
    };

    graph::FlowNetwork G (list);
    int max_flow = graph::FordFulkerson::max_flow(G);

    EXPECT_EQ(max_flow, 200);
}
