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


    unsigned long get_number_of_nodes();

    std::vector<std::vector<edge>> get_adjacency_list() const;
  };
}  // namespace graph
