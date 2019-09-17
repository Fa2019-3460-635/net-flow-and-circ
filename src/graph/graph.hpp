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

    Graph();

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
    
    void reduce_edge_capacity(int start_node, int end_node, int amount)
    {
      // search through each edge connected to the start node
      for(int i = 0; i < m_adjacency_list[start_node].size(); ++i) {
        // when you find the correct end node
        if(m_adjacency_list[start_node][i].node == end_node) {
          // reduce the capacity
          m_adjacency_list[start_node][i].capacity -= amount;
          // if the capacity is then zero, delete the node
          if(m_adjacency_list[start_node][i].capacity == 0) {
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
      for(int i = 0; i < m_adjacency_list[start_node].size(); ++i) {
        // when you find the correct end node
        if(m_adjacency_list[start_node][i].node == end_node) {
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

    /* The source will have no edges pointing to it*/
    int find_source()
    {
      std::vector<bool> points_to;

      for(int i = 0; i < m_adjacency_list.size(); ++i) {
        points_to.push_back(false); /* Start with nothing being pointed to*/
      }

      for(int x = 0; x < m_adjacency_list.size(); ++x) {
        for(int y = 0; y < m_adjacency_list[x].size(); ++y) {
          points_to[m_adjacency_list[x][y].node] = true;
        }
      }

      for(int i = 0; i < points_to.size(); ++i) {
        if(points_to[i] == false) {
          return i;
        }
      }
      return -1; //fail
    }

    //sink points to nothing
    int find_sink()
    {
      for(int x = 0; x < m_adjacency_list.size(); ++x) {
        if(m_adjacency_list[x].size() == 0) { //if the node has no edges (points to nothing)
          return x;
        }
      }
      return -1; //fail
    }


    // this function finds the sum of the capacity leaving a node
    int total_capacity_out(int node)
    {
      int total_capacity = 0;
      for(int i = 0; i < m_adjacency_list[node].size(); ++i) {
        total_capacity += m_adjacency_list[node][i].capacity;
      }
      return total_capacity;
    }

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
