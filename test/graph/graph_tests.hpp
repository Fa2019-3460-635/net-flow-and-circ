#pragma once
#include "gtest/gtest.h"

#include "graph.hpp"

TEST(Graph, ParseTestFromProjectDefinition)
{
   std::string test_file = R"(1 3 2 6 3 8
2 2
3 1
)";
   std::cout << "[" << test_file << "]" << std::endl;

   auto *G = new graph::Graph();
   std::istringstream file_stream(test_file);
   G->parse(file_stream);

   G->print();

   auto adjacency_list = G->get_adjacency_list();

   EXPECT_EQ(adjacency_list[0][0].node, 1);
   EXPECT_EQ(adjacency_list[0][0].capacity, 3);
   EXPECT_EQ(adjacency_list[0][1].node, 2);
   EXPECT_EQ(adjacency_list[0][1].capacity, 6);
   EXPECT_EQ(adjacency_list[0][2].node, 3);
   EXPECT_EQ(adjacency_list[0][2].capacity, 8);

   EXPECT_EQ(adjacency_list[1][0].node, 2);
   EXPECT_EQ(adjacency_list[1][0].capacity, 2);

   EXPECT_EQ(adjacency_list[2][0].node, 3);
   EXPECT_EQ(adjacency_list[2][0].capacity, 1);

}

TEST(Graph, ParseTestBlankLines)
{
   std::string test_file = R"(1 3 2 6 3 8

2 2
3 1
)";
   std::cout << "[" << test_file << "]" << std::endl;

   auto *G = new graph::Graph();
   std::istringstream file_stream(test_file);
   G->parse(file_stream);

   G->print();

   auto adjacency_list = G->get_adjacency_list();

   EXPECT_EQ(adjacency_list[0][0].node, 1);
   EXPECT_EQ(adjacency_list[0][0].capacity, 3);
   EXPECT_EQ(adjacency_list[0][1].node, 2);
   EXPECT_EQ(adjacency_list[0][1].capacity, 6);
   EXPECT_EQ(adjacency_list[0][2].node, 3);
   EXPECT_EQ(adjacency_list[0][2].capacity, 8);

   EXPECT_EQ(adjacency_list[2][0].node, 2);
   EXPECT_EQ(adjacency_list[2][0].capacity, 2);

   EXPECT_EQ(adjacency_list[3][0].node, 3);
   EXPECT_EQ(adjacency_list[3][0].capacity, 1);

}
