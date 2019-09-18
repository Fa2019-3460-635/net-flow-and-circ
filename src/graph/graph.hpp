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
      int flow = 0;
    };

  private:
    std::vector<std::vector<edge>> m_adjacency_list;

  public:

    /**
     * @brief Default Constructor
     */
    Graph();

    /**
     * @brief Constructor for Graph
     *
     * @param adjacency_list: a pre-build adjacency list
     */
    Graph(const std::vector<std::vector<edge>> &adjacency_list);

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
    
    /**
     * @brief Reduce the capacity of the edge between the given nodes
     * 
     * @param start_node
     * @param end_node
     * @param amount: The amount by which to reduce the capacity of the edge.
     */
    void reduce_edge_capacity(int start_node, int end_node, int amount);
    
    /**
     * @brief Increases the capacity of the edge between the given nodes
     * 
     * @param start_node
     * @param end_node
     * @param amount: The amount by which to increase the capacity of the edge.
     */
    void increase_edge_capacity(int start_node, int end_node, int amount);

    /**
     * @brief The source will have no edges pointing to it
     * 
     * This method assumes that the graph contains a single source
     */
    int find_source();
    

    /**
     * @brief The sink points to nothing
     * 
     * This method assumes that the graph contains a single sink
     */
    int find_sink();

    /**
     * @brief This function finds the sum of the capacity leaving a node
     *
     * @param node: the node in question
     */
    int total_capacity_out(int node);
    
    unsigned long get_number_of_nodes();

    std::vector<std::vector<edge>> get_adjacency_list() const;

    /**
     * @brief Find the sources for this graph
     * @return a list of source-node indicies.
     */
    std::vector<int> get_sources();

    /**
     * @brief Find the sinks for this graph
     * @return a list of sink-node indicies.
     */
    std::vector<int> get_sinks();

    /**
     * @brief get_capacity_of_path
     * @param path: The path to traverse
     * @return the capacity of the given path
     */
    int get_capacity_of_path(std::vector<int> path);

    /**
     * @brief Transform the given graph which potentially has multiple sources/sinks to 
     * one that has a single source/sink.
     *
     * @param G: The graph to transform
     * @return A new graph that has one source and one sink
     */
    static Graph transform_to_single_source_sink(const graph::Graph& G);

    /**
     * @brief Get the residual graph based on the original graph, the augmenting path, and
     * the increased flow along the path
     * @param G: The graph to augment
     * @param p: the augmenting path
     * @param f: the flow along the augmenting path
     * @return Gf, the residual graph.
     */
    static Graph get_residual_graph(const Graph& G, std::vector<int> p, int f);

  private:
    std::vector<int> m_sources;
    std::vector<int> m_sinks;
  };
}  // namespace graph
