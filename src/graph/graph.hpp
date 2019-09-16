#pragma once

#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iostream>

#include "edge.hpp"

namespace graph {

  class Graph {

  public:
    struct edge {
      int node;
      int capacity;
    };

  private:
    std::vector<std::vector<edge>> m_adjacency_list;

  public:

    Graph();

    Graph(const std::vector<std::vector<edge>>& adjacency_list);
    /**
     * @brief parse() takes in a file stream, whose contents
     * should reflect the construction of a weighted
     * directed graph and instantiates the members of the graph.
     *
     * There is one line in the stream for
     * each node in the graph. The naming conventions
     * starts with the first line being node 0. Lines may be blank.
     * On each line there should be an even number of integers.
     * The first integer represents which node is being
     * connected to, the second ineger is the capacity of the edge.
     *
     * This functions returns true if it has successfully
     * parsed the data into 'adjacency_list', and false
     * if it has encountered something unexpected.
     *
     * @param input_data
     * @return true if the parse was successful, false otherwise.
     */
    bool parse(std::istream &input_data);


    /**
     * @brief Print a plain-text version of the contents of
     * the graph directly to std::cout.
     */
    void print() const;

    void reduce_edge_capacity(int start_node,int end_node, int amount)
    {
        // search through each edge connected to the start node
        for(int i =0; i < m_adjacency_list[start_node].size();++i)
        {
            // when you find the correct end node
            if(m_adjacency_list[start_node][i].node == end_node)
            {
                // reduce the capacity
                m_adjacency_list[start_node][i].capacity -= amount;
                // if the capacity is then zero, delete the node
                if(m_adjacency_list[start_node][i].capacity == 0)
                {
                    m_adjacency_list[start_node][i] = m_adjacency_list[start_node].back();
                    m_adjacency_list[start_node].pop_back();
                }
                return;
            }
        }
    }

    void increase_edge_capacity(int start_node, int end_node, int amount)
    {
        // search through each edge connected to the start node
        for(int i =0; i < m_adjacency_list[start_node].size();++i)
        {
            // when you find the correct end node
            if(m_adjacency_list[start_node][i].node == end_node)
            {
                // increase the capacity
                m_adjacency_list[start_node][i].capacity += amount;
                return;
            }
        }

        // if the edge was not in the graph, create it and add it
        edge new_edge;
        new_edge.node = end_node;
        new_edge.capacity = amount;
        m_adjacency_list[start_node].push_back(new_edge);
        return;
    }


    unsigned long get_number_of_nodes();

    std::vector<std::vector<edge>> get_adjacency_list() const;
  };
}  // namespace graph
