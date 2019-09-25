#pragma once

#include "graph.hpp"

namespace graph {

class FlowNetwork : public Graph
{
//==============================================================================
// Nested Types
//==============================================================================
public:

  struct flow_edge
  {
    int flow = 0;
  };

//==============================================================================
// Constructors
//==============================================================================
public:

    /**
     * @brief Default constructor for FlowNetwork
     */
    FlowNetwork ()
    : Graph() {}

    /**
     * @brief Constructor for FlowNetwork
     *
     * @param adjacency_list: a pre-build adjacency list
     */
    FlowNetwork (std::vector<std::vector<Graph::edge>> const & adj_list)
    : Graph(adj_list) {}

//==============================================================================
// Static Utility Methods
//==============================================================================
public:

    /**
     * @brief Get redidual graph by 
     * @brief Get the residual graph based on the original graph, the augmenting path, and
     *        the increased flow along the path

     * @param G: graph to augment
     * @param p: augmenting path
     * @param f: flow along augmenting path

     * @return Gf, the residual graph.
     */
    static Graph get_residual_graph(const Graph& G, std::vector<int> p, int f);

//==============================================================================
// Public Methods
//==============================================================================
public:

    /**
     * @brief This function finds the sum of the capacity leaving a node
     *
     * @param node: the node in question
     */
    int total_capacity_out (int node);

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
     * @brief get_capacity_of_path
     * @param path: The path to traverse
     * @return the capacity of the given path
     */
    int get_capacity_of_path(std::vector<int> path);

    /**
     * @brief Reduce the capacity of the edge between the given nodes
     * 
     * @param start_node
     * @param end_node
     * @param amount: The amount by which to reduce the capacity of the edge.
     */
    void reduce_edge_capacity (int start_node, int end_node, int amount);
    
    /**
     * @brief Increases the capacity of the edge between the given nodes
     * 
     * @param start_node
     * @param end_node
     * @param amount: The amount by which to increase the capacity of the edge.
     */
    void increase_edge_capacity (int start_node, int end_node, int amount);

    /**
     * @brief Transform the given graph which potentially has multiple sources/sinks to 
     * one that has a single source/sink.
     *
     * @param G: The graph to transform
     * @return A new graph that has one source and one sink
     */
    static FlowNetwork transform_to_single_source_sink (const FlowNetwork & G);

    /**
     * @brief Find the sources for this graph
     * @return a list of source-node indicies.
     */
    std::vector<int> get_sources ();

    /**
     * @brief Find the sinks for this graph
     * @return a list of sink-node indicies.
     */
    std::vector<int> get_sinks ();

//==============================================================================
// Private Attributes
//==============================================================================
private:

    std::vector<int> m_sources;
    std::vector<int> m_sinks;

};

} // namespace graph